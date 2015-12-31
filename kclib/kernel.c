#include <sys/kernel.h>
#include "intinc/locale.h"
#include "intinc/stdio.h"
#include "intinc/stdlib.h"

#ifdef __KCLIB_KERNEL_MODE

void __initialize_kclib(){

	__initialize_malloc();
	__initialize_locale();
	__initialize_streams();

}

#endif
