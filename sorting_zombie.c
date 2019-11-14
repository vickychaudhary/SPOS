/*
Implement following programs to exhibit UNIX Process Control 
Parent process 	- sorts array elements in ascending order 

Child process 	- sorts array elements in descending order 
Demonstrate ZOMBIE state; where child process terminates and waits for parent process to collect its exit status */
  
#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 20
#include "defined_function.h"

int main()
{
	int arr[MAX], *status=NULL;
	pid_t cpid;
	
	fflush(stdout);	

	accept_nos(arr);

	printf("\n\tThis is the parent process. PID: %d",getpid());
	
	sort_asc(arr);

	cpid = fork();

	if( cpid == 0 ) //CHILD PROCESS
	{
		sleep(5);
		printf("\n*************** This is child process ***************\n ");
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());
		
 		sort_desc(arr);
		printf("\n*************** Child process terminates *************\n");			
	}
	else
	{
		printf("\n\tParent process sleeping!\n");
		sleep(25);
	 	printf("\n\nSleep time complete!\n");
	 	printf("\nWait returns: (cleanup zombie process from process table)");	
	}//end of if-else

	return 0;	
}//end of main


