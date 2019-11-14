#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 20
#include "defined_function.h"
int main()
{
	pid_t pid;
	int arr[10];
	char * argv_list[] = {"ls","-lart","/home",NULL}; 
	pid=fork();    

	if(pid==0)
	{
		accept_nos(arr);
		execv("/bin/ls",argv_list);
		printf("\n This is child \n");
	}
	else
	{
		sleep(50);  
		printf("\n This is parent\n");
	}
}
