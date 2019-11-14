%{
/* Lex program to change case of given input (Upper, Lower, Sentence,Toggle) */
	#include<stdio.h>
	#include<stdlib.h>
%}
lower [a-z]
upper [A-Z]
/* Rule Section */
%%
{lower}		{ printf("%c",yytext[0]-32);}
{upper}		{ printf("%c",yytext[0]+32);}
[ \t\n]+  		ECHO;
. 			ECHO;
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

