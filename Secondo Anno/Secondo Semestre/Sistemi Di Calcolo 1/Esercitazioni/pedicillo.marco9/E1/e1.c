#include "e1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseCSV(const char* file, person_t** out, int minAge) {
	*out = NULL;
	
	FILE* f = fopen(file, "r");
	if(f == NULL) return -1;
	
	person_t* last = NULL;
	while(1){	
		char line[64];
		char* res = fgets(line, sizeof(line), f);
		
		if(res == NULL) break;	
			
		char name[64], surname[64], date[11], phd[5];
		
		for(int i=0; i<4; i++){
			char* tk = strtok(res,",");
			if(tk == NULL){
				fclose(f);
				return -1;
			}
			int len = strlen(tk);
			if(tk[len-1] == '\n')
				tk[len-1] = '\0';
		
			switch(i){
			case 0:{strncpy(name, tk, sizeof(name)); break;}
			case 1:{strncpy(surname, tk, sizeof(surname)); break;}
			case 2:{strncpy(date, tk, sizeof(date)); break;}
			case 3:{strncpy(phd, tk, sizeof(phd)); break;}
			deafault: {fclose(f); return -1;}	
			}

			res=NULL;		
		}
		
		int year = atoi(date + 6);
		if(year >= minAge){
			person_t* current = malloc(sizeof(person_t));
			if(current==NULL){
				fclose(f);
				return -1;			
			} 
			current->name = strdup(name); //copia stringa e l'alloca dinamicamente
			current->surname = strdup(surname);
			current->year = year;	
			current->has_phd = strcmp(phd, "yes") == 0 ? 1:0;
			current->next = NULL;
			
			if(last == NULL){
				*out = current;			
			}else{
				last->next = current;
			}
			last = current;
		}
			
	}

	if(fclose(f) != 0) return -1;
	return 0;
}
