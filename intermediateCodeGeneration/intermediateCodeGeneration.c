#include <ctype.h>
#include <stdio.h>

int tempCount = 0;

void generateCode(char op, char operand1, char operand2);
void intermediateCode(char *expr);

int main() {
  char expr[100];
  printf("Enter an expression: ");
  scanf("%s", expr);

  intermediateCode(expr);

  return 0;
}

void generateCode(char op, char operand1, char operand2) {
  printf("t%d = %c %c %c\n", tempCount, operand1, op, operand2);
  tempCount++;
}

void intermediateCode(char *expr) {
  char operandStack[100];
  int top = -1;

  for (int i = 0; expr[i] != '\0'; i++) {
    if (isalnum(expr[i])) {
      operandStack[++top] = expr[i];
    } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
               expr[i] == '/') {
      char operand2 = operandStack[top--];
      char operand1 = operandStack[top--];

      generateCode(expr[i], operand1, operand2);
      operandStack[++top] = 't';
    }
  }
}
