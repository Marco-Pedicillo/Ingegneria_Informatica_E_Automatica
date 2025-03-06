#include "e1.h"
/*
int is_suffix(const char* s1, const char* s2){

    const char *s1_aux = s1;
    const char *s2_aux = s2;

    while (*s1_aux++);
    while (*s2_aux++);
    while (s1 != s1_aux && s2 != s2_aux && *(--s1_aux) == *(--s2_aux));
    return s1 == s1_aux && *s1_aux == *s2_aux;
}*/

int is_suffix(const char* s1, const char* s2){
	const char *c = s1;
	const char *d = s2;
      L:;
	char a = *c;
	char b = *d;
	a++;
	b++;
	if(a==0) goto E;
	if(b==0) goto E;
	if(*c==a) goto E;
	if(*d==b) goto E;
	a--;
	b--;
	if(*a!=*b) goto E;
      E:;
	a=*c;
	
}
