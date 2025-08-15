%{
#include "y.tab.h"
%}

%%
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
[ \t]+ ;
\n {return '\n';}
"=" {return '=';}
"(" {return '(';}
")" {return ')';}
"+" {return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
. {printf("Invalid character: %s\n", yytext);}
%%
int yywrap() {
	return 1;
}
