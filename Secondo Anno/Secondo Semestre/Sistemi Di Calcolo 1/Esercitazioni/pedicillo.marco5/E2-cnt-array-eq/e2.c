int counteq(short* v1, short* v2, int n) {
    int i, cnt = 0;
    for (i=0; i<n; ++i) cnt += (v1[i]==v2[i]);
    return cnt;
}
/*
int counteq(short* v1, short* v2, int n){
	short *ebp = v1;
	short *ebx = v2;
	int esi = n;
	int edi = 0;
	int a = 0;
      L:if(edi>= esi) goto E;
	short dx = ebp[edi];
	int c = (dx == ebx[edi]); 	// sete %cl
				// movsbl %cl, %ecx
	a+= c;
	edi++;
	goto L;
      E:return a; 
}*/
