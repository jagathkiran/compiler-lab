%{
    #include<stdio.h>
    extern FILE *yyin;
    int vowel = 0;
    int con = 0;
%}

%%
[aeiouAEIOU] {vowel++;}
[a-zA-Z] {con++;}
. {}
%%
int yywrap () {
  return 1;
}

int main () {
  FILE *file = fopen("input.txt","r");
  if(!file){
    perror("Cannot open file");
    return 1;
  }
  
  yyin = file;
  yylex();
  printf("Number of vowels = %d\n",vowel);
  printf("Number of consonants = %d\n",con);

  fclose(file);
  return 0;
}
