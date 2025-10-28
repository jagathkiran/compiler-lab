%{
    #include<stdio.h>
    extern FILE *yyin;
    int count = 0;
    char word[50];
%}

%%
[a-zA-Z]+ {
    if(!strcmp(yytext,word)){count++;}
  }
.|\n {}
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
  
  printf("Enter the word to search : ");
  scanf("%s",word);

  getchar(); // clear input buffer

  yyin = file;
  yylex();

  printf("Number of occurances = %d\n",count);

  fclose(file);
  return 0;
}
