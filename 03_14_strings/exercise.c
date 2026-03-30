#include "exercise.h"
#include <stdio.h>

void concat_strings(char *str1, const char *str2) {
	char terminator = '\0';
	int terminator_position = -1;
	int index = 0;
	while(terminator_position < 0) {
		printf("str1 char %c\n", str1[index]);
		if(str1[index] == terminator) {
			terminator_position = index;
		}
		index++;
	}
	index--;
	printf("terminator_position1: %d\n", terminator_position);
	int index2 = 0;
	int terminator_position2 = -1;
	while(terminator_position2 < 0) {
		str1[index] = *(str2 + index2);
		str1[index +1] = terminator;
		if(str2[index2] == terminator) {
			terminator_position2 = index2;
		}
		 printf("index1: %d\n", index);
		 printf("str2 char %c\n", *(str2 + index2));
		 printf("str1: %s\n", str1);
		index++;
		index2++;
	}
}

void concat_strings_solution(char *str1, const char *str2) {
 char *end = str1;
  while (*end != '\0') {
    end++;
  }

  while (*str2 != '\0') {
    *end = *str2;
    end++;
    str2++;
  }

  *end = '\0';
}
