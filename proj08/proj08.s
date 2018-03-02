# Author: Christian Soto
# 
# File: proj08.s
#
# This program, implements 5 functions or subroutines. Some of these
# functions will get called by other programs in the directory.
# Sometimes, some of these methods call eachother.

.data
	string1: .asciiz "1: "
	string2: .asciiz "2: "

.text
.globl mergePrint
mergePrint:
        addiu $sp, $sp, -24
        sw $fp, 0($sp)
        sw $ra, 4($sp)

        addi $t0, $a0, 0         # t0 = &arr1
        lw $t1, 0($a0)           # t0 = arr1
        addi $t2, $a2, 0         # t2 = &arr2
        lw $t2, 0($a2)           # t2 = *arr2
        addi $t6, $t6, 1         # t6 = 1

        LOOP:
             bne $a1, $zero, IF #if len1!=0 branch
             bne $a3, $zero, IF #if len2!=0 branch


             addiu $sp, $sp, 24
             sw $ra, 0($sp)
             sw $fp, 4($sp)

             jr $ra

            IF:
            #if statement
            beq $a3, $zero, THEN     #if(len2==0) goto THEN
            beq $a1, $zero, ELSE     #if(len1!=0) goto THEN
            slt $t4, $t2, $t1        #t4 = *arr1 > *arr2
            bne $t4, $zero, ELSE     # if(*arr1>*arr2) goto ELSE

            THEN:
                lw $t5, 0($t0)           #t5 = &arr1

                addi $v0, $zero, 4        #print string1
                la $a0, string1
                syscall

                addi $v0, $zero, 1        #print *arr1
                add $a0, $zero, $t5
                syscall

                addi $v0, $zero, 11       #print newline
                addi $a0, $zero, 0xa
                syscall

                addi $t0, $t0, 4          #arr1++
                lw $t1, 0($t0)
                sub  $a1, $a1, $t6        #len--

                j LOOP

             ELSE:
                lw $t5, 0($a2)             #t5 = &arr2

                addi $v0, $zero, 4        #print string2
                la $a0, string2
                syscall

                addi $v0, $zero, 1        #print number at *arr2
                addi $a0, $t5, 0
                syscall

                addi $v0, $zero, 11       #print newlinw
                addi $a0, $zero, 0xa
                syscall

                addi $a2, $a2, 4          #arr2++
                lw $t2, 0($a2)            #t2 = *arr2
                sub $a3, $a3, $t6         #len2--

                j LOOP


.globl mergeInto
mergeInto:
        addiu $sp, $sp, -28
        sw $fp, 0($sp)
        sw $ra, 4($sp)
	addiu $fp, $sp, 24

        addi $t0, $a0, 0         # t0 = &arr1
        lw $t1, 0($t0)           # t1 = *arr1
        addi $t2, $a2, 0         # t2 = &arr2
        lw $t2, 0($a2)           # t2 = *arr

	#load the fifth arguement
	lw $t3, 0($fp)          # t3 = &out

        addi $t6, $t6, 1         #  t6 = 1

        LOOP2:
             bne $a1, $zero, IF2 #if len1!=0 branch
             bne $a3, $zero, IF2 #if len2!=0 branch

             lw $ra, 4($sp)
             lw $fp, 0($sp)
 	     addiu $sp, $sp, 28
             jr $ra


            IF2:
            #if statement
            beq $a3, $zero, THEN2     #if(len2==0) goto THEN
            beq $a1, $zero, ELSE2     #if(len1!=0) goto THEN
            slt $t4, $t2, $t1        #t4 = *arr1 > *arr2
            bne $t4, $zero, ELSE2     # if(*arr1>*arr2) goto ELSE

            THEN2:
                lw $t5, 0($t0)           #t5 = *arr1
                sw $t5, 0($t3)           #*out = *arr1

                addi $t0, $t0, 4          #arr1++
                lw $t1, 0($t0)
                sub  $a1, $a1, $t6        #len--

		addi $t3, $t3, 4	  #out++

                j LOOP2

             ELSE2:
                lw $t5, 0($a2)            #t5 = &arr2
                sw $t5, 0($t3)            # out = arr2

                addi $a2, $a2, 4          #arr2++
                lw $t2, 0($a2)            #t2 = *arr2
                sub $a3, $a3, $t6         #len2--
		addi $t3, $t3, 4	  #out++


                j LOOP2

