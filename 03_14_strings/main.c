#include "exercise.h"
#include <stdio.h>
#include <string.h>


int main() {
	char str1[100] = "";
	char *str2 = "Hello";
	printf("%s\n", str1);
	printf("%s\n", str2);
	concat_strings(str1, str2);
	printf("%s\n", str1);
	return 0;
}

