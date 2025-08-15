%{
#include<stdio.h>
int l=1,w=1,c=0;
%}
%%
[A-Za-z0-9] {c++;}
[\t]+[ ]+ {w++;}
[\n] {l++;}
[.] {
printf("Number of Lines : %d\n",l);
printf("Number of Words : %d\n",w);
printf("Number of Characters : %d\n",c);
return 0;
}
%%
int yywrap(){
return 1;
}
int main(){
printf("Enter the text \n");
yylex();
return 0;
}
