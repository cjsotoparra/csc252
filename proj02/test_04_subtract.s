.data

.globl	print
.globl	copy
.globl	dups
.globl	subtract

print:		.word	0
copy:		.word	0
dups:		.word	0
subtract:	.word	1

.globl	alpha
.globl	bravo
.globl	charlie

alpha:		.word	36
bravo:		.word	36
charlie:	.word	36


.text

.globl	main

main:
	jal studentMain
	
	addi	$v0, $zero, 10		# syscall_exit
	syscall

