#include<unistd.h>
#include<pthread.h>
#include<stdio.h>

//Generic function prototypes
void *add(void *);
void *sub(void *);
void *mult(void *);

pthread_t th_add, th_mul, th_sub;

int n1, n2, shared; //Global buffers

int main()
{
	void *arg1,*arg2,*arg3; 
	printf("enter the value of n1 and n2 ");
	scanf("%d %d",&n1,&n2);

	pthread_create(&th_add,NULL,add,&arg1);  //thread creation for addition
	pthread_create(&th_sub,NULL,sub,&arg2);
	pthread_create(&th_mul,NULL,mult,&arg3);

	pthread_join(th_add,NULL); 
	pthread_join(th_sub,NULL); 
	pthread_join(th_mul,NULL);

	printf("\n Thread ids are : %lu %lu %lu \n" ,th_add,th_sub,th_mul);
	return 0;
}

void *add(void *arg)
{
	shared=n1+n2;
	printf("\nThe value of shared after addtion is : %d",shared);
	th_add = pthread_self();
	pthread_exit(0);  //Exits from thread , returns the value in the second parameter of pthread_join 
}


void *sub(void *arg)
{
	shared=n1-n2;
	printf("\nThe value of shared after subtraction is : %d",shared);
	th_sub = pthread_self();
	pthread_exit(0);          //Exits from thread
}

void *mult(void *arg)
{
	shared=n1*n2;
	printf("\nThe value of shared after multiplication is : %d",shared);
	th_mul = pthread_self();
	pthread_exit(0);          //Exits from thread

}
