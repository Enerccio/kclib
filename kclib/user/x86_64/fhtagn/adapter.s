[BITS 64]
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

[GLOBAL __kclib_fork_u]
__kclib_fork_u:
	mov rax, 4
	mov rsi, rdi
	xor rdi, rdi
	int 0x80
	mov [rsi], rdi
	ret

[GLOBAL __kclib_allocate]
__kclib_allocate:
	mov rax, 1
	int 0x80
	ret

[GLOBAL __kclib_deallocate]
__kclib_deallocate:
	mov rax, 2
	int 0x80
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

[GLOBAL __kclib_get_tid]
__kclib_get_tid:
	mov rax, 3
	int 0x80
	ret

[GLOBAL __kclib_halt]
__kclib_halt:
	xor rax, rax
	ret

[GLOBAL __kclib_get_mutex_global_identifier]
__kclib_get_mutex_global_identifier:
	; not supported by chtulhuos due to scheduler setup
	xor rax, rax
	ret

[GLOBAL __kclib_mutex_unlocked]
__kclib_mutex_unlocked:
	; not supported by chtulhuos due to scheduler setup
	xor rax, rax
	ret
