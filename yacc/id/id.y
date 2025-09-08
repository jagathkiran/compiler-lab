%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}
%token IDENTIFIER
%%
start:
    IDENTIFIER { printf("Valid identifier\n"); return 0; }
    ;
%%
void yyerror(const char *s) {
    printf("Invalid identifier\n");
}
int main() {
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}
