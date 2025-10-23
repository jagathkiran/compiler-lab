%{
#include "y.tab.h"
%}
%%
[a-zA-Z][a-zA-Z0-9]*    { return IDENTIFIER; }
[ \t\n]+                { /* Skip whitespace */ }
.                       { return INVALID; }
%%
int yywrap() {
    return 1;
}
