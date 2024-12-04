#include <stddef.h>
#include <stdlib.h>
#include <limits.h>
#include "listnew.h"


list *lSort(list *l) {
	listelem *p;
	listelem *e;
	int swapped = 0;
	
	while(l != NULL) {
		p = l->first;
		e = l->first;
		while(e->next != NULL) {
			listelem *tmp = e->next;
			if (e->elem > tmp->elem) {
				swapped = 1;
				e->next = tmp->next;
				tmp->next = e;
				if (e == l->first) {
					p = tmp;
					l->first = p;
				} else {
					p->next = tmp;
					p = tmp;
				}

				if (e == l->last) {
					l->last = e->next;
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

int lFree(list *l) {
	listelem *f = l->first;
	while(l != NULL) {
		listelem *tmp = f->next;
		free(f);
		f = tmp;
	}
	free(l);
	return 0;
}

int lCount(int v, list *l) {
	listelem *e = l->first;
	int c = 0;
	while(e != NULL) {
		if (e->elem == v) {
			c++;
		}

		e = e->next;
	}

	return c;
}

int lGet(list *l, int i) {
	if (i >= l->length) {
		return INT_MIN;
	}

	int j = 0;
	listelem *c = l->first;
	while (j < i && c != NULL) {
		c = c->next;
	}

	if (c == NULL) {
		return INT_MIN;
	}

	return c->elem;
}

void lAdd(list *l, int elem) {
	listelem *e = (listelem *) malloc(sizeof(listelem));
	e->elem = elem;
	e->next = NULL;
	
	if (l->length == 0) {
		l->first = e;
		l->last = e;
	} else {
		l->last->next = e;
		l->last = e;
	}
	l->length++;
}

void *lRem(list *l, listelem *r) {
	listelem *last = l->first;
	listelem *c = l->first;
	while (c != NULL) {
		if (c == r) {
			l->length--;
			if (c == l->last) {
				l->last = NULL;
				l->first = NULL;
			} else if (c == l->first) {
				l->first = c->next;
				return l;
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

int lIndexOf(list *l, int elem) {
	listelem *c = l->first;
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

list *lNew() {
	list *n = (list *) malloc(sizeof(list));
	n->first = NULL;
	n->length = 0;
	n->last = NULL;

	return n;
}

int lLength(list *l) {
	return l->length;
}


	


