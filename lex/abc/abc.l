%{
#include<stdio.h>
%}
%%
abc {printf("ABC");}
[A-Za-z] {ECHO;}
[\n] {
printf("\n");
return 0;
}
%%
int yywrap(){
return 1;
}
int main(){
printf("Enter the text\n");
yylex();
return 0;
}

