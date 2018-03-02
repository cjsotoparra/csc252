.text

.globl	main
main:
	# initialize all of the sX registers (and $fp) to nine constants, which
	# are different for every testcase.
	la	$fp, x_JUNK_VALUES
	lw	$s0,  0($fp)
	lw	$s1,  4($fp)
	lw	$s2,  8($fp)
	lw	$s3, 12($fp)
	lw	$s4, 16($fp)
	lw	$s5, 20($fp)
	lw	$s6, 24($fp)
	lw	$s7, 28($fp)
	lw	$fp, 32($fp)
	
	# record the stack pointer, so we can confirm it later.
.data
main_STACK_SAVE_PTR:
	.word	0
.text
	la	$t0, main_STACK_SAVE_PTR
	sw	$sp, 0($t0)			# STACK_SAVE_PTR = stack position
	add	$t0, $zero, $zero		# don't leak information (at least, if it's easy to discard)
	
	
	# --------------------- BEGIN REAL TESTCASE HERE ---------------------

	addiu	$sp, $sp, -8
	sw	$s0, 0($sp)
	sw	$s1, 4($sp)

	la	$s0, STR_x			# s0 = STR

	la	$s1, AFTER_STR_x		# s1 = STR+strlen(STR)+1
	sub	$s1, $s1, $s0			# s1 = strlen(STR)+1
	addi	$s1, $s1, -1

main__LOOP:
	slt	$t0, $s1, $zero
	bne	$t0, $zero, main__LOOP_END

	# printWithLen(STR, s1)
	add	$a0, $s0, $zero
	add	$a1, $s1, $zero
	jal	printWithLen

	addi	$v0, $zero, 11
	addi	$a0, $zero, 0xa
	syscall

	addi	$s1, $s1, -1
	j	main__LOOP

main__LOOP_END:

	lw	$s0, 0($sp)
	lw	$s1, 4($sp)
	addiu	$sp, $sp, 8

	# --------------------- CHECK REGISTER CONTENTS ----------------------
	la	$t0, main_STACK_SAVE_PTR
	lw	$t0, 0($t0)
	bne	$t0, $sp, main_REPORT_ERROR

	la	$t0, x_JUNK_VALUES

	lw	$t1,  0($t0)
	bne	$t1, $s0, main_REPORT_ERROR
	lw	$t1,  4($t0)
	bne	$t1, $s1, main_REPORT_ERROR
	lw	$t1,  8($t0)
	bne	$t1, $s2, main_REPORT_ERROR
	lw	$t1, 12($t0)
	bne	$t1, $s3, main_REPORT_ERROR
	lw	$t1, 16($t0)
	bne	$t1, $s4, main_REPORT_ERROR
	lw	$t1, 20($t0)
	bne	$t1, $s5, main_REPORT_ERROR
	lw	$t1, 24($t0)
	bne	$t1, $s6, main_REPORT_ERROR
	lw	$t1, 28($t0)
	bne	$t1, $s7, main_REPORT_ERROR
	lw	$t1, 32($t0)
	bne	$t1, $fp, main_REPORT_ERROR

	j	DONE

main_REPORT_ERROR:
.data
main_ERRMSG:	.ascii	"ERROR: A register was not properly saved!\n"
		.ascii	"The list below will have the stack pointer, and then the 8 sX registers and fp...\n"
		.asciiz	"With expected value on the left, and actual on the right.\n"
