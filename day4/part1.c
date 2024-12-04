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

	matrix_t *m = mNew();

	list *r = lNew();
	int rowLen = -1;
	int rowLenSet = 0;
	while((ch = fgetc(input)) != EOF) {
		if (ch != '\n') {
			//if (!rowLenSet)
			//	rowLen++;
			lAdd(r, ch);
		} else {
			//rowLenSet = 1;
			mAddR(m, r);
			r = lNew();
		}
	}

	fclose(input);

	for (int i = 0; i < mRows(m); i++) {
		list *l = mGetR(m, i);
		for (int j = 0; j < lLength(l); j++) {
			printf("%c", lGet(l, j));
		}

		printf("\n");
	}

	mFree(m);
	lFree(r);
	
	return 0;
}
