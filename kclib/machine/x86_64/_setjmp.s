[BITS 64]

[GLOBAL __set_jump]
; extern int __set_jump(void* stack)
__set_jump:
	mov rax, 0
	mov rsi, [rsp]
	mov [rdi+(8*7)], rsi
	add rsp, 8
	mov [rdi+(8*0)], rbx
	mov [rdi+(8*1)], rbp
	mov [rdi+(8*2)], rsp
	mov [rdi+(8*3)], r12
	mov [rdi+(8*4)], r13
	mov [rdi+(8*5)], r14
	mov [rdi+(8*6)], r15
	sub rsp, 8
	ret

[GLOBAL __long_jump]
; extern _Noreturn int __long_jump(void* stack, int v);
__long_jump:
	mov rax, rsi
	mov rbx, [rdi+(8*0)]
	mov rbp, [rdi+(8*1)]
	mov rsp, [rdi+(8*2)]
	mov r12, [rdi+(8*3)]
	mov r13, [rdi+(8*4)]
	mov r14, [rdi+(8*5)]
	mov r15, [rdi+(8*6)]
	mov rdx, [rdi+(8*7)]
	push rdx
	ret
