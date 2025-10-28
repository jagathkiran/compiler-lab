%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%union {int val;}
%token <val> BINARY

%%
start:
     BINARY { printf("Decimal = %d\n",$1);}
     ;
%%


void yyerror(const char *s){
  printf("Invalid\n");
  exit(0);
}

int main() {
  printf("Enter a binary : ");
  yyparse();
  return 0;
}
