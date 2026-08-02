%{
#include<stdio.h>
#include<stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token NUM
%left '+''-'
%left '*''/'

%%
expr:e {
  printf("Result:%d\n",$$);
  return 0;
}

e:e'+'e { $$ = $1 + $3; }
| e'-'e { $$=$1-$3; }
| e'*'e { $$ = $1 * $3; }
| e'/'e {
    if ($3 == 0) {
      printf("\nError: Division by Zero\n");
      exit(1);
    }
    $$ = $1 / $3;
  }
| '('e')' { $$ = $2; }
| NUM { $$ = $1;}
;
%%

int main() {
  printf("Enter the arithmatic expression\n");
  yyparse();
  printf("Valid expression\n");
  return 0;
}

void yyerror(const char *s) {
  printf("\nInvalid expression: %s\n", s);
  exit(1);
}
