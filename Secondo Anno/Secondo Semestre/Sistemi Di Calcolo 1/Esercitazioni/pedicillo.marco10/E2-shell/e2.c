#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../E1-get-cmd-line/e1.c"
#include "e2.h"

int do_shell(const char* prompt){
	while(1){
	printf("Prompt: %s ", prompt);
	char* buff[64];
	get_cmd_line(buff);
	if(buff[0] == NULL) continue;
	if((strcmp(buff[0], "quit") == 0)) break;

	pid_t pid = fork();
	if(pid==-1){
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if(pid==0){
		int  n = execvp(buff[0], buff);
		if(n == -1){
			perror("unknown command: ");	
			printf("%s\n", buff[0]);
			_exit(EXIT_FAILURE);
		}
		_exit(EXIT_SUCCESS);	
	}

	wait(NULL);

	}
	
	exit(EXIT_SUCCESS);
}


