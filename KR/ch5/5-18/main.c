#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void dirdcl(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
short dclferror;

void dcl(void) {
	int ns;
	
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	
	if (dclferror)
		return;
	
	while (ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void) {
	int type;
	
	if (dclferror) {
		return;
	}
	
	if (tokentype != '(' && tokentype != NAME) {
		printf("Warning: was expecting name or (dcl), trying to recover...\n");
		for (type = gettoken(); type != EOF && type != '\n' && type != '(' && type != NAME; type = gettoken());
		if (type == EOF || type == '\n') {
			dclferror = 1;
			printf("Fatal error: could not recover from bad input. Aborting.\n");
			return;
		}
	}
	
	if (tokentype == '(') {
		dcl();
		if (dclferror)
			return;
		if (tokentype != ')')
			printf("warning: missing )\n");
	} else if (tokentype == NAME)
		strcpy(name, token);

	if (tokentype == '\n') {
		/* Premature end of line, just finish it all */
		dclferror = 1;
		printf("Warning: premature end of line reached, stopping processing...\n");
		return;
	}
	
	while ((type=gettoken()) == PARENS || type == BRACKETS)
		if (type == PARENS)
			strcat(out, " function returning");
		else {
			char *i, *j;
			for (i = j = token+1; *i != ']'; i++) {
				if (isdigit((unsigned char) *i)) {
					*j++ = *i;
				}
				else {
					printf("Warning: invalid digit detected inside array size declaration.\n");
				}
			}
			*j++ = ']';
			*j = '\0';
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

int gettoken(void) {
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	
	while ((c = getch()) == ' ' || c == '\t')
		;
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = c = getch()) != ']' && c != EOF && c != '\n'; )
			;
		if (c == EOF || c == '\n') {
			ungetch(c);
			p[-1] = ']';
			printf("Warning: missing close bracket ]\n");
		}
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

int main() {
	dclferror = 0;
	while (gettoken() != EOF) {
		if (strcmp(token, "char")
			&& strcmp(token, "int")
			&& strcmp(token, "short")
			&& strcmp(token, "float")
			&& strcmp(token, "double")
			&& strcmp(token, "void")) {
				printf("Invalid type declaration, try again!\n");
				while (gettoken() != '\n');
				continue;
			}
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		if (!dclferror) {
			if (tokentype != '\n') {
				printf("Warning: ignoring unknown trailing characters\n");
				while (gettoken() != '\n' && tokentype != EOF);
			}
			printf("%s: %s %s\n", name, out, datatype);
		}
		dclferror = 0;
	}
	return 0;
}
