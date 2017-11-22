	.file	"optimize.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "x=%d\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	call	__alloca
	call	___main
	call	_f
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	leave
	ret
.globl _f
	.def	_f;	.scl	2;	.type	32;	.endef
_f:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$3, -4(%ebp)
	movl	$4, -8(%ebp)
	movl	-8(%ebp), %eax
	addl	-4(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	-8(%ebp), %eax
	addl	-4(%ebp), %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	-12(%ebp), %eax
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_f;	.scl	3;	.type	32;	.endef
