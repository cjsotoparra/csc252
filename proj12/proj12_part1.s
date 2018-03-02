# proj12_part1.s
#
# Author: Christian Soto
#
# Implements the Project 10 requirements.  It implements a set of functions,
# which are called by the various testcases.


.globl printWithLen
printWithLen:

            #Funtion prologue
            addiu   $sp, $sp, -24   # allocate stack space -- default of 24 here
            sw      $ra, 0($sp)     # save caller's frame pointer
            sw      $fp, 4($sp)     # save return address
            addiu   $fp, $sp, 20    # setup main's frame pointer

            #intizliaze the array of Strings
            add $t0, $zero, $a0         #t0 = *strings

            #set up loop
            addi $t1, $zero, 0          #i=0

LOOP:
            add $t3, $t0, $t1           #t3 = &strings[i]
            lb $t4, 0($t3)              #t4 = strings[i]
            beq $t1, $a1, AFTER_LOOP    #if (t1 = a1) Branch

            #print chars
            addi $v0, $zero, 11          #print_char
            addi $a0, $t4, 0             #print strings[i]
            syscall

            #increment i
            addi $t1, $t1, 1            #i++

            j LOOP

AFTER_LOOP:

           # Function epilogue -- restore stack & frame pointers and return
           lw      $fp, 4($sp)     # get return address from stack
           lw      $ra, 0($sp)     # restore the caller's frame pointer
           addiu   $sp, $sp, 24    # restore the caller's stack pointer
           jr      $ra             # return to caller's code

.globl formulaRecurse
formulaRecurse:

           #Funtion prologue
           addiu   $sp, $sp, -24   # allocate stack space -- default of 24 here
           sw      $ra, 0($sp)     # save caller's frame pointer
           sw      $fp, 4($sp)     # save return address
           addiu   $fp, $sp, 20    # setup main's frame pointer

           addiu $sp, $sp, -4
           sw    $s0, 0($sp)

           #set pos
           addi $t0, $zero, 0       #pos = 0
           addi $t1, $zero, 0       # val1 =0
           addi $t2, $zero, 0       # val2 = 0
           addi $t3, $zero, 0       #len = 0
           add  $s0, $zero, $a0

           #if statement
IF:
           addi $t4, $zero, 0
           add $t5, $t4, $s0        # t5 = &buf[0]
           lb $t6, 0($t5)           # t6 = buf[0]
           addi $t7, $zero, 40    #t7 = '('

           bne $t6, $t7, GOTO_ELSE #if(buf[0] != '(') Branch to else

           #increment pos
           addi $t0, $t0, 1         #pos++

           #set parameter
           add $a0, $t0, $s0        #s0 = buf + pos

           #save vriables on the stack
           addiu $sp, $sp, -16
           sw $t0, 0($sp)
           sw $t1, 4($sp)
           sw $t2, 8($sp)
           sw $t3, 12($sp)

           #recurse on function
           jal formulaRecurse

           #restore the variables
           lw $t3, 12($sp)
           lw $t2, 8($sp)
           lw $t1, 4($sp)
           lw $t0, 0($sp)
           addiu $sp, $sp, 16

           #save the return values
           add $t3, $zero, $v0        #len = v0
           add $t1, $zero, $v1        #val1 = v1

           #increment len
           addi $t8, $t3, 1         #len+1

           #add pos and len +1
           add $t0, $t0, $t8        #pos = pos + len+1

           j AFTER_ELSE
GOTO_ELSE:

           add $t8, $t0, $a0        # t5 = &buf[pos]
           lb $t9, 0($t8)           # t9 = buf[pos]

           addi $t6, $zero, 48      # t6 = '0'

           sub $t1, $t9, $t6        # val1 = buf[pos] - '0'

           #increment pos
           addi $t0, $t0, 1              #pos++
AFTER_ELSE:

           #intialize opertator
           add $t6, $t0, $s0        # t8 = &buf[pos]
           lb $t9, 0($t6)           # t9 = buf[pos]
           add $t8, $zero, $t9      # operator = buf[pos]

           #incremnet pos
           addi $t0, $t0, 1         #pos++

IF2:
           add $t5, $t0, $s0        # t5 = &buf[pos]
           lb $t6, 0($t5)           # t6 = buf[pos]
           addi $t7, $zero, 40    #t7 = '('

           bne $t6, $t7, GOTO_ELSE2 #if(buf[pos] != '(') Branch to else

           #increment pos
           addi $t0, $t0, 1         #pos++

           #set parameter
           add $a0, $t0, $s0        #a0 = buf + pos

           #save vriables on the stack
           addiu $sp, $sp, -16
           sw $t0, 0($sp)
           sw $t1, 4($sp)
           sw $t2, 8($sp)
           sw $t3, 12($sp)

           #recurse on function
           jal formulaRecurse

           #restore the variables
           lw $t3, 12($sp)
           lw $t2, 8($sp)
           lw $t1, 4($sp)
           lw $t0, 0($sp)
           addiu $sp, $sp, 16

           #save the return values
           add $t3, $zero, $v0        #len = v0
           add $t2, $zero, $v1        #val2 = v1

           #increment len
           addi $t8, $t3, 1         #len+1

           #add pos and len
           add $t0, $t0, $t8        #pos = pos + len+1

           j AFTER_ELSE2
GOTO_ELSE2:

           add $t4, $t0, $s0        # t4 = &buf[pos]
           lb $t5, 0($t4)           # t5 = buf[pos]

           addi $t7, $zero, 48      # t7 = '0'

           sub $t2, $t5, $t7        # val2 = buf[pos] - '0'

           #increment pos
           addi $t0, $t0, 1              #pos++
AFTER_ELSE2:

           #printWithLen and set arguement 2
           add $a1, $zero, $t0     #a1 = pos
           add $a0, $zero, $s0     #a0 = buf

           #save vriables on the stack
           addiu $sp, $sp, -16
           sw $t0, 0($sp)
           sw $t1, 4($sp)
           sw $t2, 8($sp)
           sw $t3, 12($sp)

           #recurse on function
           jal printWithLen

           #restore the variables
           lw $t3, 12($sp)
           lw $t2, 8($sp)
           lw $t1, 4($sp)
           lw $t0, 0($sp)
           addiu $sp, $sp, 16

           #print new line
           addi	$v0, $zero, 11			# print_char('\n')
	   addi	$a0, $zero, 0xa
	   syscall

           #get operator charatars
           addi $t4, $zero, 43                  # t4 = '+'
           addi $t5, $zero, 45                  # t5 = '-'

IF3:
           bne $t8, $t4, GOTO_ELSE3             #if(opertaor != '+')BRANCH

           #set retVal
           add $t7, $t1, $t2                    #retVal = val1 + val2

           j AFTER_ELSE3
GOTO_ELSE3:

           #set retVal
           mul $t7, $t1, $t2                    #retVal = val1 * val2

AFTER_ELSE3:

           #print new line and retval
           addi $v0, $zero, 1                  # print %d
           add $a0, $t7, $zero
           syscall

           addi $v0, $zero, 11                  # print_char('\n')
           addi $a0, $zero, 0xa
           syscall

           lw $s0, 0($sp)
           addiu $sp, $sp, 4

           #set return values
           add $v0, $zero, $t0
           add $v1, $zero, $t7

           # Function epilogue -- restore stack & frame pointers and return
           lw      $fp, 4($sp)     # get return address from stack
           lw      $ra, 0($sp)     # restore the caller's frame pointer
           addiu   $sp, $sp, 24    # restore the caller's stack pointer
           jr      $ra             # return to caller's code
