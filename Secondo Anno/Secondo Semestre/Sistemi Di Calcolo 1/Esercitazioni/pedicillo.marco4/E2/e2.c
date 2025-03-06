int find(int* v, int n, int x) {
    int i;
    for (i=0; i<n; ++i)
        if (v[i] == x) return 1;
    return 0;
}

/*#int find(int* v, int n, int x) {
        int *c = v;
        int a = n;
        int d = x;
        int i=0;	
L:	if(i>=a) goto E;
        if(c[i]!=d) goto L2;
         a=1;
        goto E1;
L2:
        i++;
        goto L;
E:
        a=0;
E1:
        return a; 
}*/
    



	
