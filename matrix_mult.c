//Implement matrix multiplication using multithreading with pthread library.

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX 3

int a[MAX][MAX];
int b[MAX][MAX];
int c[MAX][MAX];

//Generic function prototypes
void* mult(void*);

int main()
{ 
    pthread_t tid1,tid2,tid3; //Threads for row1, row2, and row3
    int row1,row2,row3;
    int i,j;

    printf("\n\nEnter First matrix : ");
    
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            printf("\nEnter a[%d][%d] : ",i,j);
            scanf("%d",&a[i][j]);
        }
    }

    printf("\n\nEnter Second matrix");
    
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            printf("\nEnter b[%d][%d] : ",i,j);
            scanf("%d",&b[i][j]);
        }
    }  
  
    row1=0;
    //Create a thread as tid1; executing mult routine; accepting index of row1
    pthread_create(&tid1,NULL,mult,&row1);
    
    row2=1;
    //Create a thread as tid1; executing mult routine; accepting index of row1
    pthread_create(&tid2,NULL,mult,&row2);
	
    row3=2;
    //Create a thread as tid1; executing mult routine; accepting index of row1
    pthread_create(&tid3,NULL,mult,&row3);
	
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    
    printf("\n\nResult is : \n");
    
    for(i=0;i<MAX;i++){       
       for(j=0;j<MAX;j++){
          printf("%d ",c[i][j]);
       }        
       printf("\n");    
    }
    
   exit(0);

}//End of main


void* mult(void * arg)
{      
	int i,j,k;
	i = *(int * )arg;

	for(j=0;j<MAX;j++){       
		c[i][j] = 0;       
		for(k=0;k<MAX;k++){
			c[i][j] += a[i][k] * b[k][j];
		}       
	}
	printf("\nThread id is : %ld",pthread_self()); 	
}//END 

