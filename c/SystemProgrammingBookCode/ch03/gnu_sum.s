	.data
sum: .long 0
	.text
.globl _asmMain
	.def _asmMain; .scl	2; .type 32; .endef
_asmMain:
	mov $1, %eax
FOR1:
	addl %eax, sum
	addl $1, %eax
	cmpl $10,%eax
	jle FOR1
	movl sum, %eax
	ret
	