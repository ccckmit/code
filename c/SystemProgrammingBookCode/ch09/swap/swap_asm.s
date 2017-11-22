	.file	"swap.c"
	.def ___main; .scl 2; .type	32; .endef
	.section .rdata,"dr"
LC0:
	.ascii "x=%d\12\0"
LC1:
	.ascii "y=%d\12\0"
	.data
x:	.long 5
y:	.long 3
t:	.long 0
	.text
.globl _main
	.def _main; .scl 2; .type 32; .endef
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
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	call	__alloca
	call	___main
	movl	x, %eax
	movl	%eax, t
	movl	y, %eax
	movl	%eax, x
	movl	t, %eax
	movl	%eax, y
	movl	x, %eax
	movl	%eax, 4(%esp)
	movl	$LC0, (%esp)
	call	_printf
	movl	y, %eax
	movl	%eax, 4(%esp)
	movl	$LC1, (%esp)
	call	_printf
	movl	$1, %eax
	leave
	ret
	.def _printf; .scl 3; .type 32; .endef
