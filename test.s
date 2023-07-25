	.file	"test.cpp"
	.text
	.section	.text._ZNKSt5ctypeIcE8do_widenEc,"axG",@progbits,_ZNKSt5ctypeIcE8do_widenEc,comdat
	.align 2
	.p2align 4
	.weak	_ZNKSt5ctypeIcE8do_widenEc
	.type	_ZNKSt5ctypeIcE8do_widenEc, @function
_ZNKSt5ctypeIcE8do_widenEc:
.LFB1565:
	.cfi_startproc
	endbr64
	movl	%esi, %eax
	ret
	.cfi_endproc
.LFE1565:
	.size	_ZNKSt5ctypeIcE8do_widenEc, .-_ZNKSt5ctypeIcE8do_widenEc
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv:
.LFB12351:
	.cfi_startproc
	endbr64
	movl	$16842756, 40(%rdi)
	ret
	.cfi_endproc
.LFE12351:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv:
.LFB12395:
	.cfi_startproc
	endbr64
	movl	12(%rdi), %edx
	movq	%rdi, %r9
	movq	%rdx, %rsi
	salq	$5, %rdx
	addq	$24, %rdx
	movq	%rdx, 32(%rdi)
	testl	%esi, %esi
	je	.L4
	leal	-1(%rsi), %eax
	movq	80(%rdi), %rdi
	movq	88(%r9), %r8
	cmpl	$4, %eax
	jbe	.L9
	pxor	%xmm2, %xmm2
	movdqa	.LC0(%rip), %xmm4
	movl	%esi, %ecx
	xorl	%eax, %eax
	movdqa	%xmm2, %xmm8
	movdqa	%xmm2, %xmm7
	shrl	$2, %ecx
	pxor	%xmm6, %xmm6
	movdqa	.LC1(%rip), %xmm3
	pcmpgtd	%xmm4, %xmm8
	salq	$4, %rcx
	movdqa	%xmm6, %xmm5
	pcmpgtd	%xmm3, %xmm7
	.p2align 4,,10
	.p2align 3
.L7:
	movdqu	(%rdi,%rax), %xmm0
	movdqa	%xmm2, %xmm10
	movdqa	%xmm8, %xmm11
	movdqu	(%r8,%rax), %xmm1
	movdqa	%xmm7, %xmm12
	addq	$16, %rax
	movdqa	%xmm0, %xmm9
	punpckldq	%xmm0, %xmm9
	punpckhdq	%xmm0, %xmm0
	pcmpgtd	%xmm9, %xmm10
	pmuludq	%xmm9, %xmm11
	pmuludq	%xmm4, %xmm9
	pmuludq	%xmm4, %xmm10
	paddq	%xmm11, %xmm10
	movdqa	%xmm2, %xmm11
	psllq	$32, %xmm10
	paddq	%xmm10, %xmm9
	movdqa	%xmm1, %xmm10
	punpckldq	%xmm1, %xmm10
	punpckhdq	%xmm1, %xmm1
	pcmpgtd	%xmm10, %xmm11
	pmuludq	%xmm10, %xmm12
	pmuludq	%xmm3, %xmm10
	pmuludq	%xmm3, %xmm11
	paddq	%xmm12, %xmm11
	psllq	$32, %xmm11
	paddq	%xmm11, %xmm10
	paddq	%xmm10, %xmm9
	movdqa	%xmm8, %xmm10
	paddq	%xmm9, %xmm5
	pmuludq	%xmm0, %xmm10
	movdqa	%xmm2, %xmm9
	pcmpgtd	%xmm0, %xmm9
	pmuludq	%xmm4, %xmm0
	pmuludq	%xmm4, %xmm9
	paddq	%xmm10, %xmm9
	movdqa	%xmm7, %xmm10
	psllq	$32, %xmm9
	pmuludq	%xmm1, %xmm10
	paddq	%xmm9, %xmm0
	movdqa	%xmm2, %xmm9
	pcmpgtd	%xmm1, %xmm9
	pmuludq	%xmm3, %xmm1
	pmuludq	%xmm3, %xmm9
	paddq	%xmm10, %xmm9
	psllq	$32, %xmm9
	paddq	%xmm9, %xmm1
	paddq	%xmm1, %xmm0
	paddq	%xmm0, %xmm6
	cmpq	%rcx, %rax
	jne	.L7
	paddq	%xmm6, %xmm5
	movdqa	%xmm5, %xmm0
	psrldq	$8, %xmm0
	paddq	%xmm0, %xmm5
	movq	%xmm5, %rax
	addq	%rax, %rdx
	movl	%esi, %eax
	andl	$-4, %eax
	testb	$3, %sil
	je	.L8
.L6:
	movl	%eax, %ecx
	movslq	(%r8,%rcx,4), %r10
	movslq	(%rdi,%rcx,4), %rcx
	salq	$3, %rcx
	leaq	(%rcx,%r10,4), %rcx
	addq	%rcx, %rdx
	leal	1(%rax), %ecx
	cmpl	%ecx, %esi
	jbe	.L8
	movslq	(%rdi,%rcx,4), %r10
	movslq	(%r8,%rcx,4), %rcx
	salq	$2, %rcx
	leaq	(%rcx,%r10,8), %rcx
	addq	%rcx, %rdx
	leal	2(%rax), %ecx
	cmpl	%ecx, %esi
	jbe	.L8
	movslq	(%rdi,%rcx,4), %r10
	movslq	(%r8,%rcx,4), %rcx
	salq	$2, %rcx
	leaq	(%rcx,%r10,8), %rcx
	addq	%rcx, %rdx
	leal	3(%rax), %ecx
	cmpl	%ecx, %esi
	jbe	.L8
	movslq	(%rdi,%rcx,4), %r10
	movslq	(%r8,%rcx,4), %rcx
	addl	$4, %eax
	salq	$2, %rcx
	leaq	(%rcx,%r10,8), %rcx
	addq	%rcx, %rdx
	cmpl	%eax, %esi
	jbe	.L8
	movslq	(%r8,%rax,4), %rcx
	movslq	(%rdi,%rax,4), %rax
	salq	$3, %rax
	leaq	(%rax,%rcx,4), %rax
	addq	%rax, %rdx
.L8:
	movq	%rdx, 32(%r9)
.L4:
	ret
.L9:
	xorl	%eax, %eax
	jmp	.L6
	.cfi_endproc
.LFE12395:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv
	.section	.rodata._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv.str1.8,"aMS",@progbits,1
	.align 8
.LC2:
	.string	"void IVSparse::SparseMatrix<T, indexT, 2, columnMajor>::checkValueType() [with T = int; indexT = int; bool columnMajor = true]"
	.align 8
.LC3:
	.string	"IVSparse/src/VCSC/VCSC_Private_Methods.hpp"
	.align 8
.LC4:
	.string	"byte0 == sizeof(T) && \"Value type size does not match\""
	.align 8
.LC5:
	.string	"byte1 == std::is_floating_point_v<T> && \"Value type is not floating point\""
	.align 8
.LC6:
	.string	"byte2 == std::is_signed_v<T> && \"Value type is not signed\""
	.align 8
.LC7:
	.string	"byte3 == columnMajor && \"Major direction does not match\""
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv:
.LFB13425:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	40(%rdi), %eax
	movl	%eax, %ecx
	movl	%eax, %edx
	movl	%eax, %esi
	shrl	$8, %ecx
	shrl	$16, %edx
	shrl	$24, %esi
	cmpb	$4, %al
	jne	.L20
	testb	%cl, %cl
	jne	.L21
	cmpb	$1, %dl
	jne	.L22
	cmpl	$1, %esi
	jne	.L23
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L20:
	.cfi_restore_state
	leaq	.LC2(%rip), %rcx
	movl	$34, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	__assert_fail@PLT
.L23:
	leaq	.LC2(%rip), %rcx
	movl	$37, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	__assert_fail@PLT
.L22:
	leaq	.LC2(%rip), %rcx
	movl	$36, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC6(%rip), %rdi
	call	__assert_fail@PLT
.L21:
	leaq	.LC2(%rip), %rcx
	movl	$35, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC5(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE13425:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv
	.section	.rodata._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc.str1.1,"aMS",@progbits,1
.LC8:
	.string	"wb"
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc:
.LFB13427:
	.cfi_startproc
	endbr64
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	%rsi, %rdi
	leaq	.LC8(%rip), %rsi
	call	fopen@PLT
	movq	48(%rbx), %rdi
	movl	$24, %edx
	movl	$1, %esi
	movq	%rax, %rcx
	movq	%rax, %rbp
	call	fwrite@PLT
	movl	12(%rbx), %eax
	testl	%eax, %eax
	je	.L32
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L26:
	movq	80(%rbx), %rax
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movl	$1, %esi
	addl	$1, %r12d
	leaq	(%rax,%rdx,4), %rdi
	movl	$4, %edx
	call	fwrite@PLT
	movl	12(%rbx), %eax
	cmpl	%r12d, %eax
	ja	.L26
	testl	%eax, %eax
	je	.L32
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L27:
	movq	88(%rbx), %rax
	movl	%r12d, %edx
	movq	%rbp, %rcx
	movl	$1, %esi
	addl	$1, %r12d
	leaq	(%rax,%rdx,4), %rdi
	movl	$4, %edx
	call	fwrite@PLT
	movl	12(%rbx), %eax
	cmpl	%r12d, %eax
	ja	.L27
	testl	%eax, %eax
	je	.L32
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L29:
	movq	80(%rbx), %rdx
	movl	%r12d, %eax
	movq	56(%rbx), %rcx
	movl	$1, %esi
	addl	$1, %r12d
	movslq	(%rdx,%rax,4), %rdx
	movq	(%rcx,%rax,8), %rdi
	movq	%rbp, %rcx
	salq	$2, %rdx
	call	fwrite@PLT
	movl	12(%rbx), %eax
	cmpl	%r12d, %eax
	ja	.L29
	testl	%eax, %eax
	je	.L32
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L31:
	movq	80(%rbx), %rdx
	movl	%r12d, %eax
	movq	64(%rbx), %rcx
	movl	$1, %esi
	addl	$1, %r12d
	movslq	(%rdx,%rax,4), %rdx
	movq	(%rcx,%rax,8), %rdi
	movq	%rbp, %rcx
	salq	$2, %rdx
	call	fwrite@PLT
	movl	12(%rbx), %eax
	cmpl	%r12d, %eax
	ja	.L31
	testl	%eax, %eax
	je	.L32
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L33:
	movq	88(%rbx), %rdx
	movl	%r12d, %eax
	movq	72(%rbx), %rcx
	movl	$1, %esi
	addl	$1, %r12d
	movslq	(%rdx,%rax,4), %rdx
	movq	(%rcx,%rax,8), %rdi
	movq	%rbp, %rcx
	salq	$2, %rdx
	call	fwrite@PLT
	cmpl	%r12d, 12(%rbx)
	ja	.L33
.L32:
	popq	%rbx
	.cfi_def_cfa_offset 24
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	jmp	fclose@PLT
	.cfi_endproc
.LFE13427:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC9:
	.string	"basic_string::_M_construct null not valid"
	.text
	.align 2
	.p2align 4
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0:
.LFB13449:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	testq	%rdx, %rdx
	je	.L53
	testq	%rsi, %rsi
	je	.L69
.L53:
	subq	%rbp, %r12
	movq	%r12, (%rsp)
	cmpq	$15, %r12
	ja	.L70
	movq	(%rbx), %rdi
	cmpq	$1, %r12
	jne	.L56
	movzbl	0(%rbp), %eax
	movb	%al, (%rdi)
	movq	(%rsp), %r12
	movq	(%rbx), %rdi
.L57:
	movq	%r12, 8(%rbx)
	movb	$0, (%rdi,%r12)
	movq	8(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L71
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L56:
	.cfi_restore_state
	testq	%r12, %r12
	je	.L57
	jmp	.L55
	.p2align 4,,10
	.p2align 3
.L70:
	movq	%rbx, %rdi
	movq	%rsp, %rsi
	xorl	%edx, %edx
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm@PLT
	movq	%rax, (%rbx)
	movq	%rax, %rdi
	movq	(%rsp), %rax
	movq	%rax, 16(%rbx)
.L55:
	movq	%r12, %rdx
	movq	%rbp, %rsi
	call	memcpy@PLT
	movq	(%rsp), %r12
	movq	(%rbx), %rdi
	jmp	.L57
.L69:
	leaq	.LC9(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
.L71:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE13449:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
	.section	.rodata._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv.str1.8,"aMS",@progbits,1
	.align 8
.LC10:
	.string	"void IVSparse::SparseMatrix<T, indexT, 2, columnMajor>::userChecks() [with T = int; indexT = int; bool columnMajor = true]"
	.align 8
.LC11:
	.string	"(innerDim > 1 || outerDim > 1 || nnz > 1) && \"The matrix must have at least one row, column, and nonzero value\""
	.align 8
.LC12:
	.string	"(innerDim < std::numeric_limits<indexT>::max() && outerDim < std::numeric_limits<indexT>::max()) && \"The number of rows and columns must be less than the maximum value of the index type\""
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv:
.LFB13426:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	8(%rdi), %eax
	cmpl	$1, %eax
	jbe	.L83
	cmpl	$2147483646, %eax
	ja	.L76
	movl	12(%rdi), %eax
.L74:
	cmpl	$2147483646, %eax
	ja	.L76
.L75:
	movq	(%rdi), %rax
	leaq	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv(%rip), %rdx
	movq	8(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L77
	movl	40(%rdi), %eax
	movl	%eax, %edx
	movl	%eax, %esi
	movl	%eax, %ecx
	shrl	$8, %edx
	shrl	$16, %esi
	shrl	$24, %ecx
	cmpb	$4, %al
	jne	.L84
	testb	%dl, %dl
	jne	.L85
	cmpb	$1, %sil
	jne	.L86
	cmpl	$1, %ecx
	jne	.L87
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L83:
	.cfi_restore_state
	movl	12(%rdi), %eax
	cmpl	$1, %eax
	ja	.L74
	cmpl	$1, 24(%rdi)
	ja	.L75
	leaq	.LC10(%rip), %rcx
	movl	$44, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC11(%rip), %rdi
	call	__assert_fail@PLT
	.p2align 4,,10
	.p2align 3
.L77:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	*%rax
.L76:
	.cfi_restore_state
	leaq	.LC10(%rip), %rcx
	movl	$48, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC12(%rip), %rdi
	call	__assert_fail@PLT
.L87:
	leaq	.LC2(%rip), %rcx
	movl	$37, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	__assert_fail@PLT
.L84:
	leaq	.LC2(%rip), %rcx
	movl	$34, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	__assert_fail@PLT
.L86:
	leaq	.LC2(%rip), %rcx
	movl	$36, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC6(%rip), %rdi
	call	__assert_fail@PLT
.L85:
	leaq	.LC2(%rip), %rcx
	movl	$35, %edx
	leaq	.LC3(%rip), %rsi
	leaq	.LC5(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE13426:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv
	.section	.text._ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_,comdat
	.align 2
	.p2align 4
	.type	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0, @function
_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0:
.LFB13451:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, 16(%rsp)
	testq	%rdi, %rdi
	je	.L88
.L124:
	movq	16(%rsp), %rax
	movq	24(%rax), %rax
	movq	%rax, (%rsp)
	testq	%rax, %rax
	je	.L90
.L121:
	movq	(%rsp), %rax
	movq	24(%rax), %rax
	movq	%rax, 8(%rsp)
	testq	%rax, %rax
	je	.L91
.L118:
	movq	8(%rsp), %rax
	movq	24(%rax), %r15
	testq	%r15, %r15
	je	.L92
.L115:
	movq	24(%r15), %r12
	testq	%r12, %r12
	je	.L93
.L112:
	movq	24(%r12), %rbp
	testq	%rbp, %rbp
	je	.L94
.L109:
	movq	24(%rbp), %r13
	testq	%r13, %r13
	je	.L95
.L106:
	movq	24(%r13), %r14
	testq	%r14, %r14
	je	.L96
.L103:
	movq	24(%r14), %r9
	testq	%r9, %r9
	je	.L97
.L100:
	movq	24(%r9), %rdi
	movq	%r9, 24(%rsp)
	call	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0
	movq	24(%rsp), %r9
	movq	40(%r9), %rdi
	movq	56(%r9), %rsi
	movq	16(%r9), %rbx
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	je	.L98
	call	_ZdlPvm@PLT
	movq	24(%rsp), %rdi
	movl	$64, %esi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	jne	.L99
.L97:
	movq	40(%r14), %rdi
	movq	16(%r14), %rbx
	testq	%rdi, %rdi
	je	.L101
	movq	56(%r14), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L101:
	movl	$64, %esi
	movq	%r14, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L96
	movq	%rbx, %r14
	jmp	.L103
.L94:
	movq	40(%r12), %rdi
	movq	16(%r12), %rbx
	testq	%rdi, %rdi
	je	.L110
	movq	56(%r12), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L110:
	movl	$64, %esi
	movq	%r12, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L93
	movq	%rbx, %r12
	jmp	.L112
.L98:
	movl	$64, %esi
	movq	%r9, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L97
.L99:
	movq	%rbx, %r9
	jmp	.L100
	.p2align 4,,10
	.p2align 3
.L95:
	movq	40(%rbp), %rdi
	movq	16(%rbp), %rbx
	testq	%rdi, %rdi
	je	.L107
	movq	56(%rbp), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L107:
	movl	$64, %esi
	movq	%rbp, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L94
	movq	%rbx, %rbp
	jmp	.L109
.L93:
	movq	40(%r15), %rdi
	movq	16(%r15), %rbx
	testq	%rdi, %rdi
	je	.L113
	movq	56(%r15), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L113:
	movl	$64, %esi
	movq	%r15, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L92
	movq	%rbx, %r15
	jmp	.L115
	.p2align 4,,10
	.p2align 3
.L96:
	movq	40(%r13), %rdi
	movq	16(%r13), %rbx
	testq	%rdi, %rdi
	je	.L104
	movq	56(%r13), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L104:
	movl	$64, %esi
	movq	%r13, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L95
	movq	%rbx, %r13
	jmp	.L106
.L92:
	movq	8(%rsp), %r15
	movq	40(%r15), %rdi
	movq	16(%r15), %rbx
	testq	%rdi, %rdi
	je	.L116
	movq	56(%r15), %rax
	movq	%rax, %rsi
	movq	%rax, 8(%rsp)
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	movl	$64, %esi
	movq	%r15, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L91
.L117:
	movq	%rbx, 8(%rsp)
	jmp	.L118
.L116:
	movq	%r15, %rdi
	movl	$64, %esi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	jne	.L117
.L91:
	movq	(%rsp), %r15
	movq	40(%r15), %rdi
	movq	16(%r15), %rbx
	testq	%rdi, %rdi
	je	.L119
	movq	56(%r15), %rax
	movq	%rax, %rsi
	movq	%rax, (%rsp)
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	movl	$64, %esi
	movq	%r15, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L90
.L120:
	movq	%rbx, (%rsp)
	jmp	.L121
.L119:
	movq	%r15, %rdi
	movl	$64, %esi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	jne	.L120
.L90:
	movq	16(%rsp), %r14
	movq	40(%r14), %rdi
	movq	16(%r14), %rbx
	testq	%rdi, %rdi
	je	.L122
	movq	56(%r14), %rax
	movq	%rax, %rsi
	movq	%rax, (%rsp)
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
	movl	$64, %esi
	movq	%r14, %rdi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	je	.L88
.L123:
	movq	%rbx, 16(%rsp)
	jmp	.L124
.L122:
	movq	%r14, %rdi
	movl	$64, %esi
	call	_ZdlPvm@PLT
	testq	%rbx, %rbx
	jne	.L123
.L88:
	addq	$40, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13451:
	.size	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0, .-_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0
	.section	.text._ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_,comdat
	.align 2
	.p2align 4
	.type	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0, @function
_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0:
.LFB13454:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	movl	$64, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdx, %rbx
	leaq	8(%rbp), %r15
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	call	_Znwm@PLT
	pxor	%xmm0, %xmm0
	movq	%rax, %r12
	movq	(%rbx), %rax
	movl	(%rax), %r13d
	movups	%xmm0, 40(%r12)
	movq	$0, 56(%r12)
	movl	%r13d, 32(%r12)
	cmpq	%r15, %r14
	je	.L237
	movl	32(%r14), %edx
	movq	%r14, %rbx
	cmpl	%edx, %r13d
	jge	.L191
	movq	24(%rbp), %r14
	cmpq	%r14, %rbx
	je	.L215
	movq	%rbx, %rdi
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base@PLT
	movq	%rax, %r8
	cmpl	32(%rax), %r13d
	jg	.L238
	movq	16(%rbp), %rbx
	testq	%rbx, %rbx
	jne	.L197
	jmp	.L239
	.p2align 4,,10
	.p2align 3
.L218:
	movq	%rax, %rbx
.L197:
	movl	32(%rbx), %edx
	movq	24(%rbx), %rax
	cmpl	%edx, %r13d
	cmovl	16(%rbx), %rax
	setl	%cl
	testq	%rax, %rax
	jne	.L218
	movq	%rbx, %r8
	testb	%cl, %cl
	je	.L206
.L195:
	cmpq	%rbx, %r14
	je	.L220
.L236:
	movq	%rbx, %rdi
	call	_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base@PLT
	movq	%rbx, %r8
	movl	32(%rax), %edx
	movq	%rax, %rbx
	cmpl	%edx, %r13d
	jg	.L189
.L190:
	movq	%r12, %rdi
	movl	$64, %esi
	movq	%rbx, %r12
	call	_ZdlPvm@PLT
.L233:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r12, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L191:
	.cfi_restore_state
	movl	%edx, 12(%rsp)
	jle	.L190
	movq	32(%rbp), %r8
	cmpq	%r8, %r14
	je	.L221
	movq	%r14, %rdi
	call	_ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base@PLT
	movq	%rax, %r8
	cmpl	32(%rax), %r13d
	jge	.L200
	cmpq	$0, 24(%r14)
	movl	12(%rsp), %edx
	jne	.L229
	movq	%r14, %r8
	jmp	.L201
	.p2align 4,,10
	.p2align 3
.L237:
	cmpq	$0, 40(%rbp)
	je	.L182
	movq	32(%rbp), %r8
	cmpl	32(%r8), %r13d
	jle	.L182
.L183:
	xorl	%eax, %eax
	jmp	.L209
	.p2align 4,,10
	.p2align 3
.L182:
	movq	16(%rbp), %rbx
	testq	%rbx, %rbx
	jne	.L186
	movq	%r15, %rbx
.L184:
	cmpq	%rbx, 24(%rbp)
	jne	.L236
	movq	%rbx, %r8
	xorl	%ebx, %ebx
	jmp	.L194
	.p2align 4,,10
	.p2align 3
.L212:
	movq	%rax, %rbx
.L186:
	movl	32(%rbx), %edx
	movq	24(%rbx), %rax
	cmpl	%edx, %r13d
	cmovl	16(%rbx), %rax
	setl	%cl
	testq	%rax, %rax
	jne	.L212
	movq	%rbx, %r8
	testb	%cl, %cl
	jne	.L184
.L206:
	cmpl	%edx, %r13d
	jle	.L190
.L189:
	xorl	%ebx, %ebx
	testq	%r8, %r8
	je	.L190
.L194:
	testq	%rbx, %rbx
	setne	%al
.L209:
	cmpq	%r8, %r15
	je	.L229
	testb	%al, %al
	je	.L240
.L229:
	movl	$1, %edi
.L202:
	movq	%r15, %rcx
	movq	%r8, %rdx
	movq	%r12, %rsi
	call	_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_@PLT
	addq	$1, 40(%rbp)
	jmp	.L233
	.p2align 4,,10
	.p2align 3
.L238:
	cmpq	$0, 24(%rax)
	je	.L183
	movq	%rbx, %r8
	jmp	.L194
	.p2align 4,,10
	.p2align 3
.L240:
	movl	32(%r8), %edx
.L201:
	xorl	%edi, %edi
	cmpl	%edx, %r13d
	setl	%dil
	jmp	.L202
	.p2align 4,,10
	.p2align 3
.L215:
	movq	%r14, %r8
.L192:
	movq	%r14, %rbx
	jmp	.L194
	.p2align 4,,10
	.p2align 3
.L200:
	movq	16(%rbp), %rbx
	testq	%rbx, %rbx
	jne	.L205
	movq	%r15, %rbx
	jmp	.L203
	.p2align 4,,10
	.p2align 3
.L225:
	movq	%rax, %rbx
.L205:
	movl	32(%rbx), %edx
	movq	24(%rbx), %rax
	cmpl	%edx, %r13d
	cmovl	16(%rbx), %rax
	setl	%cl
	testq	%rax, %rax
	jne	.L225
	movq	%rbx, %r8
	testb	%cl, %cl
	je	.L206
.L203:
	cmpq	%rbx, 24(%rbp)
	jne	.L236
	movq	%rbx, %r8
	jmp	.L189
.L220:
	movq	%r14, %r8
	jmp	.L189
	.p2align 4,,10
	.p2align 3
.L221:
	xorl	%r14d, %r14d
	jmp	.L192
.L239:
	movq	%r15, %rbx
	jmp	.L195
	.cfi_endproc
.LFE13454:
	.size	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0, .-_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0
	.section	.rodata._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv.str1.1,"aMS",@progbits,1
.LC13:
	.string	"IVSparse Matrix"
.LC14:
	.string	"Error: Index out of bounds"
.LC15:
	.string	" "
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv:
.LFB13428:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	leaq	_ZSt4cout(%rip), %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movq	_ZSt4cout(%rip), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %r12
	testq	%r12, %r12
	je	.L245
	cmpb	$0, 56(%r12)
	movq	%rdi, %r15
	je	.L243
	movsbl	67(%r12), %esi
.L244:
	movq	%rbp, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	$15, %edx
	leaq	.LC13(%rip), %rsi
	movq	%rbp, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cout(%rip), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %r12
	testq	%r12, %r12
	je	.L245
	cmpb	$0, 56(%r12)
	je	.L246
	movsbl	67(%r12), %esi
.L247:
	movq	%rbp, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	16(%r15), %eax
	cmpl	$99, %eax
	ja	.L248
	movl	20(%r15), %edx
	cmpl	$99, %edx
	ja	.L249
	xorl	%r13d, %r13d
	leaq	.LC15(%rip), %rbx
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %r12
	testl	%eax, %eax
	je	.L249
.L250:
	xorl	%r14d, %r14d
	testl	%edx, %edx
	je	.L260
.L261:
	cmpl	%r13d, %eax
	jbe	.L265
	movq	80(%r15), %rdx
	testq	%rdx, %rdx
	je	.L288
	movl	%r14d, %eax
	movl	(%rdx,%rax,4), %esi
	testl	%esi, %esi
	je	.L254
	movq	56(%r15), %rdx
	movq	(%rdx,%rax,8), %r9
	movq	64(%r15), %rdx
	movq	(%rdx,%rax,8), %r8
	movq	72(%r15), %rdx
	movq	(%rdx,%rax,8), %rcx
	movq	88(%r15), %rdx
	testq	%rdx, %rdx
	je	.L288
	movl	(%rdx,%rax,4), %edi
	movl	(%rcx), %esi
	movl	(%r8), %eax
	testl	%edi, %edi
	jle	.L288
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L259:
	cmpl	%esi, %r13d
	je	.L337
.L255:
	addl	$1, %edx
	subl	$1, %eax
	jne	.L256
	cmpl	%edi, %edx
	jge	.L257
	movl	4(%rcx), %esi
	movl	4(%r8), %eax
	addq	$4, %r9
	addq	$4, %rcx
	addq	$4, %r8
	cmpl	%esi, %r13d
	jne	.L255
.L337:
	movl	(%r9), %esi
.L254:
	movq	%rbp, %rdi
	addl	$1, %r14d
	call	_ZNSolsEi@PLT
	movl	$1, %edx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpl	%r14d, 20(%r15)
	jbe	.L260
	movl	16(%r15), %eax
	jmp	.L261
.L248:
	cmpl	$100, %eax
	je	.L249
	cmpl	$100, 20(%r15)
	jbe	.L249
	xorl	%r13d, %r13d
	leaq	.LC15(%rip), %rbx
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %r12
.L264:
	xorl	%r14d, %r14d
	.p2align 4,,10
	.p2align 3
.L278:
	cmpl	%eax, %r13d
	jnb	.L265
	cmpl	%r14d, 20(%r15)
	jbe	.L265
	movq	80(%r15), %rax
	testq	%rax, %rax
	je	.L296
	movl	(%rax,%r14,4), %esi
	leaq	0(,%r14,4), %rdx
	testl	%esi, %esi
	je	.L269
	movq	56(%r15), %rax
	movq	(%rax,%r14,8), %r9
	movq	64(%r15), %rax
	movq	(%rax,%r14,8), %r8
	movq	72(%r15), %rax
	movq	(%rax,%r14,8), %rcx
	movq	88(%r15), %rax
	testq	%rax, %rax
	je	.L296
	movl	(%rax,%rdx), %edi
	movl	(%rcx), %esi
	movl	(%r8), %eax
	testl	%edi, %edi
	jle	.L296
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L274:
	cmpl	%esi, %r13d
	je	.L338
.L270:
	addl	$1, %edx
	subl	$1, %eax
	jne	.L271
	cmpl	%edi, %edx
	jge	.L272
	movl	4(%rcx), %esi
	movl	4(%r8), %eax
	addq	$4, %r9
	addq	$4, %r8
	addq	$4, %rcx
	cmpl	%esi, %r13d
	jne	.L270
.L338:
	movl	(%r9), %esi
.L269:
	movq	%rbp, %rdi
	addq	$1, %r14
	call	_ZNSolsEi@PLT
	movl	$1, %edx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpq	$100, %r14
	je	.L339
	movl	16(%r15), %eax
	jmp	.L278
.L249:
	movq	_ZSt4cout(%rip), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %r12
	testq	%r12, %r12
	je	.L245
	cmpb	$0, 56(%r12)
	je	.L279
	movsbl	67(%r12), %esi
.L280:
	movq	%rbp, %rdi
	call	_ZNSo3putEc@PLT
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	movq	%rax, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_ZNSo5flushEv@PLT
	.p2align 4,,10
	.p2align 3
.L256:
	.cfi_restore_state
	movl	4(%rcx), %esi
	addq	$4, %rcx
.L257:
	cmpl	%edi, %edx
	jne	.L259
.L288:
	xorl	%esi, %esi
	jmp	.L254
.L260:
	movq	0(%rbp), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %r14
	testq	%r14, %r14
	je	.L245
	cmpb	$0, 56(%r14)
	je	.L262
	movsbl	67(%r14), %esi
.L263:
	movq	%rbp, %rdi
	addl	$1, %r13d
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	16(%r15), %eax
	cmpl	%r13d, %eax
	jbe	.L249
	movl	20(%r15), %edx
	jmp	.L250
.L262:
	movq	%r14, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r14), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%r12, %rax
	je	.L263
	movq	%r14, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L263
.L246:
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r12), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L247
	movq	%r12, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L247
.L243:
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r12), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L244
	movq	%r12, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L244
.L279:
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r12), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L280
	movq	%r12, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L280
	.p2align 4,,10
	.p2align 3
.L271:
	movl	4(%rcx), %esi
	addq	$4, %rcx
.L272:
	cmpl	%edi, %edx
	jne	.L274
.L296:
	xorl	%esi, %esi
	jmp	.L269
.L339:
	movq	0(%rbp), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %r14
	testq	%r14, %r14
	je	.L245
	cmpb	$0, 56(%r14)
	je	.L276
	movsbl	67(%r14), %esi
.L277:
	movq	%rbp, %rdi
	addl	$1, %r13d
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	cmpl	$100, %r13d
	je	.L249
	movl	16(%r15), %eax
	jmp	.L264
.L276:
	movq	%r14, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r14), %rax
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%r12, %rax
	je	.L277
	movq	%r14, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L277
.L265:
	leaq	_ZSt4cerr(%rip), %rbp
	movl	$26, %edx
	leaq	.LC14(%rip), %rsi
	movq	%rbp, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	_ZSt4cerr(%rip), %rax
	movq	-24(%rax), %rax
	movq	240(%rbp,%rax), %r12
	testq	%r12, %r12
	je	.L245
	cmpb	$0, 56(%r12)
	je	.L267
	movsbl	67(%r12), %esi
.L268:
	movq	%rbp, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	$1, %edi
	call	exit@PLT
.L267:
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r12), %rax
	movl	$10, %esi
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L268
	movq	%r12, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L268
.L245:
	call	_ZSt16__throw_bad_castv@PLT
	.cfi_endproc
.LFE13428:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv
	.section	.text.unlikely._ZN5Eigen8internal19throw_std_bad_allocEv,"axG",@progbits,_ZN5Eigen8internal19throw_std_bad_allocEv,comdat
	.weak	_ZN5Eigen8internal19throw_std_bad_allocEv
	.type	_ZN5Eigen8internal19throw_std_bad_allocEv, @function
_ZN5Eigen8internal19throw_std_bad_allocEv:
.LFB4798:
	.cfi_startproc
	endbr64
	pushq	%rax
	.cfi_def_cfa_offset 16
	popq	%rax
	.cfi_def_cfa_offset 8
	movl	$8, %edi
	pushq	%rax
	.cfi_def_cfa_offset 16
	call	__cxa_allocate_exception@PLT
	movq	_ZNSt9bad_allocD1Ev@GOTPCREL(%rip), %rdx
	leaq	_ZTISt9bad_alloc(%rip), %rsi
	movq	%rax, %rdi
	leaq	16+_ZTVSt9bad_alloc(%rip), %rax
	movq	%rax, (%rdi)
	call	__cxa_throw@PLT
	.cfi_endproc
.LFE4798:
	.size	_ZN5Eigen8internal19throw_std_bad_allocEv, .-_ZN5Eigen8internal19throw_std_bad_allocEv
	.text
	.align 2
	.p2align 4
	.globl	_ZNK8IVSparse16SparseMatrixBase4rowsEv
	.type	_ZNK8IVSparse16SparseMatrixBase4rowsEv, @function
_ZNK8IVSparse16SparseMatrixBase4rowsEv:
.LFB10802:
	.cfi_startproc
	endbr64
	movl	16(%rdi), %eax
	ret
	.cfi_endproc
.LFE10802:
	.size	_ZNK8IVSparse16SparseMatrixBase4rowsEv, .-_ZNK8IVSparse16SparseMatrixBase4rowsEv
	.align 2
	.p2align 4
	.globl	_ZNK8IVSparse16SparseMatrixBase4colsEv
	.type	_ZNK8IVSparse16SparseMatrixBase4colsEv, @function
_ZNK8IVSparse16SparseMatrixBase4colsEv:
.LFB10803:
	.cfi_startproc
	endbr64
	movl	20(%rdi), %eax
	ret
	.cfi_endproc
.LFE10803:
	.size	_ZNK8IVSparse16SparseMatrixBase4colsEv, .-_ZNK8IVSparse16SparseMatrixBase4colsEv
	.align 2
	.p2align 4
	.globl	_ZNK8IVSparse16SparseMatrixBase9innerSizeEv
	.type	_ZNK8IVSparse16SparseMatrixBase9innerSizeEv, @function
_ZNK8IVSparse16SparseMatrixBase9innerSizeEv:
.LFB10804:
	.cfi_startproc
	endbr64
	movl	8(%rdi), %eax
	ret
	.cfi_endproc
.LFE10804:
	.size	_ZNK8IVSparse16SparseMatrixBase9innerSizeEv, .-_ZNK8IVSparse16SparseMatrixBase9innerSizeEv
	.align 2
	.p2align 4
	.globl	_ZNK8IVSparse16SparseMatrixBase9outerSizeEv
	.type	_ZNK8IVSparse16SparseMatrixBase9outerSizeEv, @function
_ZNK8IVSparse16SparseMatrixBase9outerSizeEv:
.LFB10805:
	.cfi_startproc
	endbr64
	movl	12(%rdi), %eax
	ret
	.cfi_endproc
.LFE10805:
	.size	_ZNK8IVSparse16SparseMatrixBase9outerSizeEv, .-_ZNK8IVSparse16SparseMatrixBase9outerSizeEv
	.align 2
	.p2align 4
	.globl	_ZNK8IVSparse16SparseMatrixBase8nonZerosEv
	.type	_ZNK8IVSparse16SparseMatrixBase8nonZerosEv, @function
_ZNK8IVSparse16SparseMatrixBase8nonZerosEv:
.LFB10806:
	.cfi_startproc
	endbr64
	movl	24(%rdi), %eax
	ret
	.cfi_endproc
.LFE10806:
	.size	_ZNK8IVSparse16SparseMatrixBase8nonZerosEv, .-_ZNK8IVSparse16SparseMatrixBase8nonZerosEv
	.align 2
	.p2align 4
	.globl	_ZNK8IVSparse16SparseMatrixBase8byteSizeEv
	.type	_ZNK8IVSparse16SparseMatrixBase8byteSizeEv, @function
_ZNK8IVSparse16SparseMatrixBase8byteSizeEv:
.LFB10807:
	.cfi_startproc
	endbr64
	movq	32(%rdi), %rax
	ret
	.cfi_endproc
.LFE10807:
	.size	_ZNK8IVSparse16SparseMatrixBase8byteSizeEv, .-_ZNK8IVSparse16SparseMatrixBase8byteSizeEv
	.section	.text.unlikely,"ax",@progbits
.LCOLDB16:
	.text
.LHOTB16:
	.p2align 4
	.globl	_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_
	.type	_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_, @function
_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_:
.LFB11287:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA11287
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movq	64(%rdi), %rax
	leaq	16(%rsp), %r12
	movb	$0, 16(%rsp)
	movq	%r12, (%rsp)
	movq	%rsp, %r9
	movq	$0, 8(%rsp)
	testq	%rax, %rax
	je	.L349
	movq	48(%rdi), %r8
	testq	%r8, %r8
	je	.L370
	cmpq	%r8, %rax
	ja	.L370
.L350:
	movq	56(%rdi), %rcx
	xorl	%edx, %edx
	xorl	%esi, %esi
	movq	%r9, %rdi
	subq	%rcx, %r8
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm@PLT
.LEHE0:
.L352:
	movq	64(%rbx), %rax
	leaq	48(%rsp), %r13
	movb	$0, 48(%rsp)
	leaq	32(%rsp), %rdi
	movq	%r13, 32(%rsp)
	movq	$0, 40(%rsp)
	testq	%rax, %rax
	je	.L380
	movq	48(%rbx), %r8
	testq	%r8, %r8
	je	.L371
	cmpq	%r8, %rax
	ja	.L371
.L357:
	movq	56(%rbx), %rcx
	xorl	%edx, %edx
	xorl	%esi, %esi
	subq	%rcx, %r8
.LEHB1:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm@PLT
.LEHE1:
.L359:
	movq	32(%rsp), %r14
	movq	(%rsp), %rbp
	movq	%r14, %rsi
	movq	%rbp, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	sete	%r15b
	cmpq	%r13, %r14
	je	.L361
	movq	48(%rsp), %rax
	movq	%r14, %rdi
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
	movq	(%rsp), %rbp
.L361:
	cmpq	%r12, %rbp
	je	.L348
	movq	16(%rsp), %rax
	movq	%rbp, %rdi
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L348:
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L381
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movl	%r15d, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L371:
	.cfi_restore_state
	movq	%rax, %r8
	jmp	.L357
	.p2align 4,,10
	.p2align 3
.L370:
	movq	%rax, %r8
	jmp	.L350
	.p2align 4,,10
	.p2align 3
.L349:
	leaq	96(%rdi), %rsi
	movq	%r9, %rdi
.LEHB2:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_assignERKS4_@PLT
.LEHE2:
	jmp	.L352
	.p2align 4,,10
	.p2align 3
.L380:
	leaq	96(%rbx), %rsi
.LEHB3:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_assignERKS4_@PLT
.LEHE3:
	jmp	.L359
.L381:
	call	__stack_chk_fail@PLT
.L369:
	endbr64
	movq	%rax, %rbp
	jmp	.L355
.L368:
	endbr64
	movq	%rax, %rbp
	jmp	.L362
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA11287:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE11287-.LLSDACSB11287
.LLSDACSB11287:
	.uleb128 .LEHB0-.LFB11287
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L369-.LFB11287
	.uleb128 0
	.uleb128 .LEHB1-.LFB11287
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L368-.LFB11287
	.uleb128 0
	.uleb128 .LEHB2-.LFB11287
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L369-.LFB11287
	.uleb128 0
	.uleb128 .LEHB3-.LFB11287
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L368-.LFB11287
	.uleb128 0
.LLSDACSE11287:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC11287
	.type	_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_.cold, @function
_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_.cold:
.LFSB11287:
.L355:
	.cfi_def_cfa_offset 144
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	(%rsp), %rdi
	cmpq	%r12, %rdi
	je	.L356
	movq	16(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L356:
	movq	%rbp, %rdi
.LEHB4:
	call	_Unwind_Resume@PLT
.L362:
	movq	32(%rsp), %rdi
	cmpq	%r13, %rdi
	je	.L363
	movq	48(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L363:
	movq	(%rsp), %rdi
	cmpq	%r12, %rdi
	je	.L365
	movq	16(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L365:
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE4:
	.cfi_endproc
.LFE11287:
	.section	.gcc_except_table
.LLSDAC11287:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC11287-.LLSDACSBC11287
.LLSDACSBC11287:
	.uleb128 .LEHB4-.LCOLDB16
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSEC11287:
	.section	.text.unlikely
	.text
	.size	_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_, .-_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_
	.section	.text.unlikely
	.size	_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_.cold, .-_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_.cold
.LCOLDE16:
	.text
.LHOTE16:
	.section	.text._ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev,"axG",@progbits,_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev
	.type	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev, @function
_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev:
.LFB11746:
	.cfi_startproc
	endbr64
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	%rax, (%rdi)
	movq	72(%rdi), %rdi
	leaq	88(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L383
	movq	88(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L383:
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	leaq	56(%rbx), %rdi
	movq	%rax, (%rbx)
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_ZNSt6localeD1Ev@PLT
	.cfi_endproc
.LFE11746:
	.size	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev, .-_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev
	.weak	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED1Ev
	.set	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED1Ev,_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED2Ev
	.section	.text._ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED0Ev,"axG",@progbits,_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED0Ev
	.type	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED0Ev, @function
_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED0Ev:
.LFB11748:
	.cfi_startproc
	endbr64
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rdi, %rbp
	movq	%rax, (%rdi)
	movq	72(%rdi), %rdi
	leaq	88(%rbp), %rax
	cmpq	%rax, %rdi
	je	.L386
	movq	88(%rbp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L386:
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	leaq	56(%rbp), %rdi
	movq	%rax, 0(%rbp)
	call	_ZNSt6localeD1Ev@PLT
	movq	%rbp, %rdi
	movl	$104, %esi
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	_ZdlPvm@PLT
	.cfi_endproc
.LFE11748:
	.size	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED0Ev, .-_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED0Ev
	.section	.text.unlikely
.LCOLDB19:
	.text
.LHOTB19:
	.p2align 4
	.type	_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0, @function
_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0:
.LFB13459:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA13459
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdx, %rbx
	subq	$536, %rsp
	.cfi_def_cfa_offset 592
	movq	%fs:40, %rax
	movq	%rax, 520(%rsp)
	leaq	64+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, %xmm3
	movq	%rax, %xmm4
	movq	8(%rsi), %rax
	movhps	.LC17(%rip), %xmm3
	movhps	.LC18(%rip), %xmm4
	movaps	%xmm3, 32(%rsp)
	movaps	%xmm4, 48(%rsp)
	testq	%rax, %rax
	je	.L465
	movl	228(%rdx), %edx
	movq	%rsi, %r14
	movq	$0, 80(%rsp)
	movq	$0, 88(%rsp)
	leal	2(%rdx), %ecx
	cmpl	$1, %ecx
	ja	.L466
.L391:
	movq	$0, 8(%rsp)
	testb	$1, 232(%rbx)
	je	.L467
.L429:
	movq	0(%rbp), %rax
	movq	-24(%rax), %r12
	addq	%rbp, %r12
	cmpb	$0, 225(%r12)
	movq	16(%r12), %rax
	movq	%rax, (%rsp)
	je	.L407
	movzbl	224(%r12), %r13d
.L408:
	movq	8(%rbx), %rdx
	movq	(%rbx), %rsi
	movq	%rbp, %rdi
	xorl	%r12d, %r12d
.LEHB5:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpq	$0, 8(%r14)
	movq	8(%rsp), %r15
	jg	.L412
	jmp	.L423
	.p2align 4,,10
	.p2align 3
.L421:
	addq	$1, %r12
	cmpq	%r12, %rax
	jle	.L423
.L422:
	movq	168(%rbx), %rdx
	movq	160(%rbx), %rsi
	movq	%rbp, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
.L412:
	movq	72(%rbx), %rdx
	movq	64(%rbx), %rsi
	movq	%rbp, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	testq	%r15, %r15
	je	.L415
	movq	0(%rbp), %rax
	movzbl	224(%rbx), %ecx
	movq	-24(%rax), %rdx
	addq	%rbp, %rdx
	cmpb	$0, 225(%rdx)
	je	.L468
.L416:
	movb	%cl, 224(%rdx)
	movq	0(%rbp), %rax
	movq	-24(%rax), %rax
	movq	%r15, 16(%rbp,%rax)
.L415:
	movq	(%r14), %rax
	movq	%rbp, %rdi
	movl	(%rax,%r12,4), %esi
	call	_ZNSolsEi@PLT
	movq	104(%rbx), %rdx
	movq	96(%rbx), %rsi
	movq	%rbp, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	8(%r14), %rax
	leaq	-1(%rax), %rdx
	cmpq	%r12, %rdx
	jle	.L421
	movq	136(%rbx), %rdx
	movq	128(%rbx), %rsi
	movq	%rbp, %rdi
	addq	$1, %r12
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpq	%r12, 8(%r14)
	jg	.L422
.L423:
	movq	40(%rbx), %rdx
	movq	32(%rbx), %rsi
	movq	%rbp, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	cmpq	$0, 80(%rsp)
	je	.L414
	movq	0(%rbp), %rax
	movq	88(%rsp), %rbx
	movq	-24(%rax), %rax
	movq	%rbx, 8(%rbp,%rax)
.L414:
	cmpq	$0, 8(%rsp)
	je	.L388
	movq	0(%rbp), %rax
	movq	-24(%rax), %rbx
	addq	%rbp, %rbx
	cmpb	$0, 225(%rbx)
	je	.L469
.L425:
	movb	%r13b, 224(%rbx)
	movq	0(%rbp), %rax
	movq	(%rsp), %rbx
	movq	-24(%rax), %rax
	movq	%rbx, 16(%rbp,%rax)
.L388:
	movq	520(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L464
	addq	$536, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L468:
	.cfi_restore_state
	movq	240(%rdx), %rdi
	testq	%rdi, %rdi
	je	.L417
	cmpb	$0, 56(%rdi)
	jne	.L419
	movb	%cl, 32(%rsp)
	movq	%rdx, 24(%rsp)
	movq	%rdi, 16(%rsp)
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
.LEHE5:
	movq	16(%rsp), %rdi
	movq	24(%rsp), %rdx
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rcx
	movq	(%rdi), %rax
	movq	48(%rax), %rax
	cmpq	%rcx, %rax
	movzbl	32(%rsp), %ecx
	jne	.L470
.L419:
	movb	$1, 225(%rdx)
	jmp	.L416
	.p2align 4,,10
	.p2align 3
.L466:
	movslq	%edx, %rcx
	movq	%rcx, 80(%rsp)
	testq	%rcx, %rcx
	je	.L391
	movq	(%rdi), %rdx
	movq	-24(%rdx), %rdi
	addq	%rbp, %rdi
	movq	%rdi, %rdx
	movq	8(%rdi), %rdi
	movq	%rcx, 8(%rdx)
	movq	%rdi, 88(%rsp)
	jmp	.L391
	.p2align 4,,10
	.p2align 3
.L467:
	testq	%rax, %rax
	jle	.L429
	leaq	128(%rsp), %rax
	movq	$0, (%rsp)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %r15
	leaq	256(%rsp), %r12
	movq	%rax, 64(%rsp)
	jmp	.L406
	.p2align 4,,10
	.p2align 3
.L471:
	cmpq	%r8, %rax
	ja	.L442
.L397:
	movq	184(%rsp), %rcx
	xorl	%edx, %edx
	xorl	%esi, %esi
	subq	%rcx, %r8
.LEHB6:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_replaceEmmPKcm@PLT
.LEHE6:
.L399:
	movq	8(%rsp), %rcx
	movq	104(%rsp), %rax
	movq	96(%rsp), %rdi
	cmpq	%rax, %rcx
	cmovge	%rcx, %rax
	movq	%rax, 8(%rsp)
	cmpq	%r13, %rdi
	je	.L401
	movq	112(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L401:
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movdqa	32(%rsp), %xmm2
	movq	224(%rsp), %rdi
	movq	%rax, 128(%rsp)
	addq	$80, %rax
	movq	%rax, 256(%rsp)
	movaps	%xmm2, 144(%rsp)
	cmpq	24(%rsp), %rdi
	je	.L405
	movq	240(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L405:
	movq	16(%rsp), %rdi
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 152(%rsp)
	call	_ZNSt6localeD1Ev@PLT
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%r12, %rdi
	movq	-24(%rax), %rax
	movq	%rcx, 128(%rsp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 144(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 144(%rsp,%rax)
	movq	-24(%r15), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%r15, 128(%rsp)
	movq	%rcx, 128(%rsp,%rax)
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 256(%rsp)
	movq	$0, 136(%rsp)
	call	_ZNSt8ios_baseD2Ev@PLT
	addq	$1, (%rsp)
	movq	(%rsp), %rax
	cmpq	8(%r14), %rax
	jge	.L429
.L406:
	movq	%r12, %rdi
	call	_ZNSt8ios_baseC2Ev@PLT
	pxor	%xmm0, %xmm0
	movq	64(%rsp), %rdi
	xorl	%esi, %esi
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movups	%xmm0, 488(%rsp)
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 256(%rsp)
	xorl	%eax, %eax
	movw	%ax, 480(%rsp)
	movups	%xmm0, 504(%rsp)
	movq	-24(%r15), %rax
	movq	$0, 472(%rsp)
	movq	%r15, 128(%rsp)
	movq	%rcx, 128(%rsp,%rax)
	movq	$0, 136(%rsp)
	addq	-24(%r15), %rdi
.LEHB7:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE7:
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	leaq	144(%rsp), %r13
	xorl	%esi, %esi
	movq	-24(%rax), %rdi
	movq	%rax, 144(%rsp)
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	addq	%r13, %rdi
	movq	%rax, (%rdi)
.LEHB8:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE8:
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	pxor	%xmm0, %xmm0
	movdqa	48(%rsp), %xmm1
	movq	-24(%rax), %rax
	movq	%rcx, 128(%rsp,%rax)
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, 128(%rsp)
	addq	$80, %rax
	movq	%rax, 256(%rsp)
	leaq	208(%rsp), %rax
	movq	%rax, %rdi
	movq	%rax, 16(%rsp)
	movaps	%xmm1, 144(%rsp)
	movaps	%xmm0, 160(%rsp)
	movaps	%xmm0, 176(%rsp)
	movaps	%xmm0, 192(%rsp)
	call	_ZNSt6localeC1Ev@PLT
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%r12, %rdi
	movl	$24, 216(%rsp)
	movq	%rax, 152(%rsp)
	leaq	240(%rsp), %rax
	movq	%rax, 24(%rsp)
	movq	%rax, 224(%rsp)
	leaq	152(%rsp), %rax
	movq	%rax, %rsi
	movb	$0, 240(%rsp)
	movq	$0, 232(%rsp)
	movq	%rax, 72(%rsp)
.LEHB9:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE9:
	movq	0(%rbp), %rax
	movq	%r12, %rdi
	movq	-24(%rax), %rsi
	addq	%rbp, %rsi
.LEHB10:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE7copyfmtERKS2_@PLT
	movq	(%r14), %rax
	movq	(%rsp), %rcx
	movq	%r13, %rdi
	movl	(%rax,%rcx,4), %esi
	call	_ZNSolsEi@PLT
.LEHE10:
	leaq	112(%rsp), %r13
	movb	$0, 112(%rsp)
	leaq	96(%rsp), %rdi
	movq	192(%rsp), %rax
	movq	%r13, 96(%rsp)
	movq	$0, 104(%rsp)
	testq	%rax, %rax
	je	.L396
	movq	176(%rsp), %r8
	testq	%r8, %r8
	jne	.L471
.L442:
	movq	%rax, %r8
	jmp	.L397
	.p2align 4,,10
	.p2align 3
.L396:
	leaq	224(%rsp), %rsi
.LEHB11:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_assignERKS4_@PLT
.LEHE11:
	jmp	.L399
	.p2align 4,,10
	.p2align 3
.L407:
	movq	240(%r12), %r15
	testq	%r15, %r15
	je	.L417
	cmpb	$0, 56(%r15)
	je	.L410
	movzbl	89(%r15), %r13d
.L411:
	movb	%r13b, 224(%r12)
	movb	$1, 225(%r12)
	jmp	.L408
	.p2align 4,,10
	.p2align 3
.L465:
	movq	8(%rdx), %rdx
	movq	(%rbx), %rsi
.LEHB12:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movq	520(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L464
	movq	40(%rbx), %rdx
	movq	32(%rbx), %rsi
	addq	$536, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	.p2align 4,,10
	.p2align 3
.L410:
	.cfi_restore_state
	movq	%r15, %rdi
	movl	$32, %r13d
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r15), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L411
	movl	$32, %esi
	movq	%r15, %rdi
	call	*%rax
	movl	%eax, %r13d
	jmp	.L411
	.p2align 4,,10
	.p2align 3
.L470:
	movb	%cl, 24(%rsp)
	movl	$32, %esi
	movq	%rdx, 16(%rsp)
	call	*%rax
	movq	16(%rsp), %rdx
	movzbl	24(%rsp), %ecx
	movb	$1, 225(%rdx)
	jmp	.L416
	.p2align 4,,10
	.p2align 3
.L469:
	movq	240(%rbx), %r12
	testq	%r12, %r12
	je	.L417
	cmpb	$0, 56(%r12)
	jne	.L427
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	(%r12), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L472
.L427:
	movb	$1, 225(%rbx)
	jmp	.L425
.L472:
	movl	$32, %esi
	movq	%r12, %rdi
	call	*%rax
	jmp	.L427
.L464:
	call	__stack_chk_fail@PLT
.L417:
	call	_ZSt16__throw_bad_castv@PLT
.LEHE12:
.L441:
	endbr64
	movq	%rax, %rbp
	jmp	.L402
.L438:
	endbr64
	movq	%rax, %rbx
	jmp	.L394
.L439:
	endbr64
	movq	%rax, %rbx
	jmp	.L395
.L440:
	endbr64
	movq	%rax, %rbx
	jmp	.L393
.L437:
	endbr64
	movq	%rax, %rbp
	jmp	.L404
	.section	.gcc_except_table
.LLSDA13459:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE13459-.LLSDACSB13459
.LLSDACSB13459:
	.uleb128 .LEHB5-.LFB13459
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB13459
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L441-.LFB13459
	.uleb128 0
	.uleb128 .LEHB7-.LFB13459
	.uleb128 .LEHE7-.LEHB7
	.uleb128 .L438-.LFB13459
	.uleb128 0
	.uleb128 .LEHB8-.LFB13459
	.uleb128 .LEHE8-.LEHB8
	.uleb128 .L440-.LFB13459
	.uleb128 0
	.uleb128 .LEHB9-.LFB13459
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L439-.LFB13459
	.uleb128 0
	.uleb128 .LEHB10-.LFB13459
	.uleb128 .LEHE10-.LEHB10
	.uleb128 .L437-.LFB13459
	.uleb128 0
	.uleb128 .LEHB11-.LFB13459
	.uleb128 .LEHE11-.LEHB11
	.uleb128 .L441-.LFB13459
	.uleb128 0
	.uleb128 .LEHB12-.LFB13459
	.uleb128 .LEHE12-.LEHB12
	.uleb128 0
	.uleb128 0
.LLSDACSE13459:
	.text
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC13459
	.type	_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0.cold, @function
_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0.cold:
.LFSB13459:
.L402:
	.cfi_def_cfa_offset 592
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	movq	96(%rsp), %rdi
	cmpq	%r13, %rdi
	je	.L404
	movq	112(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L404:
	movq	64(%rsp), %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbp, %rdi
.LEHB13:
	call	_Unwind_Resume@PLT
.L393:
	movq	-24(%r15), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%r15, 128(%rsp)
	movq	%rcx, 128(%rsp,%rax)
	movq	$0, 136(%rsp)
.L394:
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	%r12, %rdi
	movq	%rax, 256(%rsp)
	call	_ZNSt8ios_baseD2Ev@PLT
	movq	%rbx, %rdi
	call	_Unwind_Resume@PLT
.LEHE13:
.L395:
	movq	72(%rsp), %rdi
	call	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED1Ev
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	-24(%rax), %rax
	movq	%rcx, 128(%rsp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 144(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 144(%rsp,%rax)
	movq	-24(%r15), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%r15, 128(%rsp)
	movq	%rcx, 128(%rsp,%rax)
	movq	$0, 136(%rsp)
	jmp	.L394
	.cfi_endproc
.LFE13459:
	.section	.gcc_except_table
.LLSDAC13459:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC13459-.LLSDACSBC13459
.LLSDACSBC13459:
	.uleb128 .LEHB13-.LCOLDB19
	.uleb128 .LEHE13-.LEHB13
	.uleb128 0
	.uleb128 0
.LLSDACSEC13459:
	.section	.text.unlikely
	.text
	.size	_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0, .-_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0
	.section	.text.unlikely
	.size	_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0.cold, .-_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0.cold
.LCOLDE19:
	.text
.LHOTE19:
	.section	.text._ZN5Eigen12SparseMatrixIiLi0EiED2Ev,"axG",@progbits,_ZN5Eigen12SparseMatrixIiLi0EiED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN5Eigen12SparseMatrixIiLi0EiED2Ev
	.type	_ZN5Eigen12SparseMatrixIiLi0EiED2Ev, @function
_ZN5Eigen12SparseMatrixIiLi0EiED2Ev:
.LFB11767:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	24(%rdi), %rdi
	call	free@PLT
	movq	32(%rbx), %rdi
	call	free@PLT
	movq	40(%rbx), %rdi
	call	free@PLT
	movq	48(%rbx), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.cfi_endproc
.LFE11767:
	.size	_ZN5Eigen12SparseMatrixIiLi0EiED2Ev, .-_ZN5Eigen12SparseMatrixIiLi0EiED2Ev
	.weak	_ZN5Eigen12SparseMatrixIiLi0EiED1Ev
	.set	_ZN5Eigen12SparseMatrixIiLi0EiED1Ev,_ZN5Eigen12SparseMatrixIiLi0EiED2Ev
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev:
.LFB11773:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	16+_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE(%rip), %rax
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rax, (%rdi)
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L476
	call	_ZdaPv@PLT
.L476:
	movq	56(%rbx), %r8
	testq	%r8, %r8
	je	.L477
	movl	12(%rbx), %eax
	testl	%eax, %eax
	je	.L478
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L481:
	movq	(%r8,%rbp,8), %rdi
	testq	%rdi, %rdi
	je	.L479
	call	free@PLT
	movl	12(%rbx), %edx
	addq	$1, %rbp
	movq	56(%rbx), %r8
	movq	%rdx, %rax
	cmpq	%rbp, %rdx
	ja	.L481
.L478:
	movq	%r8, %rdi
	call	free@PLT
.L477:
	movq	64(%rbx), %r8
	testq	%r8, %r8
	je	.L482
	movl	12(%rbx), %eax
	testl	%eax, %eax
	je	.L483
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L486:
	movq	(%r8,%rbp,8), %rdi
	testq	%rdi, %rdi
	je	.L484
	call	free@PLT
	movl	12(%rbx), %edx
	addq	$1, %rbp
	movq	64(%rbx), %r8
	movq	%rdx, %rax
	cmpq	%rbp, %rdx
	ja	.L486
.L483:
	movq	%r8, %rdi
	call	free@PLT
.L482:
	movq	72(%rbx), %r8
	testq	%r8, %r8
	je	.L487
	movl	12(%rbx), %eax
	testl	%eax, %eax
	je	.L488
	xorl	%ebp, %ebp
	.p2align 4,,10
	.p2align 3
.L491:
	movq	(%r8,%rbp,8), %rdi
	testq	%rdi, %rdi
	je	.L489
	call	free@PLT
	movl	12(%rbx), %edx
	addq	$1, %rbp
	movq	72(%rbx), %r8
	movq	%rdx, %rax
	cmpq	%rbp, %rdx
	ja	.L491
.L488:
	movq	%r8, %rdi
	call	free@PLT
.L487:
	movq	80(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L492
	call	free@PLT
.L492:
	movq	88(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L475
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.p2align 4,,10
	.p2align 3
.L489:
	.cfi_restore_state
	addq	$1, %rbp
	movl	%eax, %edx
	cmpq	%rbp, %rdx
	ja	.L491
	jmp	.L488
	.p2align 4,,10
	.p2align 3
.L479:
	addq	$1, %rbp
	movl	%eax, %edx
	cmpq	%rbp, %rdx
	ja	.L481
	jmp	.L478
	.p2align 4,,10
	.p2align 3
.L484:
	addq	$1, %rbp
	movl	%eax, %edx
	cmpq	%rbp, %rdx
	ja	.L486
	jmp	.L483
	.p2align 4,,10
	.p2align 3
.L475:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11773:
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED1Ev
	.set	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED1Ev,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED2Ev
	.section	.text._ZN5Eigen8IOFormatD2Ev,"axG",@progbits,_ZN5Eigen8IOFormatD5Ev,comdat
	.align 2
	.p2align 4
	.weak	_ZN5Eigen8IOFormatD2Ev
	.type	_ZN5Eigen8IOFormatD2Ev, @function
_ZN5Eigen8IOFormatD2Ev:
.LFB11799:
	.cfi_startproc
	endbr64
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	192(%rdi), %rdi
	leaq	208(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L520
	movq	208(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L520:
	movq	160(%rbx), %rdi
	leaq	176(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L521
	movq	176(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L521:
	movq	128(%rbx), %rdi
	leaq	144(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L522
	movq	144(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L522:
	movq	96(%rbx), %rdi
	leaq	112(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L523
	movq	112(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L523:
	movq	64(%rbx), %rdi
	leaq	80(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L524
	movq	80(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L524:
	movq	32(%rbx), %rdi
	leaq	48(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L525
	movq	48(%rbx), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L525:
	movq	(%rbx), %rdi
	leaq	16(%rbx), %rax
	cmpq	%rax, %rdi
	je	.L519
	movq	16(%rbx), %rsi
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	addq	$1, %rsi
	jmp	_ZdlPvm@PLT
	.p2align 4,,10
	.p2align 3
.L519:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11799:
	.size	_ZN5Eigen8IOFormatD2Ev, .-_ZN5Eigen8IOFormatD2Ev
	.weak	_ZN5Eigen8IOFormatD1Ev
	.set	_ZN5Eigen8IOFormatD1Ev,_ZN5Eigen8IOFormatD2Ev
	.section	.rodata._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE.str1.8,"aMS",@progbits,1
	.align 8
.LC20:
	.string	"Eigen::Matrix<Type, -1, 1> IVSparse::SparseMatrix<T, indexT, 2, columnMajor>::vectorMultiply(Eigen::Matrix<Type, -1, 1>&) [with T = int; indexT = int; bool columnMajor = true]"
	.align 8
.LC21:
	.string	"IVSparse/src/VCSC/VCSC_BLAS.hpp"
	.align 8
.LC22:
	.string	"vec.rows() == outerDim && \"The vector must be the same size as the number of columns in the matrix!\""
	.align 8
.LC23:
	.string	"void* Eigen::internal::aligned_malloc(std::size_t)"
	.align 8
.LC24:
	.string	"/usr/local/include/Eigen/src/Core/util/Memory.h"
	.align 8
.LC25:
	.string	"(size<16 || (std::size_t(result)%16)==0) && \"System's malloc returned an unaligned pointer. Compile with EIGEN_MALLOC_ALREADY_ALIGNED=0 to fallback to handmade aligned memory allocator.\""
	.align 8
.LC26:
	.string	"Eigen::DenseCoeffsBase<Derived, 1>::Scalar& Eigen::DenseCoeffsBase<Derived, 1>::operator()(Eigen::Index) [with Derived = Eigen::Matrix<int, -1, 1>; Eigen::DenseCoeffsBase<Derived, 1>::Scalar = int; Eigen::Index = long int]"
	.align 8
.LC27:
	.string	"/usr/local/include/Eigen/src/Core/DenseCoeffsBase.h"
	.section	.rodata._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE.str1.1,"aMS",@progbits,1
.LC28:
	.string	"index >= 0 && index < size()"
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE:
.LFB12105:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12105
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$56, %rsp
	.cfi_def_cfa_offset 112
	movl	12(%rsi), %eax
	movq	%rdi, 40(%rsp)
	movq	%rdx, 24(%rsp)
	cmpq	8(%rdx), %rax
	jne	.L573
	movl	8(%rsi), %ebp
	movq	%rsi, %rbx
	movq	$0, (%rdi)
	movq	%rax, %r12
	movq	$0, 8(%rdi)
	xorl	%ecx, %ecx
	testq	%rbp, %rbp
	jne	.L574
.L530:
	cmpl	$-1, %r12d
	je	.L528
	movq	80(%rbx), %rax
	xorl	%r10d, %r10d
	xorl	%r8d, %r8d
	movq	$0, 8(%rsp)
	movq	%rax, 16(%rsp)
	leal	1(%r12), %eax
	movq	%rax, 32(%rsp)
	.p2align 4,,10
	.p2align 3
.L544:
	movq	16(%rsp), %rax
	testq	%rax, %rax
	je	.L546
	movl	(%rax,%r8), %edx
	testl	%edx, %edx
	je	.L536
	movq	56(%rbx), %rax
	movq	(%rax,%r10), %r12
	movq	64(%rbx), %rax
	movq	(%rax,%r10), %r14
	movq	72(%rbx), %rax
	movq	(%rax,%r10), %r9
	movq	88(%rbx), %rax
	testq	%rax, %rax
	je	.L536
	movl	(%rax,%r8), %r13d
	movl	(%r9), %r11d
	movl	(%r14), %esi
	testl	%r13d, %r13d
	jle	.L536
	movq	24(%rsp), %rax
	movq	8(%rsp), %rdx
	cmpq	%rdx, 8(%rax)
	jle	.L537
	movq	(%rax), %r15
	xorl	%edi, %edi
	.p2align 4,,10
	.p2align 3
.L543:
	movl	(%r15,%r8), %eax
	imull	(%r12), %eax
	movl	%eax, %edx
	movslq	%r11d, %rax
	testq	%rax, %rax
	js	.L537
	cmpq	%rax, %rbp
	jle	.L537
	addl	%edx, (%rcx,%rax,4)
	addl	$1, %edi
	subl	$1, %esi
	jne	.L540
	cmpl	%r13d, %edi
	jge	.L541
	movl	4(%r14), %esi
	movl	4(%r9), %r11d
	addq	$4, %r12
	addq	$4, %r9
	addq	$4, %r14
	jmp	.L543
	.p2align 4,,10
	.p2align 3
.L540:
	movl	4(%r9), %r11d
	addq	$4, %r9
.L541:
	cmpl	%r13d, %edi
	jne	.L543
.L536:
	movq	16(%rsp), %rax
	movl	(%rax,%r8), %eax
	testl	%eax, %eax
	je	.L546
	movq	56(%rbx), %rax
	movq	(%rax,%r10), %r12
	movq	64(%rbx), %rax
	movq	(%rax,%r10), %r14
	movq	72(%rbx), %rax
	movq	(%rax,%r10), %r9
	movq	88(%rbx), %rax
	testq	%rax, %rax
	je	.L546
	movl	(%rax,%r8), %r13d
	movl	(%r9), %r11d
	movl	(%r14), %esi
	testl	%r13d, %r13d
	jle	.L546
	movq	24(%rsp), %rax
	movq	8(%rsp), %rdx
	cmpq	%rdx, 8(%rax)
	jle	.L537
	movq	(%rax), %r15
	xorl	%edi, %edi
	.p2align 4,,10
	.p2align 3
.L550:
	movl	(%r15,%r8), %eax
	imull	(%r12), %eax
	movl	%eax, %edx
	movslq	%r11d, %rax
	testq	%rax, %rax
	js	.L537
	cmpq	%rax, %rbp
	jle	.L537
	addl	%edx, (%rcx,%rax,4)
	addl	$1, %edi
	subl	$1, %esi
	jne	.L547
	cmpl	%edi, %r13d
	jle	.L548
	movl	4(%r14), %esi
	movl	4(%r9), %r11d
	addq	$4, %r12
	addq	$4, %r9
	addq	$4, %r14
	jmp	.L550
	.p2align 4,,10
	.p2align 3
.L547:
	movl	4(%r9), %r11d
	addq	$4, %r9
.L548:
	cmpl	%edi, %r13d
	jne	.L550
.L546:
	addq	$1, 8(%rsp)
	addq	$4, %r8
	movq	8(%rsp), %rax
	addq	$8, %r10
	cmpq	32(%rsp), %rax
	jne	.L544
.L528:
	movq	40(%rsp), %rax
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L574:
	.cfi_restore_state
	leaq	0(,%rbp,4), %r13
	movl	$1, %esi
	movq	%r13, %rdi
	call	calloc@PLT
	movq	%rax, %rcx
	cmpq	$15, %r13
	ja	.L575
.L531:
	testq	%rax, %rax
	je	.L576
	movq	40(%rsp), %rsi
	movq	%rax, (%rsi)
	movq	%rbp, 8(%rsi)
	jmp	.L530
.L575:
	testb	$15, %al
	je	.L531
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
.L537:
	leaq	.LC26(%rip), %rcx
	movl	$429, %edx
	leaq	.LC27(%rip), %rsi
	leaq	.LC28(%rip), %rdi
	call	__assert_fail@PLT
.L573:
	leaq	.LC20(%rip), %rcx
	movl	$51, %edx
	leaq	.LC21(%rip), %rsi
	leaq	.LC22(%rip), %rdi
	call	__assert_fail@PLT
.L576:
.LEHB14:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE14:
.L553:
	endbr64
	movq	%rax, %rbp
.L534:
	movq	40(%rsp), %rax
	movq	(%rax), %rdi
	call	free@PLT
	movq	%rbp, %rdi
.LEHB15:
	call	_Unwind_Resume@PLT
.LEHE15:
	.cfi_endproc
.LFE12105:
	.section	.gcc_except_table
.LLSDA12105:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12105-.LLSDACSB12105
.LLSDACSB12105:
	.uleb128 .LEHB14-.LFB12105
	.uleb128 .LEHE14-.LEHB14
	.uleb128 .L553-.LFB12105
	.uleb128 0
	.uleb128 .LEHB15-.LFB12105
	.uleb128 .LEHE15-.LEHB15
	.uleb128 0
	.uleb128 0
.LLSDACSE12105:
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE,comdat
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE
	.section	.rodata._ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_.str1.1,"aMS",@progbits,1
.LC29:
	.string	"vector::_M_realloc_insert"
	.section	.text._ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_,"axG",@progbits,_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_
	.type	_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_, @function
_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_:
.LFB12156:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdx, %r15
	movabsq	$1152921504606846975, %rdx
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %r12
	movq	(%rdi), %r14
	movq	%r12, %rax
	subq	%r14, %rax
	sarq	$3, %rax
	cmpq	%rdx, %rax
	je	.L597
	testq	%rax, %rax
	movl	$1, %edx
	movq	%rdi, %rbp
	movq	%rsi, %r13
	cmovne	%rax, %rdx
	xorl	%ecx, %ecx
	addq	%rdx, %rax
	movq	%rsi, %rdx
	setc	%cl
	subq	%r14, %rdx
	testq	%rcx, %rcx
	jne	.L590
	testq	%rax, %rax
	jne	.L582
	xorl	%ebx, %ebx
	xorl	%edi, %edi
.L588:
	movq	(%r15), %rax
	subq	%r13, %r12
	leaq	8(%rdi,%rdx), %r15
	movq	%rdi, %xmm0
	movq	%rax, (%rdi,%rdx)
	leaq	(%r15,%r12), %rax
	movq	%rax, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movaps	%xmm0, (%rsp)
	testq	%rdx, %rdx
	jg	.L598
	testq	%r12, %r12
	jg	.L586
	testq	%r14, %r14
	jne	.L596
.L587:
	movdqa	(%rsp), %xmm2
	movq	%rbx, 16(%rbp)
	movups	%xmm2, 0(%rbp)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L598:
	.cfi_restore_state
	movq	%r14, %rsi
	call	memmove@PLT
	testq	%r12, %r12
	jg	.L586
.L596:
	movq	16(%rbp), %rsi
	movq	%r14, %rdi
	subq	%r14, %rsi
	call	_ZdlPvm@PLT
	jmp	.L587
	.p2align 4,,10
	.p2align 3
.L586:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%r15, %rdi
	call	memcpy@PLT
	testq	%r14, %r14
	je	.L587
	jmp	.L596
	.p2align 4,,10
	.p2align 3
.L590:
	movabsq	$9223372036854775800, %rbx
.L581:
	movq	%rbx, %rdi
	movq	%rdx, (%rsp)
	call	_Znwm@PLT
	movq	(%rsp), %rdx
	movq	%rax, %rdi
	addq	%rax, %rbx
	jmp	.L588
	.p2align 4,,10
	.p2align 3
.L582:
	movabsq	$1152921504606846975, %rcx
	cmpq	%rcx, %rax
	cmova	%rcx, %rax
	leaq	0(,%rax,8), %rbx
	jmp	.L581
.L597:
	leaq	.LC29(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE12156:
	.size	_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_, .-_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_
	.section	.text._ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_,"axG",@progbits,_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_,comdat
	.align 2
	.p2align 4
	.weak	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_
	.type	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_, @function
_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_:
.LFB12644:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdx, %r15
	movabsq	$2305843009213693951, %rdx
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	8(%rdi), %r12
	movq	(%rdi), %r14
	movq	%r12, %rax
	subq	%r14, %rax
	sarq	$2, %rax
	cmpq	%rdx, %rax
	je	.L619
	testq	%rax, %rax
	movl	$1, %edx
	movq	%rdi, %rbp
	movq	%rsi, %r13
	cmovne	%rax, %rdx
	xorl	%ecx, %ecx
	addq	%rdx, %rax
	movq	%rsi, %rdx
	setc	%cl
	subq	%r14, %rdx
	testq	%rcx, %rcx
	jne	.L612
	testq	%rax, %rax
	jne	.L604
	xorl	%ebx, %ebx
	xorl	%edi, %edi
.L610:
	movl	(%r15), %eax
	subq	%r13, %r12
	leaq	4(%rdi,%rdx), %r15
	movq	%rdi, %xmm0
	movl	%eax, (%rdi,%rdx)
	leaq	(%r15,%r12), %rax
	movq	%rax, %xmm1
	punpcklqdq	%xmm1, %xmm0
	movaps	%xmm0, (%rsp)
	testq	%rdx, %rdx
	jg	.L620
	testq	%r12, %r12
	jg	.L608
	testq	%r14, %r14
	jne	.L618
.L609:
	movdqa	(%rsp), %xmm2
	movq	%rbx, 16(%rbp)
	movups	%xmm2, 0(%rbp)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L620:
	.cfi_restore_state
	movq	%r14, %rsi
	call	memmove@PLT
	testq	%r12, %r12
	jg	.L608
.L618:
	movq	16(%rbp), %rsi
	movq	%r14, %rdi
	subq	%r14, %rsi
	call	_ZdlPvm@PLT
	jmp	.L609
	.p2align 4,,10
	.p2align 3
.L608:
	movq	%r12, %rdx
	movq	%r13, %rsi
	movq	%r15, %rdi
	call	memcpy@PLT
	testq	%r14, %r14
	je	.L609
	jmp	.L618
	.p2align 4,,10
	.p2align 3
.L612:
	movabsq	$9223372036854775804, %rbx
.L603:
	movq	%rbx, %rdi
	movq	%rdx, (%rsp)
	call	_Znwm@PLT
	movq	(%rsp), %rdx
	movq	%rax, %rdi
	addq	%rax, %rbx
	jmp	.L610
	.p2align 4,,10
	.p2align 3
.L604:
	movabsq	$2305843009213693951, %rcx
	cmpq	%rcx, %rax
	cmova	%rcx, %rax
	leaq	0(,%rax,4), %rbx
	jmp	.L603
.L619:
	leaq	.LC29(%rip), %rdi
	call	_ZSt20__throw_length_errorPKc@PLT
	.cfi_endproc
.LFE12644:
	.size	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_, .-_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_,comdat
	.align 2
	.p2align 4
	.weak	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_
	.type	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_, @function
_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_:
.LFB12072:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12072
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rdi, %r15
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$200, %rsp
	.cfi_def_cfa_offset 256
	movq	%rdx, 104(%rsp)
	leaq	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv(%rip), %rdx
	movq	%rsi, 96(%rsp)
	movq	%rcx, 80(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 184(%rsp)
	movq	(%rdi), %rax
	movq	(%rax), %rax
	cmpq	%rdx, %rax
	jne	.L622
	movl	$16842756, 40(%rdi)
.L623:
	movl	$4, 44(%r15)
	movl	$24, %edi
.LEHB16:
	call	_Znam@PLT
.LEHE16:
	movq	8(%r15), %rdx
	movl	12(%r15), %ebx
	movq	%rax, 48(%r15)
	movq	%rdx, 4(%rax)
	movl	24(%r15), %edx
	leaq	0(,%rbx,8), %rbp
	movl	$2, (%rax)
	movq	%rbp, %rdi
	movl	%edx, 12(%rax)
	movq	40(%r15), %rdx
	movq	%rdx, 16(%rax)
	call	malloc@PLT
	movq	%rbp, %rdi
	movq	%rax, 56(%r15)
	call	malloc@PLT
	movq	%rbp, %rdi
	leaq	0(,%rbx,4), %rbp
	movq	%rax, 64(%r15)
	call	malloc@PLT
	movq	%rbp, %rdi
	movq	%rax, 72(%r15)
	call	malloc@PLT
	movq	%rbp, %rdi
	movq	%rax, 80(%r15)
	call	malloc@PLT
	movq	%rax, 88(%r15)
	testl	%ebx, %ebx
	je	.L624
	leaq	120(%rsp), %rax
	movl	$0, 72(%rsp)
	leaq	136(%rsp), %rbx
	movq	%rax, 88(%rsp)
	leaq	128(%rsp), %rax
	movq	$0, 48(%rsp)
	movq	%rax, 24(%rsp)
	.p2align 4,,10
	.p2align 3
.L664:
	movq	48(%rsp), %rax
	addl	$1, 72(%rsp)
	movl	$0, 136(%rsp)
	leaq	0(,%rax,4), %rdi
	movq	%rax, 56(%rsp)
	movq	%rdi, 64(%rsp)
	movq	80(%rsp), %rdi
	movq	$0, 144(%rsp)
	movl	(%rdi,%rax,4), %esi
	movl	72(%rsp), %eax
	movq	%rbx, 152(%rsp)
	movq	%rbx, 160(%rsp)
	movq	%rax, 48(%rsp)
	leaq	(%rdi,%rax,4), %rax
	movq	$0, 168(%rsp)
	movl	%esi, 8(%rsp)
	movq	%rax, 16(%rsp)
	cmpl	(%rax), %esi
	je	.L625
	jge	.L732
	movslq	8(%rsp), %r12
	movq	96(%rsp), %rax
	movl	$1, %r13d
	xorl	%r14d, %r14d
	salq	$2, %r12
	leaq	(%rax,%r12), %rbp
	addq	104(%rsp), %r12
	.p2align 4,,10
	.p2align 3
.L650:
	testq	%r14, %r14
	je	.L629
	movl	0(%rbp), %edx
	movq	%r14, %rax
	movq	%rbx, %rdi
	.p2align 4,,10
	.p2align 3
.L633:
	movq	16(%rax), %rsi
	movq	24(%rax), %rcx
	cmpl	32(%rax), %edx
	jle	.L630
.L734:
	testq	%rcx, %rcx
	je	.L733
	movq	%rcx, %rax
	movq	16(%rax), %rsi
	movq	24(%rax), %rcx
	cmpl	32(%rax), %edx
	jg	.L734
.L630:
	testq	%rsi, %rsi
	je	.L632
	movq	%rax, %rdi
	movq	%rsi, %rax
	jmp	.L633
	.p2align 4,,10
	.p2align 3
.L733:
	movq	%rdi, %rax
.L632:
	cmpq	%rbx, %rax
	je	.L629
	cmpl	32(%rax), %edx
	jge	.L735
.L629:
	movl	$4, %edi
	movl	(%r12), %r14d
.LEHB17:
	call	_Znwm@PLT
	movq	144(%rsp), %rsi
	leaq	4(%rax), %rdi
	movq	%rax, 32(%rsp)
	movq	%rdi, 40(%rsp)
	movl	%r14d, (%rax)
	testq	%rsi, %rsi
	je	.L736
	movl	0(%rbp), %ecx
	movq	%rbx, %rdi
	jmp	.L647
	.p2align 4,,10
	.p2align 3
.L738:
	testq	%rdx, %rdx
	je	.L737
	movq	%rdx, %rax
.L645:
	movq	%rax, %rsi
.L647:
	movq	16(%rsi), %rax
	movq	24(%rsi), %rdx
	cmpl	32(%rsi), %ecx
	jg	.L738
	testq	%rax, %rax
	je	.L646
	movq	%rsi, %rdi
	jmp	.L645
	.p2align 4,,10
	.p2align 3
.L735:
	movq	%rbx, %rsi
	jmp	.L637
	.p2align 4,,10
	.p2align 3
.L740:
	testq	%rcx, %rcx
	je	.L739
	movq	%rcx, %rax
.L635:
	movq	%rax, %r14
.L637:
	movq	16(%r14), %rax
	movq	24(%r14), %rcx
	cmpl	32(%r14), %edx
	jg	.L740
	testq	%rax, %rax
	je	.L636
	movq	%r14, %rsi
	jmp	.L635
	.p2align 4,,10
	.p2align 3
.L739:
	movq	%rsi, %r14
.L636:
	cmpq	%rbx, %r14
	je	.L638
	cmpl	32(%r14), %edx
	jge	.L639
.L638:
	movq	24(%rsp), %rdi
	leaq	112(%rsp), %rdx
	movq	%r14, %rsi
	movq	%rbp, 112(%rsp)
	call	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0
.LEHE17:
	movq	%rax, %r14
.L639:
	movq	48(%r14), %rsi
	cmpq	56(%r14), %rsi
	je	.L640
	movl	(%r12), %eax
	addq	$4, %rsi
	movl	%eax, -4(%rsi)
	movq	%rsi, 48(%r14)
.L642:
	movl	8(%rsp), %eax
	leaq	1(%r13), %rdx
	addq	$4, %rbp
	addq	$4, %r12
	movq	16(%rsp), %rdi
	movq	144(%rsp), %r14
	addl	%r13d, %eax
	cmpl	%eax, (%rdi)
	jle	.L741
	movq	%rdx, %r13
	jmp	.L650
	.p2align 4,,10
	.p2align 3
.L737:
	movq	%rdi, %rsi
.L646:
	cmpq	%rbx, %rsi
	je	.L643
	cmpl	32(%rsi), %ecx
	jge	.L648
.L643:
	movq	88(%rsp), %rdx
	movq	24(%rsp), %rdi
	movq	%rbp, 120(%rsp)
.LEHB18:
	call	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE22_M_emplace_hint_uniqueIJRKSt21piecewise_construct_tSt5tupleIJRS1_EESG_IJEEEEESt17_Rb_tree_iteratorIS5_ESt23_Rb_tree_const_iteratorIS5_EDpOT_.isra.0
.LEHE18:
	movq	%rax, %rsi
.L648:
	movq	40(%rsp), %rcx
	movq	32(%rsp), %xmm0
	movq	40(%rsi), %rdi
	movq	56(%rsi), %rax
	movq	%rcx, %xmm5
	movq	%rcx, 56(%rsi)
	punpcklqdq	%xmm5, %xmm0
	movups	%xmm0, 40(%rsi)
	testq	%rdi, %rdi
	je	.L642
	subq	%rdi, %rax
	movq	%rax, %rsi
	call	_ZdlPvm@PLT
	jmp	.L642
	.p2align 4,,10
	.p2align 3
.L640:
	leaq	40(%r14), %rdi
	movq	%r12, %rdx
.LEHB19:
	call	_ZNSt6vectorIiSaIiEE17_M_realloc_insertIJRKiEEEvN9__gnu_cxx17__normal_iteratorIPiS1_EEDpOT_
.LEHE19:
	jmp	.L642
	.p2align 4,,10
	.p2align 3
.L741:
	movq	168(%rsp), %r12
	movl	%r13d, 76(%rsp)
	leaq	0(,%r13,4), %r10
	movq	152(%rsp), %r9
	movl	%r12d, 40(%rsp)
	leaq	0(,%r12,4), %rdi
.L627:
	movq	56(%rsp), %rbp
	movq	56(%r15), %r12
	movq	%r9, 16(%rsp)
	movq	%r10, 32(%rsp)
	salq	$3, %rbp
	movq	%rdi, 8(%rsp)
	call	malloc@PLT
	addq	%rbp, %r12
	movq	64(%r15), %r13
	movq	8(%rsp), %rdi
	movq	%rax, (%r12)
	addq	%rbp, %r13
	call	malloc@PLT
	movq	32(%rsp), %rdi
	addq	72(%r15), %rbp
	movq	%rax, 0(%r13)
	call	malloc@PLT
	movq	64(%rsp), %rdi
	movl	40(%rsp), %ecx
	movq	%rax, 0(%rbp)
	movq	%rax, %rsi
	movq	80(%r15), %rax
	movq	16(%rsp), %r9
	movl	%ecx, (%rax,%rdi)
	movq	88(%r15), %rax
	movl	76(%rsp), %ecx
	movl	%ecx, (%rax,%rdi)
	cmpq	%rbx, %r9
	je	.L661
	movq	(%r12), %r12
	movq	0(%r13), %r13
	movq	%r14, 8(%rsp)
	xorl	%ebp, %ebp
	movq	%r9, %rdi
	movq	%r13, %r14
	movq	%r12, %r13
	movq	%rsi, %r12
	.p2align 4,,10
	.p2align 3
.L660:
	movq	40(%rdi), %rcx
	movq	48(%rdi), %rdx
	movl	32(%rdi), %eax
	subq	%rcx, %rdx
	sarq	$2, %rdx
	movl	%eax, 0(%r13)
	movl	%edx, (%r14)
	je	.L654
	leaq	0(,%rbp,4), %rax
	leaq	4(%rcx), %r10
	leaq	(%r12,%rax), %r9
	movq	%r9, %r8
	subq	%r10, %r8
	cmpq	$8, %r8
	jbe	.L655
	leaq	-1(%rdx), %r8
	cmpq	$2, %r8
	jbe	.L655
	movq	%rdx, %r8
	xorl	%eax, %eax
	shrq	$2, %r8
	salq	$4, %r8
	.p2align 4,,10
	.p2align 3
.L656:
	movdqu	(%rcx,%rax), %xmm6
	movups	%xmm6, (%r9,%rax)
	addq	$16, %rax
	cmpq	%rax, %r8
	jne	.L656
	movq	%rdx, %rax
	leaq	(%rdx,%rbp), %r8
	andq	$-4, %rax
	leaq	(%rax,%rbp), %r10
	cmpq	%rax, %rdx
	je	.L659
	movl	(%rcx,%rax,4), %r11d
	leaq	0(,%r10,4), %r9
	movl	%r11d, (%r12,%r10,4)
	leal	1(%rax), %r11d
	movslq	%r11d, %r11
	cmpq	%r11, %rdx
	jbe	.L659
	leaq	0(,%r11,4), %r10
	addl	$2, %eax
	movl	(%rcx,%r11,4), %r11d
	cltq
	movl	%r11d, 4(%r12,%r9)
	cmpq	%rax, %rdx
	jbe	.L659
	movl	4(%rcx,%r10), %eax
	movl	%eax, 8(%r12,%r9)
.L659:
	movq	%r8, %rbp
.L654:
	call	_ZSt18_Rb_tree_incrementPSt18_Rb_tree_node_base@PLT
	addq	$4, %r13
	addq	$4, %r14
	movq	%rax, %rdi
	cmpq	%rbx, %rax
	jne	.L660
	movq	8(%rsp), %r14
.L661:
	testq	%r14, %r14
	je	.L628
.L652:
	movq	24(%r14), %rdi
	call	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0
	movq	40(%r14), %rdi
	movq	16(%r14), %rbp
	testq	%rdi, %rdi
	je	.L662
	movq	56(%r14), %rsi
	subq	%rdi, %rsi
	call	_ZdlPvm@PLT
.L662:
	movl	$64, %esi
	movq	%r14, %rdi
	call	_ZdlPvm@PLT
	testq	%rbp, %rbp
	je	.L628
	movq	%rbp, %r14
	jmp	.L652
	.p2align 4,,10
	.p2align 3
.L655:
	subq	%rax, %rcx
	leaq	(%rdx,%rbp), %r8
	movq	%rbp, %rax
	.p2align 4,,10
	.p2align 3
.L658:
	movl	(%rcx,%rax,4), %edx
	movl	%edx, (%r12,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r8
	jne	.L658
	jmp	.L659
.L625:
	movq	80(%r15), %rax
	movq	64(%rsp), %rdi
	movl	$0, (%rax,%rdi)
	movq	88(%r15), %rax
	movl	$0, (%rax,%rdi)
	movq	56(%r15), %rax
	movq	56(%rsp), %rdi
	movq	$0, (%rax,%rdi,8)
	movq	64(%r15), %rax
	movq	$0, (%rax,%rdi,8)
	movq	72(%r15), %rax
	movq	$0, (%rax,%rdi,8)
.L628:
	movl	12(%r15), %eax
	cmpl	%eax, 72(%rsp)
	jb	.L664
	movq	(%r15), %rdx
	leaq	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv(%rip), %rcx
	movq	24(%rdx), %rdx
	cmpq	%rcx, %rdx
	jne	.L665
	movl	%eax, %ecx
	salq	$5, %rcx
	addq	$24, %rcx
	movq	%rcx, 32(%r15)
	testl	%eax, %eax
	je	.L621
	leal	-1(%rax), %edx
	movq	80(%r15), %rsi
	movq	88(%r15), %rdi
	cmpl	$4, %edx
	jbe	.L682
	pxor	%xmm2, %xmm2
	movl	%eax, %r8d
	pxor	%xmm5, %xmm5
	xorl	%edx, %edx
	movdqa	.LC1(%rip), %xmm4
	movdqa	%xmm2, %xmm7
	shrl	$2, %r8d
	movdqa	%xmm5, %xmm6
	movdqa	.LC0(%rip), %xmm3
	movdqa	%xmm2, %xmm8
	salq	$4, %r8
	pcmpgtd	%xmm4, %xmm8
	pcmpgtd	%xmm3, %xmm7
.L668:
	movdqu	(%rdi,%rdx), %xmm0
	movdqa	%xmm2, %xmm10
	movdqa	%xmm8, %xmm11
	movdqu	(%rsi,%rdx), %xmm1
	movdqa	%xmm7, %xmm12
	addq	$16, %rdx
	movdqa	%xmm0, %xmm9
	punpckldq	%xmm0, %xmm9
	punpckhdq	%xmm0, %xmm0
	pcmpgtd	%xmm9, %xmm10
	pmuludq	%xmm9, %xmm11
	pmuludq	%xmm4, %xmm9
	pmuludq	%xmm4, %xmm10
	paddq	%xmm11, %xmm10
	movdqa	%xmm2, %xmm11
	psllq	$32, %xmm10
	paddq	%xmm10, %xmm9
	movdqa	%xmm1, %xmm10
	punpckldq	%xmm1, %xmm10
	punpckhdq	%xmm1, %xmm1
	pcmpgtd	%xmm10, %xmm11
	pmuludq	%xmm10, %xmm12
	pmuludq	%xmm3, %xmm10
	pmuludq	%xmm3, %xmm11
	paddq	%xmm12, %xmm11
	psllq	$32, %xmm11
	paddq	%xmm11, %xmm10
	paddq	%xmm10, %xmm9
	movdqa	%xmm8, %xmm10
	paddq	%xmm9, %xmm6
	pmuludq	%xmm0, %xmm10
	movdqa	%xmm2, %xmm9
	pcmpgtd	%xmm0, %xmm9
	pmuludq	%xmm4, %xmm0
	pmuludq	%xmm4, %xmm9
	paddq	%xmm10, %xmm9
	movdqa	%xmm7, %xmm10
	psllq	$32, %xmm9
	pmuludq	%xmm1, %xmm10
	paddq	%xmm9, %xmm0
	movdqa	%xmm2, %xmm9
	pcmpgtd	%xmm1, %xmm9
	pmuludq	%xmm3, %xmm1
	pmuludq	%xmm3, %xmm9
	paddq	%xmm10, %xmm9
	psllq	$32, %xmm9
	paddq	%xmm9, %xmm1
	paddq	%xmm1, %xmm0
	paddq	%xmm0, %xmm5
	cmpq	%rdx, %r8
	jne	.L668
	paddq	%xmm6, %xmm5
	movdqa	%xmm5, %xmm0
	psrldq	$8, %xmm0
	paddq	%xmm0, %xmm5
	movq	%xmm5, %rdx
	addq	%rdx, %rcx
	movl	%eax, %edx
	andl	$-4, %edx
	testb	$3, %al
	je	.L669
.L667:
	movl	%edx, %r8d
	movslq	(%rdi,%r8,4), %r9
	movslq	(%rsi,%r8,4), %r8
	salq	$3, %r8
	leaq	(%r8,%r9,4), %r8
	addq	%r8, %rcx
	leal	1(%rdx), %r8d
	cmpl	%r8d, %eax
	jbe	.L669
	movslq	(%rsi,%r8,4), %r9
	movslq	(%rdi,%r8,4), %r8
	salq	$2, %r8
	leaq	(%r8,%r9,8), %r8
	addq	%r8, %rcx
	leal	2(%rdx), %r8d
	cmpl	%r8d, %eax
	jbe	.L669
	movslq	(%rdi,%r8,4), %r9
	movslq	(%rsi,%r8,4), %r8
	salq	$3, %r8
	leaq	(%r8,%r9,4), %r8
	addq	%r8, %rcx
	leal	3(%rdx), %r8d
	cmpl	%r8d, %eax
	jbe	.L669
	movslq	(%rdi,%r8,4), %r9
	movslq	(%rsi,%r8,4), %r8
	addl	$4, %edx
	salq	$3, %r8
	leaq	(%r8,%r9,4), %r8
	addq	%r8, %rcx
	cmpl	%edx, %eax
	jbe	.L669
	movl	%edx, %eax
	movslq	(%rdi,%rax,4), %rdx
	movslq	(%rsi,%rax,4), %rax
	salq	$3, %rax
	leaq	(%rax,%rdx,4), %rax
	addq	%rax, %rcx
.L669:
	movq	%rcx, 32(%r15)
.L621:
	movq	184(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L731
	addq	$200, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L736:
	.cfi_restore_state
	movq	%rbx, %rsi
	jmp	.L643
.L732:
	movl	$0, 76(%rsp)
	xorl	%r14d, %r14d
	movq	%rbx, %r9
	xorl	%edi, %edi
	movl	$0, 40(%rsp)
	xorl	%r10d, %r10d
	jmp	.L627
.L622:
.LEHB20:
	call	*%rax
	jmp	.L623
.L665:
	movq	184(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L731
	addq	$200, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r15, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	*%rdx
.L624:
	.cfi_restore_state
	movq	(%r15), %rax
	movq	24(%rax), %rdx
	leaq	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv(%rip), %rax
	cmpq	%rax, %rdx
	jne	.L665
	movq	$24, 32(%r15)
	jmp	.L621
.L682:
	xorl	%edx, %edx
	jmp	.L667
.L731:
	call	__stack_chk_fail@PLT
.L684:
	endbr64
	movq	%rax, %rbp
	jmp	.L671
.L683:
	endbr64
	movq	%rax, %rbp
	jmp	.L672
.L671:
	movq	32(%rsp), %rdi
	movl	$4, %esi
	call	_ZdlPvm@PLT
.L672:
	movq	144(%rsp), %rdi
	call	_ZNSt8_Rb_treeIiSt4pairIKiSt6vectorIiSaIiEEESt10_Select1stIS5_ESt4lessIiESaIS5_EE8_M_eraseEPSt13_Rb_tree_nodeIS5_E.isra.0
	movq	%rbp, %rdi
	call	_Unwind_Resume@PLT
.LEHE20:
	.cfi_endproc
.LFE12072:
	.section	.gcc_except_table
.LLSDA12072:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12072-.LLSDACSB12072
.LLSDACSB12072:
	.uleb128 .LEHB16-.LFB12072
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB17-.LFB12072
	.uleb128 .LEHE17-.LEHB17
	.uleb128 .L683-.LFB12072
	.uleb128 0
	.uleb128 .LEHB18-.LFB12072
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L684-.LFB12072
	.uleb128 0
	.uleb128 .LEHB19-.LFB12072
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L683-.LFB12072
	.uleb128 0
	.uleb128 .LEHB20-.LFB12072
	.uleb128 .LEHE20-.LEHB20
	.uleb128 0
	.uleb128 0
.LLSDACSE12072:
	.section	.text._ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_,"axG",@progbits,_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_,comdat
	.size	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_, .-_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_
	.section	.rodata._ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_.str1.8,"aMS",@progbits,1
	.align 8
.LC30:
	.string	"void Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::startVec(Eigen::Index) [with Scalar_ = int; int Options_ = 0; StorageIndex_ = int; Eigen::Index = long int]"
	.align 8
.LC31:
	.string	"/usr/local/include/Eigen/src/SparseCore/SparseMatrix.h"
	.align 8
.LC32:
	.string	"m_outerIndex[outer]==Index(m_data.size()) && \"You must call startVec for each inner vector sequentially\""
	.align 8
.LC33:
	.string	"m_outerIndex[outer+1]==0 && \"You must call startVec for each inner vector sequentially\""
	.align 8
.LC34:
	.ascii	"Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::Scalar&"
	.string	" Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::insertBackByOuterInner(Eigen::Index, Eigen::Index) [with Scalar_ = int; int Options_ = 0; StorageIndex_ = int; Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::Scalar = int; Eigen::Index = long int]"
	.align 8
.LC35:
	.string	"Index(m_outerIndex[outer+1]) == m_data.size() && \"Invalid ordered insertion (invalid outer index)\""
	.align 8
.LC36:
	.string	"(m_outerIndex[outer+1]-m_outerIndex[outer]==0 || m_data.index(m_data.size()-1)<inner) && \"Invalid ordered insertion (invalid inner index)\""
	.section	.text._ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_,"axG",@progbits,_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_,comdat
	.p2align 4
	.weak	_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_
	.type	_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_, @function
_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_:
.LFB12810:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA12810
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movq	%rsi, %r9
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdi, %r14
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$216, %rsp
	.cfi_def_cfa_offset 272
	movq	%fs:40, %rax
	movq	%rax, 200(%rsp)
	movq	8(%rsi), %rax
	movdqu	8(%rax), %xmm0
	movq	(%rax), %rcx
	movhlps	%xmm0, %xmm3
	movdqa	%xmm0, %xmm2
	movq	%rcx, 24(%rsp)
	movq	%xmm0, %rbx
	movq	%xmm3, %r10
	shufpd	$1, %xmm0, %xmm2
	movaps	%xmm2, 32(%rsp)
	testq	%r10, %r10
	jle	.L893
	leaq	0(,%rbx,4), %rsi
	xorl	%edx, %edx
	xorl	%ebp, %ebp
	jmp	.L750
	.p2align 4,,10
	.p2align 3
.L745:
	addq	$1, %rdx
	addq	%rsi, %rcx
	cmpq	%r10, %rdx
	je	.L743
.L750:
	testq	%rbx, %rbx
	jle	.L745
	xorl	%eax, %eax
.L744:
	movl	(%rcx,%rax,4), %r12d
	testl	%r12d, %r12d
	jne	.L747
	addq	$1, %rax
	cmpq	%rbx, %rax
	jne	.L744
	addq	$1, %rdx
	addq	%rsi, %rcx
	cmpq	%r10, %rdx
	jne	.L750
.L743:
	cmpb	$0, (%r9)
	je	.L751
	movq	24(%r14), %rdi
	movq	8(%r14), %rdx
	movq	%rbx, 16(%r14)
	movq	$0, 56(%r14)
	testq	%rdi, %rdi
	je	.L752
	cmpq	%rdx, %r10
	je	.L753
.L752:
	leaq	1(%r10), %rsi
	addq	$1, %rdx
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %rsi
	ja	.L997
	cmpq	%rax, %rdx
	ja	.L997
	salq	$2, %rdx
	salq	$2, %rsi
	testq	%rdi, %rdi
	je	.L1000
	cmpq	%rsi, %rdx
	je	.L757
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	testq	%rsi, %rsi
	je	.L1001
	call	realloc@PLT
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	testq	%rax, %rax
	movq	%rax, %rdi
	je	.L997
.L757:
	movq	%rdi, 24(%r14)
	movq	%r10, 8(%r14)
.L753:
	movq	32(%r14), %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	call	free@PLT
	movq	8(%r14), %r12
	movq	24(%r14), %rdi
	movq	$0, 32(%r14)
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	leaq	1(%r12), %rdx
	testq	%rdx, %rdx
	jle	.L760
	salq	$2, %rdx
	movq	%rdx, %r13
	je	.L760
	xorl	%esi, %esi
	call	memset@PLT
	movq	$0, 56(%r14)
	movq	%r13, %rdx
	xorl	%esi, %esi
	movq	%rax, %rdi
	call	memset@PLT
	movq	16(%rsp), %r9
	movq	8(%rsp), %r10
	movq	%rax, %rdi
	movq	64(%r14), %rax
	cmpq	%rbp, %rax
	jl	.L1002
.L761:
	xorl	%r11d, %r11d
	xorl	%esi, %esi
	testq	%r10, %r10
	jle	.L885
.L884:
	movq	%rbx, 8(%rsp)
	xorl	%ecx, %ecx
	xorl	%ebp, %ebp
	movq	%r11, %rbx
	movq	%r10, 16(%rsp)
	jmp	.L787
	.p2align 4,,10
	.p2align 3
.L779:
	addq	$1, %rbp
	addq	8(%rsp), %rcx
	cmpq	16(%rsp), %rbp
	jge	.L776
.L1004:
	movq	24(%r14), %rdi
.L787:
	movslq	(%rdi,%rbp,4), %r15
	leaq	0(,%rbp,4), %rdx
	movq	%r15, %rax
	cmpq	%rbx, %r15
	jne	.L830
	leaq	4(%rdx), %r11
	leaq	(%rdi,%r11), %rsi
	movl	(%rsi), %r10d
	testl	%r10d, %r10d
	jne	.L831
	movq	8(%r9), %r8
	movl	%r15d, (%rsi)
	movq	8(%r8), %r13
	testq	%r13, %r13
	jle	.L779
	movq	24(%rsp), %r8
	leaq	(%r8,%rcx,4), %r8
	movq	%r8, 48(%rsp)
	xorl	%r8d, %r8d
.L782:
	movq	48(%rsp), %r10
	movq	%r8, %r12
	movl	(%r10,%r8,4), %r10d
	testl	%r10d, %r10d
	jne	.L1003
	addq	$1, %r8
	cmpq	%r8, %r13
	jne	.L782
	addq	$1, %rbp
	addq	8(%rsp), %rcx
	cmpq	16(%rsp), %rbp
	jl	.L1004
.L776:
	cmpq	$0, 32(%r14)
	je	.L1005
.L742:
	movq	200(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L996
	addq	$216, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L747:
	.cfi_restore_state
	cmpq	%rbx, %rax
	jge	.L745
.L746:
	addq	$1, %rax
	addq	$1, %rbp
	cmpq	%rbx, %rax
	jge	.L745
.L749:
	movl	(%rcx,%rax,4), %r11d
	testl	%r11d, %r11d
	jne	.L748
	addq	$1, %rax
	cmpq	%rbx, %rax
	je	.L745
	jmp	.L749
.L748:
	cmpq	%rbx, %rax
	jge	.L745
	testq	%rax, %rax
	jns	.L746
	jmp	.L745
	.p2align 4,,10
	.p2align 3
.L751:
	leaq	1(%r10), %r12
	pxor	%xmm0, %xmm0
	movb	$0, 128(%rsp)
	movq	%r12, %rax
	movq	%rbx, 144(%rsp)
	shrq	$62, %rax
	movups	%xmm0, 152(%rsp)
	movq	$0, 136(%rsp)
	movups	%xmm0, 168(%rsp)
	movups	%xmm0, 184(%rsp)
	jne	.L997
	movq	%r12, %r13
	salq	$2, %r13
	je	.L821
	movl	$1, %esi
	movq	%r13, %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	call	calloc@PLT
	cmpq	$15, %r13
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	movq	%rax, 48(%rsp)
	jbe	.L822
	testb	$15, %al
	jne	.L767
.L822:
	cmpq	$0, 48(%rsp)
	je	.L997
	movq	48(%rsp), %rax
	movq	%r10, 136(%rsp)
	xorl	%edx, %edx
	movq	%rax, 152(%rsp)
	testq	%rbp, %rbp
	je	.L824
.L1014:
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %rbp
	jg	.L1006
	leaq	0(,%rbp,4), %r13
	movq	%r9, 16(%rsp)
	movq	%r13, %rdi
	movq	%r10, 8(%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	jbe	.L826
	testb	$15, %al
	je	.L1007
	.p2align 4,,10
	.p2align 3
.L767:
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
.L1003:
	cmpq	%r8, %r13
	jle	.L779
	movq	%r11, 56(%rsp)
	movq	%rbp, %r11
	movl	%r10d, %ebp
	movq	%r15, %r10
	movq	%rcx, 32(%rsp)
	movq	%rdx, %rcx
	movq	%r13, %rdx
.L781:
	cmpl	%eax, (%rdi,%rcx)
	je	.L788
	movq	48(%r14), %rdi
	movslq	-4(%rdi,%rbx,4), %rdi
	cmpq	%r12, %rdi
	jge	.L844
.L788:
	addl	$1, %eax
	addq	$1, %rbx
	movl	%eax, (%rsi)
	movq	64(%r14), %rax
	cmpq	%rax, %rbx
	jg	.L789
	movq	40(%r14), %r8
	movq	48(%r14), %rdi
.L790:
	leaq	0(,%rbx,4), %rax
	movq	%rbx, 56(%r14)
	movl	$0, -4(%r8,%rax)
	movl	%r12d, -4(%rdi,%rax)
	addq	$1, %r12
	movl	%ebp, (%r8,%r10,4)
	cmpq	%r12, %rdx
	jg	.L1008
.L985:
	movq	32(%rsp), %rcx
	movq	%r11, %rbp
	jmp	.L779
	.p2align 4,,10
	.p2align 3
.L789:
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rbx, %xmm0
	cvttsd2siq	%xmm0, %r15
	addq	%rbx, %r15
	cmpq	$2147483646, %r15
	jle	.L1009
	movl	$2147483648, %edi
	cmpq	%rdi, %rbx
	jge	.L997
	movq	40(%r14), %r8
	movq	%rax, %rsi
	movl	$2147483647, %r13d
	movl	$2147483647, %r15d
.L793:
	movabsq	$4611686018427387903, %rdi
	cmpq	%rdi, %rax
	ja	.L997
	salq	$2, %rax
	salq	$2, %r13
	testq	%r8, %r8
	je	.L1010
	cmpq	%r13, %rax
	je	.L796
	movq	%r10, 96(%rsp)
	movq	%r9, 88(%rsp)
	movq	%rcx, 80(%rsp)
	movq	%rdx, 72(%rsp)
	movq	%r11, 64(%rsp)
	testq	%r13, %r13
	je	.L1011
	movq	%r8, %rdi
	movq	%r13, %rsi
	call	realloc@PLT
	movq	%rax, %r8
	testq	%rax, %rax
	je	.L997
	movq	64(%r14), %rsi
.L991:
	movq	64(%rsp), %r11
	movq	72(%rsp), %rdx
	movq	%r8, 40(%r14)
	movabsq	$4611686018427387903, %rax
	movq	80(%rsp), %rcx
	movq	88(%rsp), %r9
	movq	96(%rsp), %r10
	movq	48(%r14), %rdi
	cmpq	%rax, %rsi
	ja	.L997
	salq	$2, %rsi
	testq	%rdi, %rdi
	je	.L1012
.L802:
	cmpq	%rsi, %r13
	je	.L803
	movq	%r10, 96(%rsp)
	movq	%r9, 88(%rsp)
	movq	%rcx, 80(%rsp)
	movq	%rdx, 72(%rsp)
	movq	%r11, 64(%rsp)
	testq	%r13, %r13
	je	.L1013
	movq	%r13, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L997
	movq	40(%r14), %r8
.L992:
	movq	64(%rsp), %r11
	movq	72(%rsp), %rdx
	movq	80(%rsp), %rcx
	movq	88(%rsp), %r9
	movq	96(%rsp), %r10
.L803:
	movq	%rdi, 48(%r14)
	movq	%r15, 64(%r14)
	jmp	.L790
	.p2align 4,,10
	.p2align 3
.L1008:
	movq	48(%rsp), %rsi
	movq	%r12, %rax
.L784:
	movl	(%rsi,%rax,4), %ebp
	movq	%rax, %r12
	testl	%ebp, %ebp
	jne	.L783
	addq	$1, %rax
	cmpq	%rax, %rdx
	je	.L985
	jmp	.L784
.L783:
	cmpq	%rax, %rdx
	jle	.L985
	testq	%rax, %rax
	js	.L985
	movq	56(%rsp), %rax
	movq	24(%r14), %rdi
	leaq	(%rdi,%rax), %rsi
	movslq	(%rsi), %r10
	movq	%r10, %rax
	cmpq	%rbx, %r10
	je	.L781
.L842:
	leaq	.LC34(%rip), %rcx
	movl	$427, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC35(%rip), %rdi
	call	__assert_fail@PLT
	.p2align 4,,10
	.p2align 3
.L1009:
	cmpq	%r15, %rbx
	jg	.L997
	movabsq	$4611686018427387903, %rdi
	movq	40(%r14), %r8
	movq	%rax, %rsi
	movq	%r15, %r13
	cmpq	%rdi, %r15
	jbe	.L793
.L997:
.LEHB21:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE21:
	.p2align 4,,10
	.p2align 3
.L821:
	movq	%r10, 136(%rsp)
	xorl	%edx, %edx
	movq	$0, 48(%rsp)
	testq	%rbp, %rbp
	jne	.L1014
	.p2align 4,,10
	.p2align 3
.L824:
	testq	%r10, %r10
	jle	.L829
	movq	48(%rsp), %rax
	xorl	%r11d, %r11d
	xorl	%ecx, %ecx
	movq	%rbx, 16(%rsp)
	movq	%r14, 64(%rsp)
	xorl	%edx, %edx
	movq	%r11, %rbx
	movq	%rcx, %r14
	movq	%r10, 8(%rsp)
	leaq	4(%rax), %rbp
	jmp	.L840
	.p2align 4,,10
	.p2align 3
.L832:
	addq	$1, %r14
	addq	16(%rsp), %rdx
	addq	$4, %rbp
	cmpq	8(%rsp), %r14
	je	.L1015
.L840:
	movslq	-4(%rbp), %r15
	movq	%r15, %rax
	cmpq	%r15, %rbx
	jne	.L830
	movl	0(%rbp), %ecx
	testl	%ecx, %ecx
	jne	.L831
	movq	8(%r9), %rcx
	movl	%r15d, 0(%rbp)
	movq	8(%rcx), %r13
	testq	%r13, %r13
	jle	.L832
	movq	24(%rsp), %rdi
	xorl	%ecx, %ecx
	leaq	(%rdi,%rdx,4), %rsi
	movq	%rsi, 56(%rsp)
.L835:
	movl	(%rsi,%rcx,4), %r10d
	movq	%rcx, %r12
	testl	%r10d, %r10d
	jne	.L1016
	addq	$1, %rcx
	cmpq	%rcx, %r13
	je	.L832
	jmp	.L835
.L1016:
	cmpq	%rcx, %r13
	jle	.L832
	movq	%r14, %r8
	movq	%r15, %rcx
	movq	%r13, %r14
	movl	%r10d, %r15d
.L834:
	cmpl	%eax, -4(%rbp)
	je	.L843
	movq	176(%rsp), %rsi
	movslq	-4(%rsi,%rbx,4), %rsi
	cmpq	%rsi, %r12
	jle	.L844
.L843:
	movq	192(%rsp), %rsi
	addl	$1, %eax
	addq	$1, %rbx
	movl	%eax, 0(%rbp)
	cmpq	%rsi, %rbx
	jg	.L845
	movq	168(%rsp), %r13
	movq	176(%rsp), %rdi
.L846:
	leaq	0(,%rbx,4), %rax
	movq	%rbx, 184(%rsp)
	movl	$0, -4(%r13,%rax)
	movl	%r12d, -4(%rdi,%rax)
	addq	$1, %r12
	movl	%r15d, 0(%r13,%rcx,4)
	cmpq	%r12, %r14
	jg	.L1017
.L989:
	movq	%r8, %r14
	jmp	.L832
	.p2align 4,,10
	.p2align 3
.L845:
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rbx, %xmm0
	cvttsd2siq	%xmm0, %r10
	addq	%rbx, %r10
	cmpq	$2147483646, %r10
	jle	.L1018
	movl	$2147483648, %eax
	cmpq	%rax, %rbx
	jge	.L882
	movq	168(%rsp), %r13
	movl	$2147483647, %r11d
	movl	$2147483647, %r10d
.L849:
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %rsi
	ja	.L1019
	salq	$2, %rsi
	salq	$2, %r11
	testq	%r13, %r13
	je	.L1020
	cmpq	%r11, %rsi
	je	.L855
	testq	%r11, %r11
	je	.L1021
	movq	%r11, %rsi
	movq	%r13, %rdi
	movq	%rcx, 112(%rsp)
	movq	%r9, 104(%rsp)
	movq	%rdx, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%r10, 80(%rsp)
	movq	%r11, 72(%rsp)
	call	realloc@PLT
	movq	72(%rsp), %r11
	movq	80(%rsp), %r10
	testq	%rax, %rax
	movq	88(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	%rax, %r13
	movq	104(%rsp), %r9
	movq	112(%rsp), %rcx
	je	.L1022
	movq	176(%rsp), %rdi
	movq	%rax, 168(%rsp)
	testq	%rdi, %rdi
	je	.L878
.L886:
	movq	%r11, %rsi
	movq	%rcx, 104(%rsp)
	movq	%r9, 96(%rsp)
	movq	%rdx, 88(%rsp)
	movq	%r8, 80(%rsp)
	movq	%r10, 72(%rsp)
	call	realloc@PLT
	movq	72(%rsp), %r10
	movq	80(%rsp), %r8
	testq	%rax, %rax
	movq	88(%rsp), %rdx
	movq	96(%rsp), %r9
	movq	%rax, %rdi
	movq	104(%rsp), %rcx
	je	.L1023
.L860:
	movq	%rdi, 176(%rsp)
	movq	%r10, 192(%rsp)
	jmp	.L846
	.p2align 4,,10
	.p2align 3
.L1017:
	movq	56(%rsp), %rcx
	movq	%r12, %rax
.L837:
	movl	(%rcx,%rax,4), %r15d
	movq	%rax, %r12
	testl	%r15d, %r15d
	jne	.L836
	addq	$1, %rax
	cmpq	%rax, %r14
	je	.L989
	jmp	.L837
.L836:
	testq	%rax, %rax
	js	.L989
	cmpq	%rax, %r14
	jle	.L989
	movslq	0(%rbp), %rcx
	movq	%rcx, %rax
	cmpq	%rbx, %rcx
	je	.L834
	jmp	.L842
	.p2align 4,,10
	.p2align 3
.L1015:
	movq	8(%rsp), %r10
	movq	64(%rsp), %r14
	movq	%rbx, %r11
	movl	%ebx, %esi
.L863:
	movq	48(%rsp), %rdx
	movq	%r10, %r12
	jmp	.L865
	.p2align 4,,10
	.p2align 3
.L867:
	leaq	-1(%r12), %rax
	testq	%r12, %r12
	je	.L1024
	movq	%rax, %r12
.L865:
	movl	(%rdx,%r12,4), %eax
	testl	%eax, %eax
	je	.L867
	movq	176(%rsp), %rdx
	movq	192(%rsp), %rbp
	addq	$1, %r12
.L864:
	movq	%r11, %xmm1
	movq	%rbp, %xmm7
	punpcklqdq	%xmm7, %xmm1
	cmpq	%r10, %r12
	jg	.L872
.L866:
	movq	%r10, %rax
	subq	%r12, %rax
	leaq	1(%rax), %rdi
	cmpq	$2, %rax
	jbe	.L869
	movq	48(%rsp), %rax
	movq	%rdi, %rcx
	movd	%esi, %xmm6
	shrq	$2, %rcx
	pshufd	$0, %xmm6, %xmm0
	leaq	(%rax,%r12,4), %rax
	salq	$4, %rcx
	addq	%rax, %rcx
	.p2align 4,,10
	.p2align 3
.L870:
	movups	%xmm0, (%rax)
	addq	$16, %rax
	cmpq	%rax, %rcx
	jne	.L870
	movq	%rdi, %rax
	andq	$-4, %rax
	addq	%rax, %r12
	cmpq	%rdi, %rax
	je	.L872
.L869:
	movq	48(%rsp), %rdi
	leaq	1(%r12), %rcx
	leaq	0(,%r12,4), %rax
	movl	%esi, (%rdi,%r12,4)
	cmpq	%r10, %rcx
	jg	.L872
	addq	$2, %r12
	movl	%esi, 4(%rdi,%rax)
	cmpq	%r10, %r12
	jg	.L872
	movl	%esi, 8(%rdi,%rax)
.L872:
	movq	48(%rsp), %rax
	movq	24(%r14), %rdi
	movups	%xmm1, 56(%r14)
	movdqa	32(%rsp), %xmm4
	movq	32(%r14), %r13
	movq	$0, 32(%r14)
	movq	40(%r14), %r12
	movq	48(%r14), %rbp
	movq	%rax, 24(%r14)
	movq	168(%rsp), %rax
	movq	%rdx, 48(%r14)
	movups	%xmm4, 8(%r14)
	movq	%rax, 40(%r14)
	call	free@PLT
	movq	%r13, %rdi
	call	free@PLT
	movq	%r12, %rdi
	call	free@PLT
	movq	200(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L996
	addq	$216, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%rbp, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.p2align 4,,10
	.p2align 3
.L1018:
	.cfi_restore_state
	cmpq	%r10, %rbx
	jg	.L882
	movabsq	$4611686018427387903, %rax
	movq	168(%rsp), %r13
	movq	%r10, %r11
	cmpq	%rax, %r10
	jbe	.L849
.LEHB22:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
	.p2align 4,,10
	.p2align 3
.L1010:
	testq	%r13, %r13
	je	.L796
	movq	%r13, %rdi
	movq	%r10, 104(%rsp)
	movq	%r9, 96(%rsp)
	movq	%rcx, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%r11, 72(%rsp)
	movq	%rsi, 64(%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	64(%rsp), %rsi
	movq	72(%rsp), %r11
	movq	80(%rsp), %rdx
	movq	88(%rsp), %rcx
	movq	%rax, %r8
	movq	96(%rsp), %r9
	movq	104(%rsp), %r10
	jbe	.L797
	testb	$15, %al
	jne	.L767
.L797:
	testq	%r8, %r8
	je	.L997
.L796:
	movq	48(%r14), %rdi
	movq	%r8, 40(%r14)
	salq	$2, %rsi
	testq	%rdi, %rdi
	jne	.L802
.L1012:
	testq	%r13, %r13
	je	.L803
	movq	%r13, %rdi
	movq	%r10, 104(%rsp)
	movq	%r9, 96(%rsp)
	movq	%rcx, 88(%rsp)
	movq	%rdx, 80(%rsp)
	movq	%r11, 72(%rsp)
	movq	%r8, 64(%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	64(%rsp), %r8
	movq	72(%rsp), %r11
	movq	80(%rsp), %rdx
	movq	88(%rsp), %rcx
	movq	%rax, %rdi
	movq	96(%rsp), %r9
	movq	104(%rsp), %r10
	jbe	.L804
	testb	$15, %al
	jne	.L767
.L804:
	testq	%rdi, %rdi
	jne	.L803
	jmp	.L997
	.p2align 4,,10
	.p2align 3
.L760:
	movq	64(%r14), %rax
	movq	$0, 56(%r14)
	cmpq	%rbp, %rax
	jge	.L761
.L1002:
	movabsq	$4611686018427387903, %rdx
	movq	40(%r14), %rdi
	movq	%rax, %r12
	cmpq	%rdx, %rbp
	jg	.L997
	cmpq	%rdx, %rax
	ja	.L997
	leaq	0(,%rax,4), %rax
	leaq	0(,%rbp,4), %r13
	testq	%rdi, %rdi
	je	.L1025
	cmpq	%r13, %rax
	je	.L765
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	testq	%r13, %r13
	je	.L1026
	movq	%r13, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L997
	movq	64(%r14), %r12
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
.L769:
	movq	%rax, 40(%r14)
	movq	%r12, %rax
	movq	48(%r14), %rdi
	shrq	$62, %rax
	jne	.L997
.L771:
	salq	$2, %r12
	testq	%rdi, %rdi
	je	.L1027
	cmpq	%r12, %r13
	je	.L773
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	testq	%r13, %r13
	je	.L1028
	movq	%r13, %rsi
	call	realloc@PLT
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	testq	%rax, %rax
	movq	%rax, %rdi
	je	.L997
.L773:
	movq	%rdi, 48(%r14)
	movq	%rbp, 64(%r14)
	testq	%r10, %r10
	jle	.L776
	movq	24(%r14), %rdi
	movq	56(%r14), %r11
	jmp	.L884
.L1005:
	movl	56(%r14), %esi
	movq	8(%r14), %r12
.L885:
	leaq	1(%r12), %rax
	testq	%r12, %r12
	js	.L811
	movq	24(%r14), %rdi
	movq	%r12, %rax
	jmp	.L812
	.p2align 4,,10
	.p2align 3
.L814:
	subq	$1, %rax
	jb	.L895
.L812:
	movl	(%rdi,%rax,4), %r8d
	testl	%r8d, %r8d
	je	.L814
	addq	$1, %rax
.L811:
	cmpq	%rax, %r12
	jl	.L742
	movq	24(%r14), %rdi
	jmp	.L813
.L893:
	xorl	%ebp, %ebp
	jmp	.L743
.L1020:
	testq	%r11, %r11
	je	.L852
	movq	%r11, %rdi
	movq	%rcx, 120(%rsp)
	movq	%r9, 112(%rsp)
	movq	%rdx, 104(%rsp)
	movq	%r8, 96(%rsp)
	movq	%rsi, 88(%rsp)
	movq	%r10, 80(%rsp)
	movq	%r11, 72(%rsp)
	call	malloc@PLT
	movq	72(%rsp), %r11
	movq	80(%rsp), %r10
	movq	88(%rsp), %rsi
	movq	96(%rsp), %r8
	movq	%rax, %r13
	cmpq	$15, %r11
	movq	104(%rsp), %rdx
	movq	112(%rsp), %r9
	movq	120(%rsp), %rcx
	ja	.L1029
.L853:
	testq	%r13, %r13
	je	.L1030
	movq	176(%rsp), %rdi
	movq	%r13, 168(%rsp)
	testq	%rdi, %rdi
	jne	.L1031
.L878:
	movq	%r11, %rdi
	movq	%rcx, 112(%rsp)
	movq	%r9, 104(%rsp)
	movq	%rdx, 96(%rsp)
	movq	%r8, 88(%rsp)
	movq	%r10, 80(%rsp)
	movq	%r11, 72(%rsp)
	call	malloc@PLT
	movq	72(%rsp), %r11
	movq	80(%rsp), %r10
	movq	88(%rsp), %r8
	movq	96(%rsp), %rdx
	movq	%rax, %rdi
	cmpq	$15, %r11
	movq	104(%rsp), %r9
	movq	112(%rsp), %rcx
	jbe	.L861
	testb	$15, %al
	jne	.L767
.L861:
	testq	%rdi, %rdi
	jne	.L860
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
	.p2align 4,,10
	.p2align 3
.L855:
	movq	176(%rsp), %rdi
	testq	%rdi, %rdi
	jne	.L860
	testq	%r11, %r11
	jne	.L878
	jmp	.L860
	.p2align 4,,10
	.p2align 3
.L1021:
	movq	%r13, %rdi
	movq	%rcx, 104(%rsp)
	movq	%r9, 96(%rsp)
	movq	%rdx, 88(%rsp)
	movq	%r8, 80(%rsp)
	movq	%r10, 72(%rsp)
	call	free@PLT
	movq	72(%rsp), %r10
	movq	80(%rsp), %r8
	movq	$0, 168(%rsp)
	movq	176(%rsp), %rdi
	movq	88(%rsp), %rdx
	movq	96(%rsp), %r9
	movq	104(%rsp), %rcx
	testq	%rdi, %rdi
	je	.L857
.L858:
	movq	%rcx, 104(%rsp)
	xorl	%r13d, %r13d
	movq	%r9, 96(%rsp)
	movq	%rdx, 88(%rsp)
	movq	%r8, 80(%rsp)
	movq	%r10, 72(%rsp)
	call	free@PLT
	movq	72(%rsp), %r10
	movq	80(%rsp), %r8
	xorl	%edi, %edi
	movq	88(%rsp), %rdx
	movq	96(%rsp), %r9
	movq	104(%rsp), %rcx
	jmp	.L860
.L1011:
	movq	%r8, %rdi
	call	free@PLT
	movq	64(%r14), %rsi
	xorl	%r8d, %r8d
	jmp	.L991
.L1013:
	call	free@PLT
	movq	40(%r14), %r8
	xorl	%edi, %edi
	jmp	.L992
.L1000:
	testq	%rsi, %rsi
	je	.L757
	movq	%rsi, %rdi
	movq	%r9, 48(%rsp)
	movq	%r10, 16(%rsp)
	movq	%rsi, 8(%rsp)
	call	malloc@PLT
	movq	8(%rsp), %rsi
	movq	16(%rsp), %r10
	movq	48(%rsp), %r9
	movq	%rax, %rdi
	cmpq	$15, %rsi
	jbe	.L758
	testb	$15, %al
	jne	.L767
.L758:
	testq	%rdi, %rdi
	jne	.L757
	jmp	.L997
	.p2align 4,,10
	.p2align 3
.L895:
	xorl	%eax, %eax
.L813:
	movq	%r12, %rdx
	subq	%rax, %rdx
	leaq	1(%rdx), %r8
	cmpq	$2, %rdx
	jbe	.L816
	movq	%r8, %rcx
	movd	%esi, %xmm5
	leaq	(%rdi,%rax,4), %rdx
	shrq	$2, %rcx
	pshufd	$0, %xmm5, %xmm0
	salq	$4, %rcx
	addq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L817:
	movups	%xmm0, (%rdx)
	addq	$16, %rdx
	cmpq	%rdx, %rcx
	jne	.L817
	movq	%r8, %rdx
	andq	$-4, %rdx
	addq	%rdx, %rax
	cmpq	%rdx, %r8
	je	.L742
.L816:
	leaq	1(%rax), %rcx
	movl	%esi, (%rdi,%rax,4)
	leaq	0(,%rax,4), %rdx
	cmpq	%r12, %rcx
	jg	.L742
	addq	$2, %rax
	movl	%esi, 4(%rdi,%rdx)
	cmpq	%rax, %r12
	jl	.L742
	movl	%esi, 8(%rdi,%rdx)
	jmp	.L742
.L1024:
	movq	%r11, %xmm1
	movq	176(%rsp), %rdx
	movhps	192(%rsp), %xmm1
	jmp	.L866
.L1001:
	call	free@PLT
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	xorl	%edi, %edi
	jmp	.L757
.L1029:
	testb	$15, %al
	jne	.L767
	jmp	.L853
	.p2align 4,,10
	.p2align 3
.L1025:
	testq	%r13, %r13
	je	.L765
	movq	%r13, %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	movq	%rax, %rdi
	jbe	.L766
	testb	$15, %al
	jne	.L767
.L766:
	testq	%rdi, %rdi
	je	.L997
.L765:
	movq	%rdi, 40(%r14)
	movq	48(%r14), %rdi
	jmp	.L771
.L852:
	movq	176(%rsp), %rdi
	movq	$0, 168(%rsp)
	testq	%rdi, %rdi
	jne	.L1032
.L857:
	xorl	%r13d, %r13d
	xorl	%edi, %edi
	jmp	.L860
.L1027:
	testq	%r13, %r13
	je	.L773
	movq	%r13, %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	movq	%rax, %rdi
	jbe	.L774
	testb	$15, %al
	jne	.L767
.L774:
	testq	%rdi, %rdi
	jne	.L773
	jmp	.L997
	.p2align 4,,10
	.p2align 3
.L1026:
	call	free@PLT
	movq	64(%r14), %r12
	movq	8(%rsp), %r10
	xorl	%eax, %eax
	movq	16(%rsp), %r9
	jmp	.L769
.L1028:
	call	free@PLT
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	xorl	%edi, %edi
	jmp	.L773
.L826:
	testq	%rax, %rax
	je	.L888
	movq	%r13, %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	movq	%rax, 168(%rsp)
	call	malloc@PLT
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	movq	%rax, %rdx
.L887:
	testq	%rdx, %rdx
	je	.L1033
	movq	%rdx, 176(%rsp)
	movq	%rbp, 192(%rsp)
	jmp	.L824
.L829:
	je	.L897
	xorl	%esi, %esi
	xorl	%r11d, %r11d
	jmp	.L864
.L830:
	leaq	.LC30(%rip), %rcx
	movl	$449, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC32(%rip), %rdi
	call	__assert_fail@PLT
.L1032:
	testq	%rsi, %rsi
	je	.L860
	jmp	.L858
	.p2align 4,,10
	.p2align 3
.L831:
	leaq	.LC30(%rip), %rcx
	movl	$450, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC33(%rip), %rdi
	call	__assert_fail@PLT
.L844:
	leaq	.LC34(%rip), %rcx
	movl	$428, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC36(%rip), %rdi
	call	__assert_fail@PLT
.L897:
	xorl	%r11d, %r11d
	xorl	%esi, %esi
	jmp	.L863
.L996:
	call	__stack_chk_fail@PLT
.L1007:
	testq	%rax, %rax
	je	.L888
	movq	%r13, %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	movq	%rax, 168(%rsp)
	call	malloc@PLT
	movq	8(%rsp), %r10
	movq	16(%rsp), %r9
	testb	$15, %al
	movq	%rax, %rdx
	jne	.L767
	jmp	.L887
.L1031:
	cmpq	%r11, %rsi
	je	.L860
	jmp	.L886
.L1030:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1022:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1019:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L900:
	endbr64
	movq	%rax, %rbp
	jmp	.L874
.L882:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1023:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1033:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L888:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1006:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE22:
.L874:
	leaq	128(%rsp), %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiED1Ev
	movq	%rbp, %rdi
.LEHB23:
	call	_Unwind_Resume@PLT
.LEHE23:
	.cfi_endproc
.LFE12810:
	.section	.gcc_except_table
.LLSDA12810:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE12810-.LLSDACSB12810
.LLSDACSB12810:
	.uleb128 .LEHB21-.LFB12810
	.uleb128 .LEHE21-.LEHB21
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB22-.LFB12810
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L900-.LFB12810
	.uleb128 0
	.uleb128 .LEHB23-.LFB12810
	.uleb128 .LEHE23-.LEHB23
	.uleb128 0
	.uleb128 0
.LLSDACSE12810:
	.section	.text._ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_,"axG",@progbits,_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_,comdat
	.size	_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_, .-_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC37:
	.string	"them"
.LC38:
	.string	"us"
.LC39:
	.string	"%10s %10s\n"
	.section	.rodata.str1.8
	.align 8
.LC42:
	.string	"Eigen::MapBase<Derived, 0>::MapBase(Eigen::MapBase<Derived, 0>::PointerType, Eigen::Index) [with Derived = Eigen::Map<const Eigen::Matrix<int, -1, 1>, 0, Eigen::Stride<0, 0> >; Eigen::MapBase<Derived, 0>::PointerType = const int*; Eigen::Index = long int]"
	.align 8
.LC43:
	.string	"/usr/local/include/Eigen/src/Core/MapBase.h"
	.section	.rodata.str1.1
.LC44:
	.string	"vecSize >= 0"
.LC45:
	.string	"rows in vec:"
.LC46:
	.string	"Rows and cols in dense: "
.LC47:
	.string	"Rows and cols in csf3: "
	.section	.rodata.str1.8
	.align 8
.LC48:
	.string	"typename Eigen::internal::traits<T>::Scalar Eigen::DenseBase<Derived>::redux(const Func&) const [with BinaryOp = Eigen::internal::scalar_sum_op<int, int>; Derived = Eigen::Matrix<int, -1, 1>; typename Eigen::internal::traits<T>::Scalar = int]"
	.align 8
.LC49:
	.string	"/usr/local/include/Eigen/src/Core/Redux.h"
	.align 8
.LC50:
	.string	"this->rows()>0 && this->cols()>0 && \"you are using an empty matrix\""
	.align 8
.LC51:
	.ascii	"Eigen::Product<Lhs, Rhs, Option"
	.string	">::Product(const Lhs&, const Rhs&) [with Lhs_ = Eigen::SparseMatrix<int>; Rhs_ = Eigen::Matrix<int, -1, 1>; int Option = 0; Eigen::Product<Lhs, Rhs, Option>::Lhs = Eigen::SparseMatrix<int>; Eigen::Product<Lhs, Rhs, Option>::Rhs = Eigen::Matrix<int, -1, 1>]"
	.align 8
.LC52:
	.string	"/usr/local/include/Eigen/src/Core/Product.h"
	.align 8
.LC53:
	.string	"lhs.cols() == rhs.rows() && \"invalid matrix product\" && \"if you wanted a coeff-wise or a dot product use the respective explicit functions\""
	.align 8
.LC54:
	.ascii	"typename Eigen::internal::trait"
	.string	"s<T>::Scalar Eigen::DenseBase<Derived>::redux(const Func&) const [with BinaryOp = Eigen::internal::scalar_sum_op<int, int>; Derived = Eigen::Product<Eigen::SparseMatrix<int>, Eigen::Matrix<int, -1, 1>, 0>; typename Eigen::internal::traits<T>::Scalar = int]"
	.align 8
.LC56:
	.string	"constexpr void Eigen::PlainObjectBase<Derived>::resize(Eigen::Index, Eigen::Index) [with Derived = Eigen::Matrix<int, -1, 1>; Eigen::Index = long int]"
	.align 8
.LC57:
	.string	"/usr/local/include/Eigen/src/Core/PlainObjectBase.h"
	.align 8
.LC58:
	.ascii	"internal::check_implication(RowsAtCompileTime!=Dynamic, rows"
	.ascii	"==RowsAtCompileTime) && internal::check_implication(ColsAtCo"
	.ascii	"mpileTime!=Dynamic, cols==ColsAtCompileTime) && internal::ch"
	.ascii	"eck_implication(RowsAtCompileTime==Dynamic"
	.string	" && MaxRowsAtCompileTime!=Dynamic, rows<=MaxRowsAtCompileTime) && internal::check_implication(ColsAtCompileTime==Dynamic && MaxColsAtCompileTime!=Dynamic, cols<=MaxColsAtCompileTime) && rows>=0 && cols>=0 && \"Invalid sizes when resizing a matrix or array.\""
	.section	.rodata.str1.1
.LC59:
	.string	"int main()"
.LC60:
	.string	"test.cpp"
.LC61:
	.string	"ourSum == theirSum"
.LC62:
	.string	"compareOstreams(os1, os2)"
.LC63:
	.string	"%10lu %10lu\n"
.LC64:
	.string	"IVSparse: "
.LC65:
	.string	"Eigen: "
	.section	.text.unlikely
.LCOLDB66:
	.section	.text.startup,"ax",@progbits
.LHOTB66:
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB11239:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA11239
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pxor	%xmm0, %xmm0
	leaq	.LC37(%rip), %rcx
	leaq	.LC38(%rip), %rdx
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	leaq	.LC39(%rip), %rsi
	movl	$1, %edi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	leaq	64+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	%rbx, %xmm4
	subq	$1928, %rsp
	.cfi_def_cfa_offset 1984
	movq	%fs:40, %rax
	movq	%rax, 1912(%rsp)
	xorl	%eax, %eax
	movhps	.LC18(%rip), %xmm4
	movq	$0, 432(%rsp)
	movq	$0, 464(%rsp)
	movaps	%xmm4, 112(%rsp)
	movaps	%xmm0, 416(%rsp)
	movaps	%xmm0, 448(%rsp)
.LEHB24:
	call	__printf_chk@PLT
.LEHE24:
	leaq	1120(%rsp), %rax
	movq	%rbx, %xmm5
	movl	$0, 52(%rsp)
	movq	%rax, 144(%rsp)
	leaq	1248(%rsp), %rax
	movhps	.LC17(%rip), %xmm5
	movq	%rax, 152(%rsp)
	movaps	%xmm5, 240(%rsp)
.L1261:
	movl	52(%rsp), %edi
	call	srand@PLT
	movq	152(%rsp), %rbx
	movq	%rbx, %rdi
	call	_ZNSt8ios_baseC2Ev@PLT
	pxor	%xmm0, %xmm0
	xorl	%r9d, %r9d
	xorl	%esi, %esi
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movups	%xmm0, 1480(%rsp)
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1248(%rsp)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movw	%r9w, 1472(%rsp)
	movups	%xmm0, 1496(%rsp)
	movq	%rax, 1120(%rsp)
	movq	-24(%rax), %rax
	movq	$0, 1464(%rsp)
	movq	%rcx, 1120(%rsp,%rax)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	$0, 1128(%rsp)
	movq	144(%rsp), %rax
	addq	-24(%rcx), %rax
	movq	%rax, %rdi
.LEHB25:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE25:
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	xorl	%esi, %esi
	movq	%rax, 1136(%rsp)
	leaq	1136(%rsp), %rax
	movq	%rax, 176(%rsp)
	addq	-24(%rcx), %rax
	movq	%rax, %rdi
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, (%rdi)
.LEHB26:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE26:
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	pxor	%xmm0, %xmm0
	leaq	1144(%rsp), %rbp
	movdqa	112(%rsp), %xmm2
	movq	-24(%rax), %rax
	movq	%rcx, 1120(%rsp,%rax)
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, 1120(%rsp)
	addq	$80, %rax
	movq	%rax, 1248(%rsp)
	leaq	1200(%rsp), %rax
	movq	%rax, %rdi
	movq	%rax, 200(%rsp)
	movaps	%xmm2, 1136(%rsp)
	movaps	%xmm0, 1152(%rsp)
	movaps	%xmm0, 1168(%rsp)
	movaps	%xmm0, 1184(%rsp)
	call	_ZNSt6localeC1Ev@PLT
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	movq	%rax, 1144(%rsp)
	leaq	1232(%rsp), %rax
	movl	$24, 1208(%rsp)
	movq	%rax, 208(%rsp)
	movq	%rax, 1216(%rsp)
	movq	$0, 1224(%rsp)
	movb	$0, 1232(%rsp)
.LEHB27:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE27:
	leaq	1648(%rsp), %r14
	leaq	1520(%rsp), %rbx
	movq	%r14, %rdi
	movq	%rbx, 184(%rsp)
	movq	%r14, 192(%rsp)
	call	_ZNSt8ios_baseC2Ev@PLT
	pxor	%xmm0, %xmm0
	xorl	%r8d, %r8d
	xorl	%esi, %esi
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movups	%xmm0, 1880(%rsp)
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1648(%rsp)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movw	%r8w, 1872(%rsp)
	movups	%xmm0, 1896(%rsp)
	movq	%rax, 1520(%rsp)
	movq	-24(%rax), %rax
	movq	$0, 1864(%rsp)
	movq	%rcx, 1520(%rsp,%rax)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	$0, 1528(%rsp)
	addq	-24(%rax), %rbx
	movq	%rbx, %rdi
.LEHB28:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE28:
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	xorl	%esi, %esi
	movq	-24(%rbx), %rdi
	movq	%rax, 1536(%rsp)
	leaq	1536(%rsp), %rax
	movq	%rax, 216(%rsp)
	addq	%rax, %rdi
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, (%rdi)
.LEHB29:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE29:
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	pxor	%xmm0, %xmm0
	leaq	1544(%rsp), %rbp
	movdqa	112(%rsp), %xmm3
	movq	-24(%rax), %rax
	movq	%rbx, 1520(%rsp,%rax)
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rax, 1520(%rsp)
	addq	$80, %rax
	movq	%rax, 1648(%rsp)
	leaq	1600(%rsp), %rax
	movq	%rax, %rdi
	movq	%rax, 224(%rsp)
	movaps	%xmm3, 1536(%rsp)
	movaps	%xmm0, 1552(%rsp)
	movaps	%xmm0, 1568(%rsp)
	movaps	%xmm0, 1584(%rsp)
	call	_ZNSt6localeC1Ev@PLT
	leaq	16+_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	%rbp, %rsi
	movq	%r14, %rdi
	movq	%rax, 1544(%rsp)
	leaq	1632(%rsp), %rax
	movl	$24, 1608(%rsp)
	movq	%rax, 232(%rsp)
	movq	%rax, 1616(%rsp)
	movq	$0, 1624(%rsp)
	movb	$0, 1632(%rsp)
.LEHB30:
	call	_ZNSt9basic_iosIcSt11char_traitsIcEE4initEPSt15basic_streambufIcS1_E@PLT
.LEHE30:
	pxor	%xmm0, %xmm0
	movl	$40000, %edi
	movq	$0, 480(%rsp)
	movups	%xmm0, 488(%rsp)
	call	malloc@PLT
	movq	%rax, %rbp
	testb	$15, %al
	je	.L1045
.L1069:
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
.L1045:
	testq	%rax, %rax
	je	.L1427
	movdqa	.LC40(%rip), %xmm4
	movq	%rax, 480(%rsp)
	leaq	40000(%rax), %rbx
	movups	%xmm4, 488(%rsp)
	.p2align 4,,10
	.p2align 3
.L1047:
	call	rand@PLT
	addq	$4, %rbp
	subl	$1073741824, %eax
	movl	%eax, -4(%rbp)
	cmpq	%rbp, %rbx
	jne	.L1047
	leaq	480(%rsp), %rax
	pxor	%xmm0, %xmm0
	leaq	592(%rsp), %rsi
	movb	$0, 592(%rsp)
	movq	%rax, 600(%rsp)
	leaq	512(%rsp), %rax
	movq	%rax, %rdi
	movq	%rsi, 40(%rsp)
	movq	$0, 608(%rsp)
	movq	$0, 512(%rsp)
	movq	%rax, 336(%rsp)
	movups	%xmm0, 520(%rsp)
	movups	%xmm0, 536(%rsp)
	movups	%xmm0, 552(%rsp)
	movups	%xmm0, 568(%rsp)
.LEHB31:
	call	_ZN5Eigen8internal23assign_sparse_to_sparseINS_12SparseMatrixIiLi0EiEENS_10SparseViewINS_6MatrixIiLin1ELin1ELi0ELin1ELin1EEEEEEEvRT_RKT0_
.LEHE31:
	pxor	%xmm0, %xmm0
	movq	544(%rsp), %r8
	leaq	16+_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE(%rip), %rax
	movl	$0, 616(%rsp)
	movups	%xmm0, 600(%rsp)
	pxor	%xmm0, %xmm0
	movq	520(%rsp), %rcx
	movq	$0, 624(%rsp)
	movq	%rax, 592(%rsp)
	movaps	%xmm0, 640(%rsp)
	movaps	%xmm0, 656(%rsp)
	movaps	%xmm0, 672(%rsp)
	testq	%r8, %r8
	je	.L1054
	movslq	(%r8), %r15
	movl	$1, %ebx
	leaq	-1(%rcx), %r9
	movq	%r8, %r14
	movq	536(%rsp), %r13
	movslq	4(%r13), %r12
	movl	%r15d, 4(%r13)
	movq	%r12, %rbp
	cmpq	$1, %rcx
	jg	.L1055
	jmp	.L1061
	.p2align 4,,10
	.p2align 3
.L1058:
	cltq
	movq	%rax, %r8
	subq	%r12, %r8
	testq	%r8, %r8
	jg	.L1465
.L1060:
	movslq	%ebp, %r12
	addq	%r8, %r15
.L1059:
	addl	0(%r13,%rbx,4), %edi
	movl	%edi, 4(%r13,%rbx,4)
	addq	$1, %rbx
	cmpq	%rcx, %rbx
	je	.L1466
.L1055:
	movl	(%r14,%rbx,4), %edi
	leal	(%rdi,%rbp), %eax
	movl	4(%r13,%rbx,4), %ebp
	cmpl	%ebp, %eax
	jne	.L1058
	cmpq	%rbx, %r9
	jne	.L1059
	jmp	.L1058
	.p2align 4,,10
	.p2align 3
.L1465:
	salq	$2, %r12
	salq	$2, %rax
	subq	%r12, %rax
	movq	%rax, %rdx
	je	.L1060
	movq	552(%rsp), %rdi
	leaq	0(,%r15,4), %r10
	movq	%r9, 32(%rsp)
	movq	%rcx, 24(%rsp)
	leaq	(%rdi,%r12), %rsi
	addq	%r10, %rdi
	movq	%r8, 16(%rsp)
	movq	%r10, 8(%rsp)
	movq	%rax, (%rsp)
	call	memmove@PLT
	movq	(%rsp), %rdx
	movq	8(%rsp), %rdi
	movq	560(%rsp), %rsi
	addq	560(%rsp), %rdi
	addq	%r12, %rsi
	call	memmove@PLT
	movl	(%r14,%rbx,4), %edi
	movq	32(%rsp), %r9
	movq	24(%rsp), %rcx
	movq	16(%rsp), %r8
	jmp	.L1060
	.p2align 4,,10
	.p2align 3
.L1466:
	movq	%r14, %r8
.L1061:
	movslq	0(%r13,%rcx,4), %r12
	movq	576(%rsp), %rbx
	cmpq	%rbx, %r12
	jle	.L1057
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%r12d, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %rbp
	addq	%r12, %rbp
	cmpq	$2147483646, %rbp
	jle	.L1467
	movq	552(%rsp), %rdi
	movq	%rbx, %rax
	movl	$2147483647, %ebp
	movl	$2147483647, %ebx
.L1064:
	movq	%rax, %rcx
	shrq	$62, %rcx
	jne	.L1430
	leaq	0(,%rax,4), %r13
	salq	$2, %rbp
	testq	%rdi, %rdi
	je	.L1468
	cmpq	%rbp, %r13
	je	.L1071
	movq	%r8, (%rsp)
	testq	%rbp, %rbp
	je	.L1469
	movq	%rbp, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L1432
	movq	560(%rsp), %rdi
	movq	(%rsp), %r8
	movq	%rax, 552(%rsp)
	testq	%rdi, %rdi
	je	.L1276
.L1280:
	movq	%rbp, %rsi
	movq	%r8, (%rsp)
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L1434
	movq	(%rsp), %r8
.L1077:
	movq	%rdi, 560(%rsp)
	movq	%rbx, 576(%rsp)
.L1057:
	movq	%r8, %rdi
	movq	%r12, 568(%rsp)
	call	free@PLT
	movq	$0, 544(%rsp)
	cmpq	%r12, %rbx
	jle	.L1054
	movabsq	$4611686018427387903, %rax
	movq	552(%rsp), %rdi
	cmpq	%rax, %r12
	ja	.L1435
	cmpq	%rax, %rbx
	ja	.L1436
	salq	$2, %rbx
	leaq	0(,%r12,4), %rbp
	testq	%rdi, %rdi
	je	.L1470
	cmpq	%rbp, %rbx
	je	.L1085
	testq	%rbp, %rbp
	je	.L1471
	movq	%rbp, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L1438
	movq	560(%rsp), %rdi
	movq	%rax, 552(%rsp)
	testq	%rdi, %rdi
	je	.L1270
.L1279:
	movq	%rbp, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L1440
.L1091:
	movq	%rdi, 560(%rsp)
	movq	%r12, 576(%rsp)
.L1054:
	movdqu	520(%rsp), %xmm1
	movdqa	%xmm1, %xmm0
	movq	%xmm1, %rax
	movhps	%xmm1, 32(%rsp)
	shufpd	$1, %xmm1, %xmm0
	movq	%xmm1, 8(%rsp)
	shufps	$136, %xmm0, %xmm0
	movups	%xmm0, 600(%rsp)
	testq	%rax, %rax
	je	.L1284
	movq	544(%rsp), %rcx
	testq	%rcx, %rcx
	je	.L1472
	cmpq	$0, 8(%rsp)
	js	.L1473
	movq	%rcx, %rsi
	testb	$3, %cl
	jne	.L1095
	movq	%rcx, %rdi
	movq	8(%rsp), %rax
	movl	$4, %r8d
	shrq	$2, %rdi
	negq	%rdi
	andl	$3, %edi
	cmpq	%rax, %rdi
	cmovg	%rax, %rdi
	subq	%rdi, %rax
	cqto
	movq	%rax, %r9
	idivq	%r8
	leaq	3(%r9), %rdx
	leaq	0(,%rax,4), %r10
	leaq	(%rdi,%r10), %r8
	cmpq	$6, %rdx
	jbe	.L1095
	movdqu	(%rcx,%rdi,4), %xmm0
	leaq	0(,%rdi,4), %rdx
	cmpq	$4, %r10
	jle	.L1096
	andq	$-8, %r9
	movdqu	16(%rcx,%rdx), %xmm1
	leaq	8(%rdi), %rdx
	leaq	(%rdi,%r9), %rsi
	cmpq	$8, %r9
	jle	.L1097
	.p2align 4,,10
	.p2align 3
.L1098:
	movdqu	(%rcx,%rdx,4), %xmm6
	movdqu	16(%rcx,%rdx,4), %xmm2
	addq	$8, %rdx
	paddd	%xmm6, %xmm0
	paddd	%xmm2, %xmm1
	cmpq	%rdx, %rsi
	jg	.L1098
.L1097:
	paddd	%xmm1, %xmm0
	cmpq	%r10, %r9
	jge	.L1096
	movdqu	(%rcx,%rsi,4), %xmm1
	paddd	%xmm1, %xmm0
.L1096:
	movdqa	%xmm0, %xmm1
	punpckhqdq	%xmm0, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %edx
	pshufd	$1, %xmm0, %xmm0
	movd	%xmm0, %esi
	addl	%esi, %edx
	testq	%rdi, %rdi
	je	.L1100
	addl	(%rcx), %edx
	cmpq	$1, %rdi
	je	.L1100
	addl	4(%rcx), %edx
	cmpq	$3, %rdi
	jne	.L1100
	addl	8(%rcx), %edx
.L1100:
	movq	8(%rsp), %rbx
	cmpq	%rbx, %r8
	jge	.L1092
	movq	%rbx, %r9
	subq	%r8, %r9
	leaq	-1(%r9), %rsi
	cmpq	$2, %rsi
	jbe	.L1103
	movq	%r9, %rsi
	leaq	(%rdi,%rax,4), %rax
	pxor	%xmm0, %xmm0
	shrq	$2, %rsi
	leaq	(%rcx,%rax,4), %rax
	salq	$4, %rsi
	addq	%rax, %rsi
	.p2align 4,,10
	.p2align 3
.L1104:
	movdqu	(%rax), %xmm5
	addq	$16, %rax
	paddd	%xmm5, %xmm0
	cmpq	%rax, %rsi
	jne	.L1104
	movdqa	%xmm0, %xmm1
	psrldq	$8, %xmm1
	paddd	%xmm1, %xmm0
	movdqa	%xmm0, %xmm1
	psrldq	$4, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %eax
	addl	%eax, %edx
	movq	%r9, %rax
	andq	$-4, %rax
	addq	%rax, %r8
	cmpq	%r9, %rax
	je	.L1092
.L1103:
	movq	8(%rsp), %rbx
	leaq	1(%r8), %rsi
	leaq	0(,%r8,4), %rax
	addl	(%rcx,%r8,4), %edx
	cmpq	%rbx, %rsi
	jge	.L1092
	addq	$2, %r8
	addl	4(%rcx,%rax), %edx
	cmpq	%rbx, %r8
	jge	.L1092
	addl	8(%rcx,%rax), %edx
	.p2align 4,,10
	.p2align 3
.L1092:
	movq	536(%rsp), %rax
	movq	560(%rsp), %r15
	movl	%edx, 616(%rsp)
	movq	552(%rsp), %rbp
	movq	40(%rsp), %rdi
	movq	%rax, %rcx
	movq	%r15, %rdx
	movq	%rax, 128(%rsp)
	movq	%rbp, %rsi
.LEHB32:
	call	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE11compressCSCIiiEEvPT_PT0_S6_
.LEHE32:
	movl	$400, %edi
	movq	$0, 384(%rsp)
	movq	$0, 392(%rsp)
	call	malloc@PLT
	movq	%rax, %r12
	andl	$15, %eax
	movq	%rax, 344(%rsp)
	jne	.L1069
	testq	%r12, %r12
	je	.L1441
	movq	%r12, 384(%rsp)
	leaq	400(%r12), %rbx
	movq	$100, 392(%rsp)
	.p2align 4,,10
	.p2align 3
.L1111:
	call	rand@PLT
	addq	$4, %r12
	subl	$1073741824, %eax
	movl	%eax, -4(%r12)
	cmpq	%r12, %rbx
	jne	.L1111
	movl	$12, %edx
	leaq	.LC45(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
.LEHB33:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	392(%rsp), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo9_M_insertIlEERSoT_@PLT
	movq	%rax, %r12
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r12,%rax), %r13
	testq	%r13, %r13
	je	.L1474
	cmpb	$0, 56(%r13)
	je	.L1116
	movsbl	67(%r13), %esi
.L1117:
	movq	%r12, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	$24, %edx
	leaq	.LC46(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	488(%rsp), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo9_M_insertIlEERSoT_@PLT
	leaq	.LC15(%rip), %r14
	movl	$1, %edx
	movq	%rax, %rdi
	movq	%rax, %r12
	movq	%r14, %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	496(%rsp), %rsi
	movq	%r12, %rdi
	call	_ZNSo9_M_insertIlEERSoT_@PLT
	movq	%rax, %r12
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r12,%rax), %r13
	testq	%r13, %r13
	je	.L1475
	cmpb	$0, 56(%r13)
	je	.L1119
	movsbl	67(%r13), %esi
.L1120:
	movq	%r12, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	movl	$23, %edx
	leaq	.LC47(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	608(%rsp), %esi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movl	$1, %edx
	movq	%r14, %rsi
	movq	%rax, %rdi
	movq	%rax, %r12
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movl	612(%rsp), %esi
	movq	%r12, %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movq	%rax, %r12
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r12,%rax), %r13
	testq	%r13, %r13
	je	.L1476
	cmpb	$0, 56(%r13)
	je	.L1122
	movsbl	67(%r13), %esi
.L1123:
	movq	%r12, %rdi
	call	_ZNSo3putEc@PLT
	movq	%rax, %rdi
	call	_ZNSo5flushEv@PLT
	call	_ZNSt6chrono3_V212system_clock3nowEv@PLT
	leaq	384(%rsp), %r12
	movq	40(%rsp), %rsi
	movq	%rax, %rbx
	leaq	400(%rsp), %rax
	movq	%r12, %rdx
	movq	%rax, %rdi
	movq	%rax, 104(%rsp)
	call	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE
	movq	408(%rsp), %rcx
	testq	%rcx, %rcx
	jne	.L1124
	movl	$0, 140(%rsp)
	movq	400(%rsp), %rdi
.L1125:
	call	free@PLT
	call	_ZNSt6chrono3_V212system_clock3nowEv@PLT
	subq	%rbx, %rax
	movq	%rax, 160(%rsp)
	movq	%rax, 360(%rsp)
	call	_ZNSt6chrono3_V212system_clock3nowEv@PLT
	movq	%rax, %rbx
	movq	8(%rsp), %rax
	cmpq	%rax, 392(%rsp)
	jne	.L1196
	cmpq	$0, 32(%rsp)
	movl	$0, 136(%rsp)
	je	.L1138
	jle	.L1477
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, 32(%rsp)
	jg	.L1442
	movq	32(%rsp), %rax
	movl	$1, %esi
	leaq	0(,%rax,4), %r13
	movq	%r13, %rdi
	call	calloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L1141
	testb	$15, %al
	jne	.L1069
.L1141:
	testq	%rdi, %rdi
	je	.L1443
	cmpq	$0, 8(%rsp)
	jle	.L1150
	movq	384(%rsp), %r11
	movq	544(%rsp), %r10
	xorl	%r9d, %r9d
	movq	128(%rsp), %r13
	movq	8(%rsp), %r14
	.p2align 4,,10
	.p2align 3
.L1149:
	movl	(%r11,%r9,4), %r8d
	movslq	0(%r13,%r9,4), %rcx
	testq	%r10, %r10
	je	.L1478
	movslq	(%r10,%r9,4), %rdx
	addq	%rcx, %rdx
.L1147:
	leaq	0(,%rcx,4), %rax
	leaq	0(,%rdx,4), %rsi
	cmpq	%rdx, %rcx
	jge	.L1152
	.p2align 4,,10
	.p2align 3
.L1151:
	movslq	(%r15,%rax), %rdx
	movl	0(%rbp,%rax), %ecx
	addq	$4, %rax
	imull	%r8d, %ecx
	addl	%ecx, (%rdi,%rdx,4)
	cmpq	%rax, %rsi
	jne	.L1151
.L1152:
	addq	$1, %r9
	cmpq	%r14, %r9
	jne	.L1149
.L1150:
	movq	32(%rsp), %rax
	addq	$3, %rax
	cmpq	$6, %rax
	jbe	.L1479
	movq	32(%rsp), %rdx
	movdqa	(%rdi), %xmm0
	movq	%rdx, %rax
	movq	%rdx, %rcx
	sarq	$2, %rax
	andq	$-4, %rcx
	cmpq	$1, %rax
	je	.L1153
	andq	$-8, %rdx
	movdqa	16(%rdi), %xmm1
	movq	%rdx, %r8
	cmpq	$8, %rdx
	jle	.L1154
	leaq	32(%rdi), %rdx
	leaq	(%rdi,%r8,4), %rsi
	.p2align 4,,10
	.p2align 3
.L1155:
	paddd	(%rdx), %xmm0
	paddd	16(%rdx), %xmm1
	addq	$32, %rdx
	cmpq	%rdx, %rsi
	jne	.L1155
.L1154:
	paddd	%xmm1, %xmm0
	cmpq	%rcx, %r8
	jge	.L1153
	paddd	(%rdi,%r8,4), %xmm0
.L1153:
	movdqa	%xmm0, %xmm1
	punpckhqdq	%xmm0, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %esi
	pshufd	$1, %xmm0, %xmm0
	movd	%xmm0, %edx
	addl	%esi, %edx
	movl	%edx, 136(%rsp)
	movq	32(%rsp), %rdx
	cmpq	%rcx, %rdx
	jle	.L1157
	movq	%rdx, %rsi
	subq	%rcx, %rsi
	leaq	-1(%rsi), %rdx
	cmpq	$2, %rdx
	jbe	.L1158
	movq	%rsi, %rdx
	salq	$4, %rax
	pxor	%xmm0, %xmm0
	shrq	$2, %rdx
	addq	%rdi, %rax
	salq	$4, %rdx
	addq	%rax, %rdx
	.p2align 4,,10
	.p2align 3
.L1159:
	movdqu	(%rax), %xmm7
	addq	$16, %rax
	paddd	%xmm7, %xmm0
	cmpq	%rax, %rdx
	jne	.L1159
	movdqa	%xmm0, %xmm1
	psrldq	$8, %xmm1
	paddd	%xmm1, %xmm0
	movdqa	%xmm0, %xmm1
	psrldq	$4, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %eax
	addl	%eax, 136(%rsp)
	movq	%rsi, %rax
	andq	$-4, %rax
	addq	%rax, %rcx
	cmpq	%rax, %rsi
	je	.L1157
.L1158:
	movq	32(%rsp), %r11
	leaq	1(%rcx), %rdx
	movl	(%rdi,%rcx,4), %esi
	leaq	0(,%rcx,4), %rax
	addl	%esi, 136(%rsp)
	movl	136(%rsp), %esi
	cmpq	%rdx, %r11
	jle	.L1157
	movl	%esi, %edx
	movl	4(%rdi,%rax), %esi
	addq	$2, %rcx
	addl	%esi, %edx
	movl	%edx, 136(%rsp)
	cmpq	%r11, %rcx
	jge	.L1157
	movl	8(%rdi,%rax), %eax
	addl	%eax, %edx
	movl	%edx, 136(%rsp)
.L1157:
	call	free@PLT
.L1306:
.L1138:
	call	_ZNSt6chrono3_V212system_clock3nowEv@PLT
	movq	40(%rsp), %rsi
	movq	104(%rsp), %rdi
	movq	%r12, %rdx
	subq	%rbx, %rax
	movq	%rax, 328(%rsp)
	movq	%rax, 368(%rsp)
	call	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14vectorMultiplyERN5Eigen6MatrixIiLin1ELi1ELi0ELin1ELi1EEE
.LEHE33:
	leaq	768(%rsp), %rbx
	movl	$10, %esi
	leaq	704(%rsp), %rax
	movl	$32, %edi
	movq	%rbx, 64(%rsp)
	movq	%rbx, 752(%rsp)
	leaq	800(%rsp), %rbx
	movq	%rbx, 72(%rsp)
	movq	%rbx, 784(%rsp)
	leaq	832(%rsp), %rbx
	movq	%rax, 96(%rsp)
	movq	%rax, 688(%rsp)
	leaq	736(%rsp), %rax
	movq	%rbx, 80(%rsp)
	movq	%rax, %rdx
	movq	%rbx, 816(%rsp)
	leaq	864(%rsp), %rbx
	movw	%si, 832(%rsp)
	movq	%rax, %rsi
	movq	%rbx, 88(%rsp)
	movq	%rbx, 848(%rsp)
	leaq	896(%rsp), %rbx
	movw	%di, 864(%rsp)
	leaq	880(%rsp), %rdi
	movq	$0, 696(%rsp)
	movb	$0, 704(%rsp)
	movq	%rax, 56(%rsp)
	movq	%rax, 720(%rsp)
	movq	$0, 728(%rsp)
	movb	$0, 736(%rsp)
	movq	$0, 760(%rsp)
	movb	$0, 768(%rsp)
	movq	$0, 792(%rsp)
	movb	$0, 800(%rsp)
	movq	$1, 824(%rsp)
	movq	$1, 856(%rsp)
	movq	%rdi, 24(%rsp)
	movq	%rbx, 256(%rsp)
	movq	%rbx, 880(%rsp)
.LEHB34:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE34:
	leaq	928(%rsp), %rax
	movq	688(%rsp), %rsi
	movq	696(%rsp), %rdx
	movq	%rax, 264(%rsp)
	movq	%rax, 912(%rsp)
	leaq	912(%rsp), %rax
	addq	%rsi, %rdx
	movq	%rax, %rdi
	movq	%rax, 296(%rsp)
.LEHB35:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE35:
	movq	784(%rsp), %r13
	leaq	960(%rsp), %rax
	movq	792(%rsp), %r12
	movq	%rax, 168(%rsp)
	movq	%rax, 944(%rsp)
	movq	%r13, %rax
	addq	%r12, %rax
	je	.L1164
	testq	%r13, %r13
	je	.L1480
.L1164:
	movq	%r12, 376(%rsp)
	cmpq	$15, %r12
	ja	.L1481
	cmpq	$1, %r12
	jne	.L1167
	movzbl	0(%r13), %eax
	movb	%al, 960(%rsp)
	movq	168(%rsp), %rax
.L1168:
	movq	%r12, 952(%rsp)
	movb	$0, (%rax,%r12)
	leaq	992(%rsp), %rax
	movq	752(%rsp), %rsi
	movq	760(%rsp), %rdx
	movq	%rax, 272(%rsp)
	movq	%rax, 976(%rsp)
	leaq	976(%rsp), %rax
	addq	%rsi, %rdx
	movq	%rax, %rdi
	movq	%rax, 304(%rsp)
.LEHB36:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE36:
	leaq	1024(%rsp), %rax
	movq	816(%rsp), %rsi
	movq	824(%rsp), %rdx
	movq	%rax, 280(%rsp)
	movq	%rax, 1008(%rsp)
	leaq	1008(%rsp), %rax
	addq	%rsi, %rdx
	movq	%rax, %rdi
	movq	%rax, 312(%rsp)
.LEHB37:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE37:
	leaq	1056(%rsp), %rax
	movq	848(%rsp), %rsi
	movq	856(%rsp), %rdx
	movq	$0, 1048(%rsp)
	movq	%rax, (%rsp)
	movq	%rax, 1040(%rsp)
	leaq	1088(%rsp), %rax
	addq	%rsi, %rdx
	movq	%rax, 288(%rsp)
	movq	%rax, 1072(%rsp)
	leaq	1072(%rsp), %rax
	movq	%rax, %rdi
	movb	$0, 1056(%rsp)
	movq	%rax, 320(%rsp)
.LEHB38:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE38:
	movq	.LC55(%rip), %rax
	movb	$32, 1104(%rsp)
	movq	%rax, 1108(%rsp)
	movq	920(%rsp), %rax
	movl	%eax, %edx
	subl	$1, %edx
	js	.L1171
	movslq	%eax, %r14
	movslq	%edx, %r12
	movl	%edx, %edx
	subq	$2, %r14
	subq	%rdx, %r14
	movq	%r14, 16(%rsp)
	movl	$15, %r14d
	jmp	.L1174
	.p2align 4,,10
	.p2align 3
.L1173:
	movb	$32, (%rax,%rbx)
	movq	1040(%rsp), %rax
	subq	$1, %r12
	movq	%r13, 1048(%rsp)
	movb	$0, 1(%rax,%rbx)
	cmpq	%r12, 16(%rsp)
	je	.L1171
.L1174:
	movq	912(%rsp), %rax
	cmpb	$10, (%rax,%r12)
	je	.L1171
	movq	1048(%rsp), %rbx
	movq	1040(%rsp), %rax
	movq	%r14, %rdx
	cmpq	(%rsp), %rax
	cmovne	1056(%rsp), %rdx
	leaq	1(%rbx), %r13
	cmpq	%rdx, %r13
	jbe	.L1173
	leaq	1040(%rsp), %rdi
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movq	%rbx, %rsi
	movl	$1, %r8d
.LEHB39:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm@PLT
.LEHE39:
	movq	1040(%rsp), %rax
	jmp	.L1173
.L1284:
	xorl	%edx, %edx
	jmp	.L1092
.L1095:
	movq	8(%rsp), %rax
	movl	(%rcx), %edx
	cmpq	$1, %rax
	je	.L1092
	leaq	-1(%rax), %rdi
	subq	$2, %rax
	cmpq	$2, %rax
	jbe	.L1285
	movq	%rdi, %rax
	pxor	%xmm0, %xmm0
	shrq	$2, %rax
	salq	$4, %rax
	addq	%rcx, %rax
	.p2align 4,,10
	.p2align 3
.L1108:
	movdqu	4(%rsi), %xmm6
	addq	$16, %rsi
	paddd	%xmm6, %xmm0
	cmpq	%rsi, %rax
	jne	.L1108
	movdqa	%xmm0, %xmm1
	movq	%rdi, %rsi
	psrldq	$8, %xmm1
	andq	$-4, %rsi
	paddd	%xmm1, %xmm0
	movdqa	%xmm0, %xmm1
	psrldq	$4, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %eax
	addl	%eax, %edx
	leaq	1(%rsi), %rax
	cmpq	%rdi, %rsi
	je	.L1092
.L1107:
	movq	8(%rsp), %rbx
	leaq	1(%rax), %rdi
	leaq	0(,%rax,4), %rsi
	addl	(%rcx,%rax,4), %edx
	cmpq	%rbx, %rdi
	jge	.L1092
	addq	$2, %rax
	addl	4(%rcx,%rsi), %edx
	cmpq	%rbx, %rax
	jge	.L1092
	addl	8(%rcx,%rsi), %edx
	jmp	.L1092
.L1472:
	movq	536(%rsp), %rax
	movq	8(%rsp), %rbx
	movl	(%rax,%rbx,4), %edx
	subl	(%rax), %edx
	jmp	.L1092
.L1467:
	cmpq	%rbp, %r12
	jg	.L1428
	movabsq	$4611686018427387903, %rdx
	movq	552(%rsp), %rdi
	movq	%rbx, %rax
	cmpq	%rdx, %rbp
	ja	.L1429
	movq	%rbp, %rbx
	jmp	.L1064
.L1468:
	testq	%rbp, %rbp
	je	.L1067
	movq	%rbp, %rdi
	movq	%r8, (%rsp)
	call	malloc@PLT
	cmpq	$15, %rbp
	movq	(%rsp), %r8
	jbe	.L1068
	testb	$15, %al
	jne	.L1069
.L1068:
	testq	%rax, %rax
	je	.L1431
	movq	560(%rsp), %rdi
	movq	%rax, 552(%rsp)
	testq	%rdi, %rdi
	jne	.L1482
.L1276:
	movq	%rbp, %rdi
	movq	%r8, (%rsp)
	call	malloc@PLT
	cmpq	$15, %rbp
	movq	(%rsp), %r8
	movq	%rax, %rdi
	jbe	.L1076
	testb	$15, %al
	jne	.L1069
.L1076:
	testq	%rdi, %rdi
	jne	.L1077
	jmp	.L1433
.L1071:
	movq	560(%rsp), %rdi
	testq	%rdi, %rdi
	jne	.L1077
	testq	%rbp, %rbp
	jne	.L1276
.L1073:
	xorl	%edi, %edi
	jmp	.L1077
	.p2align 4,,10
	.p2align 3
.L1171:
	movq	24(%rsp), %rdx
	movq	104(%rsp), %rsi
	movq	176(%rsp), %rdi
.LEHB40:
	call	_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0
.LEHE40:
	movq	24(%rsp), %rdi
	call	_ZN5Eigen8IOFormatD1Ev
	movq	848(%rsp), %rdi
	cmpq	88(%rsp), %rdi
	je	.L1189
	movq	864(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1189:
	movq	816(%rsp), %rdi
	cmpq	80(%rsp), %rdi
	je	.L1190
	movq	832(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1190:
	movq	784(%rsp), %rdi
	cmpq	72(%rsp), %rdi
	je	.L1191
	movq	800(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1191:
	movq	752(%rsp), %rdi
	cmpq	64(%rsp), %rdi
	je	.L1192
	movq	768(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1192:
	movq	720(%rsp), %rdi
	cmpq	56(%rsp), %rdi
	je	.L1193
	movq	736(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1193:
	movq	688(%rsp), %rdi
	cmpq	96(%rsp), %rdi
	je	.L1194
	movq	704(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1194:
	movq	400(%rsp), %rdi
	call	free@PLT
	movq	8(%rsp), %rax
	cmpq	%rax, 392(%rsp)
	jne	.L1196
	movq	64(%rsp), %rbx
	movq	96(%rsp), %rax
	movl	$32, %ecx
	movq	$0, 696(%rsp)
	movq	56(%rsp), %rdx
	movq	24(%rsp), %rdi
	movb	$0, 704(%rsp)
	movq	%rbx, 752(%rsp)
	movq	72(%rsp), %rbx
	movq	%rax, 688(%rsp)
	movq	%rdx, %rsi
	movl	$10, %eax
	movq	%rbx, 784(%rsp)
	movq	80(%rsp), %rbx
	movq	%rdx, 720(%rsp)
	movq	%rbx, 816(%rsp)
	movq	88(%rsp), %rbx
	movq	$0, 728(%rsp)
	movq	%rbx, 848(%rsp)
	movq	256(%rsp), %rbx
	movb	$0, 736(%rsp)
	movq	$0, 760(%rsp)
	movb	$0, 768(%rsp)
	movq	$0, 792(%rsp)
	movb	$0, 800(%rsp)
	movq	$1, 824(%rsp)
	movw	%ax, 832(%rsp)
	movq	$1, 856(%rsp)
	movw	%cx, 864(%rsp)
	movq	%rbx, 880(%rsp)
.LEHB41:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE41:
	movq	688(%rsp), %rsi
	movq	696(%rsp), %rdx
	movq	264(%rsp), %rax
	movq	296(%rsp), %rdi
	addq	%rsi, %rdx
	movq	%rax, 912(%rsp)
.LEHB42:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE42:
	movq	784(%rsp), %rsi
	movq	792(%rsp), %rdx
	leaq	944(%rsp), %rdi
	movq	168(%rsp), %rax
	addq	%rsi, %rdx
	movq	%rax, 944(%rsp)
.LEHB43:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE43:
	movq	752(%rsp), %rsi
	movq	760(%rsp), %rdx
	movq	272(%rsp), %rax
	movq	304(%rsp), %rdi
	addq	%rsi, %rdx
	movq	%rax, 976(%rsp)
.LEHB44:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE44:
	movq	816(%rsp), %rsi
	movq	824(%rsp), %rdx
	movq	280(%rsp), %rax
	movq	312(%rsp), %rdi
	addq	%rsi, %rdx
	movq	%rax, 1008(%rsp)
.LEHB45:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE45:
	movq	(%rsp), %rax
	movq	848(%rsp), %rsi
	movq	$0, 1048(%rsp)
	movq	856(%rsp), %rdx
	movq	320(%rsp), %rdi
	movb	$0, 1056(%rsp)
	movq	%rax, 1040(%rsp)
	movq	288(%rsp), %rax
	addq	%rsi, %rdx
	movq	%rax, 1072(%rsp)
.LEHB46:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPcEEvT_S7_St20forward_iterator_tag.isra.0
.LEHE46:
	movq	.LC55(%rip), %rax
	movb	$32, 1104(%rsp)
	movq	%rax, 1108(%rsp)
	movq	920(%rsp), %rax
	movl	%eax, %edx
	subl	$1, %edx
	js	.L1207
	movslq	%eax, %r14
	movslq	%edx, %r12
	movl	%edx, %edx
	subq	$2, %r14
	subq	%rdx, %r14
	movq	%r14, 16(%rsp)
	movl	$15, %r14d
	jmp	.L1210
	.p2align 4,,10
	.p2align 3
.L1209:
	movb	$32, (%rax,%rbx)
	movq	1040(%rsp), %rax
	subq	$1, %r12
	movq	%r13, 1048(%rsp)
	movb	$0, 1(%rax,%rbx)
	cmpq	%r12, 16(%rsp)
	je	.L1207
.L1210:
	movq	912(%rsp), %rax
	cmpb	$10, (%rax,%r12)
	je	.L1207
	movq	1048(%rsp), %rbx
	movq	1040(%rsp), %rax
	movq	%r14, %rdx
	cmpq	(%rsp), %rax
	cmovne	1056(%rsp), %rdx
	leaq	1(%rbx), %r13
	cmpq	%rdx, %r13
	jbe	.L1209
	leaq	1040(%rsp), %rdi
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	movq	%rbx, %rsi
	movl	$1, %r8d
.LEHB47:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_mutateEmmPKcm@PLT
.LEHE47:
	movq	1040(%rsp), %rax
	jmp	.L1209
.L1207:
	movq	$0, 400(%rsp)
	xorl	%ecx, %ecx
	cmpq	$0, 32(%rsp)
	movq	$0, 408(%rsp)
	je	.L1278
	js	.L1483
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, 32(%rsp)
	jg	.L1444
	movq	32(%rsp), %rax
	movl	$1, %esi
	leaq	0(,%rax,4), %rbx
	movq	%rbx, %rdi
	call	calloc@PLT
	movq	%rax, %rcx
	cmpq	$15, %rbx
	jbe	.L1227
	testb	$15, %al
	jne	.L1069
.L1227:
	testq	%rcx, %rcx
	je	.L1445
	movq	32(%rsp), %rax
	movq	%rcx, 400(%rsp)
	movq	%rax, 408(%rsp)
.L1278:
	cmpq	$0, 8(%rsp)
	jle	.L1235
	movq	384(%rsp), %r11
	movq	544(%rsp), %r10
	xorl	%r9d, %r9d
	movq	128(%rsp), %rbx
	movq	8(%rsp), %r12
	.p2align 4,,10
	.p2align 3
.L1234:
	movl	(%r11,%r9,4), %r8d
	movslq	(%rbx,%r9,4), %rsi
	testq	%r10, %r10
	je	.L1484
	movslq	(%r10,%r9,4), %rdx
	addq	%rsi, %rdx
.L1232:
	leaq	0(,%rsi,4), %rax
	leaq	0(,%rdx,4), %rdi
	cmpq	%rdx, %rsi
	jge	.L1237
	.p2align 4,,10
	.p2align 3
.L1236:
	movl	0(%rbp,%rax), %esi
	movslq	(%r15,%rax), %rdx
	addq	$4, %rax
	imull	%r8d, %esi
	addl	%esi, (%rcx,%rdx,4)
	cmpq	%rax, %rdi
	jne	.L1236
.L1237:
	addq	$1, %r9
	cmpq	%r12, %r9
	jne	.L1234
.L1235:
	movq	24(%rsp), %rdx
	movq	104(%rsp), %rsi
	movq	216(%rsp), %rdi
.LEHB48:
	call	_ZN5Eigen8internal12print_matrixINS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEERSoS4_RKT_RKNS_8IOFormatE.isra.0
.LEHE48:
	movq	400(%rsp), %rdi
	call	free@PLT
	movq	24(%rsp), %rdi
	call	_ZN5Eigen8IOFormatD1Ev
	movq	848(%rsp), %rdi
	cmpq	88(%rsp), %rdi
	je	.L1238
	movq	864(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1238:
	movq	816(%rsp), %rdi
	cmpq	80(%rsp), %rdi
	je	.L1239
	movq	832(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1239:
	movq	784(%rsp), %rdi
	cmpq	72(%rsp), %rdi
	je	.L1240
	movq	800(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1240:
	movq	752(%rsp), %rdi
	cmpq	64(%rsp), %rdi
	je	.L1241
	movq	768(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1241:
	movq	720(%rsp), %rdi
	cmpq	56(%rsp), %rdi
	je	.L1242
	movq	736(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1242:
	movq	688(%rsp), %rdi
	cmpq	96(%rsp), %rdi
	je	.L1243
	movq	704(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1243:
	movl	136(%rsp), %ebx
	cmpl	%ebx, 140(%rsp)
	jne	.L1485
	movq	184(%rsp), %rsi
	movq	144(%rsp), %rdi
.LEHB49:
	call	_Z15compareOstreamsRNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEES5_
	testb	%al, %al
	je	.L1486
	movq	328(%rsp), %rbx
	movq	160(%rsp), %rdx
	leaq	.LC63(%rip), %rsi
	xorl	%eax, %eax
	movl	$1, %edi
	movq	%rbx, %rcx
	call	__printf_chk@PLT
.LEHE49:
	movq	456(%rsp), %rsi
	cmpq	464(%rsp), %rsi
	je	.L1255
	movq	%rbx, (%rsi)
	addq	$8, %rsi
	movq	%rsi, 456(%rsp)
.L1256:
	movq	424(%rsp), %rsi
	cmpq	432(%rsp), %rsi
	je	.L1257
	movq	160(%rsp), %rax
	addq	$8, %rsi
	movq	%rax, -8(%rsi)
	movq	%rsi, 424(%rsp)
.L1258:
	movq	384(%rsp), %rdi
	call	free@PLT
	movq	40(%rsp), %rdi
	call	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED1Ev
	movq	128(%rsp), %rdi
	call	free@PLT
	movq	544(%rsp), %rdi
	call	free@PLT
	movq	%rbp, %rdi
	call	free@PLT
	movq	%r15, %rdi
	call	free@PLT
	movq	480(%rsp), %rdi
	call	free@PLT
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movdqa	240(%rsp), %xmm3
	movq	1616(%rsp), %rdi
	movq	%rax, 1520(%rsp)
	addq	$80, %rax
	movq	%rax, 1648(%rsp)
	movaps	%xmm3, 1536(%rsp)
	cmpq	232(%rsp), %rdi
	je	.L1259
	movq	1632(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1259:
	movq	224(%rsp), %rdi
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 1544(%rsp)
	call	_ZNSt6localeD1Ev@PLT
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	192(%rsp), %rdi
	movq	-24(%rax), %rax
	movq	%rbx, 1520(%rsp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	%rax, 1536(%rsp)
	movq	-24(%rax), %rax
	movq	%rbx, 1536(%rsp,%rax)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	%rax, 1520(%rsp)
	movq	-24(%rax), %rax
	movq	%rbx, 1520(%rsp,%rax)
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 1648(%rsp)
	movq	$0, 1528(%rsp)
	call	_ZNSt8ios_baseD2Ev@PLT
	leaq	24+_ZTVNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movdqa	240(%rsp), %xmm3
	movq	1216(%rsp), %rdi
	movq	%rax, 1120(%rsp)
	addq	$80, %rax
	movq	%rax, 1248(%rsp)
	movaps	%xmm3, 1136(%rsp)
	cmpq	208(%rsp), %rdi
	je	.L1260
	movq	1232(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1260:
	movq	200(%rsp), %rdi
	leaq	16+_ZTVSt15basic_streambufIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 1144(%rsp)
	call	_ZNSt6localeD1Ev@PLT
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	152(%rsp), %rdi
	movq	-24(%rax), %rax
	movq	%rbx, 1120(%rsp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	%rax, 1136(%rsp)
	movq	-24(%rax), %rax
	movq	%rbx, 1136(%rsp,%rax)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rbx
	movq	%rax, 1120(%rsp)
	movq	-24(%rax), %rax
	movq	%rbx, 1120(%rsp,%rax)
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 1248(%rsp)
	movq	$0, 1128(%rsp)
	call	_ZNSt8ios_baseD2Ev@PLT
	addl	$1, 52(%rsp)
	movl	52(%rsp), %eax
	cmpl	$1000, %eax
	jne	.L1261
	movq	416(%rsp), %rbp
	xorl	%eax, %eax
	xorl	%r14d, %r14d
	movq	424(%rsp), %rcx
	movq	448(%rsp), %r12
	movq	344(%rsp), %rdx
	subq	%rbp, %rcx
	sarq	$3, %rcx
	jmp	.L1262
.L1263:
	addq	0(%rbp,%rax,8), %rdx
	addq	(%r12,%rax,8), %r14
	addq	$1, %rax
.L1262:
	cmpq	%rax, %rcx
	jne	.L1263
	movq	%rdx, %rax
	xorl	%edx, %edx
	leaq	.LC64(%rip), %rsi
	divq	%rcx
	movq	456(%rsp), %rcx
	subq	%r12, %rcx
	xorl	%edx, %edx
	leaq	_ZSt4cout(%rip), %rdi
	sarq	$3, %rcx
	movq	%rax, %r13
	movq	%r14, %rax
	divq	%rcx
	movl	$10, %edx
	movq	%rax, %r14
.LEHB50:
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r13, %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@PLT
	movl	$7, %edx
	leaq	.LC65(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%r14, %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZNSo9_M_insertImEERSoT_@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@PLT
.LEHE50:
	testq	%r12, %r12
	je	.L1264
	movq	464(%rsp), %rsi
	movq	%r12, %rdi
	subq	%r12, %rsi
	call	_ZdlPvm@PLT
.L1264:
	testq	%rbp, %rbp
	je	.L1265
	movq	432(%rsp), %rsi
	movq	%rbp, %rdi
	subq	%rbp, %rsi
	call	_ZdlPvm@PLT
.L1265:
	movq	1912(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1487
	addq	$1928, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1484:
	.cfi_restore_state
	movslq	4(%rbx,%r9,4), %rdx
	jmp	.L1232
.L1122:
	movq	%r13, %rdi
.LEHB51:
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%r13), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L1123
	movq	%r13, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L1123
.L1119:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%r13), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L1120
	movq	%r13, %rdi
	call	*%rax
	movsbl	%al, %esi
	jmp	.L1120
.L1116:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv@PLT
	movq	0(%r13), %rax
	leaq	_ZNKSt5ctypeIcE8do_widenEc(%rip), %rdx
	movl	$10, %esi
	movq	48(%rax), %rax
	cmpq	%rdx, %rax
	je	.L1117
	movq	%r13, %rdi
	call	*%rax
.LEHE51:
	movsbl	%al, %esi
	jmp	.L1117
.L1124:
	jle	.L1488
	leaq	3(%rcx), %rax
	movq	400(%rsp), %rdi
	cmpq	$6, %rax
	jbe	.L1127
	movq	%rcx, %rax
	movq	%rcx, %rsi
	movdqa	(%rdi), %xmm0
	sarq	$2, %rax
	andq	$-4, %rsi
	cmpq	$1, %rax
	je	.L1128
	movq	%rcx, %r9
	movdqa	16(%rdi), %xmm1
	andq	$-8, %r9
	cmpq	$8, %r9
	jle	.L1129
	leaq	32(%rdi), %rdx
	leaq	(%rdi,%r9,4), %r8
	.p2align 4,,10
	.p2align 3
.L1130:
	paddd	(%rdx), %xmm0
	paddd	16(%rdx), %xmm1
	addq	$32, %rdx
	cmpq	%r8, %rdx
	jne	.L1130
.L1129:
	paddd	%xmm1, %xmm0
	cmpq	%rsi, %r9
	jge	.L1128
	paddd	(%rdi,%r9,4), %xmm0
.L1128:
	movdqa	%xmm0, %xmm1
	punpckhqdq	%xmm0, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %r8d
	pshufd	$1, %xmm0, %xmm0
	movd	%xmm0, %edx
	addl	%r8d, %edx
	movl	%edx, 140(%rsp)
	cmpq	%rsi, %rcx
	jle	.L1125
	movq	%rcx, %r8
	subq	%rsi, %r8
	leaq	-1(%r8), %rdx
	cmpq	$2, %rdx
	jbe	.L1133
	movq	%r8, %rdx
	salq	$4, %rax
	pxor	%xmm0, %xmm0
	shrq	$2, %rdx
	addq	%rdi, %rax
	salq	$4, %rdx
	addq	%rax, %rdx
	.p2align 4,,10
	.p2align 3
.L1134:
	movdqu	(%rax), %xmm7
	addq	$16, %rax
	paddd	%xmm7, %xmm0
	cmpq	%rax, %rdx
	jne	.L1134
	movdqa	%xmm0, %xmm1
	psrldq	$8, %xmm1
	paddd	%xmm1, %xmm0
	movdqa	%xmm0, %xmm1
	psrldq	$4, %xmm1
	paddd	%xmm1, %xmm0
	movd	%xmm0, %eax
	addl	%eax, 140(%rsp)
	movq	%r8, %rax
	andq	$-4, %rax
	addq	%rax, %rsi
	cmpq	%r8, %rax
	je	.L1125
.L1133:
	leaq	1(%rsi), %rdx
	movl	(%rdi,%rsi,4), %r11d
	leaq	0(,%rsi,4), %rax
	addl	%r11d, 140(%rsp)
	movl	140(%rsp), %r11d
	cmpq	%rdx, %rcx
	jle	.L1125
	movl	%r11d, %edx
	movl	4(%rdi,%rax), %r11d
	addq	$2, %rsi
	addl	%r11d, %edx
	movl	%edx, 140(%rsp)
	cmpq	%rsi, %rcx
	jle	.L1125
	movl	8(%rdi,%rax), %eax
	addl	%eax, %edx
	movl	%edx, 140(%rsp)
	jmp	.L1125
.L1167:
	testq	%r12, %r12
	jne	.L1489
	movq	168(%rsp), %rax
	jmp	.L1168
.L1481:
	leaq	376(%rsp), %rsi
	leaq	944(%rsp), %rdi
	xorl	%edx, %edx
.LEHB52:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm@PLT
.LEHE52:
	movq	%rax, 944(%rsp)
	movq	%rax, %rdi
	movq	376(%rsp), %rax
	movq	%rax, 960(%rsp)
.L1166:
	movq	%r12, %rdx
	movq	%r13, %rsi
	call	memcpy@PLT
	movq	376(%rsp), %r12
	movq	944(%rsp), %rax
	jmp	.L1168
.L1127:
	movl	(%rdi), %eax
	movl	%eax, 140(%rsp)
	cmpq	$1, %rcx
	je	.L1125
	movl	4(%rdi), %edx
	addl	%edx, %eax
	movl	%eax, 140(%rsp)
	cmpq	$3, %rcx
	jne	.L1125
	movl	8(%rdi), %ecx
	addl	%ecx, %eax
	movl	%eax, 140(%rsp)
	jmp	.L1125
.L1257:
	leaq	360(%rsp), %rdx
	leaq	416(%rsp), %rdi
.LEHB53:
	call	_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_
	jmp	.L1258
.L1255:
	leaq	368(%rsp), %rdx
	leaq	448(%rsp), %rdi
	call	_ZNSt6vectorImSaImEE17_M_realloc_insertIJRKmEEEvN9__gnu_cxx17__normal_iteratorIPmS1_EEDpOT_
.LEHE53:
	jmp	.L1256
.L1469:
	call	free@PLT
	movq	560(%rsp), %rdi
	movq	(%rsp), %r8
	movq	$0, 552(%rsp)
	testq	%rdi, %rdi
	je	.L1073
.L1074:
	movq	%r8, (%rsp)
	call	free@PLT
	movq	(%rsp), %r8
	xorl	%edi, %edi
	jmp	.L1077
.L1085:
	movq	560(%rsp), %rdi
	testq	%rdi, %rdi
	jne	.L1091
	testq	%rbp, %rbp
	je	.L1087
.L1270:
	movq	%rbp, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %rbp
	jbe	.L1090
	testb	$15, %al
	jne	.L1069
.L1090:
	testq	%rdi, %rdi
	jne	.L1091
	jmp	.L1439
.L1470:
	testq	%rbp, %rbp
	je	.L1082
	movq	%rbp, %rdi
	call	malloc@PLT
	cmpq	$15, %rbp
	jbe	.L1083
	testb	$15, %al
	jne	.L1069
.L1083:
	testq	%rax, %rax
	je	.L1437
	movq	560(%rsp), %rdi
	movq	%rax, 552(%rsp)
	testq	%rdi, %rdi
	je	.L1270
	cmpq	%rbp, %rbx
	jne	.L1279
	jmp	.L1091
.L1471:
	call	free@PLT
	movq	560(%rsp), %rdi
	movq	$0, 552(%rsp)
	testq	%rdi, %rdi
	je	.L1087
.L1088:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L1091
	.p2align 4,,10
	.p2align 3
.L1478:
	movslq	4(%r13,%r9,4), %rdx
	jmp	.L1147
.L1479:
	movl	(%rdi), %eax
	movq	32(%rsp), %rcx
	movl	%eax, 136(%rsp)
	cmpq	$1, %rcx
	je	.L1157
	movl	4(%rdi), %edx
	addl	%edx, %eax
	movl	%eax, 136(%rsp)
	cmpq	$3, %rcx
	jne	.L1157
	movl	8(%rdi), %ecx
	addl	%ecx, %eax
	movl	%eax, 136(%rsp)
	jmp	.L1157
.L1067:
	movq	560(%rsp), %rdi
	testq	%rdi, %rdi
	je	.L1073
	testq	%r13, %r13
	jne	.L1074
	jmp	.L1077
.L1285:
	movl	$1, %eax
	jmp	.L1107
.L1082:
	movq	560(%rsp), %rdi
	testq	%rdi, %rdi
	jne	.L1490
.L1087:
	xorl	%edi, %edi
	jmp	.L1091
.L1488:
	leaq	.LC48(%rip), %rcx
	movl	$498, %edx
	leaq	.LC49(%rip), %rsi
	leaq	.LC50(%rip), %rdi
	call	__assert_fail@PLT
.L1489:
	movq	168(%rsp), %rdi
	jmp	.L1166
.L1486:
	leaq	.LC59(%rip), %rcx
	movl	$74, %edx
	leaq	.LC60(%rip), %rsi
	leaq	.LC62(%rip), %rdi
	call	__assert_fail@PLT
.L1485:
	leaq	.LC59(%rip), %rcx
	movl	$72, %edx
	leaq	.LC60(%rip), %rsi
	leaq	.LC61(%rip), %rdi
	call	__assert_fail@PLT
.L1483:
	leaq	.LC56(%rip), %rcx
	movl	$285, %edx
	leaq	.LC57(%rip), %rsi
	leaq	.LC58(%rip), %rdi
	call	__assert_fail@PLT
.L1480:
	leaq	.LC9(%rip), %rdi
.LEHB54:
	call	_ZSt19__throw_logic_errorPKc@PLT
.LEHE54:
.L1477:
	leaq	.LC54(%rip), %rcx
	movl	$498, %edx
	leaq	.LC49(%rip), %rsi
	leaq	.LC50(%rip), %rdi
	call	__assert_fail@PLT
.L1196:
	leaq	.LC51(%rip), %rcx
	movl	$98, %edx
	leaq	.LC52(%rip), %rsi
	leaq	.LC53(%rip), %rdi
	call	__assert_fail@PLT
.L1476:
.LEHB55:
	call	_ZSt16__throw_bad_castv@PLT
.L1473:
	leaq	.LC42(%rip), %rcx
	movl	$168, %edx
	leaq	.LC43(%rip), %rsi
	leaq	.LC44(%rip), %rdi
	call	__assert_fail@PLT
.L1475:
	call	_ZSt16__throw_bad_castv@PLT
.L1474:
	call	_ZSt16__throw_bad_castv@PLT
.LEHE55:
.L1487:
	call	__stack_chk_fail@PLT
.L1482:
	cmpq	%rbp, %r13
	jne	.L1280
	jmp	.L1077
.L1490:
	testq	%rbx, %rbx
	jne	.L1088
	jmp	.L1091
.L1293:
	endbr64
	movq	%rax, %rbx
	jmp	.L1039
.L1304:
	endbr64
	movq	%rax, %rbx
	jmp	.L1051
.L1301:
	endbr64
	movq	%rax, %rbx
	jmp	.L1043
.L1302:
	endbr64
	movq	%rax, %rbx
	jmp	.L1041
.L1300:
	endbr64
	movq	%rax, %rbx
	jmp	.L1042
.L1298:
	endbr64
	movq	%rax, %rbx
	jmp	.L1038
.L1299:
	endbr64
	movq	%rax, %rbx
	jmp	.L1036
.L1297:
	endbr64
	movq	%rax, %rbx
	jmp	.L1037
.L1323:
	endbr64
	movq	%rax, %rbx
	jmp	.L1211
.L1322:
	endbr64
	movq	%rax, %rbx
	jmp	.L1213
.L1321:
	endbr64
	movq	%rax, %rbx
	jmp	.L1216
.L1310:
	endbr64
	movq	%rax, %rbx
	jmp	.L1184
.L1317:
	endbr64
	movq	%rax, %rbx
	jmp	.L1246
.L1320:
	endbr64
	movq	%rax, %rbx
	jmp	.L1218
.L1319:
	endbr64
	movq	%rax, %rbx
	jmp	.L1220
.L1318:
	endbr64
	movq	%rax, %rbx
	jmp	.L1222
.L1315:
	endbr64
	movq	%rax, %rbx
	jmp	.L1224
.L1308:
	endbr64
	movq	%rax, %rbx
	jmp	.L1197
.L1314:
	endbr64
	movq	%rax, %rbx
	jmp	.L1175
.L1313:
	endbr64
	movq	%rax, %rbx
	jmp	.L1177
.L1312:
	endbr64
	movq	%rax, %rbx
	jmp	.L1180
.L1423:
	endbr64
	jmp	.L1424
.L1425:
	endbr64
	jmp	.L1426
.L1309:
	endbr64
	movq	%rax, %rbx
	jmp	.L1186
.L1311:
	endbr64
	movq	%rax, %rbx
	jmp	.L1182
.L1307:
	endbr64
	movq	%rax, %rbx
	jmp	.L1188
	.section	.gcc_except_table
.LLSDA11239:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE11239-.LLSDACSB11239
.LLSDACSB11239:
	.uleb128 .LEHB24-.LFB11239
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L1293-.LFB11239
	.uleb128 0
	.uleb128 .LEHB25-.LFB11239
	.uleb128 .LEHE25-.LEHB25
	.uleb128 .L1297-.LFB11239
	.uleb128 0
	.uleb128 .LEHB26-.LFB11239
	.uleb128 .LEHE26-.LEHB26
	.uleb128 .L1299-.LFB11239
	.uleb128 0
	.uleb128 .LEHB27-.LFB11239
	.uleb128 .LEHE27-.LEHB27
	.uleb128 .L1298-.LFB11239
	.uleb128 0
	.uleb128 .LEHB28-.LFB11239
	.uleb128 .LEHE28-.LEHB28
	.uleb128 .L1300-.LFB11239
	.uleb128 0
	.uleb128 .LEHB29-.LFB11239
	.uleb128 .LEHE29-.LEHB29
	.uleb128 .L1302-.LFB11239
	.uleb128 0
	.uleb128 .LEHB30-.LFB11239
	.uleb128 .LEHE30-.LEHB30
	.uleb128 .L1301-.LFB11239
	.uleb128 0
	.uleb128 .LEHB31-.LFB11239
	.uleb128 .LEHE31-.LEHB31
	.uleb128 .L1304-.LFB11239
	.uleb128 0
	.uleb128 .LEHB32-.LFB11239
	.uleb128 .LEHE32-.LEHB32
	.uleb128 .L1423-.LFB11239
	.uleb128 0
	.uleb128 .LEHB33-.LFB11239
	.uleb128 .LEHE33-.LEHB33
	.uleb128 .L1425-.LFB11239
	.uleb128 0
	.uleb128 .LEHB34-.LFB11239
	.uleb128 .LEHE34-.LEHB34
	.uleb128 .L1307-.LFB11239
	.uleb128 0
	.uleb128 .LEHB35-.LFB11239
	.uleb128 .LEHE35-.LEHB35
	.uleb128 .L1309-.LFB11239
	.uleb128 0
	.uleb128 .LEHB36-.LFB11239
	.uleb128 .LEHE36-.LEHB36
	.uleb128 .L1311-.LFB11239
	.uleb128 0
	.uleb128 .LEHB37-.LFB11239
	.uleb128 .LEHE37-.LEHB37
	.uleb128 .L1312-.LFB11239
	.uleb128 0
	.uleb128 .LEHB38-.LFB11239
	.uleb128 .LEHE38-.LEHB38
	.uleb128 .L1313-.LFB11239
	.uleb128 0
	.uleb128 .LEHB39-.LFB11239
	.uleb128 .LEHE39-.LEHB39
	.uleb128 .L1314-.LFB11239
	.uleb128 0
	.uleb128 .LEHB40-.LFB11239
	.uleb128 .LEHE40-.LEHB40
	.uleb128 .L1308-.LFB11239
	.uleb128 0
	.uleb128 .LEHB41-.LFB11239
	.uleb128 .LEHE41-.LEHB41
	.uleb128 .L1315-.LFB11239
	.uleb128 0
	.uleb128 .LEHB42-.LFB11239
	.uleb128 .LEHE42-.LEHB42
	.uleb128 .L1318-.LFB11239
	.uleb128 0
	.uleb128 .LEHB43-.LFB11239
	.uleb128 .LEHE43-.LEHB43
	.uleb128 .L1319-.LFB11239
	.uleb128 0
	.uleb128 .LEHB44-.LFB11239
	.uleb128 .LEHE44-.LEHB44
	.uleb128 .L1320-.LFB11239
	.uleb128 0
	.uleb128 .LEHB45-.LFB11239
	.uleb128 .LEHE45-.LEHB45
	.uleb128 .L1321-.LFB11239
	.uleb128 0
	.uleb128 .LEHB46-.LFB11239
	.uleb128 .LEHE46-.LEHB46
	.uleb128 .L1322-.LFB11239
	.uleb128 0
	.uleb128 .LEHB47-.LFB11239
	.uleb128 .LEHE47-.LEHB47
	.uleb128 .L1323-.LFB11239
	.uleb128 0
	.uleb128 .LEHB48-.LFB11239
	.uleb128 .LEHE48-.LEHB48
	.uleb128 .L1317-.LFB11239
	.uleb128 0
	.uleb128 .LEHB49-.LFB11239
	.uleb128 .LEHE49-.LEHB49
	.uleb128 .L1425-.LFB11239
	.uleb128 0
	.uleb128 .LEHB50-.LFB11239
	.uleb128 .LEHE50-.LEHB50
	.uleb128 .L1293-.LFB11239
	.uleb128 0
	.uleb128 .LEHB51-.LFB11239
	.uleb128 .LEHE51-.LEHB51
	.uleb128 .L1425-.LFB11239
	.uleb128 0
	.uleb128 .LEHB52-.LFB11239
	.uleb128 .LEHE52-.LEHB52
	.uleb128 .L1310-.LFB11239
	.uleb128 0
	.uleb128 .LEHB53-.LFB11239
	.uleb128 .LEHE53-.LEHB53
	.uleb128 .L1425-.LFB11239
	.uleb128 0
	.uleb128 .LEHB54-.LFB11239
	.uleb128 .LEHE54-.LEHB54
	.uleb128 .L1310-.LFB11239
	.uleb128 0
	.uleb128 .LEHB55-.LFB11239
	.uleb128 .LEHE55-.LEHB55
	.uleb128 .L1425-.LFB11239
	.uleb128 0
.LLSDACSE11239:
	.section	.text.startup
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDAC11239
	.type	main.cold, @function
main.cold:
.LFSB11239:
.L1433:
	.cfi_def_cfa_offset 1984
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
.LEHB56:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE56:
.L1443:
.LEHB57:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE57:
.L1431:
.LEHB58:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE58:
.L1445:
.LEHB59:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE59:
.L1294:
	endbr64
.L1424:
	movq	%rax, %rbx
.L1267:
	movq	336(%rsp), %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiED1Ev
.L1052:
	movq	480(%rsp), %rdi
	call	free@PLT
.L1050:
	movq	184(%rsp), %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
.L1044:
	movq	144(%rsp), %rdi
	call	_ZNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
.L1039:
	movq	448(%rsp), %rdi
	movq	464(%rsp), %rsi
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	je	.L1268
	call	_ZdlPvm@PLT
.L1268:
	movq	416(%rsp), %rdi
	movq	432(%rsp), %rsi
	subq	%rdi, %rsi
	testq	%rdi, %rdi
	je	.L1269
	call	_ZdlPvm@PLT
.L1269:
	movq	%rbx, %rdi
.LEHB60:
	call	_Unwind_Resume@PLT
.LEHE60:
.L1316:
	endbr64
	movq	%rax, %rbx
.L1247:
	movq	24(%rsp), %rdi
	call	_ZN5Eigen8IOFormatD1Ev
.L1224:
	movq	848(%rsp), %rdi
	cmpq	88(%rsp), %rdi
	je	.L1248
	movq	864(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1248:
	movq	816(%rsp), %rdi
	cmpq	80(%rsp), %rdi
	je	.L1249
	movq	832(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1249:
	movq	784(%rsp), %rdi
	cmpq	72(%rsp), %rdi
	je	.L1250
	movq	800(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1250:
	movq	752(%rsp), %rdi
	cmpq	64(%rsp), %rdi
	je	.L1251
	movq	768(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1251:
	movq	720(%rsp), %rdi
	cmpq	56(%rsp), %rdi
	je	.L1252
	movq	736(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1252:
	movq	688(%rsp), %rdi
	cmpq	96(%rsp), %rdi
	je	.L1163
	movq	704(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1163:
	movq	384(%rsp), %rdi
	call	free@PLT
	movq	40(%rsp), %rdi
	call	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EED1Ev
	jmp	.L1267
.L1296:
.L1295:
	endbr64
.L1426:
	movq	%rax, %rbx
	jmp	.L1163
.L1427:
.LEHB61:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE61:
.L1051:
	movq	552(%rsp), %rdi
	call	free@PLT
	movq	560(%rsp), %rdi
	call	free@PLT
	jmp	.L1052
.L1303:
	endbr64
	movq	480(%rsp), %rdi
	movq	%rax, %rbx
	call	free@PLT
	jmp	.L1050
.L1043:
	movq	%rbp, %rdi
	call	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED1Ev
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	-24(%rax), %rax
	movq	%rcx, 1520(%rsp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1536(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 1536(%rsp,%rax)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1520(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 1520(%rsp,%rax)
	movq	$0, 1528(%rsp)
.L1042:
	movq	192(%rsp), %rdi
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 1648(%rsp)
	call	_ZNSt8ios_baseD2Ev@PLT
	jmp	.L1044
.L1041:
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1520(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 1520(%rsp,%rax)
	movq	$0, 1528(%rsp)
	jmp	.L1042
.L1038:
	movq	%rbp, %rdi
	call	_ZNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEED1Ev
	movq	8+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	48+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	-24(%rax), %rax
	movq	%rcx, 1120(%rsp,%rax)
	movq	32+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	40+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1136(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 1136(%rsp,%rax)
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1120(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 1120(%rsp,%rax)
	movq	$0, 1128(%rsp)
.L1037:
	movq	152(%rsp), %rdi
	leaq	16+_ZTVSt9basic_iosIcSt11char_traitsIcEE(%rip), %rax
	movq	%rax, 1248(%rsp)
	call	_ZNSt8ios_baseD2Ev@PLT
	jmp	.L1039
.L1036:
	movq	16+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rax
	movq	24+_ZTTNSt7__cxx1118basic_stringstreamIcSt11char_traitsIcESaIcEEE(%rip), %rcx
	movq	%rax, 1120(%rsp)
	movq	-24(%rax), %rax
	movq	%rcx, 1120(%rsp,%rax)
	movq	$0, 1128(%rsp)
	jmp	.L1037
.L1437:
.LEHB62:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1211:
	movq	1072(%rsp), %rdi
	cmpq	288(%rsp), %rdi
	je	.L1213
	movq	1088(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1213:
	movq	1040(%rsp), %rdi
	cmpq	(%rsp), %rdi
	je	.L1214
	movq	1056(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1214:
	movq	1008(%rsp), %rdi
	cmpq	280(%rsp), %rdi
	je	.L1216
	movq	1024(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1216:
	movq	976(%rsp), %rdi
	cmpq	272(%rsp), %rdi
	je	.L1218
	movq	992(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1218:
	movq	944(%rsp), %rdi
	cmpq	168(%rsp), %rdi
	je	.L1220
	movq	960(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1220:
	movq	912(%rsp), %rdi
	cmpq	264(%rsp), %rdi
	je	.L1222
	movq	928(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1222:
	movq	880(%rsp), %rdi
	cmpq	256(%rsp), %rdi
	je	.L1224
	movq	896(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
	jmp	.L1224
.L1439:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE62:
.L1444:
.LEHB63:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE63:
.L1175:
	movq	1072(%rsp), %rdi
	cmpq	288(%rsp), %rdi
	je	.L1177
	movq	1088(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1177:
	movq	1040(%rsp), %rdi
	cmpq	(%rsp), %rdi
	jne	.L1491
.L1178:
	movq	1008(%rsp), %rdi
	cmpq	280(%rsp), %rdi
	je	.L1180
	movq	1024(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1180:
	movq	976(%rsp), %rdi
	cmpq	272(%rsp), %rdi
	je	.L1182
	movq	992(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1182:
	movq	944(%rsp), %rdi
	cmpq	168(%rsp), %rdi
	je	.L1184
	movq	960(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1184:
	movq	912(%rsp), %rdi
	cmpq	264(%rsp), %rdi
	je	.L1186
	movq	928(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1186:
	movq	880(%rsp), %rdi
	cmpq	256(%rsp), %rdi
	je	.L1188
	movq	896(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1188:
	movq	848(%rsp), %rdi
	cmpq	88(%rsp), %rdi
	je	.L1198
	movq	864(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1198:
	movq	816(%rsp), %rdi
	cmpq	80(%rsp), %rdi
	je	.L1199
	movq	832(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1199:
	movq	784(%rsp), %rdi
	cmpq	72(%rsp), %rdi
	je	.L1200
	movq	800(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1200:
	movq	752(%rsp), %rdi
	cmpq	64(%rsp), %rdi
	je	.L1201
	movq	768(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1201:
	movq	720(%rsp), %rdi
	cmpq	56(%rsp), %rdi
	je	.L1202
	movq	736(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1202:
	movq	688(%rsp), %rdi
	cmpq	96(%rsp), %rdi
	je	.L1203
	movq	704(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
.L1203:
	movq	400(%rsp), %rdi
	call	free@PLT
	jmp	.L1163
.L1246:
	movq	400(%rsp), %rdi
	call	free@PLT
	jmp	.L1247
.L1197:
	movq	24(%rsp), %rdi
	call	_ZN5Eigen8IOFormatD1Ev
	jmp	.L1188
.L1491:
	movq	1056(%rsp), %rax
	leaq	1(%rax), %rsi
	call	_ZdlPvm@PLT
	jmp	.L1178
.L1429:
.LEHB64:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1428:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1440:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1432:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1430:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE64:
.L1441:
.LEHB65:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE65:
.L1438:
.LEHB66:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1436:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1435:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1434:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE66:
.L1442:
.LEHB67:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.LEHE67:
.L1305:
	endbr64
	jmp	.L1426
	.cfi_endproc
.LFE11239:
	.section	.gcc_except_table
.LLSDAC11239:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSEC11239-.LLSDACSBC11239
.LLSDACSBC11239:
	.uleb128 .LEHB56-.LCOLDB66
	.uleb128 .LEHE56-.LEHB56
	.uleb128 .L1294-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB57-.LCOLDB66
	.uleb128 .LEHE57-.LEHB57
	.uleb128 .L1295-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB58-.LCOLDB66
	.uleb128 .LEHE58-.LEHB58
	.uleb128 .L1294-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB59-.LCOLDB66
	.uleb128 .LEHE59-.LEHB59
	.uleb128 .L1316-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB60-.LCOLDB66
	.uleb128 .LEHE60-.LEHB60
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB61-.LCOLDB66
	.uleb128 .LEHE61-.LEHB61
	.uleb128 .L1303-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB62-.LCOLDB66
	.uleb128 .LEHE62-.LEHB62
	.uleb128 .L1294-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB63-.LCOLDB66
	.uleb128 .LEHE63-.LEHB63
	.uleb128 .L1316-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB64-.LCOLDB66
	.uleb128 .LEHE64-.LEHB64
	.uleb128 .L1294-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB65-.LCOLDB66
	.uleb128 .LEHE65-.LEHB65
	.uleb128 .L1305-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB66-.LCOLDB66
	.uleb128 .LEHE66-.LEHB66
	.uleb128 .L1294-.LCOLDB66
	.uleb128 0
	.uleb128 .LEHB67-.LCOLDB66
	.uleb128 .LEHE67-.LEHB67
	.uleb128 .L1295-.LCOLDB66
	.uleb128 0
.LLSDACSEC11239:
	.section	.text.unlikely
	.section	.text.startup
	.size	main, .-main
	.section	.text.unlikely
	.size	main.cold, .-main.cold
.LCOLDE66:
	.section	.text.startup
.LHOTE66:
	.section	.rodata._ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_.str1.8,"aMS",@progbits,1
	.align 8
.LC67:
	.ascii	"Eigen::DenseCoeffsBase<Derived, 0>::CoeffReturnType Eig"
	.string	"en::DenseCoeffsBase<Derived, 0>::operator[](Eigen::Index) const [with Derived = Eigen::CwiseNullaryOp<Eigen::internal::scalar_constant_op<int>, Eigen::Matrix<int, -1, 1> >; Eigen::DenseCoeffsBase<Derived, 0>::CoeffReturnType = int; Eigen::Index = long int]"
	.section	.text._ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_,"axG",@progbits,_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_,comdat
	.align 2
	.p2align 4
	.weak	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_
	.type	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_, @function
_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_:
.LFB12934:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	32(%rdi), %r15
	movq	8(%rdi), %rbx
	testq	%r15, %r15
	je	.L1640
	movq	%rbx, %rsi
	addq	$1, %rsi
	je	.L1556
	movq	%rsi, %rax
	shrq	$62, %rax
	jne	.L1499
	salq	$2, %rsi
	movq	%rsi, %rdi
	movq	%rsi, (%rsp)
	call	malloc@PLT
	movq	(%rsp), %rsi
	movq	%rax, %r14
	cmpq	$15, %rsi
	jbe	.L1532
	testb	$15, %al
	je	.L1532
.L1507:
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
	.p2align 4,,10
	.p2align 3
.L1640:
	testq	%rbx, %rbx
	jle	.L1492
	movq	(%rsi), %rcx
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L1496:
	cmpq	%rax, %rcx
	jle	.L1501
	movslq	12(%r13), %r14
	addq	$1, %rax
	addq	%r14, %r15
	cmpq	%rbx, %rax
	jne	.L1496
	testq	%r15, %r15
	je	.L1492
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %rbx
	jg	.L1499
	leaq	0(,%rbx,4), %rdi
	movq	%rcx, 8(%rsp)
	movq	%rdi, (%rsp)
	call	malloc@PLT
	movq	(%rsp), %rdi
	movq	8(%rsp), %rcx
	movq	%rax, %rbp
	cmpq	$15, %rdi
	ja	.L1641
.L1498:
	testq	%rbp, %rbp
	je	.L1499
	movq	%rbp, 32(%r12)
	movq	24(%r12), %rsi
	xorl	%eax, %eax
	xorl	%r8d, %r8d
	movl	$0, 0(%rbp)
	jmp	.L1500
	.p2align 4,,10
	.p2align 3
.L1502:
	movl	%r8d, 0(%rbp,%rax,4)
	cmpq	%rax, %rcx
	je	.L1501
.L1500:
	movl	4(%rsi,%rax,4), %edx
	subl	(%rsi,%rax,4), %edx
	addq	$1, %rax
	movslq	%edx, %rdx
	addq	%r14, %rdx
	addq	%rdx, %r8
	cmpq	%rbx, %rax
	jne	.L1502
	movq	64(%r12), %rdx
	addq	56(%r12), %r15
	cmpq	%r15, %rdx
	jl	.L1642
	movslq	(%rsi,%rdi), %rdx
	leaq	-1(%rax), %rbx
.L1553:
	salq	$2, %rbx
	jmp	.L1517
	.p2align 4,,10
	.p2align 3
.L1643:
	movq	48(%r12), %rdi
	leaq	0(,%rax,4), %r8
	movl	%ecx, 8(%rsp)
	movq	%r8, (%rsp)
	leaq	(%rdi,%r15), %rsi
	addq	%r8, %rdi
	call	memmove@PLT
	movq	40(%r12), %rsi
	movq	(%rsp), %rdi
	movq	%r14, %rdx
	addq	40(%r12), %rdi
	addq	%r15, %rsi
	call	memmove@PLT
	movq	24(%r12), %rsi
	movl	0(%rbp,%rbx), %edx
	movl	8(%rsp), %ecx
	leaq	(%rsi,%rbx), %rax
	movl	(%rax), %edi
	movl	%edx, (%rax)
	movq	32(%r12), %rax
	movl	%ecx, (%rax,%rbx)
	subq	$4, %rbx
	cmpq	$-4, %rbx
	je	.L1516
.L1515:
	movslq	%edi, %rdx
.L1517:
	leaq	(%rsi,%rbx), %r8
	movl	%edx, %ecx
	salq	$2, %rdx
	movslq	0(%rbp,%rbx), %rax
	movslq	(%r8), %r15
	subl	%r15d, %ecx
	movq	%r15, %rdi
	salq	$2, %r15
	subq	%r15, %rdx
	movq	%rdx, %r14
	jne	.L1643
	movl	%eax, (%r8)
	movq	32(%r12), %rax
	movl	%ecx, (%rax,%rbx)
	subq	$4, %rbx
	cmpq	$-4, %rbx
	jne	.L1515
.L1516:
	movq	8(%r12), %rcx
	leaq	0(,%rcx,4), %rdi
.L1513:
	testq	%rcx, %rcx
	jle	.L1644
	movq	32(%r12), %rdx
	movl	-4(%rsi,%rdi), %eax
	addl	-4(%rdx,%rdi), %eax
	cmpq	%rcx, 0(%r13)
	jl	.L1501
	addl	12(%r13), %eax
	movl	%eax, (%rsi,%rdi)
.L1519:
	movq	64(%r12), %rdx
	movslq	%eax, %r14
	cmpq	%rdx, %r14
	jle	.L1520
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %rbx
	addq	%r14, %rbx
	cmpq	$2147483646, %rbx
	jle	.L1645
	movq	40(%r12), %rdi
	movq	%rdx, %r13
	movl	$2147483647, %ebx
	movl	$2147483647, %ebp
.L1550:
	movq	%rdx, %rax
	shrq	$62, %rax
	jne	.L1499
	salq	$2, %rdx
	salq	$2, %rbp
	testq	%rdi, %rdi
	je	.L1646
	cmpq	%rbp, %rdx
	je	.L1523
	testq	%rbp, %rbp
	je	.L1647
	movq	%rbp, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L1499
	movq	64(%r12), %r13
.L1526:
	movq	%rax, 40(%r12)
	movq	%r13, %rax
	movq	48(%r12), %rdi
	shrq	$62, %rax
	jne	.L1499
.L1552:
	salq	$2, %r13
	testq	%rdi, %rdi
	je	.L1648
	cmpq	%rbp, %r13
	je	.L1528
	testq	%rbp, %rbp
	je	.L1649
	movq	%rbp, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L1639:
	testq	%rdi, %rdi
	je	.L1499
.L1528:
	movq	%rdi, 48(%r12)
	movq	%rbx, 64(%r12)
.L1520:
	movq	%r14, 56(%r12)
.L1492:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1556:
	.cfi_restore_state
	xorl	%r14d, %r14d
.L1531:
	cmpq	$0, 64(%r12)
	movl	$0, (%r14,%rbx,4)
	jns	.L1650
.L1499:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
	.p2align 4,,10
	.p2align 3
.L1641:
	testb	$15, %al
	jne	.L1507
	jmp	.L1498
	.p2align 4,,10
	.p2align 3
.L1532:
	testq	%r14, %r14
	je	.L1499
	testq	%rbx, %rbx
	jle	.L1531
	movq	24(%r12), %rdi
	movq	0(%r13), %r8
	xorl	%ebp, %ebp
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L1533:
	movl	%ebp, (%r14,%rdx,4)
	movslq	(%r15,%rdx,4), %rcx
	movl	4(%rdi,%rdx,4), %eax
	subl	(%rdi,%rdx,4), %eax
	subl	%ecx, %eax
	cltq
	cmpq	%rdx, %r8
	jle	.L1501
	movslq	12(%r13), %r9
	cmpq	%rax, %r9
	cmovl	%rax, %r9
	addq	$1, %rdx
	addq	%rcx, %r9
	addq	%r9, %rbp
	cmpq	%rbx, %rdx
	jne	.L1533
	movq	64(%r12), %rcx
	movl	%ebp, -4(%r14,%rsi)
	cmpq	%rcx, %rbp
	jle	.L1534
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rbp, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %rbx
	addq	%rbp, %rbx
	cmpq	$2147483646, %rbx
	jle	.L1651
	cmpq	$2147483647, %rbp
	jg	.L1499
	movq	40(%r12), %rdi
	movq	%rcx, %r15
	movl	$2147483647, %r13d
	movl	$2147483647, %ebx
.L1548:
	movq	%rcx, %rax
	shrq	$62, %rax
	jne	.L1499
	salq	$2, %rcx
	salq	$2, %r13
	testq	%rdi, %rdi
	je	.L1652
	cmpq	%r13, %rcx
	je	.L1537
	testq	%r13, %r13
	je	.L1653
	movq	%r13, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L1499
	movq	64(%r12), %r15
.L1540:
	movq	%rax, 40(%r12)
	movq	%r15, %rax
	movq	48(%r12), %rdi
	shrq	$62, %rax
	jne	.L1499
.L1555:
	salq	$2, %r15
	testq	%rdi, %rdi
	je	.L1654
	cmpq	%r13, %r15
	je	.L1542
	testq	%r13, %r13
	je	.L1655
	movq	%r13, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L1637:
	testq	%rdi, %rdi
	je	.L1499
.L1542:
	movq	%rdi, 48(%r12)
	movq	24(%r12), %rdi
	movq	%rbx, 64(%r12)
	movq	8(%r12), %rbx
.L1551:
	movq	%rbp, 56(%r12)
	subq	$1, %rbx
	js	.L1545
.L1554:
	salq	$2, %rbx
	.p2align 4,,10
	.p2align 3
.L1547:
	movq	32(%r12), %rax
	movslq	(%rax,%rbx), %rax
	salq	$2, %rax
	movq	%rax, %r13
	je	.L1546
	movslq	(%rdi,%rbx), %rbp
	movslq	(%r14,%rbx), %r15
	movq	%r13, %rdx
	movq	40(%r12), %rax
	salq	$2, %r15
	salq	$2, %rbp
	leaq	(%rax,%rbp), %rsi
	leaq	(%rax,%r15), %rdi
	call	memmove@PLT
	movq	48(%r12), %rsi
	movq	48(%r12), %rdi
	movq	%r13, %rdx
	addq	%r15, %rdi
	addq	%rbp, %rsi
	call	memmove@PLT
	movq	24(%r12), %rdi
.L1546:
	subq	$4, %rbx
	cmpq	$-4, %rbx
	jne	.L1547
.L1545:
	movq	%r14, 24(%r12)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.p2align 4,,10
	.p2align 3
.L1534:
	.cfi_restore_state
	movq	%rbp, 56(%r12)
	leaq	-1(%rdx), %rbx
	jmp	.L1554
.L1652:
	testq	%r13, %r13
	je	.L1537
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L1538
	testb	$15, %al
	jne	.L1507
.L1538:
	testq	%rdi, %rdi
	je	.L1499
.L1537:
	movq	%rdi, 40(%r12)
	movq	48(%r12), %rdi
	jmp	.L1555
.L1651:
	cmpq	%rbx, %rbp
	jg	.L1499
	movq	%rbx, %rax
	movq	40(%r12), %rdi
	movq	%rbx, %r13
	movq	%rcx, %r15
	shrq	$62, %rax
	je	.L1548
	jmp	.L1499
	.p2align 4,,10
	.p2align 3
.L1642:
	movq	%rdx, %rax
	movq	40(%r12), %rdi
	orq	%r15, %rax
	shrq	$62, %rax
	jne	.L1499
	leaq	0(,%rdx,4), %rax
	leaq	0(,%r15,4), %r14
	testq	%rdi, %rdi
	je	.L1656
	cmpq	%r14, %rax
	je	.L1505
	testq	%r14, %r14
	je	.L1657
	movq	%r14, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L1499
	movq	64(%r12), %rdx
.L1505:
	movq	%rdx, %rax
	movq	%rdi, 40(%r12)
	movq	48(%r12), %rdi
	shrq	$62, %rax
	jne	.L1499
	salq	$2, %rdx
	testq	%rdi, %rdi
	je	.L1658
	cmpq	%r14, %rdx
	je	.L1510
	testq	%r14, %r14
	je	.L1659
	movq	%r14, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L1635:
	testq	%rdi, %rdi
	je	.L1499
.L1510:
	movq	8(%r12), %rcx
	movq	24(%r12), %rsi
	movq	%rdi, 48(%r12)
	movq	%r15, 64(%r12)
	movq	%rcx, %rbx
	movslq	(%rsi,%rcx,4), %rdx
	leaq	0(,%rcx,4), %rdi
	subq	$1, %rbx
	jns	.L1553
	jmp	.L1513
.L1646:
	testq	%rbp, %rbp
	je	.L1523
	movq	%rbp, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %rbp
	jbe	.L1524
	testb	$15, %al
	jne	.L1507
.L1524:
	testq	%rdi, %rdi
	je	.L1499
.L1523:
	movq	%rdi, 40(%r12)
	movq	48(%r12), %rdi
	jmp	.L1552
.L1650:
	movq	24(%r12), %rdi
	xorl	%ebp, %ebp
	jmp	.L1551
.L1656:
	testq	%r14, %r14
	je	.L1505
	movq	%r14, %rdi
	movq	%rdx, (%rsp)
	call	malloc@PLT
	cmpq	$15, %r14
	movq	(%rsp), %rdx
	movq	%rax, %rdi
	jbe	.L1506
	testb	$15, %al
	jne	.L1507
.L1506:
	testq	%rdi, %rdi
	jne	.L1505
	jmp	.L1499
	.p2align 4,,10
	.p2align 3
.L1644:
	movl	(%rsi,%rdi), %eax
	jmp	.L1519
.L1654:
	testq	%r13, %r13
	je	.L1542
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L1637
	testb	$15, %al
	jne	.L1507
	jmp	.L1637
	.p2align 4,,10
	.p2align 3
.L1645:
	cmpq	%rbx, %r14
	jg	.L1499
	movq	%rbx, %rax
	movq	40(%r12), %rdi
	movq	%rdx, %r13
	movq	%rbx, %rbp
	shrq	$62, %rax
	je	.L1550
	jmp	.L1499
	.p2align 4,,10
	.p2align 3
.L1653:
	call	free@PLT
	movq	64(%r12), %r15
	xorl	%eax, %eax
	jmp	.L1540
.L1655:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L1542
.L1648:
	testq	%rbp, %rbp
	je	.L1528
	movq	%rbp, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %rbp
	jbe	.L1639
	testb	$15, %al
	jne	.L1507
	jmp	.L1639
	.p2align 4,,10
	.p2align 3
.L1647:
	call	free@PLT
	movq	64(%r12), %r13
	xorl	%eax, %eax
	jmp	.L1526
.L1658:
	testq	%r14, %r14
	je	.L1510
	movq	%r14, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r14
	jbe	.L1635
	testb	$15, %al
	jne	.L1507
	jmp	.L1635
	.p2align 4,,10
	.p2align 3
.L1649:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L1528
.L1501:
	leaq	.LC67(%rip), %rcx
	movl	$165, %edx
	leaq	.LC27(%rip), %rsi
	leaq	.LC28(%rip), %rdi
	call	__assert_fail@PLT
.L1659:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L1510
.L1657:
	call	free@PLT
	movq	64(%r12), %rdx
	xorl	%edi, %edi
	jmp	.L1505
	.cfi_endproc
.LFE12934:
	.size	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_, .-_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_
	.section	.rodata._ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_.str1.8,"aMS",@progbits,1
	.align 8
.LC68:
	.ascii	"Eigen::DenseCoeffsBase<Derived, 0>::CoeffReturnType Ei"
	.string	"gen::DenseCoeffsBase<Derived, 0>::operator[](Eigen::Index) const [with Derived = Eigen::CwiseNullaryOp<Eigen::internal::sparse_reserve_op<int>, Eigen::Matrix<int, -1, 1> >; Eigen::DenseCoeffsBase<Derived, 0>::CoeffReturnType = int; Eigen::Index = long int]"
	.section	.text._ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_,"axG",@progbits,_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_,comdat
	.align 2
	.p2align 4
	.weak	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_
	.type	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_, @function
_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_:
.LFB12947:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	movq	32(%rdi), %r14
	movq	8(%rdi), %r11
	testq	%r14, %r14
	je	.L1840
	movq	%r11, %r15
	addq	$1, %r15
	je	.L1731
	movq	%r15, %rax
	movq	%r11, (%rsp)
	shrq	$62, %rax
	jne	.L1668
	salq	$2, %r15
	movq	%r15, %rdi
	call	malloc@PLT
	cmpq	$15, %r15
	movq	(%rsp), %r11
	movq	%rax, %r13
	jbe	.L1703
	testb	$15, %al
	je	.L1703
.L1677:
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
	.p2align 4,,10
	.p2align 3
.L1840:
	testq	%r11, %r11
	jle	.L1660
	movq	(%rsi), %r15
	xorl	%eax, %eax
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L1665:
	cmpq	%rax, %r15
	jle	.L1670
	movq	32(%rbx), %r12
	movl	16(%rbx), %r14d
	movl	20(%rbx), %edx
	movq	24(%rbx), %r13
	cmpq	%rax, %r12
	jle	.L1664
	cmpq	%rax, %r13
	jg	.L1664
	movq	%rax, %rdi
	movslq	%edx, %rcx
	subq	%r13, %rdi
	cmpq	%rcx, %rdi
	setl	%cl
	movzbl	%cl, %ecx
	addl	%r14d, %ecx
	movslq	%ecx, %rcx
	addq	%rcx, %rsi
.L1664:
	addq	$1, %rax
	cmpq	%r11, %rax
	jne	.L1665
	testq	%rsi, %rsi
	je	.L1660
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %r11
	jg	.L1668
	leaq	0(,%r11,4), %rax
	movl	%edx, 28(%rsp)
	movq	%rax, %rdi
	movq	%rsi, 16(%rsp)
	movq	%r11, (%rsp)
	movq	%rax, 8(%rsp)
	call	malloc@PLT
	cmpq	$15, 8(%rsp)
	movq	(%rsp), %r11
	movq	16(%rsp), %rsi
	movslq	28(%rsp), %rdx
	movq	%rax, %r8
	ja	.L1841
.L1667:
	testq	%r8, %r8
	je	.L1668
	movq	%r13, %r9
	movq	%r8, 32(%rbp)
	movq	24(%rbp), %rcx
	xorl	%eax, %eax
	movl	$0, (%r8)
	negq	%r9
	xorl	%edi, %edi
	movq	%rdx, (%rsp)
	jmp	.L1669
	.p2align 4,,10
	.p2align 3
.L1843:
	cmpq	%rax, %r13
	jg	.L1730
	xorl	%r10d, %r10d
	cmpq	%r9, (%rsp)
	setg	%r10b
	addl	%r14d, %r10d
	movslq	%r10d, %r10
.L1671:
	movl	4(%rcx,%rax,4), %edx
	subl	(%rcx,%rax,4), %edx
	addq	$1, %rax
	movslq	%edx, %rdx
	addq	%r10, %rdx
	addq	%rdx, %rdi
	cmpq	%r11, %rax
	je	.L1842
	movl	%edi, (%r8,%rax,4)
	addq	$1, %r9
	cmpq	%r15, %rax
	je	.L1670
.L1669:
	cmpq	%rax, %r12
	jg	.L1843
.L1730:
	xorl	%r10d, %r10d
	jmp	.L1671
	.p2align 4,,10
	.p2align 3
.L1831:
	movq	8(%rbp), %rsi
	movq	8(%rsp), %rbx
	leaq	0(,%rsi,4), %r9
.L1683:
	testq	%rsi, %rsi
	jg	.L1688
	movl	(%rcx,%r9), %eax
.L1689:
	movq	64(%rbp), %rdx
	movslq	%eax, %r13
	cmpq	%rdx, %r13
	jle	.L1691
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %r14
	addq	%r13, %r14
	cmpq	$2147483646, %r14
	jle	.L1844
	movq	40(%rbp), %rdi
	movq	%rdx, %rbx
	movl	$2147483647, %r14d
	movl	$2147483647, %r12d
.L1724:
	movq	%rdx, %rax
	shrq	$62, %rax
	jne	.L1668
	salq	$2, %rdx
	salq	$2, %r12
	testq	%rdi, %rdi
	je	.L1845
	cmpq	%r12, %rdx
	je	.L1694
	testq	%r12, %r12
	je	.L1846
	movq	%r12, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L1668
	movq	64(%rbp), %rbx
.L1697:
	movq	%rax, 40(%rbp)
	movq	%rbx, %rax
	movq	48(%rbp), %rdi
	shrq	$62, %rax
	jne	.L1668
.L1726:
	salq	$2, %rbx
	testq	%rdi, %rdi
	je	.L1847
	cmpq	%r12, %rbx
	je	.L1699
	testq	%r12, %r12
	je	.L1848
	movq	%r12, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L1836:
	testq	%rdi, %rdi
	je	.L1668
.L1699:
	movq	%rdi, 48(%rbp)
	movq	%r14, 64(%rbp)
.L1691:
	movq	%r13, 56(%rbp)
.L1660:
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1841:
	.cfi_restore_state
	testb	$15, %al
	jne	.L1677
	jmp	.L1667
	.p2align 4,,10
	.p2align 3
.L1731:
	xorl	%r13d, %r13d
.L1702:
	movl	$0, 0(%r13,%r11,4)
	cmpq	$0, 64(%rbp)
	js	.L1668
	movq	24(%rbp), %rdi
	xorl	%r12d, %r12d
	jmp	.L1725
	.p2align 4,,10
	.p2align 3
.L1842:
	movq	64(%rbp), %rdx
	addq	56(%rbp), %rsi
	movq	%rsi, %r12
	cmpq	%rsi, %rdx
	jl	.L1849
	movq	8(%rsp), %rsi
	subq	$1, %rax
	movl	(%rcx,%rsi), %edx
.L1727:
	movq	%rbx, 8(%rsp)
	leaq	0(,%rax,4), %r12
	movq	%r8, %rbx
	jmp	.L1687
	.p2align 4,,10
	.p2align 3
.L1850:
	movq	48(%rbp), %rdi
	salq	$2, %r9
	movq	%rax, %rdx
	movq	%r9, (%rsp)
	leaq	(%rdi,%r14), %rsi
	addq	%r9, %rdi
	call	memmove@PLT
	movq	40(%rbp), %rsi
	movq	(%rsp), %rdi
	movq	%r13, %rdx
	addq	40(%rbp), %rdi
	addq	%r14, %rsi
	call	memmove@PLT
	movq	24(%rbp), %rcx
	movl	(%rbx,%r12), %edx
	leaq	(%rcx,%r12), %rax
	movl	(%rax), %edi
	movl	%edx, (%rax)
.L1839:
	movq	32(%rbp), %rax
	movl	%r15d, (%rax,%r12)
	subq	$4, %r12
	cmpq	$-4, %r12
	je	.L1831
	movl	%edi, %edx
.L1687:
	leaq	(%rcx,%r12), %r10
	movl	%edx, %r15d
	movslq	%edx, %rax
	movslq	(%rbx,%r12), %r9
	movslq	(%r10), %r14
	salq	$2, %rax
	subl	%r14d, %r15d
	movq	%r14, %rdi
	salq	$2, %r14
	subq	%r14, %rax
	movq	%rax, %r13
	jne	.L1850
	movl	%r9d, (%r10)
	jmp	.L1839
	.p2align 4,,10
	.p2align 3
.L1703:
	testq	%r13, %r13
	je	.L1668
	testq	%r11, %r11
	jle	.L1702
	movq	%rbp, (%rsp)
	movq	24(%rbp), %rdi
	xorl	%r12d, %r12d
	xorl	%edx, %edx
	movq	(%rbx), %r10
	.p2align 4,,10
	.p2align 3
.L1707:
	movl	%r12d, 0(%r13,%rdx,4)
	movslq	(%r14,%rdx,4), %rcx
	movl	4(%rdi,%rdx,4), %eax
	subl	(%rdi,%rdx,4), %eax
	subl	%ecx, %eax
	cltq
	cmpq	%rdx, %r10
	jle	.L1670
	movl	16(%rbx), %r9d
	movslq	20(%rbx), %r8
	movq	24(%rbx), %rsi
	cmpq	%rdx, 32(%rbx)
	jle	.L1704
	cmpq	%rdx, %rsi
	jg	.L1704
	movq	%rdx, %rbp
	subq	%rsi, %rbp
	cmpq	%r8, %rbp
	setl	%sil
	movzbl	%sil, %esi
	addl	%r9d, %esi
	movslq	%esi, %rsi
	cmpq	%rax, %rsi
	cmovl	%rax, %rsi
	addq	$1, %rdx
	addq	%rcx, %rsi
	addq	%rsi, %r12
	cmpq	%r11, %rdx
	jne	.L1707
.L1837:
	movq	(%rsp), %rbp
	movl	%r12d, -4(%r13,%r15)
	movq	64(%rbp), %rdx
	cmpq	%rdx, %r12
	jle	.L1708
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%r12, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %rbx
	addq	%r12, %rbx
	cmpq	$2147483646, %rbx
	jle	.L1851
	cmpq	$2147483647, %r12
	jg	.L1668
	movq	40(%rbp), %rdi
	movq	%rdx, %r15
	movl	$2147483647, %r14d
	movl	$2147483647, %ebx
.L1722:
	movq	%rdx, %rax
	shrq	$62, %rax
	jne	.L1668
	salq	$2, %rdx
	salq	$2, %r14
	testq	%rdi, %rdi
	je	.L1852
	cmpq	%r14, %rdx
	je	.L1711
	testq	%r14, %r14
	je	.L1853
	movq	%r14, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L1668
	movq	64(%rbp), %r15
.L1714:
	movq	%rax, 40(%rbp)
	movq	%r15, %rax
	movq	48(%rbp), %rdi
	shrq	$62, %rax
	jne	.L1668
.L1729:
	salq	$2, %r15
	testq	%rdi, %rdi
	je	.L1854
	cmpq	%r14, %r15
	je	.L1716
	testq	%r14, %r14
	je	.L1855
	movq	%r14, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L1834:
	testq	%rdi, %rdi
	je	.L1668
.L1716:
	movq	%rbx, 64(%rbp)
	movq	8(%rbp), %r11
	movq	%rdi, 48(%rbp)
	movq	24(%rbp), %rdi
.L1725:
	movq	%r11, %rbx
	movq	%r12, 56(%rbp)
	subq	$1, %rbx
	js	.L1719
.L1728:
	salq	$2, %rbx
	.p2align 4,,10
	.p2align 3
.L1721:
	movq	32(%rbp), %rax
	movslq	(%rax,%rbx), %rax
	salq	$2, %rax
	movq	%rax, %r14
	je	.L1720
	movslq	(%rdi,%rbx), %r12
	movslq	0(%r13,%rbx), %r15
	movq	%r14, %rdx
	movq	40(%rbp), %rax
	salq	$2, %r15
	salq	$2, %r12
	leaq	(%rax,%r12), %rsi
	leaq	(%rax,%r15), %rdi
	call	memmove@PLT
	movq	48(%rbp), %rsi
	movq	48(%rbp), %rdi
	movq	%r14, %rdx
	addq	%r15, %rdi
	addq	%r12, %rsi
	call	memmove@PLT
	movq	24(%rbp), %rdi
.L1720:
	subq	$4, %rbx
	cmpq	$-4, %rbx
	jne	.L1721
.L1719:
	movq	%r13, 24(%rbp)
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	free@PLT
	.p2align 4,,10
	.p2align 3
.L1704:
	.cfi_restore_state
	xorl	%esi, %esi
	testq	%rax, %rax
	cmovs	%rsi, %rax
	addq	$1, %rdx
	addq	%rcx, %rax
	addq	%rax, %r12
	cmpq	%r11, %rdx
	jne	.L1707
	jmp	.L1837
	.p2align 4,,10
	.p2align 3
.L1708:
	movq	%r12, 56(%rbp)
	leaq	-1(%r11), %rbx
	jmp	.L1728
	.p2align 4,,10
	.p2align 3
.L1688:
	movq	32(%rbp), %rdx
	movl	-4(%rcx,%r9), %eax
	subq	$1, %rsi
	addl	-4(%rdx,%r9), %eax
	cmpq	(%rbx), %rsi
	jge	.L1670
	movl	16(%rbx), %r8d
	movslq	20(%rbx), %rdx
	movq	24(%rbx), %rdi
	cmpq	32(%rbx), %rsi
	jge	.L1690
	cmpq	%rdi, %rsi
	jl	.L1690
	subq	%rdi, %rsi
	cmpq	%rdx, %rsi
	setl	%dl
	movzbl	%dl, %edx
	addl	%r8d, %edx
	addl	%edx, %eax
.L1690:
	movl	%eax, (%rcx,%r9)
	jmp	.L1689
.L1852:
	testq	%r14, %r14
	je	.L1711
	movq	%r14, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r14
	jbe	.L1712
	testb	$15, %al
	jne	.L1677
.L1712:
	testq	%rdi, %rdi
	je	.L1668
.L1711:
	movq	%rdi, 40(%rbp)
	movq	48(%rbp), %rdi
	jmp	.L1729
	.p2align 4,,10
	.p2align 3
.L1849:
	movq	%rdx, %rax
	movq	40(%rbp), %rdi
	orq	%rsi, %rax
	shrq	$62, %rax
	jne	.L1668
	leaq	0(,%rdx,4), %rax
	leaq	0(,%rsi,4), %r13
	testq	%rdi, %rdi
	je	.L1856
	cmpq	%r13, %rax
	je	.L1675
	movq	%r8, (%rsp)
	testq	%r13, %r13
	je	.L1857
	movq	%r13, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L1668
	movq	64(%rbp), %rdx
	movq	(%rsp), %r8
.L1675:
	movq	%rdx, %rax
	movq	%rdi, 40(%rbp)
	movq	48(%rbp), %rdi
	shrq	$62, %rax
	jne	.L1668
	salq	$2, %rdx
	testq	%rdi, %rdi
	je	.L1858
	cmpq	%r13, %rdx
	je	.L1680
	movq	%r8, (%rsp)
	testq	%r13, %r13
	je	.L1859
	movq	%r13, %rsi
	call	realloc@PLT
	movq	(%rsp), %r8
	testq	%rax, %rax
	movq	%rax, %rdi
	je	.L1668
.L1680:
	movq	8(%rbp), %rsi
	movq	24(%rbp), %rcx
	movq	%rdi, 48(%rbp)
	movq	%r12, 64(%rbp)
	movq	%rsi, %rax
	movl	(%rcx,%rsi,4), %edx
	leaq	0(,%rsi,4), %r9
	subq	$1, %rax
	jns	.L1727
	jmp	.L1683
.L1856:
	testq	%r13, %r13
	je	.L1675
	movq	%r13, %rdi
	movq	%rdx, 8(%rsp)
	movq	%r8, (%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	(%rsp), %r8
	movq	8(%rsp), %rdx
	movq	%rax, %rdi
	jbe	.L1676
	testb	$15, %al
	jne	.L1677
.L1676:
	testq	%rdi, %rdi
	jne	.L1675
.L1668:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
	.p2align 4,,10
	.p2align 3
.L1846:
	call	free@PLT
	movq	64(%rbp), %rbx
	xorl	%eax, %eax
	jmp	.L1697
	.p2align 4,,10
	.p2align 3
.L1851:
	cmpq	%rbx, %r12
	jg	.L1668
	movq	%rbx, %rax
	movq	40(%rbp), %rdi
	movq	%rbx, %r14
	movq	%rdx, %r15
	shrq	$62, %rax
	je	.L1722
	jmp	.L1668
	.p2align 4,,10
	.p2align 3
.L1854:
	testq	%r14, %r14
	je	.L1716
	movq	%r14, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r14
	jbe	.L1834
	testb	$15, %al
	jne	.L1677
	jmp	.L1834
	.p2align 4,,10
	.p2align 3
.L1844:
	cmpq	%r14, %r13
	jg	.L1668
	movq	%r14, %rax
	movq	40(%rbp), %rdi
	movq	%rdx, %rbx
	movq	%r14, %r12
	shrq	$62, %rax
	je	.L1724
	jmp	.L1668
	.p2align 4,,10
	.p2align 3
.L1845:
	testq	%r12, %r12
	je	.L1694
	movq	%r12, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r12
	jbe	.L1695
	testb	$15, %al
	jne	.L1677
.L1695:
	testq	%rdi, %rdi
	je	.L1668
.L1694:
	movq	%rdi, 40(%rbp)
	movq	48(%rbp), %rdi
	jmp	.L1726
.L1853:
	call	free@PLT
	movq	64(%rbp), %r15
	xorl	%eax, %eax
	jmp	.L1714
.L1855:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L1716
.L1847:
	testq	%r12, %r12
	je	.L1699
	movq	%r12, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r12
	jbe	.L1836
	testb	$15, %al
	jne	.L1677
	jmp	.L1836
	.p2align 4,,10
	.p2align 3
.L1858:
	testq	%r13, %r13
	je	.L1680
	movq	%r13, %rdi
	movq	%r8, (%rsp)
	call	malloc@PLT
	cmpq	$15, %r13
	movq	(%rsp), %r8
	movq	%rax, %rdi
	jbe	.L1681
	testb	$15, %al
	jne	.L1677
.L1681:
	testq	%rdi, %rdi
	jne	.L1680
	jmp	.L1668
	.p2align 4,,10
	.p2align 3
.L1848:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L1699
.L1670:
	leaq	.LC68(%rip), %rcx
	movl	$165, %edx
	leaq	.LC27(%rip), %rsi
	leaq	.LC28(%rip), %rdi
	call	__assert_fail@PLT
.L1857:
	call	free@PLT
	movq	64(%rbp), %rdx
	movq	(%rsp), %r8
	xorl	%edi, %edi
	jmp	.L1675
.L1859:
	call	free@PLT
	movq	(%rsp), %r8
	xorl	%edi, %edi
	jmp	.L1680
	.cfi_endproc
.LFE12947:
	.size	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_, .-_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_
	.section	.rodata._ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll.str1.8,"aMS",@progbits,1
	.align 8
.LC70:
	.ascii	"Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::Scalar&"
	.ascii	" Eigen::SparseMatrix<Sca"
	.string	"lar_, Flags_, StorageIndex_>::insertUncompressedAtByOuterInner(Eigen::Index, Eigen::Index, Eigen::Index) [with Scalar_ = int; int Options_ = 0; StorageIndex_ = int; Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::Scalar = int; Eigen::Index = long int]"
	.section	.rodata._ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll.str1.1,"aMS",@progbits,1
.LC71:
	.string	"!isCompressed()"
.LC73:
	.string	"maxReserveSize > 0"
	.section	.rodata._ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll.str1.8
	.align 8
.LC74:
	.string	"Eigen::CwiseNullaryOp<NullaryOp, MatrixType>::CwiseNullaryOp(Eigen::Index, Eigen::Index, const NullaryOp&) [with NullaryOp = Eigen::internal::scalar_constant_op<int>; PlainObjectType = Eigen::Matrix<int, -1, 1>; Eigen::Index = long int]"
	.align 8
.LC75:
	.string	"/usr/local/include/Eigen/src/Core/CwiseNullaryOp.h"
	.align 8
.LC76:
	.string	"rows >= 0 && (RowsAtCompileTime == Dynamic || RowsAtCompileTime == rows) && cols >= 0 && (ColsAtCompileTime == Dynamic || ColsAtCompileTime == cols)"
	.align 8
.LC77:
	.string	"Eigen::CwiseNullaryOp<NullaryOp, MatrixType>::CwiseNullaryOp(Eigen::Index, Eigen::Index, const NullaryOp&) [with NullaryOp = Eigen::internal::sparse_reserve_op<int>; PlainObjectType = Eigen::Matrix<int, -1, 1>; Eigen::Index = long int]"
	.section	.text._ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll,"axG",@progbits,_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll,comdat
	.align 2
	.p2align 4
	.weak	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	.type	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll, @function
_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll:
.LFB12728:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$88, %rsp
	.cfi_def_cfa_offset 144
	movq	32(%rdi), %rsi
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	testq	%rsi, %rsi
	je	.L1948
	movq	%rdx, %r14
	movq	%rcx, %r15
	movq	24(%rdi), %rdx
	movq	8(%rdi), %rcx
	movq	%rdi, %r12
	leaq	-1(%r13), %rbx
	movq	%r13, %rbp
	jmp	.L1862
	.p2align 4,,10
	.p2align 3
.L1863:
	leaq	0(,%rbx,4), %rax
	movslq	(%rdx,%rbx,4), %r9
	movslq	4(%rdx,%rax), %rdi
	leaq	4(%rax), %r8
	movslq	(%rsi,%rbx,4), %rax
	addq	%r9, %rax
	cmpq	%rax, %rdi
	jg	.L1949
	subq	$1, %rbx
.L1862:
	testq	%rbx, %rbx
	js	.L1943
	cmpq	%rcx, %rbp
	jge	.L1863
	jmp	.L1883
	.p2align 4,,10
	.p2align 3
.L1864:
	addq	$1, %rbp
	testq	%rbx, %rbx
	jns	.L1863
.L1943:
	cmpq	%rcx, %rbp
	jge	.L1950
.L1883:
	movslq	(%rdx,%rbp,4), %rdi
	movslq	(%rsi,%rbp,4), %rax
	addq	%rdi, %rax
	movslq	4(%rdx,%rbp,4), %rdi
	cmpq	%rax, %rdi
	jle	.L1864
	movq	40(%r12), %rdx
	leaq	0(,%r15,4), %rcx
	leaq	(%rdx,%rcx), %r8
	cmpq	%r15, %rax
	jg	.L1951
.L1865:
	leaq	0(,%r13,4), %rax
	addl	$1, (%rsi,%rax)
	cmpq	%r13, %rbp
	jle	.L1871
	movq	%rbp, %rsi
	movq	24(%r12), %rcx
	subq	%r13, %rsi
	leaq	-1(%rsi), %rdx
	cmpq	$2, %rdx
	jbe	.L1868
	movq	%rsi, %rdx
	leaq	4(%rcx,%rax), %rax
	movdqa	.LC72(%rip), %xmm1
	shrq	$2, %rdx
	salq	$4, %rdx
	addq	%rax, %rdx
	.p2align 4,,10
	.p2align 3
.L1869:
	movdqu	(%rax), %xmm0
	addq	$16, %rax
	paddd	%xmm1, %xmm0
	movups	%xmm0, -16(%rax)
	cmpq	%rax, %rdx
	jne	.L1869
	movq	%rsi, %rax
	andq	$-4, %rax
	addq	%rax, %r13
	cmpq	%rax, %rsi
	je	.L1871
.L1868:
	leaq	1(%r13), %rdx
	leaq	0(,%rdx,4), %rax
	addl	$1, (%rcx,%rax)
	cmpq	%rdx, %rbp
	jle	.L1871
	addq	$2, %r13
	addl	$1, 4(%rcx,%rax)
	cmpq	%r13, %rbp
	jle	.L1871
	addl	$1, 8(%rcx,%rax)
.L1871:
	movq	48(%r12), %rax
	movl	%r14d, (%rax,%r15,4)
	movl	$0, (%r8)
.L1860:
	movq	72(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L1952
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r8, %rax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L1949:
	.cfi_restore_state
	movq	%r15, %rax
	movq	40(%r12), %rcx
	subq	%rdi, %rax
	testq	%rax, %rax
	jg	.L1953
.L1875:
	addl	$1, (%rsi,%r13,4)
	cmpq	%r13, %rbx
	jge	.L1880
	movq	%r13, %rsi
	movq	24(%r12), %rdx
	subq	%rbx, %rsi
	leaq	-1(%rsi), %rax
	cmpq	$2, %rax
	jbe	.L1877
	movq	%rsi, %rax
	addq	%rdx, %r8
	pcmpeqd	%xmm1, %xmm1
	shrq	$2, %rax
	salq	$4, %rax
	addq	%r8, %rax
	.p2align 4,,10
	.p2align 3
.L1878:
	movdqu	(%r8), %xmm0
	addq	$16, %r8
	paddd	%xmm1, %xmm0
	movups	%xmm0, -16(%r8)
	cmpq	%r8, %rax
	jne	.L1878
	movq	%rsi, %rax
	andq	$-4, %rax
	addq	%rax, %rbx
	cmpq	%rsi, %rax
	je	.L1880
.L1877:
	leaq	1(%rbx), %rsi
	leaq	0(,%rsi,4), %rax
	subl	$1, (%rdx,%rax)
	cmpq	%rsi, %r13
	jle	.L1880
	addq	$2, %rbx
	subl	$1, 4(%rdx,%rax)
	cmpq	%rbx, %r13
	jle	.L1880
	subl	$1, 8(%rdx,%rax)
.L1880:
	movq	48(%r12), %rax
	subq	$1, %r15
	leaq	(%rcx,%r15,4), %r8
	movl	%r14d, (%rax,%r15,4)
	movl	$0, (%r8)
	jmp	.L1860
	.p2align 4,,10
	.p2align 3
.L1950:
	leaq	0(,%r13,4), %rbx
	movq	64(%r12), %r8
	leaq	(%rdx,%rbx), %rdi
	movslq	(%rdi), %rax
	subq	%rax, %r15
	testq	%r8, %r8
	je	.L1954
	movl	$2147483647, %eax
	subq	%r8, %rax
	testq	%rax, %rax
	jle	.L1955
	cmpq	%rcx, %rax
	jge	.L1956
	movq	%rcx, %rsi
	movq	%r13, %xmm0
	movq	%rcx, 32(%rsp)
	subq	%r13, %rsi
	cmpq	%rax, %rsi
	cmovg	%rax, %rsi
	leaq	0(%r13,%rsi), %rdx
	movq	%rdx, %xmm3
	cqto
	idivq	%rsi
	punpcklqdq	%xmm3, %xmm0
	movups	%xmm0, 56(%rsp)
	movd	%eax, %xmm1
	movd	%edx, %xmm4
	punpckldq	%xmm4, %xmm1
	movq	%xmm1, 48(%rsp)
	testq	%rcx, %rcx
	js	.L1957
	leaq	32(%rsp), %rsi
	movq	%r12, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal17sparse_reserve_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_
	movq	24(%r12), %rdi
	movq	32(%r12), %rsi
	movq	40(%r12), %rbp
	addq	%rbx, %rdi
.L1896:
	movslq	(%rdi), %r13
	addq	%rbx, %rsi
	movslq	(%rsi), %rdx
	addq	%r15, %r13
	leaq	0(,%r13,4), %rcx
	movq	%rdx, %rax
	subq	%r15, %rdx
	movq	%rcx, 8(%rsp)
	leaq	0(%rbp,%rcx), %r8
	testq	%rdx, %rdx
	jg	.L1958
.L1905:
	addl	$1, %eax
	movl	%eax, (%rsi)
	movq	48(%r12), %rax
	movl	%r14d, (%rax,%r13,4)
	movl	$0, (%r8)
	jmp	.L1860
.L1951:
	salq	$2, %rax
	subq	%rcx, %rax
	movq	%rax, %rbx
	je	.L1865
	leaq	4(%rcx), %r9
	movq	%r8, %rsi
	movq	%rcx, 8(%rsp)
	leaq	(%rdx,%r9), %rdi
	movq	%rax, %rdx
	movq	%r9, 16(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rdi
	movq	%rbx, %rdx
	addq	48(%r12), %rsi
	addq	48(%r12), %rdi
	call	memmove@PLT
	movq	8(%rsp), %rcx
	addq	40(%r12), %rcx
	movq	32(%r12), %rsi
	movq	%rcx, %r8
	jmp	.L1865
.L1954:
	testq	%rcx, %rcx
	jle	.L1959
	pxor	%xmm0, %xmm0
	movl	$2147483647, %eax
	cvtsi2sdq	%rcx, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %r13
	addq	%rcx, %r13
	cmpq	%rax, %r13
	cmovg	%rax, %r13
	cmpq	%r13, %rcx
	jg	.L1890
	movq	40(%r12), %rdi
	leaq	0(,%r13,4), %rsi
	testq	%rdi, %rdi
	je	.L1960
	movq	%rcx, 16(%rsp)
	movq	%rsi, 8(%rsp)
	call	realloc@PLT
	movq	%rax, %rbp
	testq	%rax, %rax
	je	.L1890
	movq	64(%r12), %rax
	movq	48(%r12), %rdi
	movq	%rbp, 40(%r12)
	movq	%rax, %rcx
	shrq	$62, %rcx
	jne	.L1890
	salq	$2, %rax
	testq	%rdi, %rdi
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rcx
	je	.L1909
	cmpq	%rsi, %rax
	je	.L1895
.L1910:
	movq	%rcx, 8(%rsp)
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L1890
	movq	40(%r12), %rbp
	movq	8(%rsp), %rcx
.L1895:
	movq	24(%r12), %rdx
	movq	8(%r12), %rax
	movq	%rdi, 48(%r12)
	movq	%r13, 64(%r12)
	movq	32(%r12), %rsi
	leaq	(%rdx,%rbx), %rdi
	jmp	.L1886
.L1953:
	salq	$2, %rax
	movq	%rax, %rbp
	je	.L1875
	leaq	0(,%rdi,4), %r9
	leaq	-4(,%rdi,4), %r10
	movq	%rax, %rdx
	movq	%r8, 24(%rsp)
	leaq	(%rcx,%r9), %rsi
	leaq	(%rcx,%r10), %rdi
	movq	%r9, 16(%rsp)
	movq	%r10, 8(%rsp)
	call	memmove@PLT
	movq	16(%rsp), %rsi
	movq	8(%rsp), %rdi
	movq	%rbp, %rdx
	addq	48(%r12), %rsi
	addq	48(%r12), %rdi
	call	memmove@PLT
	movq	32(%r12), %rsi
	movq	40(%r12), %rcx
	movq	24(%rsp), %r8
	jmp	.L1875
.L1958:
	salq	$2, %rdx
	movq	%rdx, %r15
	je	.L1905
	leaq	4(,%r13,4), %r9
	movq	%r8, %rsi
	leaq	0(%rbp,%r9), %rdi
	movq	%r9, 16(%rsp)
	call	memmove@PLT
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rdi
	movq	%r15, %rdx
	addq	48(%r12), %rsi
	addq	48(%r12), %rdi
	call	memmove@PLT
	movq	32(%r12), %rsi
	movq	8(%rsp), %rcx
	addq	40(%r12), %rcx
	addq	%rbx, %rsi
	movq	%rcx, %r8
	movl	(%rsi), %eax
	jmp	.L1905
.L1956:
	movq	%rcx, 32(%rsp)
	movl	$1, 44(%rsp)
	testq	%rcx, %rcx
	js	.L1961
	leaq	32(%rsp), %rsi
	movq	%r12, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE19reserveInnerVectorsINS_14CwiseNullaryOpINS_8internal18scalar_constant_opIiEENS_6MatrixIiLin1ELi1ELi0ELin1ELi1EEEEEEEvRKT_
	movq	24(%r12), %rdi
	movq	32(%r12), %rsi
	movq	40(%r12), %rbp
	addq	%rbx, %rdi
	jmp	.L1896
.L1959:
	movq	40(%r12), %rbp
	movq	%rcx, %rax
.L1886:
	movq	%rcx, 56(%r12)
	leaq	4(,%rax,4), %rcx
	leaq	(%rdx,%rcx), %r8
	cmpq	%rdx, %r8
	je	.L1896
	subq	$4, %rcx
	movq	%rdx, %rax
	movq	%rcx, %r9
	shrq	$2, %r9
	addq	$1, %r9
	cmpq	$8, %rcx
	jbe	.L1912
	movq	%r9, %rcx
	movdqa	.LC69(%rip), %xmm0
	movdqa	.LC1(%rip), %xmm2
	shrq	$2, %rcx
	salq	$4, %rcx
	addq	%rdx, %rcx
	.p2align 4,,10
	.p2align 3
.L1898:
	movdqa	%xmm0, %xmm1
	addq	$16, %rax
	paddd	%xmm2, %xmm0
	movups	%xmm1, -16(%rax)
	cmpq	%rcx, %rax
	jne	.L1898
	movq	%r9, %rcx
	andq	$-4, %rcx
	movl	%ecx, %eax
	leaq	(%rdx,%rcx,4), %rdx
	cmpq	%r9, %rcx
	je	.L1896
.L1897:
	leaq	4(%rdx), %rcx
	movl	%eax, (%rdx)
	leal	1(%rax), %r9d
	cmpq	%rcx, %r8
	je	.L1896
	leaq	8(%rdx), %rcx
	movl	%r9d, 4(%rdx)
	addl	$2, %eax
	cmpq	%rcx, %r8
	je	.L1896
	movl	%eax, 8(%rdx)
	jmp	.L1896
.L1912:
	xorl	%eax, %eax
	jmp	.L1897
.L1960:
	movq	%rsi, %rdi
	movq	%rcx, 16(%rsp)
	movq	%rsi, 8(%rsp)
	call	malloc@PLT
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rcx
	movq	%rax, %rbp
	cmpq	$15, %rsi
	jbe	.L1889
	testb	$15, %al
	jne	.L1894
.L1889:
	testq	%rbp, %rbp
	je	.L1890
	movq	48(%r12), %rdi
	movq	%rbp, 40(%r12)
	testq	%rdi, %rdi
	jne	.L1910
.L1909:
	movq	%rsi, %rdi
	movq	%rcx, 16(%rsp)
	movq	%rsi, 8(%rsp)
	call	malloc@PLT
	movq	8(%rsp), %rsi
	movq	16(%rsp), %rcx
	movq	%rax, %rdi
	cmpq	$15, %rsi
	jbe	.L1893
	testb	$15, %al
	je	.L1893
.L1894:
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
.L1893:
	testq	%rdi, %rdi
	jne	.L1895
.L1890:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
.L1957:
	leaq	.LC77(%rip), %rcx
	movl	$73, %edx
	leaq	.LC75(%rip), %rsi
	leaq	.LC76(%rip), %rdi
	call	__assert_fail@PLT
.L1955:
	leaq	.LC70(%rip), %rcx
	movl	$1752, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC73(%rip), %rdi
	call	__assert_fail@PLT
.L1948:
	leaq	.LC70(%rip), %rcx
	movl	$1700, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC71(%rip), %rdi
	call	__assert_fail@PLT
.L1952:
	call	__stack_chk_fail@PLT
.L1961:
	leaq	.LC74(%rip), %rcx
	movl	$73, %edx
	leaq	.LC75(%rip), %rsi
	leaq	.LC76(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE12728:
	.size	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll, .-_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	.section	.rodata._ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll.str1.8,"aMS",@progbits,1
	.align 8
.LC78:
	.ascii	"Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::Sca"
	.string	"lar& Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::insertByOuterInner(Eigen::Index, Eigen::Index) [with Scalar_ = int; int Options_ = 0; StorageIndex_ = int; Eigen::SparseMatrix<Scalar_, Flags_, StorageIndex_>::Scalar = int; Eigen::Index = long int]"
	.align 8
.LC79:
	.string	"(dst == end || m_data.index(dst) != i) && \"you cannot insert an element that already exists, you must call coeffRef to this end\""
	.section	.text._ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll,"axG",@progbits,_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll,comdat
	.align 2
	.p2align 4
	.weak	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	.type	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll, @function
_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll:
.LFB12161:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	leaq	0(,%rsi,4), %r9
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	movq	%rsi, %r13
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdx, %r12
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	24(%rdi), %rbx
	movq	32(%rdi), %r8
	movslq	(%rbx,%rsi,4), %rax
	testq	%r8, %r8
	je	.L2018
	movslq	(%r8,%rsi,4), %rdi
	addq	%rax, %rdi
	cmpq	%rdi, %rax
	jne	.L1964
.L1966:
	movslq	4(%rbx,%r9), %rax
	cmpq	%rdi, %rax
	jle	.L1986
	movq	48(%rbp), %rax
	addl	$1, (%r8,%r9)
	movl	%r12d, (%rax,%rdi,4)
	movq	40(%rbp), %rax
	leaq	(%rax,%rdi,4), %rax
	movl	$0, (%rax)
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L2018:
	.cfi_restore_state
	movslq	4(%rbx,%r9), %rdi
	movq	%rax, %r14
	cmpq	%rdi, %rax
	je	.L1965
.L1964:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbp), %r10
	leaq	0(,%rdi,4), %rax
	subq	%rdx, %rax
	leaq	(%r10,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L1968:
	testq	%rax, %rax
	jle	.L2019
.L1969:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	movslq	(%rcx), %r11
	cmpq	%r11, %r12
	jle	.L1985
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L1969
.L2019:
	movq	%rsi, %rax
	subq	%r10, %rax
	sarq	$2, %rax
	movq	%rax, %r14
	cmpq	%rdi, %rax
	je	.L1966
	movslq	(%rsi), %rax
	cmpq	%r12, %rax
	je	.L2020
.L1971:
	testq	%r8, %r8
	je	.L1965
.L1973:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	movq	%r14, %rcx
	movq	%r12, %rdx
	movq	%r13, %rsi
	popq	%rbx
	.cfi_def_cfa_offset 48
	movq	%rbp, %rdi
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	jmp	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	.p2align 4,,10
	.p2align 3
.L1985:
	.cfi_restore_state
	movq	%rdx, %rax
	jmp	.L1968
	.p2align 4,,10
	.p2align 3
.L1965:
	movq	8(%rbp), %r15
	testq	%r15, %r15
	je	.L1973
	movq	%r15, %rax
	shrq	$62, %rax
	jne	.L1976
	leaq	0(,%r15,4), %rcx
	movl	$1, %esi
	movq	%r15, 8(%rsp)
	movq	%rcx, %rdi
	movq	%rcx, (%rsp)
	call	calloc@PLT
	movq	(%rsp), %rcx
	movq	8(%rsp), %r8
	movq	%rax, %rdx
	cmpq	$15, %rcx
	jbe	.L1975
	testb	$15, %al
	je	.L1975
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
	.p2align 4,,10
	.p2align 3
.L1975:
	testq	%rdx, %rdx
	je	.L1976
	movl	(%rbx,%r15,4), %eax
	movq	%rdx, 32(%rbp)
	testl	%eax, %eax
	je	.L1973
	testq	%r15, %r15
	je	.L1973
	leaq	4(%rbx), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L1987
	cmpq	$1, %r15
	je	.L1987
	leaq	-1(%r15), %rax
	cmpq	$2, %rax
	jbe	.L1988
	movq	%r15, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L1979:
	movdqu	4(%rbx,%rax), %xmm0
	movdqu	(%rbx,%rax), %xmm2
	psubd	%xmm2, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L1979
	movq	%r15, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r15
	je	.L1973
	subq	%rcx, %r15
	movq	%r15, %r8
	cmpq	$1, %r15
	je	.L1982
.L1978:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	(%rbx,%rcx,4), %xmm0
	movq	%r8, %rcx
	movq	-4(%rbx,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r8
	je	.L1973
.L1982:
	addq	$1, %rax
	movl	(%rbx,%rax,4), %ecx
	subl	-4(%rbx,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L1973
.L1987:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L1977:
	movl	4(%rbx,%rax,4), %ecx
	subl	(%rbx,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r15
	jne	.L1977
	jmp	.L1973
.L1988:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L1978
.L2020:
	leaq	.LC78(%rip), %rcx
	movl	$581, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC79(%rip), %rdi
	call	__assert_fail@PLT
.L1986:
	movq	%rdi, %r14
	jmp	.L1971
.L1976:
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
	.cfi_endproc
.LFE12161:
	.size	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll, .-_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	.section	.text.unlikely
.LCOLDB80:
	.text
.LHOTB80:
	.p2align 4
	.globl	_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE
	.type	_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE, @function
_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE:
.LFB11290:
	.cfi_startproc
	endbr64
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	xorl	%edx, %edx
	xorl	%esi, %esi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %rbx
	subq	$40, %rsp
	.cfi_def_cfa_offset 96
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$2, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$1, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$3, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$2, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$5, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$3, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$6, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$1, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$7, %edx
	xorl	%esi, %esi
	movq	%rbx, %rdi
	movl	$3, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %r8
	movl	$8, (%rax)
	movslq	4(%rbp), %rax
	testq	%r8, %r8
	je	.L2924
	movslq	4(%r8), %rdi
	addq	%rax, %rdi
	cmpq	%rdi, %rax
	jne	.L2023
.L2025:
	movslq	8(%rbp), %rax
	cmpq	%rdi, %rax
	jle	.L2436
	movq	48(%rbx), %rax
	addl	$1, 4(%r8)
	movl	$3, (%rax,%rdi,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%rdi,4), %rax
	movl	$0, (%rax)
.L2031:
	movl	$1, (%rax)
	movl	$4, %edx
	movl	$1, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %r9
	movl	$3, (%rax)
	movslq	4(%rbp), %rax
	testq	%r9, %r9
	je	.L2925
	movslq	4(%r9), %r8
	addq	%rax, %r8
	cmpq	%r8, %rax
	jne	.L2045
.L2047:
	movslq	8(%rbp), %rax
	cmpq	%r8, %rax
	jle	.L2440
	movq	48(%rbx), %rax
	addl	$1, 4(%r9)
	movl	$5, (%rax,%r8,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%r8,4), %rax
	movl	$0, (%rax)
	jmp	.L2053
	.p2align 4,,10
	.p2align 3
.L2924:
	movslq	8(%rbp), %rdi
	movq	%rax, %r12
	cmpq	%rdi, %rax
	je	.L2024
.L2023:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r9
	leaq	0(,%rdi,4), %rax
	subq	%rdx, %rax
	leaq	(%r9,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2027:
	testq	%rax, %rax
	jle	.L2926
.L2028:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	cmpl	$2, (%rcx)
	jg	.L2435
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2028
.L2926:
	movq	%rsi, %rax
	subq	%r9, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%rdi, %rax
	je	.L2025
	cmpl	$3, (%rsi)
	je	.L2054
.L2030:
	testq	%r8, %r8
	je	.L2024
.L2032:
	movq	%r12, %rcx
	movl	$3, %edx
	movl	$1, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	jmp	.L2031
	.p2align 4,,10
	.p2align 3
.L2435:
	movq	%rdx, %rax
	jmp	.L2027
	.p2align 4,,10
	.p2align 3
.L2925:
	movslq	8(%rbp), %r8
	movq	%rax, %r12
	cmpq	%r8, %rax
	je	.L2046
.L2045:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %rdi
	leaq	0(,%r8,4), %rax
	subq	%rdx, %rax
	leaq	(%rdi,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2049:
	testq	%rax, %rax
	jle	.L2927
.L2050:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	cmpl	$4, (%rcx)
	jg	.L2439
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2050
.L2927:
	movq	%rsi, %rax
	subq	%rdi, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%r8, %rax
	je	.L2047
	cmpl	$5, (%rsi)
	je	.L2054
.L2052:
	testq	%r9, %r9
	je	.L2046
.L2055:
	movq	%r12, %rcx
	movl	$5, %edx
	movl	$1, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
.L2053:
	movl	$8, (%rax)
	movl	$1, %esi
	movl	$6, %edx
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rsi
	movl	$7, (%rax)
	movslq	4(%rbp), %rax
	testq	%rsi, %rsi
	je	.L2928
	movslq	4(%rsi), %r9
	addq	%rax, %r9
	cmpq	%r9, %rax
	jne	.L2067
.L2069:
	movslq	8(%rbp), %rax
	cmpq	%r9, %rax
	jle	.L2444
	movq	48(%rbx), %rax
	addl	$1, 4(%rsi)
	movl	$8, (%rax,%r9,4)
	movq	40(%rbx), %rax
	movl	$1, (%rax,%r9,4)
	movslq	4(%rbp), %rax
	movslq	4(%rsi), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	je	.L2089
.L2087:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2091:
	testq	%rax, %rax
	jle	.L2929
.L2092:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rdi,%rdx,4), %rcx
	cmpl	$8, (%rcx)
	jg	.L2447
	subq	%rdx, %rax
	leaq	4(%rcx), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2092
.L2929:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%r12, %rcx
	je	.L2089
	cmpl	$9, (%rdi)
	je	.L2054
.L2094:
	testq	%rsi, %rsi
	je	.L2449
.L2098:
	movl	$9, %edx
	movl	$1, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
.L2095:
	movl	$2, (%rax)
	movl	$2, %esi
	xorl	%edx, %edx
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rsi
	movl	$2, (%rax)
	movslq	8(%rbp), %rax
	testq	%rsi, %rsi
	je	.L2930
	movslq	8(%rsi), %r9
	addq	%rax, %r9
	cmpq	%r9, %rax
	jne	.L2108
.L2110:
	movslq	12(%rbp), %rax
	cmpq	%r9, %rax
	jle	.L2455
	movq	48(%rbx), %rax
	addl	$1, 8(%rsi)
	movl	$2, (%rax,%r9,4)
	movq	40(%rbx), %rax
	movl	$2, (%rax,%r9,4)
	movslq	8(%rbp), %rax
	movslq	8(%rsi), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	je	.L2130
.L2128:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2132:
	testq	%rax, %rax
	jle	.L2931
.L2133:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rdi,%rdx,4), %rcx
	cmpl	$4, (%rcx)
	jg	.L2458
	subq	%rdx, %rax
	leaq	4(%rcx), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2133
.L2931:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%r12, %rcx
	je	.L2130
	cmpl	$5, (%rdi)
	je	.L2054
.L2135:
	testq	%rsi, %rsi
	je	.L2460
.L2139:
	movl	$5, %edx
	movl	$2, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
.L2136:
	movl	$1, (%rax)
	movl	$7, %edx
	movl	$2, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$9, %edx
	movl	$2, %esi
	movq	%rbx, %rdi
	movl	$3, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	xorl	%edx, %edx
	movl	$4, %esi
	movq	%rbx, %rdi
	movl	$1, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %r9
	movl	$1, (%rax)
	movslq	16(%rbp), %rax
	testq	%r9, %r9
	je	.L2932
	movslq	16(%r9), %rdi
	addq	%rax, %rdi
	cmpq	%rdi, %rax
	jne	.L2149
.L2151:
	movslq	20(%rbp), %rax
	cmpq	%rdi, %rax
	jle	.L2466
	movq	48(%rbx), %rax
	addl	$1, 16(%r9)
	movl	$3, (%rax,%rdi,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%rdi,4), %rax
	movl	$0, (%rax)
	jmp	.L2157
	.p2align 4,,10
	.p2align 3
.L2439:
	movq	%rdx, %rax
	jmp	.L2049
	.p2align 4,,10
	.p2align 3
.L2928:
	movslq	8(%rbp), %r9
	movq	%rax, %r12
	cmpq	%r9, %rax
	je	.L2068
.L2067:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%r9,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2071:
	testq	%rax, %rax
	jle	.L2933
.L2072:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rdi,%rdx,4), %rcx
	cmpl	$7, (%rcx)
	jg	.L2443
	subq	%rdx, %rax
	leaq	4(%rcx), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2072
.L2933:
	movq	%rdi, %rax
	subq	%r8, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%r9, %rax
	je	.L2069
	cmpl	$8, (%rdi)
	je	.L2054
.L2074:
	testq	%rsi, %rsi
	je	.L2068
.L2077:
	movl	$1, %esi
	movq	%r12, %rcx
	movl	$8, %edx
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rsi
	movl	$1, (%rax)
	movslq	4(%rbp), %rax
	testq	%rsi, %rsi
	je	.L2934
	movslq	4(%rsi), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2087
.L2089:
	movslq	8(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2448
	movq	48(%rbx), %rax
	addl	$1, 4(%rsi)
	movl	$9, (%rax,%r12,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%r12,4), %rax
	movl	$0, (%rax)
	jmp	.L2095
	.p2align 4,,10
	.p2align 3
.L2443:
	movq	%rdx, %rax
	jmp	.L2071
	.p2align 4,,10
	.p2align 3
.L2447:
	movq	%rdx, %rax
	jmp	.L2091
	.p2align 4,,10
	.p2align 3
.L2930:
	movslq	12(%rbp), %r9
	movq	%rax, %r12
	cmpq	%r9, %rax
	je	.L2109
.L2108:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%r9,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2112:
	testq	%rax, %rax
	jle	.L2935
.L2113:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rdi,%rdx,4), %rcx
	cmpl	$1, (%rcx)
	jg	.L2454
	subq	%rdx, %rax
	leaq	4(%rcx), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2113
.L2935:
	movq	%rdi, %rax
	subq	%r8, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%r9, %rax
	je	.L2110
	cmpl	$2, (%rdi)
	je	.L2054
.L2115:
	testq	%rsi, %rsi
	je	.L2109
.L2118:
	movl	$2, %esi
	movq	%r12, %rcx
	movl	$2, %edx
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rsi
	movl	$2, (%rax)
	movslq	8(%rbp), %rax
	testq	%rsi, %rsi
	je	.L2936
	movslq	8(%rsi), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2128
.L2130:
	movslq	12(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2459
	movq	48(%rbx), %rax
	addl	$1, 8(%rsi)
	movl	$5, (%rax,%r12,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%r12,4), %rax
	movl	$0, (%rax)
	jmp	.L2136
	.p2align 4,,10
	.p2align 3
.L2454:
	movq	%rdx, %rax
	jmp	.L2112
	.p2align 4,,10
	.p2align 3
.L2458:
	movq	%rdx, %rax
	jmp	.L2132
	.p2align 4,,10
	.p2align 3
.L2149:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%rdi,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2153:
	testq	%rax, %rax
	jle	.L2937
.L2154:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	cmpl	$2, (%rcx)
	jg	.L2465
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2154
.L2937:
	movq	%rsi, %rax
	subq	%r8, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%rdi, %rax
	je	.L2151
	cmpl	$3, (%rsi)
	je	.L2054
.L2156:
	testq	%r9, %r9
	je	.L2150
.L2158:
	movq	%r12, %rcx
	movl	$3, %edx
	movl	$4, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
.L2157:
	movl	$1, (%rax)
	movl	$4, %edx
	movl	$4, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %r9
	movl	$3, (%rax)
	movslq	16(%rbp), %rax
	testq	%r9, %r9
	je	.L2938
	movslq	16(%r9), %r8
	addq	%rax, %r8
	cmpq	%r8, %rax
	jne	.L2169
.L2171:
	movslq	20(%rbp), %rax
	cmpq	%r8, %rax
	jle	.L2470
	movq	48(%rbx), %rax
	addl	$1, 16(%r9)
	movl	$6, (%rax,%r8,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%r8,4), %rax
	movl	$0, (%rax)
	jmp	.L2177
	.p2align 4,,10
	.p2align 3
.L2465:
	movq	%rdx, %rax
	jmp	.L2153
	.p2align 4,,10
	.p2align 3
.L2169:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %rdi
	leaq	0(,%r8,4), %rax
	subq	%rdx, %rax
	leaq	(%rdi,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2173:
	testq	%rax, %rax
	jle	.L2939
.L2174:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	cmpl	$5, (%rcx)
	jg	.L2469
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2174
.L2939:
	movq	%rsi, %rax
	subq	%rdi, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%r8, %rax
	je	.L2171
	cmpl	$6, (%rsi)
	je	.L2054
.L2176:
	testq	%r9, %r9
	je	.L2170
.L2178:
	movq	%r12, %rcx
	movl	$6, %edx
	movl	$4, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
.L2177:
	movl	$2, (%rax)
	movl	$7, %edx
	movl	$4, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %r9
	movl	$1, (%rax)
	movslq	20(%rbp), %rax
	testq	%r9, %r9
	je	.L2940
	movslq	20(%r9), %r8
	addq	%rax, %r8
	cmpq	%r8, %rax
	jne	.L2189
.L2191:
	movslq	24(%rbp), %rax
	cmpq	%r8, %rax
	jle	.L2474
	movq	48(%rbx), %rax
	addl	$1, 20(%r9)
	movl	$0, (%rax,%r8,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%r8,4), %rax
	movl	$0, (%rax)
	jmp	.L2197
	.p2align 4,,10
	.p2align 3
.L2469:
	movq	%rdx, %rax
	jmp	.L2173
	.p2align 4,,10
	.p2align 3
.L2024:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2032
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2034
	testb	$15, %al
	je	.L2034
	.p2align 4,,10
	.p2align 3
.L2057:
	leaq	.LC23(%rip), %rcx
	movl	$219, %edx
	leaq	.LC24(%rip), %rsi
	leaq	.LC25(%rip), %rdi
	call	__assert_fail@PLT
	.p2align 4,,10
	.p2align 3
.L2046:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2055
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2056
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2056:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %eax
	movq	%rdx, 32(%rbx)
	testl	%eax, %eax
	je	.L2055
	testq	%r13, %r13
	je	.L2055
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2441
	cmpq	$1, %r13
	je	.L2441
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2442
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2060:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm3
	psubd	%xmm3, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2060
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2055
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2063
.L2059:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2055
.L2063:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2055
	.p2align 4,,10
	.p2align 3
.L2189:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %rdi
	leaq	0(,%r8,4), %rax
	subq	%rdx, %rax
	leaq	(%rdi,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2193:
	testq	%rax, %rax
	jle	.L2941
.L2194:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	movl	(%rcx), %r10d
	testl	%r10d, %r10d
	jns	.L2473
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2194
.L2941:
	movq	%rsi, %rax
	subq	%rdi, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%r8, %rax
	je	.L2191
	movl	(%rsi), %eax
	testl	%eax, %eax
	je	.L2054
.L2196:
	testq	%r9, %r9
	je	.L2190
.L2198:
	movq	%r12, %rcx
	xorl	%edx, %edx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
.L2197:
	movl	$8, (%rax)
	movl	$2, %edx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$1, (%rax)
	movslq	20(%rbp), %rax
	testq	%rdx, %rdx
	je	.L2942
	movslq	20(%rdx), %rcx
	leaq	(%rcx,%rax), %r9
	cmpq	%r9, %rax
	jne	.L2209
.L2211:
	movslq	24(%rbp), %rax
	cmpq	%r9, %rax
	jle	.L2478
	movq	48(%rbx), %rax
	addl	$1, 20(%rdx)
	movl	$3, (%rax,%r9,4)
	movq	40(%rbx), %rax
	movl	$4, (%rax,%r9,4)
	movslq	20(%rbp), %rax
	movslq	20(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2229
.L2231:
	movslq	24(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2482
	movq	48(%rbx), %rax
	addl	$1, 20(%rdx)
	movl	$5, (%rax,%r12,4)
	movq	40(%rbx), %rax
	movl	$3, (%rax,%r12,4)
	movslq	20(%rbp), %rax
	jmp	.L2237
	.p2align 4,,10
	.p2align 3
.L2209:
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r9,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2213:
	testq	%rax, %rax
	jle	.L2943
.L2214:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$2, (%rsi)
	jg	.L2477
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2214
.L2943:
	movq	%rdi, %rax
	subq	%r8, %rax
	sarq	$2, %rax
	movq	%rax, %r12
	cmpq	%rax, %r9
	je	.L2211
	cmpl	$3, (%rdi)
	je	.L2054
.L2216:
	testq	%rdx, %rdx
	je	.L2210
.L2219:
	movl	$3, %edx
	movq	%r12, %rcx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$4, (%rax)
	movslq	20(%rbp), %rax
	testq	%rdx, %rdx
	je	.L2944
	movslq	20(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	je	.L2231
.L2229:
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2233:
	testq	%rax, %rax
	jle	.L2945
.L2234:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$4, (%rsi)
	jg	.L2481
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2234
.L2945:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %r12
	je	.L2231
	cmpl	$5, (%rdi)
	je	.L2054
.L2236:
	testq	%rdx, %rdx
	je	.L2483
.L2241:
	movl	$5, %edx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$3, (%rax)
	movslq	20(%rbp), %rax
	testq	%rdx, %rdx
	je	.L2946
.L2237:
	movslq	20(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2250
.L2252:
	movslq	24(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2489
	movq	48(%rbx), %rax
	addl	$1, 20(%rdx)
	movl	$7, (%rax,%r12,4)
	movq	40(%rbx), %rax
	movl	$1, (%rax,%r12,4)
	movslq	20(%rbp), %rax
	jmp	.L2258
	.p2align 4,,10
	.p2align 3
.L2250:
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2254:
	testq	%rax, %rax
	jle	.L2947
.L2255:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$6, (%rsi)
	jg	.L2488
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2255
.L2947:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %r12
	je	.L2252
	cmpl	$7, (%rdi)
	je	.L2054
.L2257:
	testq	%rdx, %rdx
	je	.L2490
.L2262:
	movl	$7, %edx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$1, (%rax)
	movslq	20(%rbp), %rax
	testq	%rdx, %rdx
	je	.L2948
.L2258:
	movslq	20(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2271
.L2273:
	movslq	24(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2496
	movq	48(%rbx), %rax
	addl	$1, 20(%rdx)
	movl	$8, (%rax,%r12,4)
	movq	40(%rbx), %rax
	movl	$2, (%rax,%r12,4)
	movslq	24(%rbp), %rax
.L2279:
	movslq	24(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2294
.L2296:
	movslq	28(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2503
	movq	48(%rbx), %rax
	addl	$1, 24(%rdx)
	movl	$3, (%rax,%r12,4)
	movq	40(%rbx), %rax
	movl	$6, (%rax,%r12,4)
	movslq	24(%rbp), %rax
.L2302:
	movslq	24(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2317
.L2319:
	movslq	28(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2510
	movq	48(%rbx), %rax
	addl	$1, 24(%rdx)
	movl	$5, (%rax,%r12,4)
	movq	40(%rbx), %rax
	movl	$1, (%rax,%r12,4)
	movslq	24(%rbp), %rax
.L2325:
	movslq	24(%rdx), %r12
	addq	%rax, %r12
	cmpq	%rax, %r12
	jne	.L2340
.L2342:
	movslq	28(%rbp), %rax
	cmpq	%r12, %rax
	jle	.L2517
	movq	48(%rbx), %rax
	addl	$1, 24(%rdx)
	movl	$7, (%rax,%r12,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%r12,4), %rax
	movl	$0, (%rax)
.L2348:
	movl	$3, (%rax)
	movl	$2, %edx
	movl	$7, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$4, %edx
	movl	$7, %esi
	movq	%rbx, %rdi
	movl	$3, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$5, %edx
	movl	$7, %esi
	movq	%rbx, %rdi
	movl	$4, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	%rbx, %rdi
	movl	$8, %edx
	movl	$7, %esi
	movl	$1, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %r12
	movq	32(%rbx), %rdi
	movl	$2, (%rax)
	movslq	28(%r12), %rax
	testq	%rdi, %rdi
	je	.L2949
	movslq	28(%rdi), %rbp
	addq	%rax, %rbp
	cmpq	%rbp, %rax
	jne	.L2363
.L2365:
	movslq	32(%r12), %rax
	cmpq	%rbp, %rax
	jle	.L2524
	movq	48(%rbx), %rax
	addl	$1, 28(%rdi)
	movl	$9, (%rax,%rbp,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%rbp,4), %rax
	movl	$0, (%rax)
.L2371:
	movl	$3, (%rax)
	movq	%rbx, %rdi
	xorl	%edx, %edx
	movl	$8, %esi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	24(%rbx), %r12
	movq	32(%rbx), %rdi
	movl	$2, (%rax)
	movslq	32(%r12), %rax
	testq	%rdi, %rdi
	je	.L2950
	movslq	32(%rdi), %rbp
	addq	%rax, %rbp
	cmpq	%rbp, %rax
	jne	.L2385
.L2387:
	movslq	36(%r12), %rax
	cmpq	%rbp, %rax
	jle	.L2532
	movq	48(%rbx), %rax
	addl	$1, 32(%rdi)
	movl	$2, (%rax,%rbp,4)
	movq	40(%rbx), %rax
	leaq	(%rax,%rbp,4), %rax
	movl	$0, (%rax)
.L2393:
	movl	$1, (%rax)
	movl	$3, %edx
	movl	$8, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$5, %edx
	movl	$8, %esi
	movq	%rbx, %rdi
	movl	$2, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$7, %edx
	movl	$8, %esi
	movq	%rbx, %rdi
	movl	$3, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$9, %edx
	movl	$8, %esi
	movq	%rbx, %rdi
	movl	$3, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$3, %edx
	movl	$9, %esi
	movq	%rbx, %rdi
	movl	$1, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$4, %edx
	movl	$9, %esi
	movq	%rbx, %rdi
	movl	$2, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$7, %edx
	movl	$9, %esi
	movq	%rbx, %rdi
	movl	$4, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movl	$8, %edx
	movl	$9, %esi
	movq	%rbx, %rdi
	movl	$1, (%rax)
	call	_ZN5Eigen12SparseMatrixIiLi0EiE18insertByOuterInnerEll
	movq	32(%rbx), %r11
	movl	$1, (%rax)
	testq	%r11, %r11
	je	.L2021
	movq	24(%rbx), %rdi
	movslq	(%r11), %r8
	movq	8(%rbx), %rsi
	movslq	4(%rdi), %r14
	movl	%r8d, 4(%rdi)
	movq	%r14, %r13
	cmpq	$1, %rsi
	jle	.L2408
	movl	$1, %ebp
	jmp	.L2412
	.p2align 4,,10
	.p2align 3
.L2409:
	cltq
	movq	%r9, (%rsp)
	movq	%rax, %r10
	subq	%r14, %r10
	testq	%r10, %r10
	jg	.L2951
.L2411:
	addl	(%rdi,%r15), %edx
	addq	$1, %rbp
	movslq	%r13d, %r14
	addq	%r10, %r8
	movl	%edx, (%rcx)
	cmpq	%rsi, %rbp
	jge	.L2408
.L2412:
	leaq	0(,%rbp,4), %r15
	movl	(%r11,%rbp,4), %edx
	leaq	4(%r15), %r9
	leaq	(%rdi,%r9), %rcx
	leal	(%rdx,%r13), %eax
	movl	(%rcx), %r13d
	cmpl	%r13d, %eax
	jne	.L2409
	leaq	-1(%rsi), %r10
	cmpq	%rbp, %r10
	je	.L2409
	addl	(%rdi,%r15), %edx
	addq	$1, %rbp
	movl	%edx, (%rcx)
	cmpq	%rsi, %rbp
	jl	.L2412
	.p2align 4,,10
	.p2align 3
.L2408:
	movslq	(%rdi,%rsi,4), %r12
	movq	64(%rbx), %rdx
	cmpq	%rdx, %r12
	jle	.L2413
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%r12d, %xmm0
	mulsd	.LC41(%rip), %xmm0
	cvttsd2siq	%xmm0, %r13
	addq	%r12, %r13
	cmpq	$2147483646, %r13
	jle	.L2952
	movq	40(%rbx), %rdi
	movq	%rdx, %r14
	movl	$2147483647, %r13d
	movl	$2147483647, %ebp
.L2433:
	movq	%rdx, %rax
	shrq	$62, %rax
	jne	.L2035
	salq	$2, %rdx
	salq	$2, %rbp
	testq	%rdi, %rdi
	je	.L2953
	cmpq	%rbp, %rdx
	je	.L2416
	testq	%rbp, %rbp
	je	.L2954
	movq	%rbp, %rsi
	call	realloc@PLT
	testq	%rax, %rax
	je	.L2035
	movq	64(%rbx), %r14
.L2419:
	movq	%rax, 40(%rbx)
	movq	%r14, %rax
	movq	48(%rbx), %rdi
	shrq	$62, %rax
	jne	.L2035
.L2434:
	salq	$2, %r14
	testq	%rdi, %rdi
	je	.L2955
	cmpq	%rbp, %r14
	je	.L2421
	testq	%rbp, %rbp
	je	.L2956
	movq	%rbp, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L2921:
	testq	%rdi, %rdi
	je	.L2035
.L2421:
	movq	%rdi, 48(%rbx)
	movq	32(%rbx), %r11
	movq	%r13, 64(%rbx)
.L2413:
	movq	%r12, 56(%rbx)
	movq	%r11, %rdi
	call	free@PLT
	movq	64(%rbx), %rax
	movq	56(%rbx), %r13
	movq	$0, 32(%rbx)
	cmpq	%r13, %rax
	jle	.L2021
	movq	%rax, %rbp
	orq	%r13, %rax
	movq	40(%rbx), %rdi
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%rbp,4), %rax
	leaq	0(,%r13,4), %r12
	testq	%rdi, %rdi
	je	.L2957
	cmpq	%r12, %rax
	je	.L2426
	testq	%r12, %r12
	je	.L2958
	movq	%r12, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
	testq	%rax, %rax
	je	.L2035
	movq	64(%rbx), %rbp
.L2426:
	movq	%rbp, %rax
	movq	%rdi, 40(%rbx)
	movq	48(%rbx), %rdi
	shrq	$62, %rax
	jne	.L2035
	salq	$2, %rbp
	testq	%rdi, %rdi
	je	.L2959
	cmpq	%r12, %rbp
	je	.L2430
	testq	%r12, %r12
	je	.L2960
	movq	%r12, %rsi
	call	realloc@PLT
	movq	%rax, %rdi
.L2922:
	testq	%rdi, %rdi
	je	.L2035
.L2430:
	movq	%rdi, 48(%rbx)
	movq	%r13, 64(%rbx)
.L2021:
	addq	$40, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L2271:
	.cfi_restore_state
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2275:
	testq	%rax, %rax
	jle	.L2961
.L2276:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$7, (%rsi)
	jg	.L2495
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2276
.L2961:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %r12
	je	.L2273
	cmpl	$8, (%rdi)
	je	.L2054
.L2278:
	testq	%rdx, %rdx
	je	.L2962
.L2285:
	movl	$8, %edx
	movl	$5, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$2, (%rax)
	movslq	24(%rbp), %rax
	testq	%rdx, %rdx
	jne	.L2279
	movslq	28(%rbp), %r12
	cmpq	%r12, %rax
	jne	.L2294
.L2295:
	movq	8(%rbx), %r14
	movq	%r14, %r15
	testq	%r14, %r14
	je	.L2304
	movq	%r14, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r14,4), %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L2305
	testb	$15, %al
	jne	.L2057
.L2305:
	testq	%rdi, %rdi
	je	.L2035
	movl	0(%rbp,%r14,4), %r8d
	movq	%rdi, 32(%rbx)
	testl	%r8d, %r8d
	je	.L2306
	testq	%r14, %r14
	je	.L2506
	leaq	4(%rbp), %rdx
	movq	%rdi, %rax
	subq	%rdx, %rax
	cmpq	$12, %rax
	jbe	.L2507
	cmpq	$1, %r14
	je	.L2507
	leaq	-1(%r14), %rax
	cmpq	$2, %rax
	jbe	.L2508
	movq	%r14, %rdx
	xorl	%eax, %eax
	shrq	$2, %rdx
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L2311:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm6
	psubd	%xmm6, %xmm0
	movups	%xmm0, (%rdi,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L2311
	movq	%r14, %rdx
	andq	$-4, %rdx
	movq	%rdx, %rax
	cmpq	%r14, %rdx
	je	.L2506
	movq	%r14, %r15
	subq	%rdx, %r15
	cmpq	$1, %r15
	je	.L2314
.L2310:
	addq	$1, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	0(%rbp,%rdx,4), %xmm0
	movq	%r15, %rdx
	movq	-4(%rbp,%rcx), %xmm1
	andq	$-2, %rdx
	addq	%rdx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdi,%rcx)
	cmpq	%r15, %rdx
	je	.L2506
.L2314:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %edx
	subl	-4(%rbp,%rax,4), %edx
	movl	%edx, -4(%rdi,%rax,4)
.L2506:
	movq	%r12, %rcx
	jmp	.L2308
	.p2align 4,,10
	.p2align 3
.L2473:
	movq	%rdx, %rax
	jmp	.L2193
	.p2align 4,,10
	.p2align 3
.L2477:
	movq	%rcx, %rax
	jmp	.L2213
	.p2align 4,,10
	.p2align 3
.L2481:
	movq	%rcx, %rax
	jmp	.L2233
	.p2align 4,,10
	.p2align 3
.L2488:
	movq	%rcx, %rax
	jmp	.L2254
	.p2align 4,,10
	.p2align 3
.L2495:
	movq	%rcx, %rax
	jmp	.L2275
	.p2align 4,,10
	.p2align 3
.L2068:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2077
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2078
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2078:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %eax
	movq	%rdx, 32(%rbx)
	testl	%eax, %eax
	je	.L2077
	testq	%r13, %r13
	je	.L2077
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2445
	cmpq	$1, %r13
	je	.L2445
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2446
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2081:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm4
	psubd	%xmm4, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2081
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2077
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2084
.L2080:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2077
.L2084:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2077
	.p2align 4,,10
	.p2align 3
.L2934:
	movslq	8(%rbp), %r12
	cmpq	%r12, %rax
	jne	.L2087
.L2088:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2096
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2097
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2097:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %eax
	movq	%rdx, 32(%rbx)
	movq	%r12, %rcx
	testl	%eax, %eax
	je	.L2098
	testq	%r13, %r13
	je	.L2098
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2452
	cmpq	$1, %r13
	je	.L2452
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2453
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2101:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm5
	psubd	%xmm5, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2101
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2917
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2104
.L2100:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2917
.L2104:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
.L2917:
	movq	%r12, %rcx
	jmp	.L2098
	.p2align 4,,10
	.p2align 3
.L2936:
	movslq	12(%rbp), %r12
	cmpq	%r12, %rax
	jne	.L2128
.L2129:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2137
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2138
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2138:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %eax
	movq	%rdx, 32(%rbx)
	movq	%r12, %rcx
	testl	%eax, %eax
	je	.L2139
	testq	%r13, %r13
	je	.L2139
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2463
	cmpq	$1, %r13
	je	.L2463
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2464
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2142:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm7
	psubd	%xmm7, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2142
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2918
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2145
.L2141:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2918
.L2145:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
.L2918:
	movq	%r12, %rcx
	jmp	.L2139
	.p2align 4,,10
	.p2align 3
.L2294:
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2298:
	testq	%rax, %rax
	jle	.L2963
.L2299:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$2, (%rsi)
	jg	.L2502
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2299
.L2963:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %r12
	je	.L2296
	cmpl	$3, (%rdi)
	je	.L2054
.L2301:
	testq	%rdx, %rdx
	je	.L2964
.L2308:
	movl	$3, %edx
	movl	$6, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$6, (%rax)
	movslq	24(%rbp), %rax
	testq	%rdx, %rdx
	jne	.L2302
	movslq	28(%rbp), %r12
	cmpq	%r12, %rax
	je	.L2318
.L2317:
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2321:
	testq	%rax, %rax
	jle	.L2965
.L2322:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$4, (%rsi)
	jg	.L2509
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2322
.L2965:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %r12
	je	.L2319
	cmpl	$5, (%rdi)
	je	.L2054
.L2324:
	testq	%rdx, %rdx
	je	.L2966
.L2331:
	movl	$5, %edx
	movl	$6, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	movq	24(%rbx), %rbp
	movq	32(%rbx), %rdx
	movl	$1, (%rax)
	movslq	24(%rbp), %rax
	testq	%rdx, %rdx
	jne	.L2325
	movslq	28(%rbp), %r12
	cmpq	%r12, %rax
	je	.L2341
.L2340:
	leaq	0(,%rax,4), %rcx
	movq	48(%rbx), %r8
	leaq	0(,%r12,4), %rax
	subq	%rcx, %rax
	leaq	(%r8,%rcx), %rdi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2344:
	testq	%rax, %rax
	jle	.L2967
.L2345:
	movq	%rax, %rcx
	sarq	%rcx
	leaq	(%rdi,%rcx,4), %rsi
	cmpl	$6, (%rsi)
	jg	.L2516
	subq	%rcx, %rax
	leaq	4(%rsi), %rdi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2345
.L2967:
	movq	%rdi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %r12
	je	.L2342
	cmpl	$7, (%rdi)
	je	.L2054
.L2347:
	testq	%rdx, %rdx
	je	.L2968
.L2353:
	movl	$7, %edx
	movl	$6, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	jmp	.L2348
	.p2align 4,,10
	.p2align 3
.L2109:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2118
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2119
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2119:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %eax
	movq	%rdx, 32(%rbx)
	testl	%eax, %eax
	je	.L2118
	testq	%r13, %r13
	je	.L2118
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2456
	cmpq	$1, %r13
	je	.L2456
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2457
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2122:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm6
	psubd	%xmm6, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2122
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2118
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2125
.L2121:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2118
.L2125:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2118
	.p2align 4,,10
	.p2align 3
.L2502:
	movq	%rcx, %rax
	jmp	.L2298
	.p2align 4,,10
	.p2align 3
.L2509:
	movq	%rcx, %rax
	jmp	.L2321
	.p2align 4,,10
	.p2align 3
.L2516:
	movq	%rcx, %rax
	jmp	.L2344
	.p2align 4,,10
	.p2align 3
.L2951:
	salq	$2, %r14
	leaq	0(,%rax,4), %r12
	subq	%r14, %r12
	je	.L2411
	movq	40(%rbx), %rdi
	leaq	0(,%r8,4), %rcx
	movq	%r12, %rdx
	movq	%r10, 24(%rsp)
	movq	%r8, 16(%rsp)
	leaq	(%rdi,%r14), %rsi
	addq	%rcx, %rdi
	movq	%rcx, 8(%rsp)
	call	memmove@PLT
	movq	48(%rbx), %rsi
	movq	8(%rsp), %rdi
	movq	%r12, %rdx
	addq	48(%rbx), %rdi
	addq	%r14, %rsi
	call	memmove@PLT
	movq	24(%rbx), %rdi
	movq	32(%rbx), %r11
	movq	(%rsp), %r9
	movq	8(%rbx), %rsi
	movl	(%r11,%r15), %edx
	movq	24(%rsp), %r10
	movq	16(%rsp), %r8
	leaq	(%rdi,%r9), %rcx
	jmp	.L2411
	.p2align 4,,10
	.p2align 3
.L2932:
	movslq	20(%rbp), %rdi
	movq	%rax, %r12
	cmpq	%rdi, %rax
	jne	.L2149
.L2150:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2158
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2159
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2159:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %r14d
	movq	%rdx, 32(%rbx)
	testl	%r14d, %r14d
	je	.L2158
	testq	%r13, %r13
	je	.L2158
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2467
	cmpq	$1, %r13
	je	.L2467
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2468
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2162:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm7
	psubd	%xmm7, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2162
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2158
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2165
.L2161:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2158
.L2165:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2158
	.p2align 4,,10
	.p2align 3
.L2938:
	movslq	20(%rbp), %r8
	movq	%rax, %r12
	cmpq	%r8, %rax
	jne	.L2169
.L2170:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2178
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2179
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2179:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %r11d
	movq	%rdx, 32(%rbx)
	testl	%r11d, %r11d
	je	.L2178
	testq	%r13, %r13
	je	.L2178
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2471
	cmpq	$1, %r13
	je	.L2471
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2472
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2182:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm6
	psubd	%xmm6, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2182
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2178
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2185
.L2181:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2178
.L2185:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2178
	.p2align 4,,10
	.p2align 3
.L2940:
	movslq	24(%rbp), %r8
	movq	%rax, %r12
	cmpq	%r8, %rax
	jne	.L2189
.L2190:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2198
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2199
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2199:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %eax
	movq	%rdx, 32(%rbx)
	testl	%eax, %eax
	je	.L2198
	testq	%r13, %r13
	je	.L2198
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2475
	cmpq	$1, %r13
	je	.L2475
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2476
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2202:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm5
	psubd	%xmm5, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2202
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2198
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2205
.L2201:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2198
.L2205:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2198
	.p2align 4,,10
	.p2align 3
.L2949:
	movslq	32(%r12), %rbp
	cmpq	%rbp, %rax
	je	.L2364
.L2363:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%rbp,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2367:
	testq	%rax, %rax
	jle	.L2969
.L2368:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	cmpl	$8, (%rcx)
	jg	.L2523
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2368
.L2969:
	movq	%rsi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %rbp
	je	.L2365
	cmpl	$9, (%rsi)
	je	.L2054
.L2370:
	testq	%rdi, %rdi
	je	.L2970
.L2372:
	movl	$9, %edx
	movl	$7, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	jmp	.L2371
	.p2align 4,,10
	.p2align 3
.L2523:
	movq	%rdx, %rax
	jmp	.L2367
	.p2align 4,,10
	.p2align 3
.L2942:
	movslq	24(%rbp), %r9
	movq	%rax, %r12
	cmpq	%r9, %rax
	jne	.L2209
.L2210:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2219
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2220
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2220:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %r14d
	movq	%rdx, 32(%rbx)
	testl	%r14d, %r14d
	je	.L2219
	testq	%r13, %r13
	je	.L2219
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2479
	cmpq	$1, %r13
	je	.L2479
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2480
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2223:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm4
	psubd	%xmm4, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2223
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2219
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2226
.L2222:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2219
.L2226:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2219
	.p2align 4,,10
	.p2align 3
.L2944:
	movslq	24(%rbp), %r12
	cmpq	%r12, %rax
	jne	.L2229
.L2230:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2239
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2240
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2240:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %r11d
	movq	%rdx, 32(%rbx)
	movq	%r12, %rcx
	testl	%r11d, %r11d
	je	.L2241
	testq	%r13, %r13
	je	.L2241
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2486
	cmpq	$1, %r13
	je	.L2486
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2487
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2244:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm3
	psubd	%xmm3, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2244
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%r13, %rcx
	je	.L2919
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2247
.L2243:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%r15, %rcx
	je	.L2919
.L2247:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
.L2919:
	movq	%r12, %rcx
	jmp	.L2241
	.p2align 4,,10
	.p2align 3
.L2950:
	movslq	36(%r12), %rbp
	cmpq	%rbp, %rax
	je	.L2386
.L2385:
	leaq	0(,%rax,4), %rdx
	movq	48(%rbx), %r8
	leaq	0(,%rbp,4), %rax
	subq	%rdx, %rax
	leaq	(%r8,%rdx), %rsi
	sarq	$2, %rax
	.p2align 4,,10
	.p2align 3
.L2389:
	testq	%rax, %rax
	jle	.L2971
.L2390:
	movq	%rax, %rdx
	sarq	%rdx
	leaq	(%rsi,%rdx,4), %rcx
	cmpl	$1, (%rcx)
	jg	.L2531
	subq	%rdx, %rax
	leaq	4(%rcx), %rsi
	subq	$1, %rax
	testq	%rax, %rax
	jg	.L2390
.L2971:
	movq	%rsi, %rcx
	subq	%r8, %rcx
	sarq	$2, %rcx
	cmpq	%rcx, %rbp
	je	.L2387
	cmpl	$2, (%rsi)
	je	.L2054
.L2392:
	testq	%rdi, %rdi
	je	.L2972
.L2394:
	movl	$2, %edx
	movl	$8, %esi
	movq	%rbx, %rdi
	call	_ZN5Eigen12SparseMatrixIiLi0EiE32insertUncompressedAtByOuterInnerElll
	jmp	.L2393
	.p2align 4,,10
	.p2align 3
.L2531:
	movq	%rdx, %rax
	jmp	.L2389
	.p2align 4,,10
	.p2align 3
.L2946:
	movslq	24(%rbp), %r12
	cmpq	%r12, %rax
	jne	.L2250
.L2251:
	movq	8(%rbx), %r13
	movq	%r13, %r15
	testq	%r13, %r13
	je	.L2260
	movq	%r13, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r13,4), %r14
	movl	$1, %esi
	movq	%r14, %rdi
	call	calloc@PLT
	movq	%rax, %rdx
	cmpq	$15, %r14
	jbe	.L2261
	testb	$15, %al
	jne	.L2057
	.p2align 4,,10
	.p2align 3
.L2261:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %r10d
	movq	%rdx, 32(%rbx)
	movq	%r12, %rcx
	testl	%r10d, %r10d
	je	.L2262
	testq	%r13, %r13
	je	.L2262
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2493
	cmpq	$1, %r13
	je	.L2493
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2494
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2265:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm2
	psubd	%xmm2, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rcx, %rax
	jne	.L2265
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2920
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2268
.L2264:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%r15, %rcx
	je	.L2920
.L2268:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
.L2920:
	movq	%r12, %rcx
	jmp	.L2262
	.p2align 4,,10
	.p2align 3
.L2948:
	movslq	24(%rbp), %r12
	cmpq	%r12, %rax
	jne	.L2271
.L2272:
	movq	8(%rbx), %r14
	movq	%r14, %r15
	testq	%r14, %r14
	je	.L2281
	movq	%r14, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r14,4), %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L2282
	testb	$15, %al
	jne	.L2057
.L2282:
	testq	%rdi, %rdi
	je	.L2035
	movl	0(%rbp,%r14,4), %r9d
	movq	%rdi, 32(%rbx)
	testl	%r9d, %r9d
	je	.L2283
	testq	%r14, %r14
	je	.L2499
	leaq	4(%rbp), %rdx
	movq	%rdi, %rax
	subq	%rdx, %rax
	cmpq	$12, %rax
	jbe	.L2500
	cmpq	$1, %r14
	je	.L2500
	leaq	-1(%r14), %rax
	cmpq	$2, %rax
	jbe	.L2501
	movq	%r14, %rdx
	xorl	%eax, %eax
	shrq	$2, %rdx
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L2288:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm5
	psubd	%xmm5, %xmm0
	movups	%xmm0, (%rdi,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L2288
	movq	%r14, %rdx
	andq	$-4, %rdx
	movq	%rdx, %rax
	cmpq	%r14, %rdx
	je	.L2499
	movq	%r14, %r15
	subq	%rdx, %r15
	cmpq	$1, %r15
	je	.L2291
.L2287:
	addq	$1, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	0(%rbp,%rdx,4), %xmm0
	movq	%r15, %rdx
	movq	-4(%rbp,%rcx), %xmm1
	andq	$-2, %rdx
	addq	%rdx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdi,%rcx)
	cmpq	%r15, %rdx
	je	.L2499
.L2291:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %edx
	subl	-4(%rbp,%rax,4), %edx
	movl	%edx, -4(%rdi,%rax,4)
.L2499:
	movq	%r12, %rcx
	jmp	.L2285
.L2970:
	movq	%rcx, %rbp
.L2364:
	movq	8(%rbx), %r14
	movq	%r14, %r15
	testq	%r14, %r14
	je	.L2528
	movq	%r14, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r14,4), %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	ja	.L2973
.L2373:
	testq	%rdi, %rdi
	je	.L2035
	movl	(%r12,%r14,4), %edx
	movq	%rdi, 32(%rbx)
	testl	%edx, %edx
	je	.L2374
	testq	%r14, %r14
	je	.L2528
	leaq	4(%r12), %rdx
	movq	%rdi, %rax
	subq	%rdx, %rax
	cmpq	$12, %rax
	jbe	.L2529
	cmpq	$1, %r14
	je	.L2529
	leaq	-1(%r14), %rax
	cmpq	$2, %rax
	jbe	.L2530
	movq	%r14, %rdx
	xorl	%eax, %eax
	shrq	$2, %rdx
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L2378:
	movdqu	4(%r12,%rax), %xmm0
	movdqu	(%r12,%rax), %xmm3
	psubd	%xmm3, %xmm0
	movups	%xmm0, (%rdi,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L2378
	movq	%r14, %rdx
	andq	$-4, %rdx
	movq	%rdx, %rax
	cmpq	%rdx, %r14
	je	.L2528
	movq	%r14, %r15
	subq	%rdx, %r15
	cmpq	$1, %r15
	je	.L2381
.L2377:
	addq	$1, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	(%r12,%rdx,4), %xmm0
	movq	%r15, %rdx
	movq	-4(%r12,%rcx), %xmm1
	andq	$-2, %rdx
	addq	%rdx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdi,%rcx)
	cmpq	%r15, %rdx
	je	.L2528
.L2381:
	addq	$1, %rax
	movl	(%r12,%rax,4), %edx
	subl	-4(%r12,%rax,4), %edx
	movl	%edx, -4(%rdi,%rax,4)
.L2528:
	movq	%rbp, %rcx
	jmp	.L2372
.L2972:
	movq	%rcx, %rbp
.L2386:
	movq	8(%rbx), %r14
	movq	%r14, %r15
	testq	%r14, %r14
	je	.L2536
	movq	%r14, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r14,4), %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L2395
	testb	$15, %al
	jne	.L2057
.L2395:
	testq	%rdi, %rdi
	je	.L2035
	movl	(%r12,%r14,4), %eax
	movq	%rdi, 32(%rbx)
	testl	%eax, %eax
	je	.L2396
	testq	%r14, %r14
	je	.L2536
	leaq	4(%r12), %rdx
	movq	%rdi, %rax
	subq	%rdx, %rax
	cmpq	$12, %rax
	jbe	.L2537
	cmpq	$1, %r14
	je	.L2537
	leaq	-1(%r14), %rax
	cmpq	$2, %rax
	jbe	.L2538
	movq	%r14, %rdx
	xorl	%eax, %eax
	shrq	$2, %rdx
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L2400:
	movdqu	4(%r12,%rax), %xmm0
	movdqu	(%r12,%rax), %xmm2
	psubd	%xmm2, %xmm0
	movups	%xmm0, (%rdi,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L2400
	movq	%r14, %rdx
	andq	$-4, %rdx
	movq	%rdx, %rax
	cmpq	%r14, %rdx
	je	.L2536
	movq	%r14, %r15
	subq	%rdx, %r15
	cmpq	$1, %r15
	je	.L2403
.L2399:
	addq	$1, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	(%r12,%rdx,4), %xmm0
	movq	%r15, %rdx
	movq	-4(%r12,%rcx), %xmm1
	andq	$-2, %rdx
	addq	%rdx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdi,%rcx)
	cmpq	%r15, %rdx
	je	.L2536
.L2403:
	addq	$1, %rax
	movl	(%r12,%rax,4), %edx
	subl	-4(%r12,%rax,4), %edx
	movl	%edx, -4(%rdi,%rax,4)
.L2536:
	movq	%rbp, %rcx
	jmp	.L2394
.L2966:
	movq	%rcx, %r12
.L2318:
	movq	8(%rbx), %r14
	movq	%r14, %r15
	testq	%r14, %r14
	je	.L2327
	movq	%r14, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r14,4), %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L2328
	testb	$15, %al
	jne	.L2057
.L2328:
	testq	%rdi, %rdi
	je	.L2035
	movl	0(%rbp,%r14,4), %esi
	movq	%rdi, 32(%rbx)
	testl	%esi, %esi
	je	.L2329
	testq	%r14, %r14
	je	.L2513
	leaq	4(%rbp), %rdx
	movq	%rdi, %rax
	subq	%rdx, %rax
	cmpq	$12, %rax
	jbe	.L2514
	cmpq	$1, %r14
	je	.L2514
	leaq	-1(%r14), %rax
	cmpq	$2, %rax
	jbe	.L2515
	movq	%r14, %rdx
	xorl	%eax, %eax
	shrq	$2, %rdx
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L2334:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm7
	psubd	%xmm7, %xmm0
	movups	%xmm0, (%rdi,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L2334
	movq	%r14, %rdx
	andq	$-4, %rdx
	movq	%rdx, %rax
	cmpq	%r14, %rdx
	je	.L2513
	movq	%r14, %r15
	subq	%rdx, %r15
	cmpq	$1, %r15
	je	.L2337
.L2333:
	addq	$1, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	0(%rbp,%rdx,4), %xmm0
	movq	%r15, %rdx
	movq	-4(%rbp,%rcx), %xmm1
	andq	$-2, %rdx
	addq	%rdx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdi,%rcx)
	cmpq	%r15, %rdx
	je	.L2513
.L2337:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %edx
	subl	-4(%rbp,%rax,4), %edx
	movl	%edx, -4(%rdi,%rax,4)
.L2513:
	movq	%r12, %rcx
	jmp	.L2331
.L2968:
	movq	%rcx, %r12
.L2341:
	movq	8(%rbx), %r14
	movq	%r14, %r15
	testq	%r14, %r14
	je	.L2349
	movq	%r14, %rax
	shrq	$62, %rax
	jne	.L2035
	leaq	0(,%r14,4), %r13
	movq	%r13, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r13
	jbe	.L2350
	testb	$15, %al
	jne	.L2057
.L2350:
	testq	%rdi, %rdi
	je	.L2035
	movl	0(%rbp,%r14,4), %ecx
	movq	%rdi, 32(%rbx)
	testl	%ecx, %ecx
	je	.L2351
	testq	%r14, %r14
	je	.L2520
	leaq	4(%rbp), %rdx
	movq	%rdi, %rax
	subq	%rdx, %rax
	cmpq	$12, %rax
	jbe	.L2521
	cmpq	$1, %r14
	je	.L2521
	leaq	-1(%r14), %rax
	cmpq	$2, %rax
	jbe	.L2522
	movq	%r14, %rdx
	xorl	%eax, %eax
	shrq	$2, %rdx
	salq	$4, %rdx
	.p2align 4,,10
	.p2align 3
.L2356:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm4
	psubd	%xmm4, %xmm0
	movups	%xmm0, (%rdi,%rax)
	addq	$16, %rax
	cmpq	%rdx, %rax
	jne	.L2356
	movq	%r14, %rdx
	andq	$-4, %rdx
	movq	%rdx, %rax
	cmpq	%rdx, %r14
	je	.L2520
	movq	%r14, %r15
	subq	%rdx, %r15
	cmpq	$1, %r15
	je	.L2359
.L2355:
	addq	$1, %rdx
	leaq	0(,%rdx,4), %rcx
	movq	0(%rbp,%rdx,4), %xmm0
	movq	%r15, %rdx
	movq	-4(%rbp,%rcx), %xmm1
	andq	$-2, %rdx
	addq	%rdx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdi,%rcx)
	cmpq	%r15, %rdx
	je	.L2520
.L2359:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %edx
	subl	-4(%rbp,%rax,4), %edx
	movl	%edx, -4(%rdi,%rax,4)
.L2520:
	movq	%r12, %rcx
	jmp	.L2353
	.p2align 4,,10
	.p2align 3
.L2449:
	movq	%rcx, %r12
	jmp	.L2088
	.p2align 4,,10
	.p2align 3
.L2034:
	testq	%rdx, %rdx
	je	.L2035
	movl	0(%rbp,%r13,4), %ecx
	movq	%rdx, 32(%rbx)
	testl	%ecx, %ecx
	je	.L2032
	testq	%r13, %r13
	je	.L2032
	leaq	4(%rbp), %rcx
	movq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	$12, %rax
	jbe	.L2437
	cmpq	$1, %r13
	je	.L2437
	leaq	-1(%r13), %rax
	cmpq	$2, %rax
	jbe	.L2438
	movq	%r13, %rcx
	xorl	%eax, %eax
	shrq	$2, %rcx
	salq	$4, %rcx
	.p2align 4,,10
	.p2align 3
.L2038:
	movdqu	4(%rbp,%rax), %xmm0
	movdqu	0(%rbp,%rax), %xmm2
	psubd	%xmm2, %xmm0
	movups	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	%rax, %rcx
	jne	.L2038
	movq	%r13, %rcx
	andq	$-4, %rcx
	movq	%rcx, %rax
	cmpq	%rcx, %r13
	je	.L2032
	movq	%r13, %r15
	subq	%rcx, %r15
	cmpq	$1, %r15
	je	.L2041
.L2037:
	addq	$1, %rcx
	leaq	0(,%rcx,4), %rsi
	movq	0(%rbp,%rcx,4), %xmm0
	movq	%r15, %rcx
	movq	-4(%rbp,%rsi), %xmm1
	andq	$-2, %rcx
	addq	%rcx, %rax
	psubd	%xmm1, %xmm0
	movq	%xmm0, -4(%rdx,%rsi)
	cmpq	%rcx, %r15
	je	.L2032
.L2041:
	addq	$1, %rax
	movl	0(%rbp,%rax,4), %ecx
	subl	-4(%rbp,%rax,4), %ecx
	movl	%ecx, -4(%rdx,%rax,4)
	jmp	.L2032
	.p2align 4,,10
	.p2align 3
.L2460:
	movq	%rcx, %r12
	jmp	.L2129
.L2973:
	testb	$15, %al
	jne	.L2057
	jmp	.L2373
	.p2align 4,,10
	.p2align 3
.L2452:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2099:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2099
	jmp	.L2917
.L2456:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2120:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2120
	jmp	.L2118
.L2442:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2059
.L2446:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2080
	.p2align 4,,10
	.p2align 3
.L2483:
	movq	%rcx, %r12
	jmp	.L2230
.L2490:
	movq	%rcx, %r12
	jmp	.L2251
.L2962:
	movq	%rcx, %r12
	jmp	.L2272
.L2952:
	cmpq	%r13, %r12
	jg	.L2035
	movq	%r13, %rax
	movq	40(%rbx), %rdi
	movq	%rdx, %r14
	movq	%r13, %rbp
	shrq	$62, %rax
	je	.L2433
	jmp	.L2035
	.p2align 4,,10
	.p2align 3
.L2964:
	movq	%rcx, %r12
	jmp	.L2295
.L2953:
	testq	%rbp, %rbp
	je	.L2416
	movq	%rbp, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %rbp
	jbe	.L2417
	testb	$15, %al
	jne	.L2057
.L2417:
	testq	%rdi, %rdi
	je	.L2974
.L2416:
	movq	%rdi, 40(%rbx)
	movq	48(%rbx), %rdi
	jmp	.L2434
.L2096:
	movq	$0, 32(%rbx)
	jmp	.L2917
.L2137:
	movq	$0, 32(%rbx)
	jmp	.L2918
.L2283:
	testq	%r14, %r14
	je	.L2499
	testq	%r13, %r13
	je	.L2499
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	memset@PLT
	movq	%r12, %rcx
	jmp	.L2285
.L2306:
	testq	%r14, %r14
	je	.L2506
	testq	%r13, %r13
	je	.L2506
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	memset@PLT
	movq	%r12, %rcx
	jmp	.L2308
.L2329:
	testq	%r14, %r14
	je	.L2513
	testq	%r13, %r13
	je	.L2513
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	memset@PLT
	movq	%r12, %rcx
	jmp	.L2331
.L2351:
	testq	%r14, %r14
	je	.L2520
	testq	%r13, %r13
	je	.L2520
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	memset@PLT
	movq	%r12, %rcx
	jmp	.L2353
.L2374:
	testq	%r14, %r14
	je	.L2528
	testq	%r13, %r13
	je	.L2528
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	memset@PLT
	movq	%rbp, %rcx
	jmp	.L2372
.L2239:
	movq	$0, 32(%rbx)
	jmp	.L2919
.L2955:
	testq	%rbp, %rbp
	je	.L2421
	movq	%rbp, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %rbp
	jbe	.L2921
	testb	$15, %al
	jne	.L2057
	jmp	.L2921
	.p2align 4,,10
	.p2align 3
.L2396:
	testq	%r14, %r14
	je	.L2536
	testq	%r13, %r13
	je	.L2536
	movq	%r13, %rdx
	xorl	%esi, %esi
	call	memset@PLT
	movq	%rbp, %rcx
	jmp	.L2394
.L2260:
	movq	$0, 32(%rbx)
	jmp	.L2920
.L2281:
	movq	$0, 32(%rbx)
	movq	%r12, %rcx
	jmp	.L2285
.L2304:
	movq	$0, 32(%rbx)
	movq	%r12, %rcx
	jmp	.L2308
.L2327:
	movq	$0, 32(%rbx)
	movq	%r12, %rcx
	jmp	.L2331
.L2437:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2036:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2036
	jmp	.L2032
.L2349:
	movq	$0, 32(%rbx)
	movq	%r12, %rcx
	jmp	.L2353
.L2441:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2058:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2058
	jmp	.L2055
.L2954:
	call	free@PLT
	movq	64(%rbx), %r14
	xorl	%eax, %eax
	jmp	.L2419
.L2445:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2079:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2079
	jmp	.L2077
.L2956:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L2421
.L2957:
	testq	%r12, %r12
	je	.L2426
	movq	%r12, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r12
	jbe	.L2427
	testb	$15, %al
	jne	.L2057
.L2427:
	testq	%rdi, %rdi
	jne	.L2426
	jmp	.L2035
	.p2align 4,,10
	.p2align 3
.L2959:
	testq	%r12, %r12
	je	.L2430
	movq	%r12, %rdi
	call	malloc@PLT
	movq	%rax, %rdi
	cmpq	$15, %r12
	jbe	.L2922
	testb	$15, %al
	jne	.L2057
	jmp	.L2922
	.p2align 4,,10
	.p2align 3
.L2463:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2140:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2140
	jmp	.L2918
.L2467:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2160:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2160
	jmp	.L2158
.L2471:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2180:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2180
	jmp	.L2178
.L2475:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2200:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2200
	jmp	.L2198
.L2479:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2221:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%r13, %rax
	jne	.L2221
	jmp	.L2219
.L2958:
	call	free@PLT
	movq	64(%rbx), %rbp
	xorl	%edi, %edi
	jmp	.L2426
.L2960:
	call	free@PLT
	xorl	%edi, %edi
	jmp	.L2430
.L2486:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2242:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%r13, %rax
	jne	.L2242
	jmp	.L2919
.L2493:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2263:
	movl	4(%rbp,%rax,4), %ecx
	subl	0(%rbp,%rax,4), %ecx
	movl	%ecx, (%rdx,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r13
	jne	.L2263
	jmp	.L2920
.L2500:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2286:
	movl	4(%rbp,%rax,4), %edx
	subl	0(%rbp,%rax,4), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	cmpq	%r14, %rax
	jne	.L2286
	jmp	.L2499
.L2507:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2309:
	movl	4(%rbp,%rax,4), %edx
	subl	0(%rbp,%rax,4), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	cmpq	%r14, %rax
	jne	.L2309
	jmp	.L2506
.L2438:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2037
.L2514:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2332:
	movl	4(%rbp,%rax,4), %edx
	subl	0(%rbp,%rax,4), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	cmpq	%r14, %rax
	jne	.L2332
	jmp	.L2513
.L2521:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L2354:
	movl	4(%rbp,%rax,4), %edx
	subl	0(%rbp,%rax,4), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r14
	jne	.L2354
	jmp	.L2520
.L2453:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2100
.L2529:
	xorl	%eax, %eax
.L2376:
	movl	4(%r12,%rax,4), %edx
	subl	(%r12,%rax,4), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	cmpq	%rax, %r14
	jne	.L2376
	jmp	.L2528
.L2457:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2121
.L2537:
	xorl	%eax, %eax
.L2398:
	movl	4(%r12,%rax,4), %edx
	subl	(%r12,%rax,4), %edx
	movl	%edx, (%rdi,%rax,4)
	addq	$1, %rax
	cmpq	%r14, %rax
	jne	.L2398
	jmp	.L2536
.L2464:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2141
.L2468:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2161
.L2472:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2181
.L2476:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2201
.L2487:
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	jmp	.L2243
.L2480:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.L2222
.L2501:
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L2287
.L2494:
	xorl	%eax, %eax
	xorl	%ecx, %ecx
	jmp	.L2264
.L2054:
	leaq	.LC78(%rip), %rcx
	movl	$581, %edx
	leaq	.LC31(%rip), %rsi
	leaq	.LC79(%rip), %rdi
	call	__assert_fail@PLT
.L2508:
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L2310
.L2522:
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L2355
.L2515:
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L2333
.L2530:
	xorl	%eax, %eax
	xorl	%edx, %edx
	jmp	.L2377
.L2538:
	xorl	%edx, %edx
	xorl	%eax, %eax
	jmp	.L2399
.L2466:
	movq	%rdi, %r12
	jmp	.L2156
.L2470:
	movq	%r8, %r12
	jmp	.L2176
.L2448:
	movq	%r12, %rcx
	jmp	.L2094
.L2444:
	movq	%r9, %r12
	jmp	.L2074
.L2436:
	movq	%rdi, %r12
	jmp	.L2030
.L2459:
	movq	%r12, %rcx
	jmp	.L2135
.L2440:
	movq	%r8, %r12
	jmp	.L2052
.L2532:
	movq	%rbp, %rcx
	jmp	.L2392
.L2524:
	movq	%rbp, %rcx
	jmp	.L2370
.L2517:
	movq	%r12, %rcx
	jmp	.L2347
.L2510:
	movq	%r12, %rcx
	jmp	.L2324
.L2503:
	movq	%r12, %rcx
	jmp	.L2301
.L2496:
	movq	%r12, %rcx
	jmp	.L2278
.L2489:
	movq	%r12, %rcx
	jmp	.L2257
.L2482:
	movq	%r12, %rcx
	jmp	.L2236
.L2478:
	movq	%r9, %r12
	jmp	.L2216
.L2474:
	movq	%r8, %r12
	jmp	.L2196
.L2455:
	movq	%r9, %r12
	jmp	.L2115
.L2974:
	jmp	.L2035
	.cfi_endproc
	.section	.text.unlikely
	.cfi_startproc
	.type	_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE.cold, @function
_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE.cold:
.LFSB11290:
.L2035:
	.cfi_def_cfa_offset 96
	.cfi_offset 3, -56
	.cfi_offset 6, -48
	.cfi_offset 12, -40
	.cfi_offset 13, -32
	.cfi_offset 14, -24
	.cfi_offset 15, -16
	call	_ZN5Eigen8internal19throw_std_bad_allocEv
	.cfi_endproc
.LFE11290:
	.text
	.size	_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE, .-_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE
	.section	.text.unlikely
	.size	_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE.cold, .-_Z6getMatRN5Eigen12SparseMatrixIiLi0EiEE.cold
.LCOLDE80:
	.text
.LHOTE80:
	.section	.text.startup
	.p2align 4
	.type	_GLOBAL__sub_I__ZNK8IVSparse16SparseMatrixBase4rowsEv, @function
_GLOBAL__sub_I__ZNK8IVSparse16SparseMatrixBase4rowsEv:
.LFB13432:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	leaq	_ZStL8__ioinit(%rip), %rbp
	movq	%rbp, %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	movq	%rbp, %rsi
	popq	%rbp
	.cfi_def_cfa_offset 8
	leaq	__dso_handle(%rip), %rdx
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE13432:
	.size	_GLOBAL__sub_I__ZNK8IVSparse16SparseMatrixBase4rowsEv, .-_GLOBAL__sub_I__ZNK8IVSparse16SparseMatrixBase4rowsEv
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__ZNK8IVSparse16SparseMatrixBase4rowsEv
	.weak	_ZTSN8IVSparse16SparseMatrixBaseE
	.section	.rodata._ZTSN8IVSparse16SparseMatrixBaseE,"aG",@progbits,_ZTSN8IVSparse16SparseMatrixBaseE,comdat
	.align 16
	.type	_ZTSN8IVSparse16SparseMatrixBaseE, @object
	.size	_ZTSN8IVSparse16SparseMatrixBaseE, 30
_ZTSN8IVSparse16SparseMatrixBaseE:
	.string	"N8IVSparse16SparseMatrixBaseE"
	.weak	_ZTIN8IVSparse16SparseMatrixBaseE
	.section	.data.rel.ro._ZTIN8IVSparse16SparseMatrixBaseE,"awG",@progbits,_ZTIN8IVSparse16SparseMatrixBaseE,comdat
	.align 8
	.type	_ZTIN8IVSparse16SparseMatrixBaseE, @object
	.size	_ZTIN8IVSparse16SparseMatrixBaseE, 16
_ZTIN8IVSparse16SparseMatrixBaseE:
	.quad	_ZTVN10__cxxabiv117__class_type_infoE+16
	.quad	_ZTSN8IVSparse16SparseMatrixBaseE
	.weak	_ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE
	.section	.rodata._ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE,"aG",@progbits,_ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE,comdat
	.align 32
	.type	_ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE, @object
	.size	_ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE, 38
_ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE:
	.string	"N8IVSparse12SparseMatrixIiiLh2ELb1EEE"
	.weak	_ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE
	.section	.data.rel.ro._ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE,"awG",@progbits,_ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE,comdat
	.align 8
	.type	_ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE, @object
	.size	_ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE, 24
_ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE:
	.quad	_ZTVN10__cxxabiv120__si_class_type_infoE+16
	.quad	_ZTSN8IVSparse12SparseMatrixIiiLh2ELb1EEE
	.quad	_ZTIN8IVSparse16SparseMatrixBaseE
	.weak	_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE
	.section	.data.rel.ro.local._ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE,"awG",@progbits,_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE,comdat
	.align 8
	.type	_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE, @object
	.size	_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE, 64
_ZTVN8IVSparse12SparseMatrixIiiLh2ELb1EEE:
	.quad	0
	.quad	_ZTIN8IVSparse12SparseMatrixIiiLh2ELb1EEE
	.quad	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE15encodeValueTypeEv
	.quad	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE14checkValueTypeEv
	.quad	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE10userChecksEv
	.quad	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE17calculateCompSizeEv
	.quad	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5writeEPKc
	.quad	_ZN8IVSparse12SparseMatrixIiiLh2ELb1EE5printEv
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	8
	.long	8
	.long	8
	.long	8
	.align 16
.LC1:
	.long	4
	.long	4
	.long	4
	.long	4
	.section	.data.rel.ro,"aw"
	.align 8
.LC17:
	.quad	_ZTVNSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEEE+16
	.align 8
.LC18:
	.quad	_ZTVSt15basic_streambufIcSt11char_traitsIcEE+16
	.section	.rodata.cst16
	.align 16
.LC40:
	.quad	100
	.quad	100
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC41:
	.long	0
	.long	0
	.align 8
.LC55:
	.long	-1
	.long	0
	.section	.rodata.cst16
	.align 16
.LC69:
	.long	0
	.long	1
	.long	2
	.long	3
	.align 16
.LC72:
	.long	1
	.long	1
	.long	1
	.long	1
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
