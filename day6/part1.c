#include <stdio.h>
#include <stdlib.h>
#include "listnew.h"
#include "matrix.h"

int walk(matrix_t *map, int sI, int sJ) {
	int gi = sI;
	int gj = sJ;

	int dir;
	while (1) {
		if (gi >= mRows(map) || gi < 0 || gj >= mCols(map) || gj < 0) {
			break;
		}

		
		dir = mGet(map, gi, gj);
		if (dir == '^') {
			if (mGet(map, gi - 1, gj) == '#') {
				mSet(map, gi, gj, '>');
				continue;
			}

			mSet(map, gi, gj, 'X');

			gi--;

			mSet(map, gi, gj, dir);
		} else if (dir == '>') {
			if (mGet(map, gi, gj + 1) == '#') {
				mSet(map, gi, gj, 'v');
				continue;
			}

			mSet(map, gi, gj, 'X');

			gj++;
			mSet(map, gi, gj, dir);
		} else if (dir == 'v') {
			if (mGet(map, gi + 1, gj) == '#') {
				mSet(map, gi, gj, '<');
				continue;
			}

			mSet(map, gi, gj, 'X');

			gi++;
			mSet(map, gi, gj, dir);
		} else if (dir == '<') {
			if (mGet(map, gi, gj - 1) == '#') {
				mSet(map, gi, gj, '^');
				continue;
			}

			mSet(map, gi, gj, 'X');

			gj--;
			mSet(map, gi, gj, dir);
		} else {
			printf("Something is wrong: %c\n", dir);
		}
	}

	int numVisited = 0;
	for (int i = 0; i < mRows(map); i++) {
		numVisited += lCount('X', mGetR(map, i));
		for (int j = 0; j < mCols(map); j++) {
			printf("%c", mGet(map, i, j));
		}
		printf("\n");
	}

	return numVisited;
}

int main(int argc, char *argv[]) {
	FILE *input = fopen(argv[1], "r"); 

	if (input == NULL) {
	  printf("Could not open %s\n", argv[1]);
		return 1;
	}

	int ch;

	int guardI = -1;
	int guardJ = -1;

	matrix_t *map = mNew();
	list *row = lNew();

	int i = 0;
	int j = 0;

	while(1) {
		ch = fgetc(input);
		if (ch == '^' || ch == '>' || ch == '<' || ch == 'v') {
			guardI = i;
			guardJ = j;
		}
		
		if (ch != '\n' && ch != EOF) {
			lAdd(row, ch);
			j++;
		} else {
			j = 0;
			i++;
			mAddR(map, row);
			row = lNew();

			if (ch == EOF)
				break;
		}	
	}
	
	fclose(input);
	for (int i = 0; i < mRows(map); i++) {
		for (int j = 0; j < mCols(map); j++) {
			printf("%c", mGet(map, i, j));
		}
		printf("\n");
	}
	printf("\n");

	int res = walk(map, guardI, guardJ);
	printf("Number of visited squares: %d\n", res);
	
	mFree(map);
	lFree(row);
	
	return 0;
}
