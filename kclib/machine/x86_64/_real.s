[BITS 64]

;int __fpclassify_f(float x);
[GLOBAL __fpclassify_f]
__fpclassify_f:
	movd edx, xmm0
	mov eax, edx
	mov edi, 0x7FC00000
	xor eax, edi
	jz .nan
	mov eax, edx
	mov edi, 0x7F800000
	xor eax, edi
	jz .inf
	mov eax, edx
	mov edi, 0xFF800000
	xor eax, edi
	jz .inf
	mov eax, edx
	mov edi, 0
	xor eax, edi
	jz .zero
	mov eax, edx
	mov edi, 0x80000000
	xor eax, edi
	jz .zero
	mov eax, edx
	bt eax, 22
	jz .subn
	mov eax, 2
	ret
.nan:
	mov eax, 1
	ret
.inf:
	mov eax, 0
	ret
.zero:
	mov eax, 4
	ret
.subn:
	mov eax, 3
	ret

;int __fpclassify_d(double x);
[GLOBAL __fpclassify_d]
__fpclassify_d:
	movq rdx, xmm0
	mov rax, rdx
	mov rdi, 0x7fffffff
	shl rdi, 32
	mov esi, 0xffffffff
	or rdi, rsi
	xor rax, rdi
	jz .nan
	mov rax, rdx
	mov rdi, 0x7ff00000
	shl rdi, 32
	xor rax, rdi
	jz .inf
	mov rax, rdx
	mov rdi, 0xfff00000
	shl rdi, 32
	xor rax, rdi
	jz .inf
	mov rax, rdx
	xor rax, 0
	jz .zero
	mov rax, rdx
	mov rdi, 0x80000000
	shl rdi, 32
	xor rax, rdi
	jz .zero
	mov rax, rdx
	bt rax, 52
	jz .subn
	mov rax, 2
	ret
.nan:
	mov rax, 1
	ret
.inf:
	mov rax, 0
	ret
.zero:
	mov rax, 4
	ret
.subn:
	mov rax, 3
	ret

; int __signbit_f(float x);
[GLOBAL __signbit_f]
__signbit_f:
	movd eax, xmm0
	shr eax, 31
	ret

; int __signbit_d(double x);
[GLOBAL __signbit_d]
__signbit_d:
	movq rax, xmm0
	shr rax, 63
	ret
