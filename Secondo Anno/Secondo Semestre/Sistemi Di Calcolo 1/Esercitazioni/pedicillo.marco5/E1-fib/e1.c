int fib(int n) {
    if (n<2) return 1;
    return fib(n-1)+fib(n-2);
}
/*
int fib(int n){
	int c=n;
	if(c>=2) goto L;
	int a=1;
	goto E;
      L:
	c-=1;
	int d=fib(c);
	c-=1;
	a =fib(c);
	a+=d;
      E:
	return a;
}*/


