	.file	"optimize.c"
	.text
	.p2align 4,,15
.globl _f
	.def	_f;	.scl	2;	.type	32;	.endef
_f:
	pushl	%ebp
	movl	$14, %eax
	movl	%esp, %ebp
	popl	%ebp
	ret
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "x=%d\12\0"
	.text
	.p2align 4,,15
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	$16, %eax
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	call	__alloca
	call	___main
	movl	$LC0, (%esp)
	movl	$14, %eax
	movl	%eax, 4(%esp)
	call	_printf
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
	.def	_f;	.scl	3;	.type	32;	.endef
