#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 20
#define EPSILON 'e' // Using 'e' for epsilon

int n;               // Number of productions
char prod[MAX][MAX]; // Productions
char nonTerminals[MAX];
int ntCount = 0;
char first[MAX][MAX];
char follow[MAX][MAX];

// Add character to a set if not already present
void add(char *set, char c) {
  if (!strchr(set, c)) {
    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
  }
}
// Print set with commas between characters
void printSet(char *set) {
  for (int i = 0; set[i]; i++) {
    printf("%c", set[i]);
    if (set[i + 1])
      printf(", ");
  }
}
// Find all non-terminals
void findNonTerminals() {
  for (int i = 0; i < n; i++)
    if (!strchr(nonTerminals, prod[i][0]))
      add(nonTerminals, prod[i][0]);
  ntCount = strlen(nonTerminals);
}

// Recursive function to compute FIRST of a symbol
void findFirst(char symbol, char *res) {
  if (!isupper(symbol)) { // Terminal
    add(res, symbol);
    return;
  }

  for (int i = 0; i < n; i++) {
    if (prod[i][0] == symbol) {
      char *rhs = prod[i] + 3; // Skip 'A->'
      if (rhs[0] == EPSILON)
        add(res, EPSILON);
      else {
        for (int j = 0; rhs[j]; j++) {
          char temp[MAX] = "";
          findFirst(rhs[j], temp);
          for (int k = 0; temp[k]; k++)
            if (temp[k] != EPSILON)
              add(res, temp[k]);
          if (!strchr(temp, EPSILON))
            break; // Stop if epsilon not present
          if (!rhs[j + 1])
            add(res, EPSILON); // All symbols can be epsilon
        }
      }
    }
  }
}

// Iterative function to compute FOLLOW sets
void findFollowSets() {
  // Initialize FOLLOW sets
  for (int i = 0; i < ntCount; i++)
    follow[i][0] = '\0';

  add(follow[0], '$'); // Start symbol

  int changed;
  do {
    changed = 0;
    for (int i = 0; i < n; i++) {
      char lhs = prod[i][0];
      char *rhs = prod[i] + 3;

      for (int j = 0; rhs[j]; j++) {
        if (isupper(rhs[j])) {
          int idx = -1;
          for (int t = 0; t < ntCount; t++)
            if (nonTerminals[t] == rhs[j])
              idx = t;

          int oldLen = strlen(follow[idx]);

          // Look at symbols after rhs[j]
          int k = j + 1;
          int addFollow = 0;
          while (rhs[k]) {
            if (isupper(rhs[k])) {
              char temp[MAX] = "";
              findFirst(rhs[k], temp);
              int epsilon = 0;
              for (int t = 0; temp[t]; t++) {
                if (temp[t] != EPSILON)
                  add(follow[idx], temp[t]);
                else
                  epsilon = 1;
              }
              if (!epsilon)
                break;
            } else {
              add(follow[idx], rhs[k]);
              break;
            }
            k++;
            if (!rhs[k])
              addFollow = 1; // If end reached
          }

          if (!rhs[j + 1] || addFollow) {
            int lhsIdx = -1;
            for (int t = 0; t < ntCount; t++)
              if (nonTerminals[t] == lhs)
                lhsIdx = t;
            for (int t = 0; follow[lhsIdx][t]; t++)
              add(follow[idx], follow[lhsIdx][t]);
          }

          if (strlen(follow[idx]) > oldLen)
            changed = 1;
        }
      }
    }
  } while (changed);
}

int main() {
  printf("Enter number of productions: ");
  scanf("%d", &n);
  printf("Enter productions (use 'e' for epsilon):\n");
  for (int i = 0; i < n; i++)
    scanf("%s", prod[i]);

  findNonTerminals();

  printf("\nFIRST sets:\n");
  for (int i = 0; i < ntCount; i++) {
    char res[MAX] = "";
    findFirst(nonTerminals[i], res);
    strcpy(first[i], res);
    printf("FIRST(%c) = { ", nonTerminals[i]);
    printSet(res);
    printf(" }\n");
  }

  findFollowSets();
  printf("\nFOLLOW sets:\n");
  for (int i = 0; i < ntCount; i++) {
    printf("FOLLOW(%c) = { ", nonTerminals[i]);
    printSet(follow[i]);
    printf(" }\n");
  }

  return 0;
}
