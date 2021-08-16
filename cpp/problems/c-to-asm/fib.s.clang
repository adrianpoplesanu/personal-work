	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 12
	.globl	_fib
	.align	4, 0x90
_fib:                                   ## @fib
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp0:
	.cfi_def_cfa_offset 16
Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp2:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	%edi, -8(%rbp)
	cmpl	$2, -8(%rbp)
	jge	LBB0_2
## BB#1:
	movl	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	LBB0_3
LBB0_2:
	movl	-8(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	callq	_fib
	movl	-8(%rbp), %edi
	subl	$2, %edi
	movl	%eax, -12(%rbp)         ## 4-byte Spill
	callq	_fib
	movl	-12(%rbp), %edi         ## 4-byte Reload
	addl	%eax, %edi
	movl	%edi, -4(%rbp)
LBB0_3:
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc


.subsections_via_symbols
