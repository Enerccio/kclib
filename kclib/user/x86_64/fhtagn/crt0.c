#include "../../../intinc/locale.h"
#include "../../../intinc/stdio.h"
#include "../../../intinc/stdlib.h"
#include "../../../intinc/string.h"
#include "../../../intinc/shmath.h"

#include <stdlib.h>
#include <sys/external.h>

extern int main(int argc, char** argv);
extern void _init();

char** envp;

void _start(int argc, char** argv, char** e) {
	envp = e;

	__initialize_malloc();
	__initialize_locale();
	__initialize_streams();

	_init();

	exit(main(argc, argv));
}
