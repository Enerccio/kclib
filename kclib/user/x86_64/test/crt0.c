#include <stdlib.h>
#include <sys/external.h>

extern int testmain(int argc, char** argv);
extern void _init();
extern void _fini();

char** envp;

void _start(int argc, char** argv, char** e) {
	envp = e;

	_init();

	int err = testmain(argc, argv);

	_fini();

	__asm__ __volatile__ (
			"   syscall"
			:
			: "a"(60), "D"((long)err)
			: "cc", "rcx", "r11", "memory"
	);
}
