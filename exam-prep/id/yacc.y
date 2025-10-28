%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token ID INVALID

%%
start:
     ID { printf("Valid Identifier\n"); return 0;}
     INVALID { printf("Invalid Identifier\n"); return 0;}
     ;
%%


void yyerror(const char *s){
  printf("Invalid Identifier\n");
  exit(0);
}

int main() {
  printf("Enter an Identifier: ");
  yyparse();
  return 0;
}
