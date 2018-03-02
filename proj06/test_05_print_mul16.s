.text

.globl	main
main:
	# initialize all of the sX registers (and $fp) to nine constants, which
	# are different for every testcase.
	la	$fp, JUNK_VALUES
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
	
	
	# ----------------- BEGIN REAL TESTCASE HERE -------------------------

	# nested loops:
	#
	# for (int i=1; i<65536; i<<=1)
	# for (int j=0; j<100;   j+=13)
	#     printf("%d * %d = %d\n", i,j, mul16_simple(i*j));
	#
	# REGISTERS:
	# t0 - i
	# t1 - j
	# t2 - temporaries

	addi	$t0, $zero, 1		# i = 1

main_OUTER_LOOP:
	andi	$t2, $t0, 0xffff	# t2 = lower 16 bits of i
	bne	$t2, $t0, main_OUTER_LOOP_END   # if (i >= 65536) break

	addi	$t1, $zero, 0		# j = 0

main_INNER_LOOP:
	slti	$t2, $t1, 100		# t2 = (j < 100)
	beq	$t2, $zero, main_INNER_LOOP_END

.data
main_MSG1:	.asciiz	" * "
main_MSG2:	.asciiz	": "
.text
	# print_int(i)
	addi	$v0, $zero, 1
	add	$a0, $t0, $zero
	syscall

	# print_str(MSG1)
	addi	$v0, $zero, 4
	la	$a0, main_MSG1
	syscall

	# print_int(j)
	addi	$v0, $zero, 1
	add	$a0, $t1, $zero
	syscall

	# print_str(MSG2)
	addi	$v0, $zero, 4
	la	$a0, main_MSG2
	syscall


	# print_mul16_simple(i,j)
	#
	# REGISTERS TO SAVE IN THE 
	#   t0 - i
	#   t1 - j
	addiu	$sp, $sp, -8
	sw	$t0, 4($sp)
	sw	$t1, 0($sp)

	add	$a0, $t0, $zero
	add	$a1, $t1, $zero
	jal	print_mul16_simple

	# RESTORE t0,t1
	lw	$t1, 0($sp)
	lw	$t0, 4($sp)
	addiu	$sp, $sp, 8

	addi	$t1, $t1, 13
	j	main_INNER_LOOP

main_INNER_LOOP_END:

	sll	$t0, $t0, 1
	j	main_OUTER_LOOP

main_OUTER_LOOP_END:


	# ------------------ CHECK REGISTER CONTENTS -------------------------
	la	$t0, main_STACK_SAVE_PTR
	lw	$t0, 0($t0)
	bne	$t0, $sp, main_REPORT_ERROR

	la	$t0, JUNK_VALUES

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
		.ascii	"The list below will have the stack pointer, and then the 8 sX registers...\n"
		.asciiz	"With expected value on the left, and actual on the right."
