.data

        range: .word 1
	scanInts: .word 1
	forward: .word 1

	string1: .asciiz ": "
	newline: .asciiz "\n"

.text

        #set $s0 = range
        la $t0, range
        lw $s0, 0($t0)      #s0 =range

	#set $s1 = scanInts
	la $t0, scanInts
	lw $s1, 0($t0)

	#set $s2 = forward
	la $t0, forward
	lw $s2, 0($t0)

        #Task 1: Print Out A Range of Integers
        beq $s0, 0, FORWARD     #if(range == 0) branch to FORWARD

        #set $t0 = start
        addi $t0, $zero, start  #t0 = start

	#set $t1 = step
	addi $t1, $zero, step   #t1 = step

	#set i = 0
	addi $t2, $zero, 0      #t2 = 0

	#set t3 = count
	addi $t3, $zero, count  #t3 = count

	LOOP:
	slt $t4, $t2, $t3       #t4 = (i<count)
	beq $t4, $zero, AFTER   #if(i>=count)branch to AFTER

	#print i
	addi $v0, 1	#print_int
	addi $a0, $zero, $t2	#print i
	syscall

	#print string ": "
	addi $v0, $zero, 4		#print string
	la $a0, string1
	syscall

	#print num or $t1
	addi $v0, $zero, 0		#print_int
	addi $a0, $zero, $t1	#print string1
	syscall

	#increment $t1
	addi $t1, $t1, 1

	#incrment i
	addi $t2, $t2, 1

	#jump back to loop
	j LOOP

	AFTER:
	#print newline
	addi $v0, $zero, 4 #print string
	la $a0, newline
	syscall

	#Task 2: Print Out Integers Forward (with filtering)

