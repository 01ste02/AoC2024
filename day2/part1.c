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

	int numSafe = 0;
	int safe = 1;
	int lastDigit = -1;
	int diff = 0;
	
	int n;
	int dir = 0;
	while((ch = fgetc(input)) != EOF) {
		if (ch == '\n') {
			if (safe && dir != 0)
				numSafe++;
			safe = 1;
			lastDigit = -1;
			dir = 0;
			printf("\n");
		} else if (ch != ' ' && safe) {
			n = ch - 48;
			diff = n - lastDigit;
			
			if (lastDigit != -1) {
				if (dir == 0) {
					dir = (lastDigit < n) ? 1 : -1;
				}

				printf("Dir: %d, n: %d, last: %d, diff: %d, safe: ", dir, n, lastDigit, diff);
			
				if (diff > 3 || diff < -3 ||
				    (diff > -1 && diff < 1) ||
				    (dir < 0 && diff > 0) ||
				    (dir > 0 && diff < 0)) {
					safe = 0;
				}

				printf("%d\n", safe);
			}

			lastDigit = n;
		}
	}

	printf("Number of safe rows: %d\n", numSafe);

	fclose(input);
	
	return 0;
}
