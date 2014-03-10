#include <stdlib.h>
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
    PTR = '>',
    END
  } type;
  int n; /* meaningless if type != NUMBER */
} token;

void next_token(void) {
  int c;
  if ((c = getchar()) == EOF)
    token.type = END;
  if (c == '(')
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

struct mdl_node *md_node(void);
struct mdl_node *md_list(void) {
  if (token.type == END)
    return NULL;
  struct mdl_node *n = md_node();
  if (token.type == PTR) {
    next_token();
    n->next = md_list();
  }
  return n;
}

struct mdl_node *md_node(void) {
  struct mdl_node *n = malloc(sizeof(*n));
  n->val = token.n;
  n->child = n->next = NULL;
  next_token();
  if (token.type == OPEN_P) {
    next_token();
    n->child = md_list();
    if (token.type != CLOSE_P)
      fprintf(stderr, "Missing close parentheses\n");
    else
      next_token();
  }
  return n;
}

void print_list(struct mdl_node *h) {
  while (h) {
    printf("%d", h->val);
    if (h->child) {
      printf("(");
      print_list(h->child);
      printf(")");
    }
    printf("->");
    h = h->next;
  }
  printf("END");
}

int main(void) {
  next_token();
  print_list(md_list());
  printf("\n");
  return 0;
}
