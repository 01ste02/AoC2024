#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void printRow(list_t *c) {
	while(c != NULL) {
		printf("%d ", c->elem);
		c = c->next;
	}
	printf("\n");
}

void printRowSkip(list_t *c, int skip) {
	int index = 0;
	while(c != NULL) {
		if (index != skip) {
			printf("%d ", c->elem);
		}
		c = c->next;
		index++;
	}
	printf("\n");
}

int safePart1(list_t *l) {
	int last = l->elem;
	l = l->next;
	if (l == NULL)
		return 0;
	int dir = (last < l->elem) ? 1 : -1;
	int diff;
	while (l != NULL) {
		diff = l->elem - last;
		//printf("n: %d, l: %d, d: %d, diff: %d\n", l->elem, last, dir, diff);
		if (diff > 3 || diff < -3 || diff == 0 ||
		    (dir < 0 && diff > 0) ||
		    (dir > 0 && diff < 0)) {
			//printf("\n");
			return 0;
		}
		
		last = l->elem;
		l = l->next;
	}
	//printf("\n");
	return 1;
}

int safePart2(list_t *l) {
	list_t *c = l;
	int len = length(l);
	int skip = -1;

	int safe = 1;
	int dir = 0;
	int diff;
	int last = -1;

	int index = 0;

	if (c->next == NULL) {
		return 0;
	}

	while (skip < len) {
		index = 1;
		safe = 1;
		//printRowSkip(c, skip);
		if (skip == 0) {
			c = c->next;
			index++;
		}
		
		last = c->elem;
		
		if (skip == 1) {
			c = c->next;
			index++;
		}
		
		c = c->next;
		if (c != NULL) {
			dir = (last < c->elem) ? 1 : -1;
		}
		
		while (c != NULL) {
			if (index == skip) {
				index++;
				c = c->next;
				continue;
			}
			
			diff = c->elem - last;
			//printf("i: %d, skip: %d, n: %d, l: %d, d: %d, diff: %d\n", index, skip, c->elem, last, dir, diff);
			if (diff > 3 || diff < -3 || diff == 0 ||
			    (dir < 0 && diff > 0) ||
			    (dir > 0 && diff < 0)) {
				safe=0;
				//printf("Unsafe\n");
				break;
			}
		
			last = c->elem;
			c = c->next;
			index++;
			//printf("\n");
		}
		//printf("\n");
		if (safe) {
			return 1;
		}
		
		skip++;
		c = l;
	}

	return 0;
}

int main(int argc, char *argv[]) {
	FILE *input = fopen(argv[1], "r"); 

	if (input == NULL) {
	  printf("Could not open %s\n", argv[1]);
		return 1;
	}

	int ch;

	int numSafe = 0;
	int numSkipSafe = 0;
	int n = 0;

	list_t *row = (list_t *) malloc(sizeof(list_t));
	list_t *c = row;
	while((ch = fgetc(input)) != EOF) {
		if (ch == ' ') {
			c->elem = n;
			c->next = (list_t *) malloc(sizeof(list_t));
			c = c->next;
			n = 0;
		} else if (ch == '\n') {
			c->elem = n;
			c->next = NULL;
			
			numSafe += safePart1(row);
			//int s = safePart2(row);
			//numSkipSafe += s;
			//printf("Added %d\n", s);
			numSkipSafe += safePart2(row);
			
			freeList(row);
			row = (list_t *) malloc(sizeof(list_t));
			c = row;
			n = 0;
		} else {
			n = n*10 + (ch - 48);
		}
	}

	free(row);

	printf("Number of safe rows: %d\n", numSafe);
	printf("Number of safe rows with skipping: %d\n", numSkipSafe);
	
	fclose(input);
	
	return 0;
}
