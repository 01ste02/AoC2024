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
	list *before = lNew();
	list *after = lNew();

	int printing = 0;
	int last = ' ';

	int num = 0;
	int bf = 0;

	int midSum = 0;
	list *pages = lNew();
	while(1) {
		ch = fgetc(input);
		if (last == '\n' && ch == '\n') {
			// Second section
			printing = 1;
			num = 0;
		} else if (printing == 0 && ch == '|') {
			bf = 1;
			lAdd(before, num);
			num = 0;
		} else if (printing == 0 && ch == '\n') {
			bf = 0;
			lAdd(after, num);
			num = 0;
		}  else if (ch == ',') {
		        lAdd(pages, num);
			num = 0;
		} else if (printing == 1 && (ch == '\n' || ch == EOF)) {
			lAdd(pages, num);
			//for (int i = 0; i < lLength(pages); i++) {
			//	printf("%d,", lGet(pages, i));
			//}
			//printf("\n");
			// Check correctness
			int correct = 1;
			for (int i = 0; i < lLength(pages); i++) {
				int b = lGet(pages, i);
				for (int j = i + 1; j < lLength(pages); j++) {
					int a = lGet(pages, j);
					//printf("Before: %d, After: %d\n", b, a);
					for (int k = 0; k < lLength(before); k++) {
						if (lGet(before, k) == a && lGet(after, k) == b) {
							//printf("WRONG\n");
							correct = 0;
							break;
						}
					}
				}
				if (!correct)
					break;
			}
			if (correct)
				midSum += lGet(pages, lLength(pages) / 2);
			lFree(pages);

			if (ch == EOF)
				break;
			pages = lNew();
			num = 0;
		} else {
			num = num*10 + (ch - 48);
		}
		last = ch;
	}

	fclose(input);

	printf("The sum of middle elements were: %d\n", midSum);
	
	lFree(before);
	lFree(after);
	
	return 0;
}
