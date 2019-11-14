#include<iostream>
#include<time.h> 
#include<chrono> 
using namespace std;
using namespace std::chrono; 

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}
 
int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high];
    int i = (low - 1);
  
    for (int j = low; j <= high - 1; j++)  
    {   
        if (arr[j] < pivot)  
        {  
            i++;  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
} 

void quickSort(int arr[], int low, int high)  
{  
	auto start = high_resolution_clock::now();
	if (low < high)  
	{  
	        int pi = partition(arr, low, high);
	        quickSort(arr, low, pi - 1);  
	        quickSort(arr, pi + 1, high);
	}
	auto stop = high_resolution_clock::now(); 
   	auto duration = duration_cast<nanoseconds>(stop - start);
    	cout << "Time taken by function: "<< duration.count() << " nanoseconds" << endl; 
}


void merge(int arr[], int l, int m, int r) 
{ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 =  r - m; 
	int L[n1], R[n2]; 
  
	for (i = 0; i < n1; i++) 
		L[i] = arr[l + i]; 
	for (j = 0; j < n2; j++) 
		R[j] = arr[m + 1+ j]; 
  
    
	i = 0; 
	j = 0; 
	k = l; 
	while (i < n1 && j < n2) 
	{ 
		if (L[i] <= R[j]) 
	        { 
	            arr[k] = L[i]; 
	            i++; 
	        } 
	        else
	        { 
	            arr[k] = R[j]; 
	            j++; 
	        } 
        k++; 
	}
	while (i < n1) 
	{ 
	        arr[k] = L[i]; 
        	i++; 
        	k++; 
	} 
  
	while (j < n2) 
	{
	        arr[k] = R[j]; 
	        j++; 
	        k++; 
	} 
}

void mergeSort(int arr[], int l, int r) 
{ 
	auto start = high_resolution_clock::now();
	if (l < r) 
    { 
        int m = l+(r-l)/2; 
  
        mergeSort(arr, l, m); 
        mergeSort(arr, m+1, r); 
  
        merge(arr, l, m, r);
    }
	auto stop = high_resolution_clock::now(); 
   	auto duration = duration_cast<nanoseconds>(stop - start);
    	cout << "Time taken by function: "<< duration.count() << " nanoseconds" << endl;
	 
} 

void printArray(int arr[], int size)  
{  
    int i;  
    cout <<"\nThe Sorted Array is \n";
    for (i=0; i < size; i++)  
        cout <<arr[i] << " \n";  
    cout << endl;  
}     

int main() 
{ 
	int ch;
	int i,arr[5];
	
	int userBeg,userEnd;
	cout<<"Enter a start value"<<endl;
	cin>>userBeg;
	cout<<"Enter an end value"<<endl;
	cin>>userEnd;
	srand(time(NULL));
	for(i=0;i<5;i++)
		arr[i]=rand()%((userEnd-userBeg)+1)+userBeg;
		cout<<"\nThe Array is : \n";
	    
	for(i=0;i<5;i++)
		cout<<arr[i]<<" ";

	do
	{

		cout<<"\n1.Quick Sort\n2.Merge Sort\n3.Exit"<<endl;
		cout<<"Choose your choice: ";
		cin>>ch;

		int n = sizeof(arr) / sizeof(arr[0]); 
		switch(ch)
		{
			case 1:
				quickSort(arr, 0, n - 1);
				printArray(arr, n);
				break;
			case 2:
				mergeSort(arr, 0, n - 1);
				printArray(arr, n);
				break;
			case 3:
				cout<<"Thank You"<<endl;
				break;
			default:
				cout<<"Wrong Input"<<endl;
				break;
		}
   	}while(ch!=3); 	

	return 0; 
} 

