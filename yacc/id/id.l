%{
#include "y.tab.h"
%}
%%
[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
[ \t\n]                 { return yytext[0]; }
%%
int yywrap() {
    return 1;
}
