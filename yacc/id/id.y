%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}
%token IDENTIFIER INVALID
%%
start:
    IDENTIFIER { printf("Valid identifier\n"); return 0; }
    | INVALID  { printf("Invalid identifier\n"); return 0; }
    ;
%%
void yyerror(const char *s) {
    printf("Invalid identifier\n");
    exit(0);
}
int main() {
    printf("Enter an identifier: ");
    yyparse();
    return 0;
}
