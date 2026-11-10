#include <ctype.h>
#include <stdio.h>
#include <string.h>

int tempCount = 0;

void generateCode(char op, char operand1[], char operand2[], char result[]);
void intermediateCode(char *expr);

int main() {
  char expr[100];

  printf("Enter a postfix expression: ");
  scanf("%s", expr);

  intermediateCode(expr);

  return 0;
}

void generateCode(char op, char operand1[], char operand2[], char result[]) {
  sprintf(result, "t%d", tempCount);
  printf("%s = %s %c %s\n", result, operand1, op, operand2);

  tempCount++;
}

void intermediateCode(char *expr) {
  char operandStack[100][10];
  int top = -1;

  for (int i = 0; expr[i] != '\0'; i++) {
    if (isalnum((unsigned char)expr[i])) {
      char operand[2] = {expr[i], '\0'};
      strcpy(operandStack[++top], operand);
    } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
               expr[i] == '/') {

      char operand1[10], operand2[10], result[10];

      strcpy(operand2, operandStack[top--]);
      strcpy(operand1, operandStack[top--]);

      generateCode(expr[i], operand1, operand2, result);

      strcpy(operandStack[++top], result);
    }
  }
}
