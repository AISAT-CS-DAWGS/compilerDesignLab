#include <stdio.h>

int main() {
  FILE *mcode = fopen("machinecode.txt", "w");
  char tac[20][20], quad[20][40], op, oper[10][10];
  int n;

  printf("Enter the number of lines: ");
  scanf("%d", &n);

  printf("Enter the code: ");
  for (int i = 0; i < n; i++) {
    scanf("%s", tac[i]);
    quad[i][1] = tac[i][2];

    if (tac[i][3] != '\0') {
      quad[i][2] = tac[i][4];
      quad[i][0] = tac[i][3];
    } else {
      quad[i][2] = '_';
      quad[i][0] = '=';
    }
    quad[i][3] = tac[i][0];
  }

  printf("\nQuadruples: \n");
  printf("op\targ1\targ2\tresult\n");
  for (int i = 0; i < n; i++) {
    printf("\n");
    for (int j = 0; j < 4; j++) {
      printf("%c \t", quad[i][j]);
    }
  }
  for (int i = 0; i < n; i++) {
    fprintf(mcode, "MOV R%d, %c\n", i, quad[i][1]);
    op = quad[i][0];

    if (op != '=') {
      switch (op) {
      case '+':
        fprintf(mcode, "ADD R%d, %c\n", i, quad[i][2]);
        break;

      case '-':
        fprintf(mcode, "SUB R%d, %c\n", i, quad[i][2]);
        break;
      case '/':
        fprintf(mcode, "DIV R%d, %c\n", i, quad[i][2]);
        break;
      case '*':
        fprintf(mcode, "MUL R%d, %c\n", i, quad[i][2]);
        break;
      }
    }
    fprintf(mcode, "MOV %c, R%d\n", quad[i][3], i);
  }

  printf("\nTAC\n");
  for (int i = 0; i < n; i++) {
    printf("%s\n", tac[i]);
  }

  return 0;
}
