#include <stdlib.h>
#include "e1.h"

int list_add_first(node_t **l, short elem) {
    node_t *p = *l;
    node_t *n = malloc(sizeof(node_t));
    if (n == NULL) return -1;           // allocation error
    n->elem = elem;
    n->next = p;
    *l = n;
    return 0;
}
/*
int list_add_first(node_t **l, short elem){
	node_t * c = *l;
	node_t * d = malloc(sizeof(node_t));	
      L:
	if(d!=NULL) goto E;
	int a = -1;
	goto A;
      E:
	d-> elem = elem;
	d-> next = c;
	c = d;
	a=0;
      A:
	return a;
	
}*/
