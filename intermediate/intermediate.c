#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 100
#define STACK_SIZE 50
#define MAX_CODE_LINES 50

// --- Data Structures for Representations ---
struct Quadruple {
  char *op;
  char *arg1;
  char *arg2;
  char *result;
};

struct Triple {
  char *op;
  char *arg1;
  char *arg2;
};

// --- Global Arrays to Store Generated Code ---
struct Quadruple quads[MAX_CODE_LINES];
int quad_count = 0;

struct Triple triples[MAX_CODE_LINES];
int triple_count = 0;

// --- Stack for Operators (char) ---
struct CharStack {
  char items[STACK_SIZE];
  int top;
};

void pushChar(struct CharStack *s, char item) {
  if (s->top < STACK_SIZE - 1)
    s->items[++(s->top)] = item;
}
char popChar(struct CharStack *s) {
  return (s->top > -1) ? s->items[(s->top)--] : '\0';
}
char peekChar(struct CharStack *s) {
  return (s->top > -1) ? s->items[s->top] : '\0';
}

// --- Stack for Operands (char*) ---
struct StringStack {
  char *items[STACK_SIZE];
  int top;
};

void pushString(struct StringStack *s, const char *item) {
  if (s->top < STACK_SIZE - 1)
    s->items[++(s->top)] = strdup(item);
}
char *popString(struct StringStack *s) {
  return (s->top > -1) ? s->items[(s->top)--] : NULL;
}

// --- Helper to format an argument for a Triple ---
// Converts "t0", "t1", etc., to "(0)", "(1)" for triple representation
char *format_triple_arg(const char *arg) {
  if (arg[0] == 't') {
    char *formatted_arg = malloc(10);
    sprintf(formatted_arg, "(%c)", arg[1]);
    return formatted_arg;
  }
  return strdup(arg);
}

// --- Helper Functions ---
int getPrecedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*' || op == '/')
    return 2;
  return 0;
}

char *newTemp() {
  static int count = 0;
  char tempName[10];
  sprintf(tempName, "t%d", count++);
  return strdup(tempName);
}

// --- Core Logic ---
void generateCode(const char *expression, char *finalResultName) {
  struct CharStack operators = {.top = -1};
  struct StringStack operands = {.top = -1};

  for (int i = 0; expression[i] != '\0'; ++i) {
    char token = expression[i];
    if (isspace(token))
      continue;

    if (isalnum(token)) {
      char operand[MAX_EXPR_SIZE] = {0};
      int j = 0;
      while (isalnum(expression[i]))
        operand[j++] = expression[i++];
      i--;
      pushString(&operands, operand);
    } else if (token == '(') {
      pushChar(&operators, token);
    } else if (token == ')') {
      while (operators.top > -1 && peekChar(&operators) != '(') {
        char op_char = popChar(&operators);
        char op_str[2] = {op_char, '\0'};
        char *op2 = popString(&operands);
        char *op1 = popString(&operands);
        char *result = newTemp();

        // Add to Quads
        quads[quad_count++] = (struct Quadruple){strdup(op_str), strdup(op1),
                                                 strdup(op2), strdup(result)};
        // Add to Triples
        triples[triple_count++] = (struct Triple){
            strdup(op_str), format_triple_arg(op1), format_triple_arg(op2)};

        pushString(&operands, result);
        free(op1);
        free(op2);
        free(result);
      }
      popChar(&operators);
    } else { // Operator
      while (operators.top > -1 && peekChar(&operators) != '(' &&
             getPrecedence(peekChar(&operators)) >= getPrecedence(token)) {
        char op_char = popChar(&operators);
        char op_str[2] = {op_char, '\0'};
        char *op2 = popString(&operands);
        char *op1 = popString(&operands);
        char *result = newTemp();

        // Add to Quads & Triples
        quads[quad_count++] = (struct Quadruple){strdup(op_str), strdup(op1),
                                                 strdup(op2), strdup(result)};
        triples[triple_count++] = (struct Triple){
            strdup(op_str), format_triple_arg(op1), format_triple_arg(op2)};
        pushString(&operands, result);
        free(op1);
        free(op2);
        free(result);
      }
      pushChar(&operators, token);
    }
  }

  while (operators.top > -1) {
    char op_char = popChar(&operators);
    char op_str[2] = {op_char, '\0'};
    char *op2 = popString(&operands);
    char *op1 = popString(&operands);
    char *result = newTemp();

    // Add to Quads & Triples
    quads[quad_count++] = (struct Quadruple){strdup(op_str), strdup(op1),
                                             strdup(op2), strdup(result)};
    triples[triple_count++] = (struct Triple){
        strdup(op_str), format_triple_arg(op1), format_triple_arg(op2)};

    pushString(&operands, result);
    free(op1);
    free(op2);
    free(result);
  }

  if (operands.top > -1)
    strcpy(finalResultName, operands.items[operands.top]);
  while (operands.top > -1)
    free(popString(&operands));
}

