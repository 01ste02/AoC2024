#ifndef LIST
#define LIST
typedef struct list list;
typedef struct listelem listelem;

struct list {
	listelem *first;
	listelem *last;
	int length;
};

struct listelem {
	int elem;
	listelem *next;
};

list *lSort(list *l);

int lFree(list *l);

int lCount(int v, list *l);

int lGet(list *l, int i);

void lAdd(list *l, int elem);

void *lRem(list *l, listelem *r);

int lIndexOf(list *l, int elem);

int lLength(list *l);

list *lNew();

#endif
