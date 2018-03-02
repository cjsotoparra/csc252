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

.data
MSG:	.asciiz	"After the student code, charlie="
.text
	addi	$v0, $zero, 4		# print_str(MSG)
	la	$a0, MSG
	syscall

	addi	$v0, $zero, 1		# print_int(charlie)
	la	$t0, charlie
	lw	$a0, 0($t0)
	syscall

	addi	$v0, $zero, 11		# print_char('\n')
	addi	$a0, $zero, 0xa
	syscall
	
	addi	$v0, $zero, 10		# syscall_exit
	syscall

