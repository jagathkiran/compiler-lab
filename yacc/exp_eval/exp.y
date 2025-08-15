%{
#include<stdio.h>
#include<stdlib.h>

int yylex();
int yyerror(const char *s);
%}

%token NUMBER ID
%left '+' '-'
%left '*' '/'

%%
input:
	stmt '\n' {printf("valid expression\n"); return 0;}

;
stmt: 
	exp
	|ID '=' exp
	;
exp:
	exp'+'exp 
	|exp'-'exp 
	|exp'*'exp 
	|exp'/'exp 
	|'('exp')' 
	|NUMBER
	|ID
	;
%%

int yyerror(const char *s) {
	printf("Invalid Expression\n");
}

int main() {
	printf("Enter arithmatic expression : \n");
	yyparse();
}
