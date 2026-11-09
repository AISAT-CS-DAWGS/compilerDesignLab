#include <stdio.h>
#include <string.h>

// Array to store input string
char inputString[16];

// Integer variable to store length of input string
int inputLength;

// Array to store shift action
char shiftAction[10];

// Array to store reduction action
char reductionAction[20];

// Array to store stack
char stack[15];

void check();

int stackIndex = 0, inputIndex = 0, iteration = 0;

int main() {
  printf("GRAMMAR is \nE->E+E\nE->E*E\nE->(E)\nE->id\n");

  printf("Enter input string: ");
  scanf("%[^\n]", inputString);

  inputLength = strlen(inputString);

  strcpy(shiftAction, "SHIFT->");

  printf("Stack \t Input \t Action\n");

  for (iteration = 0; inputIndex < inputLength;
       iteration++, stackIndex++, inputIndex++) {

    if (inputString[inputIndex] == 'i' && inputString[inputIndex + 1] == 'd') {

      stack[stackIndex] = inputString[inputIndex];
      stack[stackIndex + 1] = inputString[inputIndex + 1];
      stack[stackIndex + 2] = '\0';

      inputString[inputIndex] = ' ';
      inputString[inputIndex + 1] = ' ';

      printf("\n$%s\t%s$\t%sid", stack, inputString, shiftAction);
      check();
    }

    else {
      stack[stackIndex] = inputString[inputIndex];
      stack[stackIndex + 1] = '\0';

      inputString[inputIndex] = ' ';

      printf("\n$%s\t%s$\t%ssymbols", stack, inputString, shiftAction);
      check();
    }
  }

  printf("\n");
}

void check() {
  strcpy(reductionAction, "REDUCTION TO E");

  for (int scanIndex = 0; scanIndex < inputLength; scanIndex++) {

    if (stack[scanIndex] == 'i' && stack[scanIndex + 1] == 'd') {
      stack[scanIndex] = 'E';
      stack[scanIndex + 1] = '\0';

      printf("\n$%s\t%s$\t%s", stack, inputString, reductionAction);
      inputIndex++;
    }
  }

  for (int scanIndex = 0; scanIndex < inputLength; scanIndex++) {

    if (stack[scanIndex] == 'E' && stack[scanIndex + 1] == '+' &&
        stack[scanIndex + 2] == 'E') {

      stack[scanIndex] = 'E';
      stack[scanIndex + 1] = '\0';
      stack[scanIndex + 2] = '\0';

      printf("\n$%s\t%s$\t%s", stack, inputString, reductionAction);
      stackIndex = stackIndex - 2;
    }
  }

  for (int scanIndex = 0; scanIndex < inputLength; scanIndex++) {

    if (stack[scanIndex] == 'E' && stack[scanIndex + 1] == '*' &&
        stack[scanIndex + 2] == 'E') {

      stack[scanIndex] = 'E';
      stack[scanIndex + 1] = '\0';
      stack[scanIndex + 2] = '\0';

      printf("\n$%s\t%s$\t%s", stack, inputString, reductionAction);
      stackIndex = stackIndex - 2;
    }
  }

  for (int scanIndex = 0; scanIndex < inputLength; scanIndex++) {

    if (stack[scanIndex] == '(' && stack[scanIndex + 1] == 'E' &&
        stack[scanIndex + 2] == ')') {

      stack[scanIndex] = 'E';
      stack[scanIndex + 1] = '\0';
      stack[scanIndex + 2] = '\0';

      printf("\n$%s\t%s$\t%s", stack, inputString, reductionAction);
      stackIndex = stackIndex - 2;
    }
  }
}
