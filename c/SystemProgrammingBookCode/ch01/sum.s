	.file	"sum.c"
	.text
.globl _sum
	.def	_sum;	.scl	2;	.type	32;	.endef
_sum:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$1, -8(%ebp)
L2:
	movl	-8(%ebp), %eax
	cmpl	8(%ebp), %eax
	jg	L3
	movl	-8(%ebp), %eax
	leal	-4(%ebp), %edx
	addl	%eax, (%edx)
	leal	-8(%ebp), %eax
	incl	(%eax)
	jmp	L2
L3:
	movl	-4(%ebp), %eax
	leave
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "sum=%d\12\0"
LC1:
	.ascii "pause\0"
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
	movl	$10, (%esp)
	call	_sum
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$LC1, (%esp)
	call	_system
	movl	$1, %eax
	leave
	ret
	.def	_system;	.scl	3;	.type	32;	.endef
	.def	_printf;	.scl	3;	.type	32;	.endef
