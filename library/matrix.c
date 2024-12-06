#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include "listnew.h"
#include "matrix.h"

int mAddR(matrix_t *m, list *r) {
	if (lLength(r) != mCols(m) && mRows(m) != 0) {
		return -1;
	} else if (r->length != m->rowLen) {
		m->rowLen = r->length;
	}

	matrixrow *mr = (matrixrow *) malloc(sizeof(matrixrow));
	mr->row = r;
	mr->next = NULL;
	
	if (m->numRow != 0) {
		m->lastRow->next = mr;
		m->lastRow = m->lastRow->next;
	} else {
		m->row = mr;
		m->lastRow = mr;
	}
	
	m->numRow++;
	return m->numRow;
}

list *mGetR(matrix_t *m, int i) {
	if (i >= m->numRow || i < 0)
		return NULL;
	matrixrow *r = m->row;
	int j = 0;
	while (j < i && r != NULL) {
		r = r->next;
		j++;
	}

	if (r == NULL)
		return NULL;
	return r->row;
	
}

int mGet(matrix_t *m, int i, int j) {
	list *row = mGetR(m, i);
	if (row == NULL)
		return INT_MIN;
	return lGet(row, j);
}

int mRows(matrix_t *m) {
	return m->numRow;
}

int mCols(matrix_t *m) {
	return m->rowLen;
}

matrix_t *mNew() {
	matrix_t *m = (matrix_t *) malloc(sizeof(matrix_t));
	m->numRow = 0;
	m->rowLen = 0;
	m->row = NULL;
	m->lastRow = NULL;

	return m;
}

void mFree(matrix_t *m) {
	matrixrow *r = m->row;
	matrixrow *rn;
	while (r != NULL) {
		rn = r->next;
		mRFree(r);
		r = rn;
	}

	free(m);
}

void mRFree(matrixrow *r) {
	lFree(r->row);
	free(r);
}
