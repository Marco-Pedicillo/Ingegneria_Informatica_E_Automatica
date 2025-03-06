#include "e1.h"
#include <string.h>
#include <stdlib.h>

int comparator(const void *p1, const void *p2){
	const person_t a = *(person_t*)p1;
	const person_t b = *(person_t*)p2;
	return strcmp(a.name,b.name);
	
}

void sort_people(person_t p[], size_t n){
	qsort(p,n, sizeof(person_t), comparator);
}

person_t *find_person(char *key, person_t sorted[], size_t n){
	person_t* res = bsearch(&key, sorted, n, sizeof(person_t), comparator);
	return res;
}
