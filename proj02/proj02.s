# proj02.s
#Author: Christian Soto
# Simple conditional statements

.data
     MSG: .asciiz "Copying from alpha to charlie.  Before: "
     string2: .asciiz "  After: "
     string3: .asciiz "alpha was the same as bravo.\n"
     string4: .asciiz "alpha was the same as charlie.\n"
     string5: .asciiz "bravo was the same as charlie.\n"
     string6: .asciiz "\n"
     string7: .asciiz "alpha-bravo-charlie="
     string8: .asciiz "Printing the three values:\n"
     string9: .asciiz ""
     my_var: .word 1

.text

.globl studentMain
studentMain:
      addiu $sp, $sp, -24 # allocate stack space -- default of 24 here
      sw $fp, 0($sp) # save caller’s frame pointer
      sw $ra, 4($sp) # save return address
      addiu $fp, $sp, 20 # setup main’s frame pointer

      #Load and set all varriables

      #set $s0 = copy
      la $t0, copy
      lw $s0, 0($t0)

      #set $s1 = dups
      la $t0, dups
      lw $s1, 0($t0)

      #set $s2 = subtract
      la $t0, subtract
      lw $s2, 0($t0)

      #set $s3 = print
      la $t0, print
      lw $s3, 0($t0)

      #set $s4 = alpha
      la $t0, alpha
      lw $s4, 0($t0)

      #set $s5 = bravo
      la $t0, bravo
      lw $s5, 0($t0)

      #set $s6 = charlie
      la $t0, charlie
      lw $s6, 0($t0)

      #set $s7 = my_var
      la $t0, my_var
      lw $s7, 0($t0)

      #Task 1: copy
      bne $s7, $s0, DO_DUPS #if they do not equal then do dups

      li $v0, 4
      la $a0, MSG
      syscall

      la $t0, charlie   #t0 = &charlie
      lw $t0, 0($t0)    #t0 = charlie

      li $v0, 1
      la $a0, ($t0)
      syscall
      
      li $v0, 4
      la $a0, string2
      syscall
      
      la $t1, alpha  #t1 = $alpha
      lw $t2, 0($t1)  #t2 = alpha
      add $s6, $zero, $t2  #s6 = t2
      
      li $v0, 1
      la $a0, ($s6)
      syscall

      li $v0, 4
      la $a0, string6
      syscall

      #Task 2: Dups
DO_DUPS: 
      bne $s7, $s1, DO_SUBTRACT #if they do not equal then do subtract
      
      bne $s4, $s5, DO_NEXT #compare alpha and bravo else print message
      li $v0, 4
      la $a0, string3
      syscall
      
DO_NEXT:      
      bne $s4, $s6, DO_NEXT2 #compare alpha and charlie else print message
      li $v0, 4
      la $a0, string4
      syscall
      
DO_NEXT2:
      bne $s5, $s6, DO_SUBTRACT #compare charlie and bravo else print message
      li $v0, 4
      la $a0, string5
      syscall
      
 DO_SUBTRACT:
     #subtract   
     bne $s7, $s2, DO_PRINT #if my_var does not equal subtract, go to print 
     
     sub $t0, $s4, $s5 #t0 = alpha - bravo
     sub $t0, $t0, $s6  # t1 = alpha - bravo - charlie
     
     li $v0, 4
     la $a0, string7
     syscall
     
     li $v0, 1
     la $a0, 0($t0)
     syscall
     
     li $v0, 4
     la $a0, string6
     syscall
      
DO_PRINT:
      #Task 4: Print

      bne $s7, $s3, DONE # if print is not 1, then go to DONE
  
      #print the message
      li $v0, 4
      la $a0, string8
      syscall
      
      #now print all the values and a new line after each one    
      li $v0, 1
      la $a0, 0($s4)
      syscall
      
      li $v0, 4
      la $a0, string6
      syscall
      
      li $v0, 1
      la $a0, 0($s5)
      syscall
      
      li $v0, 4
      la $a0, string6
      syscall
      
      li $v0, 1
      la $a0, 0($s6)
      syscall
      
      li $v0, 4
      la $a0, string6
      syscall
      

      li $v0, 4
      la $a0, string9
      syscall

      j DONE
DONE:   # Epilogue for main -- restore stack & frame pointers and return
	lw    $ra, 4($sp)     # get return address from stack
	lw    $fp, 0($sp)     # restore the caller's frame pointer
	addiu $sp, $sp, 24    # restore the caller's stack pointer
	jr    $ra             # return to caller's code
