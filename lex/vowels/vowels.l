%{
#include<stdio.h>
int v=0,c=0;
%}
%%
[aeiouAEIOU] {v++;}
[A-Za-z] {c++;}
[\n] {
printf("Number of vowels : %d \n",v);
printf("Number of consonants : %d \n",c);
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

