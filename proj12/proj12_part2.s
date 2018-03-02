# CSC 252 Spring 17
#
# Project 12, Part 2 (MIPS to C)
#
# A set of mysterious functions to reverse-engineer.  Each takes at least one
# parameter; the first parameter is always a pointer to a certain type of
# struct.
#
# Function names are taken from Order of the Stick
#    http://www.giantitp.com/comics/ootscast.html
#
# P.S. The functions are something you shuld recognize.  But they have one or
#      more noteworthy bugs.  So be careful to translate the functions
#      faithfully-no making guesses about how they "ought" to work.



.text
.globl roy
roy:
	addiu	$sp, $sp, -24
	sw	$fp, 0($sp)
	sw	$ra, 4($sp)
	addiu	$fp, $sp, 20

	# 2 args

	addiu	$sp, $sp, -8
	sw	$s0, 0($sp)
	sw	$s1, 4($sp)

	# save a0 in s0 and a1 in s1, for safekeeping.
	add	$s0, $a0, $zero
	add	$s1, $a1, $zero

        #if (arg1 == null) Branch
	beq	$a0, $zero, roy__BASE

        #$t0 = arg1->thing
	lw	$t0, 0($a0)

        #if (arg2 < arg1->thing) Branch right
	slt	$t1, $a1, $t0
	bne	$t1, $zero, roy__RIGHT

roy__LEFT:

        #arg1 = arg1->ptr1
	lw	$a0, 4($s0)
	# a1 doesn't change

        #recurse back to roy
	jal	roy

        #arg1 = roy(arg1, arg2)
	sw	$v0, 4($s0)

        #jump to roy_DONE label
	j	roy__DONE

roy__RIGHT:

        #arg1= arg1->ptr2
	lw	$a0, 8($s0)

	# a1 doesn't change

        #arg1 = roy(arg1, arg2)
	jal	roy
	sw	$v0, 8($s0)

        #return arg1
	j	roy__DONE

roy__BASE:
	# this value is 12 on a 32-bit machine.  But use
	# sizeof() in C to get the right size on your 64-bit machine!

        #load the size of the node into $a0
	addi	$a0, $zero, 12

        #malloc memory for struct node
	jal	malloc

        #arg1 = (Proj12ArgType *) malloc(sizeof(Proj1Arg12Type));
      	add	$s0, $v0, $zero

        #arg1->thing = arg2;
	sw	$s1,   0($s0)

        #arg1->ptr1 = null;
	sw	$zero, 4($s0)

        #arg1->ptr2 = null;
	sw	$zero, 8($s0)

roy__DONE:

        #return arg1
	add	$v0, $s0, $zero

	lw	$s0, 0($sp)
	lw	$s1, 4($sp)
	addiu	$sp, $sp, 8

	lw	$ra, 4($sp)
	lw	$fp, 0($sp)
	addiu	$sp, $sp, 24
	jr	$ra



.globl durkon
durkon:
	addiu	$sp, $sp, -24
	sw	$fp, 0($sp)
	sw	$ra, 4($sp)
	addiu	$fp, $sp, 20

	# 1 arg

	addiu	$sp, $sp, -4
	sw	$s0, 0($sp)

	# save a0 in s0, for safekeeping.
	add	$s0, $a0, $zero

        #if (arg1 == null) branch to durkon_DONE
	beq	$a0, $zero, durkon__DONE

        #load arg1->ptr1 into $a0
	lw	$a0, 4($s0)

        #recurse to functionn
	jal	durkon

        #print arg1->thing
	addi	$v0, $zero, 1
	lw	$a0, 0($s0)
	syscall

        #print newline
	addi	$v0, $zero, 11
	add	$a0, $zero, 0xa
	syscall

        #load arg1->ptr2 into $ao register
	lw	$a0, 8($s0)

        #call function durkon(arg1->ptr2)
	jal	durkon

durkon__DONE:

	lw	$s0, 0($sp)
	addiu	$sp, $sp, 4

	lw	$ra, 4($sp)
	lw	$fp, 0($sp)
	addiu	$sp, $sp, 24
	jr	$ra



.globl vaarsuvius
vaarsuvius:
	addiu	$sp, $sp, -24
	sw	$fp, 0($sp)
	sw	$ra, 4($sp)
	addiu	$fp, $sp, 20

	# 2 args

        #if (arg1 != NULL) BRANCH to nonEmpty
	bne	$a0, $zero, vaarsuvius__NON_EMPTY

.data
vaarsuvius__MSG1:	.asciiz	"Not found!\n"
vaarsuvius__MSG2:	.asciiz	"Found!\n"
.text

        #if arg1 != null, then print MSG1
	addi	$v0, $zero, 4
	la	$a0, vaarsuvius__MSG1
	syscall

        #jump to done
	j	vaarsuvius__DONE

vaarsuvius__NON_EMPTY:

        #t0 = arg1->thing
	lw	$t0, 0($a0)

        #if(arg1->thing != arg2)Branch to vaarsuvius_RECURSE
	bne	$t0, $a1, vaarsuvius__RECURSE

        #Print message NOT FOUND!\n
	addi	$v0, $zero, 4
	la	$a0, vaarsuvius__MSG1
	syscall

        #jump to vaarsuvuis_DONE
	j	vaarsvaarsuvius__RIGHTuvius__DONE

vaarsuvius__RECURSE:

        #t3 = arg1->thing < arg2
	slt	$t3, $t0, $a1

        #if(arg1->thing < arg2) BRANCH vaarsuvius__RIGHT
	bne	$t3, $zero, vaarsuvius__RIGHT

        #Else if(arg1->thing >arg2) BRANCH vaarsuvius

        #arg1 = arg1->ptr1
	lw	$a0, 4($a0)

	# a1 doesn't change

        #vaarsuvius(arg1)
	jal	vaarsuvius

        #jump to done
	j	vaarsuvius__DONE

vaarsuvius__RIGHT:

        #arg1 = arg->ptr2
	lw	$a0, 8($a0)

	# a1 doesn't change

        #vaarsuvius(arg1)
	jal	vaarsuvius

        #jump to done
	j	vaarsuvius__DONE

vaarsuvius__DONE:

        #return to function caller
	lw	$ra, 4($sp)
	lw	$fp, 0($sp)
	addiu	$sp, $sp, 24
	jr	$ra