.text
	# print_str(ERRMSG)
	addi	$v0, $zero, 4
	la	$a0, main_ERRMSG
	syscall

	la	$t0, main_STACK_SAVE_PTR
	add	$a0, $sp, $zero
	lw	$a1, 0($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s0, $zero
	lw	$a1,  0($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s1, $zero
	lw	$a1,  4($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s2, $zero
	lw	$a1,  8($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s3, $zero
	lw	$a1, 12($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s4, $zero
	lw	$a1, 16($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s5, $zero
	lw	$a1, 20($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s6, $zero
	lw	$a1, 24($t0)
	jal	reportMainError

	la	$t0, JUNK_VALUES
	add	$a0, $s7, $zero
	lw	$a1, 28($t0)
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



# --------------------------------------------------------
# CALLABLE FUNCTIONS
#
# This function only runs in a few testcases, but it has to be defined in
# *ALL* of them, since the student code will need to link to it.
# --------------------------------------------------------



.globl	proj06_rand
proj06_rand:
	# Function prologue -- even main has one
	addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	sw	$fp, 0($sp)     # save caller's frame pointer
	sw	$ra, 4($sp)     # save return address
	addiu	$fp, $sp, 20    # setup main's frame pointer


# this is, essentially, a static variable inside the function.  In the very
# first call, we initialize from the JUNK_VALUES array above.
.data
proj06_rand_FIRST:
	.byte	1
proj06_rand_CURVAL:
	.word	0
.text


	# if (FIRST)
	# {
	#     FIRST  = 0;
	#     CURVAL = JUNK_VALUES[19];
	# }
	la	$t0,   proj06_rand_FIRST	# t0 = &FIRST
	lw	$t1,   0($t0)			# t1 =  FIRST
	sw	$zero, 0($t0)			# FIRST = 0
	beq	$t1, $zero, proj06_rand_AFTER_INIT

	la	$t0, JUNK_VALUES		# t0 = &JUNK_VALUES
	lw	$t0, 76($t0)			# t0 =  JUNK_VALUES[19]
	la	$t1, proj06_rand_CURVAL		# t1 = &CURVAL
	sw	$t0,  0($t1)			# CURVAL = JUNK_VALUES[19]

proj06_rand_AFTER_INIT:


	# this has got to be the worst rand() in the history of programming!
	# But it's enough for a toy.
	la	$t0, proj06_rand_CURVAL
	lw	$t1, 0($t0)

	xori	$t1, $t1, 0x3456
	srl	$t2, $t1, 19			# save the top 13 bits
	sll	$t1, $t1, 13
	or	$t1, $t1, $t2			# put those 13 bits back in
	xori	$t1, $t1, 0x9f2e

	# store the value back
	sw	$t1, 0($t0)

	# copy the value (modulo 32768) to the return value.
	andi	$v0, $t1, 0x7fff


	# INTENTIONALLY TRASH THE tX REGISTERS
	#
	# Will the student code break?
	la	$t9, JUNK_VALUES
	addi	$t9, $t9, 36
	lw	$t0,  0($t9)
	lw	$t1,  4($t9)
	lw	$t2,  8($t9)
	lw	$t3, 12($t9)
	lw	$t4, 16($t9)
	lw	$t5, 20($t9)
	lw	$t6, 24($t9)
	lw	$t7, 28($t9)
	lw	$t8, 32($t9)
	lw	$t9, 36($t9)

	# Function epilogue -- restore stack & frame pointers and return
	lw	$ra, 4($sp)     # get return address from stack
	lw	$fp, 0($sp)     # restore the caller's frame pointer
	addiu	$sp, $sp, 24    # restore the caller's stack pointer
	jr	$ra             # return to caller's code



.globl	print_repeated
print_repeated:
	# Function prologue -- even main has one
	addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	sw	$fp, 0($sp)     # save caller's frame pointer
	sw	$ra, 4($sp)     # save return address
	addiu	$fp, $sp, 20    # setup main's frame pointer


	# for (int i=0; i<count; i++)
	#     print_char(c)
	#
	# REGISTERS:
	# t0 - count
	# t1 - c
	# t2 - i
	# t3 - temporaries

	add	$t0, $a1, $zero			# move 'count' into t0
	add	$t1, $a0, $zero			# move 'i' into t1
	add	$t2, $zero, 0			# i = 0

	# we can set v0/a0 once, and then use it over and over again
	addi	$v0, $zero, 11			# print_char()
	add	$a0, $t1, $zero

print_repeated_LOOP:
	slt	$t3, $t2, $t0
	beq	$t3, $zero, print_repeated_LOOP_END

	syscall		# print the character

	addi	$t2, $t2, 1
	j	print_repeated_LOOP

print_repeated_LOOP_END:


	# INTENTIONALLY TRASH THE tX REGISTERS
	#
	# Will the student code break?
	la	$t9, JUNK_VALUES
	addi	$t9, $t9, 36
	lw	$t0,  0($t9)
	lw	$t1,  4($t9)
	lw	$t2,  8($t9)
	lw	$t3, 12($t9)
	lw	$t4, 16($t9)
	lw	$t5, 20($t9)
	lw	$t6, 24($t9)
	lw	$t7, 28($t9)
	lw	$t8, 32($t9)
	lw	$t9, 36($t9)

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
.data

JUNK_VALUES:
	.word	410
	.word	0
	.word	9
	.word	-7
	.word	-125738
	.word	-572773
	.word	-530357
	.word	0
	.word	-2
	.word	-218
	.word	-5
	.word	-10
	.word	-322539
	.word	2
	.word	723
	.word	972847
	.word	209
	.word	-496
	.word	7
	.word	-345


