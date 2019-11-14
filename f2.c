#include <stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{	
	pid_t cpid;
	int  *status=NULL;
	
	cpid = fork();

	if( cpid == 0 ) { //CHILD PROCESS
		printf("\n*************** This is child process ***************\n ");
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());
		sleep(15);
			
		printf("\n*************Child process terminates ***************\n");			
	}
	else { /*Parent process waiting for child process, sorting array elements in descending 	order and calculating number of words in given statement.*/

		cpid = wait(status);
		printf("\n\n\t Parent process resumed after the execution of child process with PID %d", cpid);
		printf("\n\t My process id is : %d", getpid());
		printf("\n\t My Parent process id is : %d", getppid());
				
	}//end of if-else

	return 0;	
}//end of main
