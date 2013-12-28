#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define strcmp(a,R,b) (strcmp(a,b) R 0)
#define MAXTOKENLEN 50
#define STACKSIZE 100
#define TYPE 0
#define QUALIFIER 1
#define IDENTIFIER 2
#define push(s,t,a) s[(t)++] = a
#define pop(s,t) s[--(t)]
#define stackempty(t) ((t) == 0)
#define stackfull(t) ((t) == STACKSIZE)

struct token {
	unsigned char type;
	char string[MAXTOKENLEN];
};

struct token last;

void read_to_ID(struct token *stack, int *top);
void parse_declarator(struct token *stack, int *top);
void do_parse(void);

int main(void) {
	while (1) {
		printf("> ");
		do_parse();
		printf("\n");
	}
	return 0;
}

void do_parse(void) {
	struct token stack[STACKSIZE];
	int top = 0;
	read_to_ID(stack, &top);
	parse_declarator(stack, &top);
}

int classify_string(void) {
	char *str = last.string;
	if (strcmp(str, ==, "const")) { /* We call const "read-only" to clarify */
		strcpy(last.string, "read-only");
		return QUALIFIER;
	}
	else if	(strcmp(str, ==, "volatile"))
		return QUALIFIER;
	if (strcmp(str, ==, "int") ||
		strcmp(str, ==, "short") ||
		strcmp(str, ==, "char") ||
		strcmp(str, ==, "float") ||
		strcmp(str, ==, "double") ||
		strcmp(str, ==, "void") ||
		strcmp(str, ==, "signed") ||
		strcmp(str, ==, "unsigned") ||
		strcmp(str, ==, "long") ||
		strcmp(str, ==, "struct") ||
		strcmp(str, ==, "union") ||
		strcmp(str, ==, "enum"))
		return TYPE;
	return IDENTIFIER;
}

void gettoken(void) {
	int c;
	int i = 0;
	/* Ignore white spaces */
	while (isspace(c = getchar()) && c != EOF && c != '\n');
	if (c == EOF)
		exit(0);
	last.string[i++] = c;
	if (isalpha(c)) {
		for (; isalnum(c = getchar()) && i < MAXTOKENLEN-1; last.string[i++] = c);
		ungetc(c, stdin); /* pushes back the excess character read */
	}
	last.string[i] = '\0';
	if (isalpha((unsigned char) last.string[0]))
		last.type = classify_string();
	else {
		last.type = last.string[0];
		if (last.type == '*') {
			/* Make string contain "pointer to", otherwise, qualified pointers would be printed as '*' */
			strcpy(last.string, "pointer to");
		}
	}
}

void read_to_ID(struct token *stack, int *top) {
	for (gettoken(); last.type != IDENTIFIER && !stackfull(*top); push(stack, *top, last), gettoken());
	printf("%s: ", last.string);
	gettoken();
}

void read_array_size(void) {
	char buf[MAXTOKENLEN];
	int c, i = 0;
	while ((c = getchar()) != ']' && i < MAXTOKENLEN-1)
		buf[i++] = c;
	buf[i] = '\0';
	gettoken();
	printf("array of %s ", buf);
}

void read_function_args(void) {
	struct token stack[STACKSIZE];
	int top, c;
	if ((c = getchar()) == ')') {
		printf("function returning ");
		return;
	}
	ungetc(c, stdin);
	printf("function receiving ");
	do {
		top = 0;
		read_to_ID(stack, &top);
		parse_declarator(stack, &top);
		if (last.type == ',')
			printf("and ");
	} while (last.type == ',');
	if (last.type != ')')
		fprintf(stderr, "Warning: missing close parentheses in function\n");
	gettoken();
	printf("and returning ");
}

void check_ptr(struct token *stack, int *top) {
	struct token t;
	if (stackempty(*top))
		return;
	for (t = pop(stack, *top); t.type == '*'; t = pop(stack, *top))
		printf("pointer to ");
	push(stack, *top, t);
}	

void parse_declarator(struct token *stack, int *top) {
	struct token t;
	if (last.type == '[')
		while (last.type == '[')
			read_array_size();
	else if (last.type == '(')
		read_function_args();
	check_ptr(stack, top);
	while (!stackempty(*top)) {
		t = pop(stack, *top);
		if (t.type == '(') {
			if (last.type != ')')
				fprintf(stderr, "Warning: missing close parentheses\n");
			gettoken();
			parse_declarator(stack, top); /* Recursively parse this ( dcl ) */
		} else
			printf("%s ", t.string);
	}
}
