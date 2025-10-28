%{
#include "y.tab.h"
%}

%%
[01]+ {yylval.val = strtol(yytext, NULL, 2); return BINARY;}
\n { return 0;}
. {}
%%

int yywrap () {
  return 1;
}

