#include "e2.h"
/*
int crc32b(char *bytes, int n) {
    int magic = ~0; // operazione: not
    int crc = magic;
    while (n--) {
        int value;
        int byte = *bytes++; // attenzione!
        int index = crc ^ byte;
        get_constant(&value, index & 0xFF);
        crc = value ^ (crc >> 8);
    }
    return crc ^ magic;
}*/ 

//c_eq
int crc32b(char *bytes, int n){
	int value;
	int ebp = 0;
	ebp = ~ebp;
	int edi = ebp;
	char* esi = bytes;
	int ebx = n;
L:
	if(n<= 0) goto E;
	n--;
	char cl = *esi;
        int ecx = cl;
	esi++; 
        ecx = edi ^ ecx;
	ecx = ecx & 0xFF;
        get_constant(&value, ecx); // se ho & alloco in stack
        edi = edi >> 8;
	edi = value ^ edi;
	goto L;
E:;
	int eax = edi ^ ebp;
	return eax;
}
