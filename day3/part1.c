#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(int argc, char *argv[]) {
	FILE *input = fopen(argv[1], "r"); 

	if (input == NULL) {
	  printf("Could not open %s\n", argv[1]);
		return 1;
	}

	int ch;
	int seq = 0;

	int numL = 0;
	int numR = 0;
	int n = 0;

	int totalSum = 0;

	while((ch = fgetc(input)) != EOF) {
		n = ch - 48;
		if ((ch == 'm' && seq == 0) ||
		    (ch == 'u' && seq == 1) ||
		    (ch == 'l' && seq == 2) ||
		    (ch == '(' && seq == 3) ||
		    (ch == ',' && seq == 4)) {
			seq++;
		} else if (seq == 4 && n < 10 && n >= 0) {
			numL = numL * 10 + n;
		} else if (seq >= 5 && n < 10 && n >= 0) {
			numR = numR * 10 + n;
		} else if (seq >= 5 && ch == ')') {
			//printf("Val: %d, a: %d, b: %d\n", numL * numR, numL, numR);
			totalSum += numL * numR;
			seq = 0;
			numL = 0;
			numR = 0;
		} else {
			//Invalid
			seq = 0;
			numL = 0;
			numR = 0;
		}
	}

	printf("Total sum: %d\n", totalSum);

	fclose(input);
	
	return 0;
}
