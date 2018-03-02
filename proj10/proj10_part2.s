# proj10_part2.s
#
# Authors: Christian Soto and Russel Lewis
#
# This is the mysterious mips code that will be converted to c code


.text

.globl mysteryFunc
mysteryFunc:

	#Funtion prologue
	addiu	$sp, $sp, -24		# allocate stack space -- default of 24 here
	sw	$fp, 0($sp)		# save caller's frame pointer
	sw	$ra, 4($sp)		# save return address
	addiu	$fp, $sp, 20		# setup main's frame pointer

	#allocate memory for two s registers
	addiu	$sp, $sp, -8
	sw	$s0, 0($sp)
	sw	$s1, 4($sp)

	#set up loop
	addi	$s0, $zero, 0           #i = 0

OUTER_LOOP:
	slt	$t0, $s0, $a1		#t0 = (s0 > a1)
	beq	$t0, $zero, OUTER_LOOP_END  #if(s0 >= a1) branch

	#set inner loop
	addi	$s1, $zero, 0		#j = 0

INNER_LOOP:

	#since we are here, t0 = 1
	addi	$t0, $s1, 1		#t0 = j +1;
	slt	$t1, $t0, $a1		#t1 = t0 < a1
	beq	$t1, $zero, INNER_LOOP_END #if(t0 >= a1) branch

	sll	$t2, $s1, 2		#t2 = s1 * 4
	add	$t3, $a0, $t2		#t3 = a0 + t2

	lw	$t4, 0($t3)		#t4 = &t3
	lw	$t5, 4($t3)		#++t3
                                        #t5 = &t3

	slt	$t6, $t5, $t4           #t6 = t5 < t4
	beq	$t6, $zero, NO_SWAP     #if(t5 >= t4) branch

	sw	$t4, 4($t3)             #swap
	sw	$t5, 0($t3)             #swap

NO_SWAP:
        #increment j
	addi	$s1, $s1, 1             #j++
	j	INNER_LOOP

INNER_LOOP_END:
	addi	$s0, $s0, 1             #increment i
	j	OUTER_LOOP

OUTER_LOOP_END:

	lw	$s0, 0($sp)
	lw	$s1, 4($sp)
	addiu	$sp, $sp, 8

	lw	$ra, 4($sp)
	lw	$fp, 0($sp)
	addiu	$sp, $sp, 24
	jr	$ra

