.data

.globl	print
.globl	copy
.globl	dups
.globl	subtract

print:		.word	0
copy:		.word	0
dups:		.word	1
subtract:	.word	0

.globl	alpha
.globl	bravo
.globl	charlie

alpha:		.word	17
bravo:		.word	17
charlie:	.word	17


.text

.globl	main

main:
	jal studentMain
	
	addi	$v0, $zero, 10		# syscall_exit
	syscall

