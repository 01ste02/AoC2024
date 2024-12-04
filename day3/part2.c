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
	int enabledSum = 0;

	int enabled = 1;
	int mul = 0;

	while((ch = fgetc(input)) != EOF) {
		n = ch - 48;
		//printf("%c\n", ch);
		if (ch == 'm' && seq == 0) {
			mul = 1;
			seq++;
		} else if (ch == 'd' && seq == 0) {
			mul = 0;
			seq++;
		} else if (!mul && ((ch == 'o' && seq == 1) ||
				    (ch == '(' && (seq == 2 || seq == 5)) ||
				    (ch == 'n' && seq == 2) ||
				    (ch == '\'' && seq == 3) ||
				    (ch == 't' && seq == 4))) {
			seq++;
			//printf("c: %c, not mul\n", ch);
		} else if (!mul && ch == ')' && seq == 3) {
			enabled = 1;
			numL = 0;
			numR = 0;
			seq = 0;
			//printf("Enabled\n");
		} else if (!mul && ch == ')' && seq == 6) {
			enabled = 0;
			numL = 0;
			numR = 0;
			seq = 0;
			//printf("Disabled\n");
		} else if (mul && ((ch == 'u' && seq == 1) ||
				   (ch == 'l' && seq == 2) ||
				   (ch == '(' && seq == 3) ||
				   (ch == ',' && seq == 4))) {
			seq++;
		} else if (mul && seq == 4 && n < 10 && n >= 0) {
			numL = numL * 10 + n;
		} else if (mul && seq >= 5 && n < 10 && n >= 0) {
			numR = numR * 10 + n;
		} else if (mul && seq >= 5 && ch == ')') {
			//printf("Val: %d, a: %d, b: %d\n", enabled * numL * numR, numL, numR);
			totalSum += numL * numR;
			enabledSum += enabled * numL * numR;
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
	printf("Enabled sum: %d\n", enabledSum);

	fclose(input);
	
	return 0;
}
