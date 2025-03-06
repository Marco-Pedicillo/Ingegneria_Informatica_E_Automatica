#include <stdlib.h>
#include "e2.h"

int list_equal(const node_t *l1, const node_t *l2) {
    while (l1!=NULL && l2!=NULL) {
        if (l1->elem != l2->elem) return 0;
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1==NULL && l2==NULL;
}
/*
int list_equal(const node_t *l1, const node_t *l2){
	const node_t *c = l1;
 	const node_t *d = l2;
      L:
	if(l1==NULL) goto E;
	if(l2 == NULL) goto E;
	if (l1 -> elem != l2 -> elem) goto L1;
	l1 = l1 -> next;
	l2 = l2 -> next;
	goto L;
     L1:;
	int a = 0; 
	goto A;
	
      E:
	l1 == NULL;
	l2 == NULL;
	a = 1;
      A:
	return a;
	
}*/
