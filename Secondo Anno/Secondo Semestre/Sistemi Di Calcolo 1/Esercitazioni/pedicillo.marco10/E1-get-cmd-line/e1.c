#include "e1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_cmd_line(char* argv[MAX_TOKENS]){
	int i=0;
	char buff[1024];
	char *res = fgets(buff, 1024, stdin); 
	if(res == NULL) return;
	char *token = strtok(res, "\n\t ");
	while(token != NULL){
		argv[i]= strdup(token);
		token = strtok(NULL, "\n\t ");
		i++;
	}
	argv[i]=NULL;
}
