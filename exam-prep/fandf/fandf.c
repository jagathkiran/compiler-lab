#include <ctype.h>
#include <stdio.h>
#include <string.h>

char production[10][10];
int n;

int addToResult(char *result, char c) {
  for (int i = 0; result[i] != '\0'; i++)
    if (result[i] == c)
      return 0;
  int len = strlen(result);
  result[len] = c;
  result[len + 1] = '\0';
  return 1;
}

void first(char c, char *result) {
  if (!isupper(c)) {
    addToResult(result, c);
    return;
  }

  for (int i = 0; i < n; i++) {
    if (production[i][0] == c) {
      if (production[i][2] == '#') {
        addToResult(result, '#');
      } else if (!isupper(production[i][2])) {
        addToResult(result, production[i][2]);
      } else {
        char temp[10] = "";
        first(production[i][2], temp);
        for (int j = 0; temp[j] != '\0'; j++)
          addToResult(result, temp[j]);
      }
    }
  }
}

void follow(char c, char *result) {
  if (production[0][0] == c)
    addToResult(result, '$');

  for (int i = 0; i < n; i++) {
    for (int j = 2; production[i][j] != '\0'; j++) {
      if (production[i][j] == c) {
        if (production[i][j + 1] != '\0') {
          char f[10] = "";
          first(production[i][j + 1], f);

          for (int k = 0; f[k] != '\0'; k++) {
            if (f[k] != '#')
              addToResult(result, f[k]);
          }

          if (strchr(f, '#') != NULL) {
            char temp[10] = "";
            follow(production[i][0], temp);
            for (int k = 0; temp[k] != '\0'; k++)
              addToResult(result, temp[k]);
          }
        } else {
          if (production[i][0] != c) {
            char temp[10] = "";
            follow(production[i][0], temp);
            for (int k = 0; temp[k] != '\0'; k++)
              addToResult(result, temp[k]);
          }
        }
      }
    }
  }
}

int main() {
  char c, result[20];

  printf("Enter number of productions: ");
  scanf("%d", &n);

  printf("Enter productions (use # for epsilon, e.g., E=E+T):\n");
  for (int i = 0; i < n; i++)
    scanf("%s", production[i]);

  printf("\nEnter non-terminal for FIRST: ");
  scanf(" %c", &c);
  result[0] = '\0';
  first(c, result);
  printf("FIRST(%c) = { ", c);
  for (int i = 0; result[i] != '\0'; i++)
    printf("%c ", result[i]);
  printf("}\n");

  printf("\nEnter non-terminal for FOLLOW: ");
  scanf(" %c", &c);
  result[0] = '\0';
  follow(c, result);
  printf("FOLLOW(%c) = { ", c);
  for (int i = 0; result[i] != '\0'; i++)
    printf("%c ", result[i]);
  printf("}\n");

  return 0;
}
