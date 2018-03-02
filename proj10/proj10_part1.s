# proj10_part1.s
#
# Author: Christian Soto
#
# Implements the Project 10 requirements.  It implements a set of functions,
# which are called by the various testcases.

.data
MSG1:  .asciiz ": "
.text

.globl printManyStrings
printManyStrings:

                #Funtion prologue
                addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	        sw	$ra, 0($sp)     # save caller's frame pointer
	        sw	$fp, 4($sp)     # save return address
	        addiu	$fp, $sp, 20    # setup main's frame pointer

                #intizliaze the array of Strings
                add $t2, $zero, $a0         #t2 = *strings

                #set up loop
                addi $t3, $zero, 0      # i = 0;
LOOP:
                sll $t5, $t3, 2          #t5  =  i * 4
                add $t4, $t2, $t5        #t4  =  &strings[i]
                lw  $t0, 0($t4)          # t0 = strings[0];
                beq $t0, $zero, AFTER_LOOP       # if (t0 == NULL) branch

                #print ("%d: %s\n", i, strings[i]);
                addi	$v0, $zero, 1	#print i;
	        add	$a0, $t3, $zero
	        syscall

                addi	$v0, $zero, 4  # print_str(MSG1)
	        la	$a0, MSG1
	        syscall

                addi    $v0, $zero, 4  # print_str(strings[i]
                addi    $a0, $t0, 0
                syscall

                addi	$v0, $zero, 11 # print_char('\n')
	        addi	$a0, $zero, 0xa
	        syscall

                #increament i;
                addi $t3, $t3, 1         # i++

                j  LOOP
AFTER_LOOP:
                # Function epilogue -- restore stack & frame pointers and return
         	lw	$fp, 4($sp)     # get return address from stack
        	lw	$ra, 0($sp)     # restore the caller's frame pointer
         	addiu	$sp, $sp, 24    # restore the caller's stack pointer
        	jr	$ra             # return to caller's code

.globl swapTwoStrings
swapTwoStrings:

                #Funtion prologue
                addiu	$sp, $sp, -24   # allocate stack space -- default of 24 here
	        sw	$ra, 0($sp)     # save caller's frame pointer
	        sw	$fp, 4($sp)     # save return address
	        addiu	$fp, $sp, 20    # setup main's frame pointer

                #Get the address of strings and x and y
                add $t0, $zero, $a0         #t0 = *strings

                #set the index for getting values of string
                sll $t3, $a1, 2             #t3 = x * 4
                sll $t4, $a2, 2             #t4 = y * 4

                #get the address of the variables
                add $t5, $t0, $t3           #t5 = &string[x]
                add $t6, $t0, $t4           #t6 = $string[y]

                #get the values at the address
                lw $t1, 0($t5)             #t1 = string[x]
                lw $t2, 0($t6)             #t2 = string[y]

                #swap the values and put them into the array
                sw $t2, 0($t5)             # &string[x] = y
                sw $t1, 0($t6)             # &string[y] = x

                # Function epilogue -- restore stack & frame pointers and return
         	lw	$fp, 4($sp)     # get return address from stack
        	lw	$ra, 0($sp)     # restore the caller's frame pointer
         	addiu	$sp, $sp, 24    # restore the caller's stack pointer
        	jr	$ra             # return to caller's code

.globl printSeveralStrlen
printSeveralStrlen:

                #Funtion prologue
                addiu   $sp, $sp, -24   # allocate stack space -- default of 24 here
                sw      $ra, 0($sp)     # save caller's frame pointer
                sw      $fp, 4($sp)     # save return address
                addiu   $fp, $sp, 20    # setup main's frame pointer

		#Get the address of strings
                add $t0, $zero, $a0         #t0 = *strings

                #set up loop 1
                addi $t1, $zero, 0          # i = 0;
p_LOOP1:
		sll $t2, $t1, 2             #t2  =  i * 4
                add $t3, $t0, $t2           #t3  =  &strings[i]
                lw  $t4, 0($t3)             #t4 = strings[i];
                beq $t1, $a1, AFTER_pLOOP1       # if (i == count) branch

		#set len and loop2
		addi $t5, $zero, 0            #len = 0
p_LOOP2:
		lb $t6, 0($t4)                #load first byte of string, t6 = str[len]
		beq $t6, $zero, AFTER_pLOOP2  #if(str[len] == '\0') branch

		#increment address
		addi $t4, $t4, 1               # else increment the address

		#increment len
		addi $t5, $zero, 1            #len

		j p_LOOP2

AFTER_pLOOP2:

		#print len
		addi    $v0, $zero, 1        #print len;
                add     $a0, $t5, $zero
                syscall

		#print newline
                addi    $v0, $zero, 11      # print_char('\n')
                addi    $a0, $zero, 0xa
                syscall

		#increment i
		addi $t1, $t1, 1             #i++

		j p_LOOP1

AFTER_pLOOP1:
		# Function epilogue -- restore stack & frame pointers and return
                lw      $fp, 4($sp)     # get return address from stack
                lw      $ra, 0($sp)     # restore the caller's frame pointer
                addiu   $sp, $sp, 24    # restore the caller's stack pointer
