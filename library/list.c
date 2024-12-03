#include <stddef.h>
#include <stdlib.h>
#include "list.h"


list_t *sort(list_t *l) {
	list_t *p;
	list_t *e;
	int swapped = 0;
	
	while(l != NULL) {
		p = l;
		e = l;
		while(e->next != NULL) {
			list_t *tmp = e->next;
			if (e->elem > tmp->elem) {
				swapped = 1;
				e->next = tmp->next;
				tmp->next = e;
				if (e == l) {
					p = tmp;
					l = p;
				} else {
					p->next = tmp;
					p = tmp;
				}
				continue;
			}
			p = e;
			e = e->next;
		}
		
		if (!swapped) {
			break;
		}
		swapped = 0;
	        
	}

	return l;
}

int freeList(list_t *l) {
	while(l != NULL) {
		list_t *tmp = l->next;
		free(l);
		l = tmp;
	}
	return 0;
}

int count(int v, list_t *l) {
	list_t *e = l;
	int c = 0;
	while(e != NULL) {
		if (e->elem == v) {
			c++;
		}

		e = e->next;
	}

	return c;
}


