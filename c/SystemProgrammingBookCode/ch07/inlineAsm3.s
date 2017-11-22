	.file	"inlineAsm3.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "abc\0"
LC1:
	.ascii "d=%s s=%s\12\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$168, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -140(%ebp)
	movl	-140(%ebp), %eax
	call	__alloca
	call	___main
	movl	LC0, %eax
	movl	%eax, -12(%ebp)
	leal	-12(%ebp), %eax
	movl	%eax, 4(%esp)
	leal	-136(%ebp), %eax
	movl	%eax, (%esp)
	call	_strcpy
	leal	-12(%ebp), %eax
	movl	%eax, 8(%esp)
	leal	-136(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	leave
	ret
	.def	_strcpy;	.scl	3;	.type	32;	.endef
_strcpy:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	pushl	%esi
	subl	$12, %esp
	movl	12(%ebp), %esi
	movl	8(%ebp), %edi
/APP
	1:	lodsb
	stosb
	testb %al,%al
	jne 1b
/NO_APP
	movl	%eax, %edx
	movl	%esi, %eax
	movl	%eax, -12(%ebp)
	movl	%edi, %eax
	movl	%eax, -16(%ebp)
	movl	%edx, %eax
	movl	%eax, -20(%ebp)
	movl	8(%ebp), %eax
	addl	$12, %esp
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.def	_printf;	.scl	3;	.type	32;	.endef
