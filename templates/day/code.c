#include <stdio.h>
#include <stdlib.h>
#include "listnew.h"
#include "matrix.h"

int main(int argc, char *argv[]) {
	FILE *input = fopen(argv[1], "r"); 

	if (input == NULL) {
	  printf("Could not open %s\n", argv[1]);
		return 1;
	}

	int ch;

	while((ch = fgetc(input)) != EOF) {

	}

	fclose(input);
	
	return 0;
}
