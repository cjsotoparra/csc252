.text

.globl	main
main:
	# initialize all of the sX registers (and $fp) to nine constants, which
	# are different for every testcase.
	la	$fp, b_JUNK_VALUES
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
	
	
	# --------------------- BEGIN REAL TESTCASE HERE -----------------------------

	la	$a0, STRING_ARRAY_bb

	la	$a1, LENGTH_bb
	lw	$a1, 0($a1)

	jal	printSeveralStrlen

	# print out the resulting array	
#	la	$a0, STRING_ARRAY_bb
#
#	la	$a1, LENGTH_bb
#	lw	$a1, 0($a1)
#
#	jal	printStringArray

	# --------------------- CHECK REGISTER CONTENTS -----------------------------
	la	$t0, main_STACK_SAVE_PTR
	lw	$t0, 0($t0)
	bne	$t0, $sp, main_REPORT_ERROR

	la	$t0, b_JUNK_VALUES

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

	la	$t0, b_JUNK_VALUES
	add	$a0, $s0, $zero
	lw	$a1,  0($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s1, $zero
	lw	$a1,  4($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s2, $zero
	lw	$a1,  8($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s3, $zero
	lw	$a1, 12($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s4, $zero
	lw	$a1, 16($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s5, $zero
	lw	$a1, 20($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s6, $zero
	lw	$a1, 24($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
	add	$a0, $s7, $zero
	lw	$a1, 28($t0)
	jal	reportMainError

	la	$t0, b_JUNK_VALUES
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

	la	$t0, b_JUNK_VALUES		# t0 = &JUNK_VALUES
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
	la	$t9, b_JUNK_VALUES
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
	la	$t9, b_JUNK_VALUES
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



printArray:
	# Function prologue -- even main has one
	addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	sw	$fp, 0($sp)     # save caller's frame pointer
	sw	$ra, 4($sp)     # save return address
	addiu	$fp, $sp, 20    # setup main's frame pointer


	# save the arguments into tX registers
	add	$t0, $a0, $zero			# arr
	add	$t1, $a1, $zero			# len


	# print the length first!
	addi	$v0, $zero, 1
	add	$a0, $t1, $zero
	syscall

.data
printArray_MSG:	.asciiz	": "
.text
	addi	$v0, $zero, 4
	la	$a0, printArray_MSG
	syscall


	# for (int i=0; i<len; i++)
	#
	# REGISTERS:
	#    t2 - i
	#    t9 - TEMPORARIES
	addi	$t2, $zero, 0			# i=0

printArray_LOOP:
	slt	$t9, $t2, $t1			# t2 = (i < len)
	beq	$t9, $zero, printArray_AFTER_LOOP	# if (i >= len)	break

	# read the [i]'th element of the array.
	sll	$t9, $t2, 2			# t9 = (t2 * 4)
	add	$t9, $t0, $t9			# t9 = &arr[t2*4]
	lw	$t9, 0($t9)			# t9 =  arr[t2*4}

	# print it
	addi	$v0, $zero, 1			# print_int(arg1)
	add	$a0, $t9, $zero
	syscall

	addi	$v0, $zero, 11			# print_char(' ')
	add	$a0, $zero, 0x20
	syscall

	addi	$t2, $t2, 1			# i++

	j	printArray_LOOP


printArray_AFTER_LOOP:

	# Function epilogue -- restore stack & frame pointers and return
	lw	$ra, 4($sp)     # get return address from stack
	lw	$fp, 0($sp)     # restore the caller's frame pointer
	addiu	$sp, $sp, 24    # restore the caller's stack pointer
	jr	$ra             # return to caller's code



printStringArray:
	# Function prologue -- even main has one
	addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	sw	$fp, 0($sp)     # save caller's frame pointer
	sw	$ra, 4($sp)     # save return address
	addiu	$fp, $sp, 20    # setup main's frame pointer

	# save $a0 for later restoration.  We'll never muck with $a1, so
	# we don't have to save that.
	sw	$a0, 8($sp)


	addi	$t0, $zero, 0	# i = 0

printStringArray__LOOP:
	slt	$t1, $t0, $a1	# t1 = (i < len)
	beq	$t1, $zero, printStringArray__LOOP_END

	lw	$a0, 8($sp)	# restore a0

	# print_str(arr[i])
	addi	$v0, $zero, 4

	sll	$t1, $t0, 2
	add	$a0, $a0, $t1
	lw	$a0, 0($a0)

	syscall

	# print_char('\n')
	addi	$v0, $zero, 11
	addi	$a0, $zero, 0xa
	syscall

	addi	$t0, $t0, 1	# i++
	j	printStringArray__LOOP


printStringArray__LOOP_END:
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

b_JUNK_VALUES:
	.word	-8
	.word	-3
	.word	-760986
	.word	-7
	.word	-10
	.word	0
	.word	-455028
	.word	5
	.word	-4
	.word	-8
	.word	384426
	.word	3
	.word	807922
	.word	-2
	.word	-4
	.word	-5
	.word	-6
	.word	723397
	.word	0
	.word	966

STR_1:
	.ascii	"This is a long string."
STR_2:
	.ascii	"  But it didn't end up there, because there was no z on the .ascii directive!"
STR_3:
	.ascii	"  You see the pattern now, this will continure forever!"
STR_4:
	.asciiz	"  Or, maybe not."
STR_5:
	.asciiz "I am getting bored."
STR_6:
	.asciiz	"Why do I have to write so many strings?"
STR_7:
	.asciiz	"Four score and seven minutes ago, Bill and Ted embarked on an Excellent Adventure."
STR_8:
	.asciiz	"Let's end with an obscure quote.  Great movie, few people have seen it:"
STR_9:
	.asciiz	"You leave a trail like a one-legged seed-drill.  - Clancy"

	.word	0		# dummy variable, just for alignment
STRING_ARRAY_bb:
	.word	STR_1
	.word	STR_2
	.word	STR_3
	.word	STR_4
	.word	STR_5
	.word	STR_6
	.word	STR_7
	.word	STR_8
	.word	STR_9
	.word	0		# NULL terminator for the string array

LENGTH_bb:
	.word	9

