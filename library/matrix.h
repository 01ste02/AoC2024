#ifndef MATRIXH
#define MATRIXH

#include "listnew.h"
typedef struct matrix_t matrix_t;
typedef struct matrixrow matrixrow;

struct matrix_t {
	int numRow;
	int rowLen;
	matrixrow *row;
	matrixrow *lastRow;
	matrixrow **quickindex;
};

struct matrixrow {
	list* row;
	matrixrow *next;
};

int mAddR(matrix_t *m, list *r);

list *mGetR(matrix_t *m, int i);

int mGet(matrix_t *m, int i, int j);

int mRows(matrix_t *m);

int mCols(matrix_t *m);

int mSet(matrix_t *m, int i, int j, int elem);

matrix_t *mNew();

void mFree(matrix_t *m);

void mRFree(matrixrow *r);




#endif
