[BITS 64]

[GLOBAL __kclib_allocate]
__kclib_allocate:
	mov rax, 1
	push rbx
	syscall
	pop rbx
	ret

[GLOBAL __kclib_deallocate]
__kclib_deallocate:
	mov rax, 2
	push rbx
	syscall
	pop rbx
	ret

[GLOBAL __kclib_get_tid]
__kclib_get_tid:
	mov rax, [gs:0]
	mov rax, [rax+8] ; tid in tls_t
	ret

[GLOBAL __kclib_get_pid_u]
__kclib_get_pid_u:
	mov rax, 5
	push rbx
	syscall
	pop rbx
	ret

[GLOBAL __kclib_futex_wait]
__kclib_futex_wait:
	mov rax, 8
	push rbx
	syscall
	pop rbx
	ret

[GLOBAL __kclib_futex_wake]
__kclib_futex_wake:
	mov rax, 9
	push rbx
	syscall
	pop rbx
	ret

; TODO: implement

[GLOBAL __kclib_open_file_u]
__kclib_open_file_u:
	xor rax, rax
	ret

[GLOBAL __kclib_fstat_u]
__kclib_fstat_u:
	xor rax, rax
	ret

[GLOBAL __kclib_terminate_u]
__kclib_terminate_u:
	xor rax, rax
	ret

[GLOBAL __kclib_open_std_stream]
__kclib_open_std_stream:
	xor rax, rax
	ret

[GLOBAL __kclib_send_data]
__kclib_send_data:
	xor rax, rax
	ret

[GLOBAL __kclib_read_data]
__kclib_read_data:
	xor rax, rax
	ret

[GLOBAL __kclib_clock]
__kclib_clock:
	xor rax, rax
	ret