.text
	# print_str(ERRMSG)
	addi	$v0, $zero, 4
	la	$a0, main_ERRMSG
	syscall

	la	$t0, main_STACK_SAVE_PTR
	add	$a0, $sp, $zero
	lw	$a1, 0($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s0, $zero
	lw	$a1,  0($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s1, $zero
	lw	$a1,  4($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s2, $zero
	lw	$a1,  8($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s3, $zero
	lw	$a1, 12($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s4, $zero
	lw	$a1, 16($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s5, $zero
	lw	$a1, 20($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s6, $zero
	lw	$a1, 24($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $s7, $zero
	lw	$a1, 28($t0)
	jal	reportMainError

	la	$t0, x_JUNK_VALUES
	add	$a0, $fp, $zero
	lw	$a1, 32($t0)
	jal	reportMainError

DONE:	
	addi	$v0, $zero, 10		# syscall_exit
	syscall


# helper function
reportMainError:
	# Function prologue -- even main has one
	addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	sw	$fp, 0($sp)     # save caller's frame pointer
	sw	$ra, 4($sp)     # save return address
	addiu	$fp, $sp, 20    # setup main's frame pointer

	# save a1, which will be used on the 3rd syscall
	sw	$a1, 12($sp)

	# printHex(a0, 8)
	  # a0 is already in the right place!
	addi	$a1, $zero, 8
	jal	printHex
	
	# print_char(' ')
	addi	$v0, $zero, 11
	addi	$a0, $zero, 0x20
	syscall

	# print_int(a1)
	lw	$a0, 12($sp)
	addi	$a1, $zero, 8
	jal	printHex

	# print_char('\n')
	addi	$v0, $zero, 11
	addi	$a0, $zero, 0xa
	syscall


	# Function epilogue -- restore stack & frame pointers and return
	lw	$ra, 4($sp)     # get return address from stack
	lw	$fp, 0($sp)     # restore the caller's frame pointer
	addiu	$sp, $sp, 24    # restore the caller's stack pointer
	jr	$ra             # return to caller's code



# --------------------------------------------------------
# CALLABLE FUNCTIONS
#
# This function only runs in a few testcases, but it has to be defined in
# *ALL* of them, since the student code will need to link to it.
# --------------------------------------------------------



# helper to the helper function
printHex:
	# Function prologue -- even main has one
	addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	sw	$fp, 0($sp)     # save caller's frame pointer
	sw	$ra, 4($sp)     # save return address
	addiu	$fp, $sp, 20    # setup main's frame pointer

	# save both parameters for later
	sw	$a0,  8($sp)


	# handle the base case!
	bne	$a1, $zero, printHex_NOT_BASE_CASE

.data
printHex_PREFIX:
	.asciiz	"0x"
.text
	addi	$v0, $zero, 4
	la	$a0, printHex_PREFIX
	syscall

	j	printHex_DONE

printHex_NOT_BASE_CASE:
	# recurse first, to print the upper part.
	srl	$a0, $a0, 4
	addi	$a1, $a1, -1
	jal	printHex

	# now, print the character for *THIS* call.  First step is to mask it off.
	lw	$a0, 8($sp)
	andi	$a0, $a0, 0xf

	# second step is to check if this will be an alpha-digit or number-digit
	slti	$t0, $a0, 10
	beq	$t0, $zero, printHex_ALPHA_DIGIT

	addi	$a0, $a0, '0'
	j	printHex_PRINT_COMMON_CODE

printHex_ALPHA_DIGIT:
	addi	$a0, $a0, 87		# 87 = -10+'a'

printHex_PRINT_COMMON_CODE:
	addi	$v0, $zero, 11
	syscall

printHex_DONE:
	# Function epilogue -- restore stack & frame pointers and return
	lw	$ra, 4($sp)     # get return address from stack
	lw	$fp, 0($sp)     # restore the caller's frame pointer
	addiu	$sp, $sp, 24    # restore the caller's stack pointer
	jr	$ra             # return to caller's code



# these constants are used by main() to initialize the sX registers *BEFORE*
# calling the user functions, and by the other functions to initialize the tX
# before returning.  In both cases, we're checking to see if the user has
# implemented the MIPS calling conventions (for register-saving) as required.
#
# The first 9 entries are for the sX initialization values; the 10 after that
# are the tX trash values
#
# UPDATE: we added a 20th value, which is the seed value for CURVAL inside
#         proj06_rand
#
# UPDATE: Add two more input data arrays
#
# UPDATE: Add a prefix to each label, which can change from testcase to testcase.
.data

x_JUNK_VALUES:
	.word	10
	.word	-4
	.word	-324178
	.word	552
	.word	-903268
	.word	605
	.word	-10
	.word	6
	.word	-615
	.word	274708
	.word	0
	.word	5
	.word	-6
	.word	4
	.word	0
	.word	-170
	.word	0
	.word	-470
	.word	-629455
	.word	-81223

STR_x:
	.asciiz	"This is a test string.  The first time you see it, you should see the entire string; after that, it should get shorter and shorter with each step, and eventually print out a blank line at the end."

AFTER_STR_x:


