#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
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

int length(list_t * l) {
	int len = 0;
	while (l != NULL) {
		len++;
		l = l->next;
	}

	return len;
}


int lGet(list_t *l, int i) {
	if (i >= l->length) {
		return INT_MIN;
	}

	int j = 0;
	list_t *c = l;
	while (j < i && c != NULL) {
		c = c->next;
	}

	if (c == NULL) {
		return INT_MIN;
	}

	return c->elem;
}

void lAdd(list_t *l, int elem) {
	l->last->next = (list_t *) malloc(sizeof(list_t));
	l->last = l->last->next;
	l->last->elem = elem;
	l->last->next = NULL;
	l->length++;
}

list_t *lRem(list_t *l, list_t *r) {
	list_t *last = l;
	list_t *c = l;
	while (c != NULL) {
		if (c == r) {
			l->length--;
			if (c == l->last) {
				l->last = NULL;
			}
			
			if (c == l) {
				c = c->next;
				return c;
			}

			last->next = c->next;
			free(c);
			return l;
		}
		last = c;
		c = c->next;
	}

	return NULL;
}

int lIndexOf(list_t *l, int elem) {
	list_t *c = l;
	int i = 0;

	while (c != NULL) {
		if (c->elem == elem) {
			return i;
		}

		i++;
		c = c->next;
	}

	return -1;
}

list_t *lNew() {
	list_t *n = (list_t *) malloc(sizeof(list_t));
	n->next = NULL;
	n->length = 0;
	n->last = NULL;

	return n;
}


	