// --- Printing and Reset Functions ---
void printAndReset() {
  printf("Three-Address Code:\n");
  for (int i = 0; i < quad_count; i++) {
    printf("%s = %s %s %s\n", quads[i].result, quads[i].arg1, quads[i].op,
           quads[i].arg2);
  }
  printf("\n");

  printf("Quadruple Representation:\n");
  printf("   | %-8s | %-8s | %-8s | %-8s\n", "Operator", "Arg1", "Arg2",
         "Result");
  printf("---------------------------------------------------\n");
  for (int i = 0; i < quad_count; i++) {
    printf("%-2d | %-8s | %-8s | %-8s | %-8s\n", i, quads[i].op, quads[i].arg1,
           quads[i].arg2, quads[i].result);
    free(quads[i].op);
    free(quads[i].arg1);
    free(quads[i].arg2);
    free(quads[i].result);
  }
  quad_count = 0;
  printf("\n");

  printf("Triple Representation:\n");
  printf("   | %-8s | %-8s | %-8s\n", "Operator", "Arg1", "Arg2");
  printf("----------------------------------------\n");
  for (int i = 0; i < triple_count; i++) {
    printf("%-2d | %-8s | %-8s | %-8s\n", i, triples[i].op, triples[i].arg1,
           triples[i].arg2);
    free(triples[i].op);
    free(triples[i].arg1);
    free(triples[i].arg2);
  }
  triple_count = 0;
}

int main() {
  FILE *file = fopen("input.txt", "r");
  if (!file) {
    perror("Error opening file");
    return 1;
  }

  char line[MAX_EXPR_SIZE];
  int lineNum = 1;
  while (fgets(line, sizeof(line), file)) {
    line[strcspn(line, "\n")] = 0;

    printf("--- Expression %d: %s ---\n", lineNum++, line);

    char *equalsPos = strchr(line, '=');
    if (equalsPos) {
      char *rhs = equalsPos + 1;
      *equalsPos = '\0';
      char *lhs = line;
      char finalResult[20] = {0};

      generateCode(rhs, finalResult);

      if (strlen(finalResult) > 0) {
        // Add the final assignment to the code lists
        quads[quad_count++] = (struct Quadruple){
            strdup("="), strdup(finalResult), strdup(""), strdup(lhs)};
        triples[triple_count++] = (struct Triple){
            strdup("="), format_triple_arg(finalResult), strdup(lhs)};
      } else { // Handle simple assignment like a = b
        quads[quad_count++] = (struct Quadruple){strdup("="), strdup(rhs),
                                                 strdup(""), strdup(lhs)};
        triples[triple_count++] =
            (struct Triple){strdup("="), strdup(rhs), strdup(lhs)};
      }
    } else {
      char finalResult[20] = {0};
      generateCode(line, finalResult);
    }

    printAndReset();
    printf("\n");
  }

  fclose(file);
  return 0;
}
