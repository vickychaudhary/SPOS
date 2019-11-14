//Queue
int Q[40];

int rear = -1;

int front = -1;

void InsertQ(int);
int  DeleteQ();



//Function InsertQ() inserts currently arrived processes in the Queue
void InsertQ(int time)
{
	int i;

	for(i=0;i<n;i++)
	{
		if(p[i].at == time ){
			if(rear<=40){
				rear++;
				Q[rear] = i;
			}
			else{
				printf("\nQueue is full !!");
				exit(0);
			}

		}//outer if

	}//for
}//End

//Function InsertQ() inserts currently arrived processes in the Queue
void InsertCP(int pid) //Insert current incomplete process
{
		if(rear<=40){
			rear++;
			Q[rear] = pid;
		}
		else{
				printf("\nQueue is full !!");
				exit(0);
			}
}//End


//Function DeleteQ() delets a process from the Queue
int DeleteQ()
{
		int temp;
		if(front!=rear)
		{
			 front++;
			temp= Q[front];
		}
		return temp;
}
//End
