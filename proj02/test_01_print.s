.data

.globl	print
.globl	copy
.globl	dups
.globl	subtract

print:		.word	1
copy:		.word	0
dups:		.word	0
subtract:	.word	0

.globl	alpha
.globl	bravo
.globl	charlie

alpha:		.word	123
bravo:		.word	17
charlie:	.word	2


.text

.globl	main

main:
	jal studentMain
	
	addi	$v0, $zero, 10		# syscall_exit
	syscall

