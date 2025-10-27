%{
#include <stdio.h>
int char_count = 0;
int word_count = 0;
int line_count = 0;
%}
%%
[a-zA-Z0-9]+ { word_count++; char_count += yyleng; }
[ \t]+ { }
\n { line_count++; }
. { char_count++; }
%%
int yywrap() {
return 1;
}
int main() {
printf("Enter text (Ctrl+D to end input):\n");
yylex();
printf("\nTotal characters (excluding spaces/tabs):
%d\n"
, char_count);
printf("Total words: %d\n"
, word_count);
printf("Total lines: %d\n"
, line_count);
return 0;
}
