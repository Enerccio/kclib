[BITS 64]

[GLOBAL __kclib_open_file_u]
__kclib_open_file_u:
	xor rax, rax
	ret

[GLOBAL __kclib_fstat_u]
__kclib_fstat_u:
	xor rax, rax
	ret

[GLOBAL __kclib_terminate]
__kclib_terminate:
	mov rax, 60
	syscall
.hang:
	jmp .hang

[GLOBAL __kclib_allocate]
__kclib_allocate:
	push rcx
	push r11
	mov rax, 9
	mov rsi, rdi
	mov rdi, 0
	mov rdx, 0x2|0x1
	mov r10, 0x20|0x02
	mov r8, -1
	mov r9, 0
	syscall
	pop rcx
	pop r11
	cmp rax, 0
	jl .error
	ret
.error:
	mov rax, 0
	ret

[GLOBAL __kclib_deallocate]
__kclib_deallocate:
	push rcx
	push r11
	mov rax, 11
	syscall
	pop rcx
	pop r11
	ret

[GLOBAL __kclib_open_std_stream]
__kclib_open_std_stream:
	mov rax, rsi
	ret

[GLOBAL __kclib_send_data]
__kclib_send_data:
	push rcx
	push r11
	mov rax, 1
	syscall
	pop rcx
	pop r11
	ret

[GLOBAL __kclib_read_data]
__kclib_read_data:
	push rcx
	push r11
	mov rax, 0
	syscall
	pop rcx
	pop r11
	ret

[GLOBAL __kclib_clock]
__kclib_clock:
	xor rax, rax
	ret

[GLOBAL __kclib_get_tid]
__kclib_get_tid:
	xor rax, rax
	ret

[GLOBAL __kclib_halt]
__kclib_halt:
	xor rax, rax
	ret

[GLOBAL __kclib_get_mutex_global_identifier]
__kclib_get_mutex_global_identifier:
	xor rax, rax
	ret

[GLOBAL __kclib_mutex_unlocked]
__kclib_mutex_unlocked:
	xor rax, rax
	ret
