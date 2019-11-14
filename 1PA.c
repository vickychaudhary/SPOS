#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 	20		// MAXIMUM SYMBOL TABLE ENTRIES
#define M_MAX 	11		// MAXIMUM MNEMONICS
#define AD_MAX 5		// MAXIMUM ASSEMBLER DIRECTIVES
#define R_MAX 	4		// MAXIMUM REGISTERS
#define C_MAX 	6		// MAXIMUM CONDITION CODES


struct SYMBTAB
{
	char Symb[10];
	int Addr;	
}S[MAX];

struct LITTAB
{
	char Lit[5];
	int Addr;
}L[MAX];

int POOLTAB[MAX],SymbCnt,LitCnt,PoolCnt,TokCnt,LC,i,j,k;
char Tok1[MAX],Tok2[MAX],Tok3[MAX],Tok4[MAX],Buffer[80],temp[MAX];
FILE *fp, *fp1,*fp2;  // fp1 is for inputfile, fp2 - IC

//DATA STRUCTURE INITIALIZATION

char MOTAB[][10]	= { "STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
char REGTAB[][10] 	= { "AREG","BREG","CREG","DREG"};
char CONDTAB[][10] 	= { "LT","LE","EQ","GT","GE","ANY"};
char ADTAB[][10]	= { "START","END","ORIGIN","EQU","LTORG"};

int SearchSymb(char *s)
{
	int i;
	for( i = 0; i < SymbCnt; i++)
	{
		if(strcmp(S[i].Symb,s)==0)
			return(i);
	}
	return -1;
}// END OF SearchSymb()

int SearchLit(char *s)
{
	int i;
	for( i = POOLTAB[PoolCnt]; i < LitCnt; i++)
	{
		if(strcmp(L[i].Lit,s)==0)
			return(i);
	}
	return -1;
}// END OF SearchLit()

int SearchOp(char *s)
{
	int i;
	for( i = 0; i < M_MAX; i++)
	{
		if(strcmp(MOTAB[i],s) == 0)
			return(i);
	}
	return -1;
}// END OF SearchOp()

int SearchReg(char *s)
{
	int i;
	for( i = 0; i < R_MAX; i++)
	{
		if(strcmp(REGTAB[i],s)==0)
			return(i);
	}
	return -1;
}//// END OF SearchReg()

int SearchCond(char *s)
{
	int i;
	for( i = 0; i < C_MAX; i++)
	{
		if(strcmp(CONDTAB[i],s)==0)
			return(i);
	}
	return -1;
}// END OF SearchCond()

int SearchDirective(char *s)
{
	int i;
	for( i = 0; i < 5; i++)
	{
		if(strcmp(ADTAB[i],s)==0)
			return(i);
	}
	return -1;
}// END OF SearchDirective()

void DispSymbTab()
{
	int i;
	//LISTING SYMBOL TABLE
	printf("\n-----------------------------");
	printf("\nSymb\tAddr");
	printf("\n-----------------------------");
	for(i=0;i<SymbCnt;i++)
		printf("\n%s\t%d",S[i].Symb,S[i].Addr);
	printf("\n-----------------------------");

}// END OF DispSymbTab()

void DispLitTab()
{
	int i;
	printf("\n-------------------------------");
	printf("\nLit#\tLit\tAddr");
	printf("\n-------------------------------");
	for(i=0;i<LitCnt;i++)
		printf("\n%02d\t%s\t%d",i,L[i].Lit,L[i].Addr);
	printf("\n-------------------------------");
}// END OF DispLitTab()

void DispPoolTab()
{
	int i;
	printf("\n--------------------");
	printf("\nPool#\tPool Base");
	printf("\n--------------------");
	for(i=0;i<PoolCnt;i++)
		printf("\n%02d\t%d",i,POOLTAB[i]);
	printf("\n--------------------");
}// END OF DispPoolTab()

void PrintFile(char *fn)
{
	fp=fopen(fn,"r");
	if( fp == NULL)
	{
		printf("\nCannot Open File %s",fn);
		exit(0);

	}
	while(fgets(Buffer,80,fp))
		printf("%s",Buffer);
	fclose(fp);
}// END OF PrintFile()


int processOP(char *T1, char *T2, char *T3){
	int i = SearchOp(T1);
	if(i >= 1 && i <= 8){	// ADD - DIV
		if(T3[0] == '=')// Operand is literal
		{
			j = SearchLit(T3);
			if( j == -1) { //LITERAL NOT PRESENT
				sprintf(temp,"(L, %02d)",LitCnt);
				strcpy(L[LitCnt++].Lit,T3);
			} 
			else 
				sprintf(temp,"(L, %02d)",j); 	
		}//literal
		else	// Operand is symbol
		{
			j = SearchSymb(T3);
			if(j == -1) { // SYMBOL NOT PRESENT
				sprintf(temp,"(S, %02d)",SymbCnt);
				strcpy(S[SymbCnt++].Symb,T3);
			}
			else { 	sprintf(temp,"(S, %02d)",j); }
		}// END OF OPERAND IS SYMBOL

		j = (i ==7) ? SearchCond(T2) : SearchReg(T2);

		fprintf(fp2,"(IS, %02d) (%d) %s\n",i,j,temp);   return 1;
	}// END OF 1 TO 8 I.E. ADD - DIV
	return 0;
}//processOP


int processDL(char *T2, char *T3){
	int j;
	if ( strcmp(Tok2, "DC") ==0 || strcmp(Tok2,"DS") == 0)
	{
		j = SearchSymb(Tok1);
		if(j == -1)// SYMBOL NOT PRESENT
		{
			strcpy(S[SymbCnt].Symb,Tok1);
			S[SymbCnt++].Addr = LC;
		}
		else// SYMBOL PRESENT
		{
			S[j].Addr = LC;						
		}// END OF SYMBOL PRESENT

		if( strcmp(Tok2,"DS") == 0) // DS
		{
			LC += atoi(Tok3)-1;
			fprintf(fp2,"(DL, 01) (C, %02d)\n",atoi(Tok3));
		}else {
			fprintf(fp2,"(DL, 00) (C, %02d)\n",atoi(Tok3));
		}
		return 1;
	}	
	return 0;				
}// processDL



void processEQU(char *T1, char *T2, char *T3)
{
	int i, j, k;
	i = SearchDirective(T2);
	if( i == 3)	// EQU
	{
		k = SearchSymb(T3);
		j = SearchSymb(T1);
		if(j == -1) // NOT PRESENT
		{
			strcpy(S[SymbCnt].Symb,T1);
			S[SymbCnt++].Addr = S[k].Addr;
		}
		else// SYMBOL PRESENT
		{
			S[j].Addr = S[k].Addr;
		}// END OF SYMBOL PRESENT

		fprintf(fp2,"(AD, %02d)\n",i);
		LC--; 	// NO LC PROCESSING FOR EQU		
	}// END OF EQU
}//processEQU




void PassOne()
{
	// fp1 - ptr of source file
	// fp2 - ptr of Intermediate file

	fp1 = fopen("input.asm","r"); // input file
	fp2 = fopen("ic.txt","w");  // IC file
	if( fp1 == NULL || fp2 == NULL)
	{
		printf("\nCannot Open File ");
		exit(0);
	}

	while ( fgets( Buffer, 80, fp1) )
	{
		// INITIALIZE TOKENS TO NULL
		strcpy(Tok1,"");    		strcpy(Tok2,"");
		strcpy(Tok3,"");   		strcpy(Tok4,"");

		TokCnt = sscanf(Buffer,"%s %s %s %s",Tok1,Tok2,Tok3,Tok4);
		switch(TokCnt)
		{
			case 1:  // STOP, START, LTORG, END
				i = SearchOp(Tok1);  
				if(i == 0) {	// STOP
					fprintf(fp2,"(IS, %02d)\n",i);
					break;
				}

				i = SearchDirective(Tok1);

				if ( i == 0 ) {//START
					fprintf(fp2,"(AD, %02d)\n",i);
					LC = -1;
				}
				else if( i == 1 || i == 4) {  // END or LTORG
					fprintf(fp2,"(AD, %02d)\n",i);

					for( k = POOLTAB[PoolCnt]; k < LitCnt; k++) { L[k].Addr = LC++;  }

					POOLTAB[++PoolCnt] = LitCnt;
					LC--;
				}				
				break;

			case 2:  // READ, PRINT, START, ORIGIN

				i = SearchOp(Tok1);  // SEARCH IN MOTAB
				if( i == 9 || i == 10) // READ or PRINT
				{
					j = SearchSymb(Tok2);
					if(j == -1) // SYMBOL IS NOT PRESENT
					{
						fprintf(fp2,"(IS, %02d) (S, %02d)\n",i,SymbCnt);
						strcpy(S[SymbCnt++].Symb,Tok2);
					}
					else {  
						fprintf(fp2,"(IS, %02d) (S, %02d)\n",i,j);
					}
					break;
				}//END OF PROCESSING READ & PRINT

				i = SearchDirective(Tok1);  // SEARCH IN ADTAB
				if(i == 0 || i == 2) { // START or ORIGIN
					LC = atoi(Tok2)-1;
					fprintf(fp2,"(AD, %02d) (C, %02d)\n",i,LC+1);
					break;
				}
				
				break;

			case 3: //ADD-DIV, DS/DC, EQU
				if (processOP(Tok1, Tok2, Tok3)) break;				
				if (processDL(Tok2, Tok3) ) break;

				processEQU(Tok1, Tok2, Tok3);
				
				break;

			case 4:// INSTRUCTION WITH LABEL
				
					j = SearchSymb(Tok1); // Label
					if(j == -1)// SYMBOL NOT PRESENT
					{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt++].Addr = LC;
					}
					else { S[j].Addr = LC; 	}//SYMBOL PRESENT
					
					if (processOP(Tok2, Tok3, Tok4)) break;							

					break;
		}//END OF SWITCH
	LC++;
	}//END OF WHILE
	fclose(fp1);
	fclose(fp2);
}//END OF PASS-1


void display_tables()
{
	DispSymbTab();
	DispLitTab();
	DispPoolTab();
}

int main()
{
	PassOne();
	display_tables();
	printf("\nIntermediate Code\n");
	PrintFile("ic.txt");
	return 0;
}
