#include <ctype.h>
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
  c = getchar();
  if (c == '(')
    token.type = OPEN_P;
  else if (c == ')')
    token.type = CLOSE_P;
  else if (c == '>')
    token.type = PTR;
  else if (isdigit(c)) {
    ungetc(c, stdin);
    scanf("%d", &token.n);
    token.type = NUMBER;
  }
  else
    token.type = END;
}

struct mdl_node *md_node(void);
struct mdl_node *md_list(void) {
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

/* The magical piece of code */
struct mdl_node *flatten_aux(struct mdl_node *);
struct mdl_node *flatten(struct mdl_node *h) {
  flatten_aux(h);
  return h;
}

struct mdl_node *flatten_aux(struct mdl_node *head) {
  struct mdl_node *n = head;
  struct mdl_node *last, *prev;
  while (n) {
    if (n->child) {
      last = flatten_aux(n->child);
      last->next = n->next;
      n->next = n->child;
      n = last->next;
      prev = last;
    }
    else {
      prev = n;
      n = n->next;
    }
  }
  return prev;
}

int main(void) {
  next_token();
  struct mdl_node *head = md_list();
  printf("Read md_list:\n");
  print_list(head);
  fflush(stdout);
  head = flatten(head);
  printf("\nFlattened version:\n");
  /* Degenerated md_list now, can't use regular print */
  for (struct mdl_node *n = head; n; n = n->next)
    printf("%d->", n->val);
  printf("END\n");
  return 0;
}
