
int count_digits(const char *s) {
    int cnt = 0;
    while (*s) {
        if (*s >= '0' && *s <= '9') cnt++;
        s++;
    }
    return cnt;
}
/*
int count_digits(const char *s){
	int eax = 0; 	
      L:
	char d = *s;
	if (d==NULL) goto E;
	if (d<'0') goto L1;
	if (d >'9') goto L1;
	eax++;
     L1:
	d++;
	goto L;
      E:
	return eax;
}*/
