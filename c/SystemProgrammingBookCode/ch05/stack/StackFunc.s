	.file	"StackFunc.c"
	.section .rdata,"dr"
LC0:
	.ascii "top < STACK_SIZE\0"
LC1:
	.ascii "StackFunc.c\0"
	.text
.globl _push
	.def	_push;	.scl	2;	.type	32;	.endef
_push:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$99, _top
	jle	L3
	movl	$LC0, 8(%esp)
	movl	$5, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert
L3:
	movl	_top, %eax
	movl	%eax, %edx
	movl	8(%ebp), %eax
	movl	%eax, _stack(,%edx,4)
	incl	_top
	leave
	ret
	.section .rdata,"dr"
LC2:
	.ascii "top > 0\0"
	.text
.globl _pop
	.def	_pop;	.scl	2;	.type	32;	.endef
_pop:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	cmpl	$0, _top
	jg	L6
	movl	$LC2, 8(%esp)
	movl	$10, 4(%esp)
	movl	$LC1, (%esp)
	call	___assert
L6:
	decl	_top
	movl	_top, %eax
	movl	_stack(,%eax,4), %eax
	leave
	ret
	.def	___assert;	.scl	3;	.type	32;	.endef
