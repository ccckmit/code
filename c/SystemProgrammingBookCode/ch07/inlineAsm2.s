	.file	"inlineAsm2.c"
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
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	call	__alloca
	call	___main
	movl	$10, -4(%ebp)
	movl	$15, -8(%ebp)
	movl	-4(%ebp), %ecx
	movl	-8(%ebp), %edx
/APP
	addl %edx,%ecx
/NO_APP
	movl	%ecx, %edx
	movl	%edx, %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
