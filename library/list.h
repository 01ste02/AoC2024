#ifndef LISTH
#define LISTH
typedef struct list_t list_t;

struct list_t {
	int elem;
	list_t *next;
	list_t *last;
	int length;
};

list_t *sort(list_t *l);

int freeList(list_t *l);

int count(int v, list_t *l);

int length(list_t *l);

int lGet(list_t *l, int i);

void lAdd(list_t *l, int elem);

list_t *lRem(list_t *l, list_t *r);

int lIndexOf(list_t *l, int elem);

list_t *lNew();

#endif