.globl join
join:
        addiu $sp, $sp, -24
        sw $fp, 0($sp)
        sw $ra, 4($sp)

	addi $t0, $a0, 0         # t0 = &arr1
        lw $t1, 0($a0)           # t1 = arr1
        addi $t2, $a2, 0         # t2 = &arr2
        lw $t2, 0($a2)           # t2 = *arr2
        addi $t6, $t6, 1         # t6 = 1

        LOOP_JOIN:
        beq $a1, $zero, AFTER_LOOP #if len1==0 branch
        beq $a3, $zero, AFTER_LOOP #if len2==0 branch

		#if/else statement
		beq $t1, $t2, IF_THEN   #if(*arr1 == *arr2) goto IF_THEN
		slt $t3, $t1, $t2       #t3 = (*arr1 > *arr2)
		beq $t3, $zero, ELSE_JOIN    #if(*arr1 >= *arr2) goto ELSE

		#ELSE_IF

		addi $t0, $t0, 4        #arr1++
		lw $t1, 0($t0)
		sub $a1, $a1, $t6	# len1--

		j LOOP_JOIN		# jump back to loop

		IF_THEN:
		#print values

		lw $t5, 0($t0)           #t5 = &arr1

                addi $v0, $zero, 1        #print *arr1
                add $a0, $zero, $t5
                syscall

                addi $v0, $zero, 11       #print newline
                addi $a0, $zero, 0xa
                syscall

                addi $t0, $t0, 4          #arr1++
                lw $t1, 0($t0)
                sub  $a1, $a1, $t6        #len1--

		addi $a2, $a2, 4          #arr2++
                lw $t2, 0($a2)
                sub  $a3, $a3, $t6        #len2--

		j LOOP_JOIN

		ELSE_JOIN:
		addi $a2, $a2, 4          #arr2++
                lw $t2, 0($a2)
                sub  $a3, $a3, $t6        #len2--

		j LOOP_JOIN

	AFTER_LOOP:
	 addiu $sp, $sp, 24
         sw $ra, 0($sp)
         sw $fp, 4($sp)

         jr $ra

.globl mergeInPlace
mergeInPlace:
        addiu $sp, $sp, -4024
        sw $fp, 0($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 24

	lw $t0, 4000($fp)

	#get arguements
	addi $t1, $a0, 0         # t1 = &arr
        lw $t2, 0($a0)           # t2 = arr
	add $t3, $zero, $a1     # t3 = len1
	add $t4, $zero, $a2     # t4 = len2

	add $t5, $t1, $t2       # t5 = arr+len1

	#set arguements to pass to function
	add $a0, $zero, $t2
	add $a1, $zero, $t3
	add $a2, $zero, $t4
	add $a3, $zero, $t5
	sw $t0, -4000($sp)

	jal mergeInto

	lw $t0, 4000($sp)

	#set for loop
	addi $t6, $zero, 0       #set i = 0
	add $t4, $t2, $t3	 #t4 = len1+len2

	FOR_LOOP:
	slt $t7, $t6, $t4	 # t7 = (i < len1+len2)
	beq $t7, $zero, AFTER_FOR # if(i >= len1+len2) branch

	#condition
	lw $t8, 0($t0)            #t8 = &buf
        sw $t8, 0($t1)            #arr[i] = buf[i]

	addi $t6, $t6, 1	#i++
	add $t0, $t0, $t6	#arr[i]

	j FOR_LOOP

	AFTER_FOR:
        lw $ra, 4($sp)
        lw $fp, 0($sp)
        addiu $sp, $sp, -4024
        jr $ra

