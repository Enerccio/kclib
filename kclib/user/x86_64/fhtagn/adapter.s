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
	xor rax, rax
	ret

[GLOBAL __kclib_allocate]
__kclib_allocate:
	mov rax, 1
	int 0x80
	ret

[GLOBAL __kclib_deallocate]
__kclib_deallocate:
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
