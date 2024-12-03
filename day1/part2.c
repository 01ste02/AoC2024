#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void) {
	FILE *input = fopen("part2.in", "r"); 

	if (input == NULL) {
		printf("Could not open part2.in\n");
		return 1;
	}

	list_t *leftlist = (list_t *) malloc(sizeof(list_t));
	list_t *rightlist = (list_t *) malloc(sizeof(list_t));

	list_t *currentLeft = leftlist;
	list_t *currentRight = rightlist;
	list_t *prevLeft = leftlist;
	list_t *prevRight = rightlist;
	
	int list = 0;
	int ch;
	
	int val = 0;
	while((ch = fgetc(input)) != EOF) {
		if (ch != '\n' && ch != ' ') {
			val = 10*val + (ch - 48);
		} else if (ch == ' ' && list == 0) {
			list = 1;
			currentLeft->elem = val;
			val = 0;
			currentLeft->next = (list_t *) malloc(sizeof(list_t));
			prevLeft = currentLeft;
			currentLeft = currentLeft->next;
		} else if (ch == '\n' && list == 1) {
			list = 0;
			currentRight->elem = val;
			val = 0;
			currentRight->next = (list_t *) malloc(sizeof(list_t));
			prevRight = currentRight;
			currentRight = currentRight->next;
		}
	}

	fclose(input);

	free(currentLeft);
	free(currentRight);
	prevLeft->next = NULL;
	prevRight->next = NULL;

	leftlist = sort(leftlist);
	rightlist = sort(rightlist);

	list_t *l = leftlist;
	list_t *r = rightlist;
	
	int totalDist = 0;
	int similarity = 0;
	while (l != NULL && r != NULL) {
		int diff= l->elem - r->elem;
		if (diff < 0) {
			diff = -diff;
		}
		totalDist += diff;
		similarity += l->elem * count(l->elem, rightlist);
		//printf("L: %d, R: %d, D: %d, T: %d\n", l->elem, r->elem, diff, totalDist);
		l = l->next;
		r = r->next;
	}

	printf("Total distance is: %d\n", totalDist);
	printf("Similarity score is: %d\n", similarity);
	freeList(leftlist);
	freeList(rightlist);
	
	return 0;
}
