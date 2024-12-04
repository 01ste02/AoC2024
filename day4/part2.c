#include <stdio.h>
#include <stdlib.h>
#include "listnew.h"
#include "matrix.h"

int findDir(matrix_t *m, int i, int j, int di, int dj) {
	int wanted[] = {'X', 'M', 'A', 'S'};
	int index = 1;
	int last = wanted[0];

	int c;

	int iv;
	int jv;
	
	for (int ii = 1; ii <= 3; ii++) {
		iv = i + di*ii;
		jv = j + dj*ii;

		c = mGet(m, iv, jv);
		//printf("c: %c, last: %c, i: %d, j: %d, w: %c\n", c, last, iv, jv, wanted[index]);
		if (last == wanted[index-1] && c != wanted[index]) {
			//We found other char
			//printf("Other\n\n");
			return 0;
		}
		last = c;
		index++;
		
	}
	//printf("Found\n\n");
	return 1;
}

int findXMAS(matrix_t *m, int i, int j) {
	int found = 0;
	found += findDir(m, i, j, 1, 1); // Diag down right
	found += findDir(m, i, j, 1, -1); // Diag down left
	found += findDir(m, i, j, 1, 0); // Down
	found += findDir(m, i, j, -1, 1); // Diag up right
	found += findDir(m, i, j, -1, -1); // Diag up left
	found += findDir(m, i, j, -1, 0); // Up
	found += findDir(m, i, j, 0, 1); // Right
	found += findDir(m, i, j, 0, -1); // Left

	return found;
}

int findX_MAS(matrix_t *m, int i, int j) {
	int uL = mGet(m, i - 1, j - 1);
	int dL = mGet(m, i + 1, j - 1);
	int uR = mGet(m, i - 1, j + 1);
	int dR = mGet(m, i + 1, j + 1);

	if (((uL == 'M' && dR == 'S') || (uL == 'S' && dR == 'M')) &&
	    ((dL == 'M' && uR == 'S') || (dL == 'S' && uR == 'M'))) {
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	FILE *input = fopen(argv[1], "r"); 

	if (input == NULL) {
	  printf("Could not open %s\n", argv[1]);
		return 1;
	}

	int ch;

	matrix_t *m = mNew();

	list *r = lNew();
	while((ch = fgetc(input)) != EOF) {
		if (ch != '\n') {
			lAdd(r, ch);
		} else {
			//rowLenSet = 1;
			mAddR(m, r);
			r = lNew();
		}
	}

	fclose(input);

	/*for (int i = 0; i < mRows(m); i++) {
		list *l = mGetR(m, i);
		for (int j = 0; j < lLength(l); j++) {
			printf("%c", lGet(l, j));
		}

		printf("\n");
		}*/

	int numFound = 0;

	for (int i = 0; i < mRows(m); i++) {
		for (int j = 0; j < mCols(m); j++) {
			int c = mGet(m, i, j);
			if (c == 'X') {
				numFound += findXMAS(m, i, j);
			        
			}
		}
	}

	int numX_MAS = 0;

	for (int i = 0; i < mRows(m); i++) {
		for (int j = 0; j < mCols(m); j++) {
			int c = mGet(m, i, j);
			if (c == 'A') {
				numX_MAS += findX_MAS(m, i, j);
			        
			}
		}
	}

	printf("Found %d XMAS\n", numFound);
	printf("Found %d X-MAS\n", numX_MAS);
	
	mFree(m);
	lFree(r);
	
	return 0;
}
