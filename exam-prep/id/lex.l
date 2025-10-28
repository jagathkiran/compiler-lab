%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* {return ID;}
[ \t\n]+ {}
. {return INVALID;}
%%

int yywrap () {
  return 1;
}

