#ifndef LISTH
#define LISTH
	typedef struct list_t list_t;

	struct list_t {
        	int elem;
        	list_t *next;
	};

	list_t *sort(list_t *l);

	int freeList(list_t *l);

	int count(int v, list_t *l);

        int length(list_t * l);

#endif
