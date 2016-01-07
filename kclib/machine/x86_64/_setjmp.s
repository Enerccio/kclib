[BITS 64]

[GLOBAL __set_jump]
; extern int __set_jump(void* stack, void* instruction, void* frame);
__set_jump:
	push rsp
	push rbp
	push rbx
	push r12
	push r13
	push r14
	push r15
	sub rsp, 8 ; bogus data to align stack to 16 bytes
	mov rcx, 0
	call .jmpcall
.jmpcall:
	mov [rdx], rbp
	mov [rdi], rsp
	mov r9, [rsp]
	mov [rsi], r9
	mov rax, rcx
	add rsp, 8
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	pop rbp
	pop rsp
	ret

[GLOBAL __long_jump]
; extern _Noreturn int __long_jump(void* stack, void* instruction, void* frame, int v);
__long_jump:
	mov rsp, [rsi]
	mov rbp, [rdx]
	ret
