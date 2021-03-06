#include <string.h>

size_t strlen(const char *s){
	size_t len = 0;
	while (*(s++) != 0) ++len;
	return len;
}

char* strcpy(char* restrict s1, register const char* restrict s2){
	register char* t = s1;
	while ((*(t++) = *(s2++)) != '\0') ;
	return s1;
}

char* strncpy(char* restrict s1, register const char* restrict s2, size_t n){
	register char* t = s1;
	size_t l = 0;
	while ((*(t++) = *(s2++)) != '\0' && l<n) ++l;
	return s1;
}
