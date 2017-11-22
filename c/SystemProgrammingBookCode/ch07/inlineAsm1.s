	.file	"inlineAsm1.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "foo=%d\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ebx
	subl	$20, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	call	__alloca
	call	___main
	movl	$10, -8(%ebp)
	movl	$15, -12(%ebp)
	movl	-8(%ebp), %eax
	movl	-12(%ebp), %ebx
/APP
	addl  %ebx,%eax
/NO_APP
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	movl	-4(%ebp), %ebx
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
