%{
#include "y.tab.h"
%}

%%
[0-9]+ {yylval.val = atoi(yytext); return NUMBER;}
[ \t]+ ;
"\n" {return '\n';}
"=" {return '=';}
"(" {return '(';}
")" {return ')';}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
. { printf("Invalid character: %s\n",yytext);}
%%

int yywrap () {
  return 1;
}

