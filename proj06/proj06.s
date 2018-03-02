# Author: Christian Soto
#
# This program, implements 5 functions or subroutines. Some of these
# functions will get called by other programs in the directory.
# Sometimes, some of these methods call eachother.

# Method: countOutLoud
# Parameters: takes in a single parameter, num.
# Prupose:  This method simple counts and prints numbers
#           up the parmarter passed in.

.text
.globl countOutLoud
 countOutLoud:
              # Function prologue
              addiu $sp, $sp, -24
              sw $fp, 0($sp)
              sw $ra, 4($sp)

              addiu $sp, $sp, -16
              sw $t1, 8 ($sp)
              sw $t2, 4( $sp)
              sw $t3, 0($sp)

              addi $t0, $zero, 1 #i=1
              add $t1, $zero, $a0  #t1 = num

              Loop:
                   slt $t2, $t1, $t0  # i > num
                   bne $t2, $zero, THERE #if i>num branch

                   #print i then a new line
                   addi $v0, $zero, 1  #print int at i
                   add $a0, $t0, $zero
                   syscall

                   addi $v0, $zero, 11 #print char newline
                   addi $a0, $zero, 0xa
                   syscall

                   addi $t0, $t0, 1 #i++
                   j Loop

              THERE:
                   lw $t3, 0($sp) #restore $t3
                   lw $t2, 4($sp) #restore $t2
                   lw $t1, 8($sp) #restore $t1
                   lw $t0, 12($sp) #restore $t0
                   addiu $sp, $sp, 16

                   # Epilogue
                   lw $ra, 4($sp)
                   lw $fp, 0($sp)
                   addiu $sp, $sp, 24
                   jr $ra

# Method: mul16_simple
# Parameters: takes in 2 parameters, int a and int b
# Prupose:  This purpose of this method is to act like
#           a multipler. It returns the result after
#           it is finished with the while loop.

.globl mul16_simple
 mul16_simple:
             # Function prologue
             addiu $sp, $sp, -24
             sw  $fp, 4($sp)
             sw  $ra, 0($sp)

             addi $t0, $zero, 0   #retVal = 0
             addi $t1, $zero, 0   #i = 0

             LOOP2:
                  slt $t2, $t1, $a1       #t3 = i > b
                  beq $t2, $zero, THERE2  #if(i>b) branch

                  add $t0, $t0, $a0        #retVal+=a;
                  addi $t1, $t1, 1          #i++

                  j LOOP2

             THERE2:
                  add $v0, $t0, $zero    #return retVal

                  lw $ra, 0($sp)
                  lw $fp, 4($sp)
                  addiu $sp, $sp, 24
                  jr $ra

# Method: print_mul16_simple
# Parameters: takes in 2 parameters, int a and int b
# Prupose:  This method takes in two parameters, passes
#           them to mul16_simple().  It then stores that
#           result and prints it.

.globl print_mul16_simple
.data
     my_string: .ascii "result="

.text
print_mul16_simple:
                    # Function prologue
                    addiu $sp, $sp, -20
                    sw $fp, 4($sp)
                    sw $ra, 0($sp)

                    add $t0, $zero, $a0 #t0 = a

                    #print my string first
                    addi $v0, $zero, 4
                    la $a0, my_string
                    syscall

                    add $a0, $t0, $zero  #a = t0

                    #call function
                    jal mul16_simple

                    #print return value
                    add $a0, $v0, $zero
                    addi $v0, $zero, 1
                    syscall

                    #print newline
                    addi $v0, $zero, 11 #print char newline
                    addi $a0, $zero, 0xa
                    syscall

                    # Epilogue
                    lw $ra, 0($sp)
                    lw $fp, 4($sp)
                    addiu $sp, $sp, 20
                    jr $ra

# Method: print_random_sums
# Parameters: takes in 1 parameter, int count
# Prupose:  This method takes calls the method
#           proj06_rand twice, adds them, and
#           then prints the result.  It does 
#           this in a while loop starting at 0
#           until it reaches count.
.text

