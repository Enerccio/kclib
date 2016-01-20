/*
 * testbase.c
 *
 *  Created on: Jan 20, 2016
 *      Author: enerccio
 */


#include "testbase.h"

extern int run_tests();
int testmain(int argc, char** argv) {
	return run_tests();
}
