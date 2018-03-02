.data

.globl	print
.globl	copy
.globl	dups
.globl	subtract

.globl	alpha
.globl	bravo
.globl	charlie

charlie:	.word	0
bravo:		.word	53
alpha:		.word	-107

dups:		.word	1
copy:		.word	1
print:		.word	1
subtract:	.word	1


.text

.globl	main

main:
	jal studentMain
	
	addi	$v0, $zero, 10		# syscall_exit
	syscall

