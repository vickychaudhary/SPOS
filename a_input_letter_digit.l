%{
/* Lex program to find out whether the given input is a letter or digit */
	#include<stdio.h>
	#include<stdlib.h>
%}

/* Rule Section */
%%
[0-9]+		{ printf("Entered input is DIGIT"); printf("\nEnter other input or exit(ctrl+c)"); }
[0-9a-zA-Z ]+	{ printf("Entered input is NOT A DIGIT"); ; printf("\nEnter other input or exit (ctrl+c)"); }
%%


/* Driver code */

int yywrap()
{ 
	return 0;
}

int main()
{
	printf("\n Enter the input :\n");
	yylex();
	return 0;
}