.globl print_random_sums
print_random_sums:
                    # Function prologue
		    addiu $sp, $sp, -24
		    sw $fp, 4($sp)
		    sw $ra, 0($sp)

		    #set i and a
		    addi $t0, $zero, 0    #i= 0
		    add $t1, $zero, $a0   # t1 = count

		    LOOP3:
			slt $t2, $t0, $t1      # t2 = i < count
			beq $t2, $zero, THERE3 # if(i=>count) branch

                        #save registers
			addiu $sp, $sp, -24
                    	sw $t0, 20($sp)
                    	sw $t1, 16($sp)
                    	sw $t2, 12($sp)
                    	sw $t3, 8($sp)
                    	sw $t4, 4($sp)
                    	sw $t5, 0($sp)

                        #call the function for the first time
			jal proj06_rand

                        #restore registers
			lw $t5, 0($sp)
                        lw $t4, 4($sp)
                        lw $t3, 8($sp)
                        lw $t2, 12($sp)
                        lw $t1, 16($sp)
                        lw $t0, 20($sp)
                        addiu $sp, $sp, 24

			#get the return value of first random value
			add $t3, $zero, $v0

                        #save registers again
			addiu $sp, $sp, -24
                        sw $t0, 20($sp)
                        sw $t1, 16($sp)
                        sw $t2, 12($sp)
                        sw $t3, 8($sp)
                        sw $t4, 4($sp)
                        sw $t5, 0($sp)

                        #call method one last time
			jal proj06_rand

                        #restore registers
			lw $t5, 0($sp)
                        lw $t4, 4($sp)
                        lw $t3, 8($sp)
                        lw $t2, 12($sp)
                        lw $t1, 16($sp)
                        lw $t0, 20($sp)
                        addiu $sp, $sp, 24

			#get the second return value
			add $t4, $zero, $v0

			#add the two return values
			add $t5, $t3, $t4       # t5= proj06_rand()+Proj06_rand()

			#print sum and then newline
			addi $v0, $zero, 1
			add $a0, $zero, $t5
			syscall

			addi $v0, $zero, 11
			addi $a0, $zero, 0xa
			syscall

			#incrment i
			addi $t0, $t0, 1

			j LOOP3

		THERE3:

                        # Epilogue
			lw $ra, 0($sp)
			lw $fp, 4($sp)
			addiu $sp, $sp, 24
			jr $ra

# Method: print_tirangle
# Parameters: takes in 1 parameters, int height
# Prupose:  This method's purpose is to print a triangle
#           that is made up of '*' and that is height tall.
#           This method also calls mul16_simple to do its
#           multimpplciation.

.globl print_triangle
.text
print_triangle:
               # Function prologue
               addiu $sp, $sp, -24
               sw $fp, 4($sp)
               sw $ra, 0($sp)

               #set i and hieght
               addi $t0, $zero, 0     #i = 0
               add $t1, $zero, $a0    #t1 = height

               LOOP4:
                    slt $t2, $t1, $t0       #t2 = (i>height)
                    bne $t2, $zero, THERE4  #if(i>height)

                    #set a0, and a1
                    addi $a0, $zero, 0x20         #$a0 = ' '
                    sub $a1, $t1, $t0             #a1 = height -i

                    #save registers
                    addiu $sp, $sp, -12
                    sw $t0, 8($sp)
                    sw $t1, 4($sp)
                    sw $t2, 0($sp)

                    jal print_repeated

                    #load registers
                    lw $t2, 0($sp)
                    lw $t1, 4($sp)
                    lw $t0, 8($sp)
                    addiu $sp, $sp, 12

                    #set $a0, and $a1 for mul16_simple
                    add $a0, $zero, $t0           #a = i
                    addi $a1, $zero, 2            #b = 2

                    #save registers
                    addiu $sp, $sp, -12
                    sw $t0, 8($sp)
                    sw $t1, 4($sp)
                    sw $t2, 0($sp)

                    jal mul16_simple

                    #load registers
                    lw $t2, 0($sp)
                    lw $t1, 4($sp)
                    lw $t0, 8($sp)
                    addiu $sp, $sp, 12

                    #set return value from mul16_simple to a1 and * to a0
                    addi $a0, $zero, 0x2A         #a1 = '*'
                    add $a1, $zero, $v0           #a0 = 2*i
                    addi $a1, $a1, 1            #a0 = 2*i+1

                    #save registers
                    addiu $sp, $sp, -12
                    sw $t0, 8($sp)
                    sw $t1, 4($sp)
                    sw $t2, 0($sp)

                    jal print_repeated

                    #load registers
                    lw $t2, 0($sp)
                    lw $t1, 4($sp)
                    lw $t0, 8($sp)
                    addiu $sp, $sp, 12

                    #print newline
                    addi $v0, $zero, 11
                    addi $a0, $zero, 0xa
                    syscall

                    #increment i
                    addi $t0, $t0, 1         #i++

                    j LOOP4

              THERE4:
                    # Epilogue
                    lw $ra, 0($sp)
                    lw $fp, 4($sp)
                    addiu $sp, $sp, 24
                    jr $ra
