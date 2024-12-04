#ifndef MATRIXH
#define MATRIXH

#include "list.h"
typedef struct matrix_t matrix_t;
typedef struct matrixrow matrixrow;

struct matrix_t {
	int numRow;
	int rowLen;
	matrixrow *row;
	matrixrow *lastRow;
};

struct matrixrow {
	list_t* row;
	matrixrow *next;
};

int mAddR(matrix_t *m, list_t *r);

list_t *mGetR(matrix_t *m, int i);

int mGet(matrix_t *m, int i, int j);

int mRows(matrix_t *m);

int mCols(matrix_t *m);

matrix_t *mNew();

void mFree(matrix_t *m);

void mRFree(matrixrow *r);




#endif
