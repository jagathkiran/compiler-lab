#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *keywords[] = {"int",   "float", "char", "if",    "else",
                    "while", "for",   "void", "return"};
int numKeywords = 9;

int isKeyword(char *str) {
  for (int i = 0; i < numKeywords; i++) {
    if (strcmp(str, keywords[i]) == 0)
      return 1;
  }
  return 0;
}

int isOperator(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' ||
          ch == '<' || ch == '>' || ch == '!');
}

int isSpecial(char ch) {
  return (ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' ||
          ch == '}' || ch == '[' || ch == ']');
}

int main() {
  FILE *fp = fopen("input.c", "r");
  if (!fp) {
    perror("Cannot Open file");
    return 1;
  }

  char ch, buffer[100];
  int i = 0;

  while ((ch = fgetc(fp)) != EOF) {
    if (ch == ' ' || ch == '\t' || ch == '\n')
      continue;

    if (ch == '"') {
      buffer[i++] = ch;
      while ((ch = fgetc(fp)) != EOF && ch != '"')
        buffer[i++] = ch;
      buffer[i++] = ch;
      buffer[i] = '\0';
      i = 0;
      printf("Literal: %s\n", buffer);
    } else if (isalpha(ch) || ch == '_') {
      buffer[i++] = ch;
      while ((ch = fgetc(fp)) != EOF && (isalnum(ch) || ch == '_'))
        buffer[i++] = ch;
      buffer[i] = '\0';
      i = 0;

      if (isKeyword(buffer))
        printf("Keyword: %s\n", buffer);
      else
        printf("Identifier: %s\n", buffer);
      ungetc(ch, fp);

    } else if (isdigit(ch)) {
      buffer[i++] = ch;
      while ((ch = fgetc(fp)) != EOF && (isdigit(ch) || ch == '.'))
        buffer[i++] = ch;
      buffer[i] = '\0';
      i = 0;
      printf("Number: %s\n", buffer);
      ungetc(ch, fp);

    } else if (isOperator(ch)) {
      printf("Operator: %c\n", ch);

    } else if (isSpecial(ch)) {
      printf("Special Character: %c\n", ch);
    }
  }

  fclose(fp);
  return 0;
}
