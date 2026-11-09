#include <ctype.h>
#include <stdio.h>
#include <string.h>

int productionCount, resultCount;
char productions[10][10], result[10];

void first(char symbol);
void follow(char symbol);

int main() {
  char symbol;
  int choice;

  printf("Enter the number of productions: ");
  scanf("%d", &productionCount);

  printf("Enter the productions (example: E=E+T): \n");
  for (int i = 0; i < productionCount; i++) {
    scanf("%s", productions[i]);
  }

  do {
    resultCount = 0;

    printf("\nEnter the element whose FIRST and FOLLOW is to be found: ");
    scanf(" %c", &symbol);

    first(symbol);

    printf("FIRST(%c) = { ", symbol);
    for (int i = 0; i < resultCount; i++) {
      printf("%c ", result[i]);
    }
    printf("}\n");

    strcpy(result, " ");
    resultCount = 0;

    follow(symbol);

    printf("FOLLOW(%c) = { ", symbol);
    for (int i = 0; i < resultCount; i++) {
      printf("%c ", result[i]);
    }
    printf("}\n");

    printf("Continue? (1 = yes / 0 = no): ");
    scanf("%d", &choice);
  } while (choice == 1);

  return 0;
}

void first(char symbol) {
  if (!isupper(symbol)) {
    result[resultCount++] = symbol;
    return;
  }

  for (int i = 0; i < productionCount; i++) {
    if (productions[i][0] == symbol) {
      if (productions[i][2] == '$') {
        follow(productions[i][0]);
      } else if (islower(productions[i][2])) {
        result[resultCount++] = productions[i][2];
      } else {
        first(productions[i][2]);
      }
    }
  }
}

void follow(char symbol) {
  if (productions[0][0] == symbol) {
    result[resultCount++] = '$';
  }

  for (int i = 0; i < productionCount; i++) {
    for (int j = 2; j < strlen(productions[i]); j++) {
      if (productions[i][j] == symbol) {
        if (productions[i][j + 1] != '\0') {
          first(productions[i][j + 1]);
        }
        if (productions[i][j + 1] == '\0' && symbol != productions[i][0]) {
          follow(productions[i][0]);
        }
      }
    }
  }
}
