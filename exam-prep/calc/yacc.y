%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%union {int val;}
%token <val> NUMBER
%type <val> expr
%left '+' '-'
%left '*' '/'

%%
start:
     expr '\n' { printf("%d\n",$1); return 0;}
;
expr:
    expr '+' expr {$$ = $1 + $3;}
    |expr '-' expr {$$ = $1 - $3;}
    |expr '*' expr {$$ = $1 * $3;}
    |expr '/' expr {$$ = $1 / $3;}
    |'('expr')' {$$ = $2;}
    |NUMBER {$$ = $1;}
    ;
%%


void yyerror(const char *s){
  printf("Invalid Expression\n");
  exit(0);
}

int main() {
  printf("Enter the expression : ");
  yyparse();
  return 0;
}
