
/* This code has been developed for educational purposes only
 * It makes dangerous assumptions to be used in a production environment (no buffer limit tests are performed)
 * This must be compiled with gcc, or any other compiler supporting __VA_ARGS__ extension in macros definition
 * HOW TO USE:
 * Compile; run the program
 * Write a valid C declaration (there is no error checking, if input is mal-formed, the parser gets confused)
 * Any declaration is supported. You can omit identifiers names if you want. The parser supports structs, enums and unions
 * in a very primitive way, by the sole use of the keyword struct, enum, or union. So, instead of struct foo x, input should be
 * struct x. Do NOT include ; in the end
 * Please don't specify any storage-class specifiers (extern, static, register, typedef, auto)
 * Enjoy! And study the code!
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define strcmp(a,R,b) (strcmp(a,b) R 0)
#define type_or_qualifier(token) (strcmp(token, ==, "volatile") || strcmp(token, ==, "int") || strcmp(token, ==, "short") || strcmp(token, ==, "char") || strcmp(token, ==, "float") || strcmp(token, ==, "double") || \
	strcmp(token, ==, "void") || strcmp(token, ==, "signed") || strcmp(token, ==, "unsigned") || strcmp(token, ==, "long") || strcmp(token, ==, "struct") || strcmp(token, ==, "union") || strcmp(token, ==, "enum") || \
	strcmp(token, ==, "const"))
#define print_spaces(d) do { \
	int x = d; \
		while (x--) { \
			putchar(' '); \
			putchar(' '); \
		} \
	} while (0);
#define pprintf(str, ...) do { \
		if (init) { \
			print_spaces(depth); \
			init = 0; \
		} \
		printf(str, ##__VA_ARGS__); \
	} while (0);
#define MAXTOKEN 512

int depth;
int init;

void decl(void);

int main(void) {
	while (1) {
		depth = 0;
		init = 1;
		printf("> ");
		decl();
		printf("\n");
	}
	return 0;
}

void type(char *buf);
void dcl(void);
void gettoken(void);

char token[MAXTOKEN];

void decl(void) {
	char decl_type[MAXTOKEN];
	decl_type[0] = '\0';
	gettoken();
	type(decl_type);
	dcl();
	pprintf("%s\n", decl_type);
}

void gettoken(void) {
	int c, i;
	while (isspace(c = getchar()) && c != '\n');
	i = 0;
	token[i++] = c;
	if (isalpha(c)) {
		for (; isalnum(c = getchar()); token[i++] = c);
		ungetc(c, stdin);
	}
	token[i] = '\0';		
}

void type(char *buf) {
	for (; ; gettoken()) {
		if (strcmp(token, ==, "const")) { /* We call const "read-only" to clarify */
			strcat(buf, "read-only ");
		}
		else if	(type_or_qualifier(token)) {
			strcat(buf, token);
			strcat(buf, " ");
		}
		else
			break;
	}
}

void direct_dcl(void);
char *ptr(char *pointers);
void dcl(void) {
	char pointers[MAXTOKEN];
	ptr(pointers);
	direct_dcl();
	pprintf("%s", pointers);
}

char *ptr(char *pointers) {
	char *p;
	if (token[0] == '*') {
		gettoken();
		p = ptr(pointers);
		return p+sprintf(p, "pointer to ");
	}
	else if (strcmp(token, ==, "const")) {
		gettoken();
		p = ptr(pointers);
		return p+sprintf(p, "read-only ");
	}
	else if (strcmp(token, ==, "volatile")) {
		gettoken();
		p = ptr(pointers);
		return p+sprintf(p, "volatile ");
	}
	else {
		*pointers = '\0';
		return pointers;
	}
}

void read_array_size(void);
void read_function_args(void);
void direct_dcl(void) {
	if (token[0] == '(') {
		gettoken();
		if (token[0] == ')' || type_or_qualifier(token))
			read_function_args();
		else
			dcl();
		if (token[0] != ')')
			fprintf(stderr, "Warning: missing close parentheses\n");
		else
			gettoken();
	}
	if (isalpha((unsigned char) token[0])) {
		pprintf("%s: ", token);
		gettoken();
	}
	if (token[0] == '[') {
		gettoken();
		read_array_size();
	}
	if (token[0] == '(') {
		gettoken();
		read_function_args();
		if (token[0] != ')')
			fprintf(stderr, "Warning: missing close parentheses in function\n");
		else
			gettoken();
	}
}


void read_array_size(void) {
	pprintf("array of ");
	while (isdigit((unsigned char) token[0])) {
		putchar((unsigned char) token[0]);
		gettoken();
	}
	putchar(' ');
	if (token[0] != ']')
		fprintf(stderr, "Warning: missing close bracket\n");
	else
		gettoken();
	if (token[0] == '[') {
		gettoken();
		read_array_size();
	}
}

void read_function_args(void) {
	char decl_type[MAXTOKEN];
	int args_left = 1;
	if (token[0] == ')') {
		pprintf("function returning ");
		return;
	}
	pprintf("function receiving:\n");
	depth++;
	while (args_left) {
		init = 1;
		decl_type[0] = '\0';
		type(decl_type);
		dcl();
		pprintf("%s\n", decl_type);
		if (token[0] == ',')
			gettoken();
		else
			args_left = 0;
	}
	depth--;
	print_spaces(depth);
	pprintf("and returning ");
}
