%{
#include <stdio.h>
#include <string.h>
extern FILE *yyin;
char* keywords[] = {
"int", "float", "char", "if", "else", "while", "return", "for", "void", "main"
};
int is_keyword(char* word) {
for (int i = 0; i < sizeof(keywords)/sizeof(char*); i++) {
if (strcmp(word, keywords[i]) == 0)
return 1;
}
return 0;
}
%}
%%
[ \t\n]+ ;
"//".* ;
"/*"([^*]|\*+[^*/])*\*+"/" ;
^#[^\n]* { printf("Preprocessor Directive: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* {
if (is_keyword(yytext))
printf("Keyword: %s\n", yytext);
else
printf("Identifier: %s\n", yytext);
}
[0-9]+(\.[0-9]+)? { printf("operand: %s\n", yytext); }
"=="|"!="|"<="|">="|"="|"<"|">" { printf("Operator: %s\n", yytext); }
"+"|"-"|"*"|"/"|"%" { printf("Operator: %s\n", yytext); }
";"|","|"("|")"|"{"|"}" { printf("Seperator: %s\n", yytext); }
. { printf("Unknown: %s\n", yytext); }
%%
int yywrap() {
return 1;
}
int main() {
FILE *file = fopen("input.c", "r");
if (!file) {
perror("Cannot open file");
return 1;
}
yyin = file;
yylex();
fclose(file);
return 0;
}

