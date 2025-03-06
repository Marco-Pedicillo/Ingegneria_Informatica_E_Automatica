#include "e2.h"

#define STRIDE 64

long f_opt(const short *v, unsigned n){
	long x = 0;
	unsigned i, j;
	for(j=0; j<n; j+=STRIDE){
		for (i=0; i<STRIDE; ++i)
         		x += v[j+i];
	}
	return x;	
}
