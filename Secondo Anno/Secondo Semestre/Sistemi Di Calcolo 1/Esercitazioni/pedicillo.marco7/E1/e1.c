#include "e1.h"

int binsearch(int *v, int n, int x) {
    int i=0, j=n;
    while (i<j) {
        int m = (i+j)/2;
        if (v[m]==x) return 1;
        if (v[m]>x) j=m;
        else i=m+1;
    }
    return 0;
}
/*
int binsearch(int *v, int n, int x){
	int c = 0;
	int ebx=x;
	int esi=n;
	int edi = *v;
      L:
	if(c>=esi) goto E;
	int d = c+esi;
	d = d/2;
	if(edi[d]!= ebx) goto L1;
	int a=1;
	return a;
     L1:
	if(edi[d]<=ebx) goto L2;
	esi=d;
     L2:
	c = d+1;
	goto L;
      E:
	a=0;
	return a;
	
}*/
