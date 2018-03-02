.data

.globl	print
.globl	copy
.globl	dups
.globl	subtract

print:		.word	0
copy:		.word	1
dups:		.word	0
subtract:	.word	0

.globl	alpha
.globl	bravo
.globl	charlie

alpha:		.word	-1023
bravo:		.word	39
charlie:	.word	0


.text

.globl	main

main:
	jal studentMain
	
	addi	$v0, $zero, 10		# syscall_exit
	syscall

