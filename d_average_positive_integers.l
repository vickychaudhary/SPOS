/* Lex program to read positive integers from a file and calculate average of it. */
  
%{ 	/* Definition section */

	#include<string.h> 
	void calc_avg(char *); 
	void display_avg(); 

	FILE *yyin; 
	int n, sum=0, count =0;
	float avg=0;
%} 
  
/* Rule Section */

%% 
"$"		display_avg();  //Termination delimiter
(.)* 		calc_avg(yytext); 
%% 
  
/* Driver code */

int yywrap()
{ 
	return 0;
}

int main() 
{ 
	yyin=fopen("input_integers.txt","r");  // Open the source file in read mode
	printf("\n Positive integers are :");
	yylex(); 		
    return 1 ; 
} 

void calc_avg(char *t) 
{  
	n = atoi(t);
	printf("\n %d", n);
	sum = sum + n;   	
	count++;
} 

void display_avg()
{
	avg = sum/count;
	printf("\n Average of the positive integers are : %f",avg);
}
