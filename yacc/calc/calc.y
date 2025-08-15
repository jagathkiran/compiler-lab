%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
int yyerror(const char *s);
%}
%union { int val;}

%token <val> NUMBER 
%type <val> exp
%left '+' '-'
%left '*' '/'

%%
input:
	exp '\n' {printf("valid expression: %d\n",$1); return 0;}

;
exp:
	exp'+'exp {$$ = $1 + $3;}
	|exp'-'exp {$$ = $1 - $3;}
	|exp'*'exp {$$ = $1 * $3;}
	|exp'/'exp {$$ = $1 / $3;}
	|'('exp')' {$$ = $2;}
	|NUMBER {$$ = $1;}
	;
%%

int yyerror(const char *s) {
	printf("Invalid Expression\n");
}

int main() {
	printf("Enter arithmatic expression : \n");
	yyparse();
}
