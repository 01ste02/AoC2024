#include <stdio.h>
#include <stdlib.h>
#include "listnew.h"
#include "matrix.h"

int fixOrder(list *pages, list *before, list *after) {
	list *newPages = lNew();
	int *added = (int *) calloc(lLength(pages), sizeof(int));
	int canAdd = 1;
	for (int i = 0; i < lLength(pages); i++) {
		canAdd = 1;
		//printf("Trying to add: %d\n", lGet(pages, i));
		if (added[i] == 1)
			continue;
		for (int j = i + 1; j < lLength(pages); j++) {
			if (added[j] == 1 || j == i)
				continue;
			//printf("Comparing to: %d\n", lGet(pages, j));
			for (int k = 0; k < lLength(before); k++) {
				if (lGet(before, k) == lGet(pages, j) &&
				    lGet(after, k) == lGet(pages, i)) {
					canAdd = 0;
					//printf("Could not add: %d must go before %d\n", lGet(before, k), lGet(after, k));
					break;
				}
			}
			if (!canAdd)
				break;
		}
		if (canAdd) {
			//printf("Adding %d\n", lGet(pages, i));
			lAdd(newPages, lGet(pages, i));
			added[i] = 1;
			i = -1;
		}
	}
	//for (int i = 0; i < lLength(newPages); i++) {
	//	printf("%d,", lGet(newPages, i));
	//}
	//printf("\n");
	int retVal = lGet(newPages, lLength(newPages) / 2);
	lFree(newPages);
	free(added);
	//printf("\n");

	return retVal;
}
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
	int midSumIncorrect = 0;
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

			int correct = 1;
			for (int i = 0; i < lLength(pages); i++) {
				int b = lGet(pages, i);
				for (int j = i + 1; j < lLength(pages); j++) {
					int a = lGet(pages, j);
					for (int k = 0; k < lLength(before); k++) {
						if (lGet(before, k) == a &&
						    lGet(after, k) == b) {
							correct = 0;
							break;
						}
					}
				}
				if (!correct)
					break;
			}
			if (correct) {
				midSum += lGet(pages, lLength(pages) / 2);
			} else {
				midSumIncorrect += fixOrder(pages, before, after);
			}
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
	printf("The sum of fixed middle elements were: %d\n", midSumIncorrect);
	
	lFree(before);
	lFree(after);
	
	return 0;
}
