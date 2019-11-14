/*
Implement following programs to exhibit UNIX Process Control 
Parent process 	- sorts array elements in ascending order 
				- Count number of vowels in the given sentence

Child process 	- sorts array elements in descending order 
				- Count number of words in the given sentence
Demonstrate wait system call; where parent process waits for child process to terminate
*/

#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 20
#include "defined_function.h"


/*
The  <sys/types.h>  header file include  definitions for system data types such as : 
pid_t ( Used for process IDs ). 
All the data types defined under sys types are preceded by _t
*/

int main()
{
	char str[20];
	int arr[MAX], *status=NULL;
	pid_t cid;
	
	fflush(stdout);	

	accept_str(str);
	accept_nos(arr);

	cid = fork();

	if( cid == 0 ) //CHILD PROCESS
	{
		printf("\n*************** This is child process ***************\n ");
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());
		sleep(15);
		sort_desc(arr);
		cnt_words(str);	
		printf("\n*************Child process terminates ***************\n");			
	}
	else
	{
	/*Parent process waiting for child process, sorting array elements in descending 	order and calculating number of words in given statement.*/

		cid = wait(status);
		printf("\n\n\t Parent process resumed after the execution of child process with PID %d", cid);
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());

		sort_asc(arr);
		cnt_vowels(str);			
	}//end of if-else

	return 0;	
}//end of main
