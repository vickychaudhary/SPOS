int n;
void accept_nos(int arr[MAX])
{
	int i;
	printf("\n\tEnter the number of elements:");
	scanf("%d", &n);
	
	printf("\n\t Enter the elements:\n");
		for( i = 0 ; i < n ; i++ )
		{
			printf("\n\t Element %d :", i+1);
			scanf("%d", &arr[i]);
		}//end of for
}//end of accept_nos


void accept_str(char str[])
{
	printf("\nEnter the statement for calculating number of vowels and words :");
	fgets(str,256,stdin);	
}

void sort_asc(int arr[MAX])
{
	int i,j,temp;
	for(i=0;i<n;i++) {
			for(j=0;j<n;j++) {
				if(arr[i]<arr[j]) {
					temp=arr[i]; 	arr[i]=arr[j];  arr[j]=temp;
				}//if
			}//inner for
		}//outer for

	printf("\n\n\tThe Numbers In Ascending Order Are:\n\t ");
	for(i=0;i<n;i++) {
			printf("%d ",arr[i]);
	}	//for printing
}//sort_asc

void sort_desc(int arr[MAX])
{
	int i,j,temp;
	for(i=0;i<n;i++){
			for(j=0;j<n;j++) {
				if(arr[i]>arr[j]) {
					temp=arr[i];
					arr[i]=arr[j];
					arr[j]=temp;
				}//if
			}//inner for
		}//outer for

	printf("\n\n\tThe Numbers In Descending Order Are:\n\t ");
	for(i=0;i<n;i++){
		printf("%d ",arr[i]);
	}//for display
}//sort_desc

void cnt_vowels(char str[]) {
	int i=0,cnt=0;

	while(str[i]!='\0') {

		if(str[i]=='a'|| str[i]=='e'|| str[i]=='i'|| str[i]=='o'|| str[i]=='u'||
		str[i]=='A'|| str[i] =='E'|| str[i]=='I'|| str[i]=='O'|| str[i]=='U') { cnt++; }

		i++;
	}//while
	printf(" \n\t Number of vowels in the given string is: %d\n",cnt);	
}//cnt_vowels

void cnt_words(char str[]){
	int cnt=1,i=0;

	for(i=0;str[i]!='\0';i++) {
               if(str[i]==' ') 	cnt++;
	}//for
	printf(" \n\t Number of words in the given string is: %d",cnt);
}//cnt_words
