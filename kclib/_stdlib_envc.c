#include <stdlib.h>
#include <string.h>

extern char** envp;

char* getenv(const char* name){
	char** envs = envp;
	while (*envs != NULL) {
		char* env = *(envs++);
		if (strcmp(name, env) == 0)
			return *envs;
	}
	return NULL;
}
