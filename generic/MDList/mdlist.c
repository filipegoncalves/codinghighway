#include <stdio.h>

struct mdl_node {
  int val;
  struct mdl_node *child;
  struct mdl_node *next;
};

struct mdl_token {
  enum token_type {
    NUMBER,
    OPEN_P = '(',
    CLOSE_P = ')',
    PTR = '>'
  } type;
  int n; /* meaningless if type != NUMBER */
} token;

void next_token(void) {
  int c;
  if ((c = getchar()) == '(')
    token.type = OPEN_P;
  else if (c == ')')
    token.type = CLOSE_P;
  else if (c == '>')
    token.type = PTR;
  else {
    ungetc(c, stdin);
    scanf("%d", &token.n);
    token.type = NUMBER;
  }
}

int main(void) {
  int c;
  while ((c = getchar()) != EOF) {
    ungetc(c, stdin);
    next_token();
    printf("Read token: ");
    if (token.type == NUMBER)
      printf("%d", token.n);
    else if (token.type == OPEN_P)
      printf("(");
    else if (token.type == CLOSE_P)
      printf(")");
    else
      printf("->");
    printf("\n");
  }
  return 0;
}
