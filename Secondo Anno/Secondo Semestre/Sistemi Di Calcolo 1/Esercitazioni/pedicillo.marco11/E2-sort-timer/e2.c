#include "e2.h"
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int i,max;

static void do_sort(int *v, int n) {
    int j;
    for (i=0; i<n; ++i)
        for (j=1; j<n; ++j)
            if (v[j-1] > v[j]) {
                int tmp = v[j-1];
                v[j-1] = v[j];
                v[j] = tmp;
            }
}

void handler(int signum){
	float p = 100*(((float) i)/((float) max));
	printf("%.2f%%\n", p);
	ualarm(500000,0);
}

void sort(int *v, int n) {
    	max=n;
	struct sigaction act = { 0 };
	act.sa_handler = handler;
	int ret = sigaction(SIGALRM, &act, NULL);
	if(ret==-1){
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	
	ualarm(500000,0);
    	do_sort(v, n);	
}

