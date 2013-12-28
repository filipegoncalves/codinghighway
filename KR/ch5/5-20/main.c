#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void dirdcl(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];

void dcl(void) {
	int ns;
	for (ns = 0; gettoken() == '*'; )
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}

void dirdcl(void) {
	int type;
	void plist(void);
	if (tokentype == '(') {
		dcl();
		if (tokentype != ')')
			printf("warning: missing )\n");
	} else if (tokentype == NAME)
		strcpy(name, token);
	else
		return; /* destroys error checkin / recovery, but allows for things like int (*)() */

	while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
		if (type == PARENS)
			strcat(out, " function returning");
		else if (type == '(') {
			strcat(out, " function receiving");
			plist();
			if (tokentype != ')')
				printf("Missing ) on function parameters declaration\n");
			strcat(out, " and returning");
		}
		else {
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
}

void plist(void) {
	char *tq_chk(void);
	char tqual[MAXTOKEN];
	char ptype[MAXTOKEN];
	strcpy(tqual, tq_chk());
	strcpy(ptype, " ");
	strcat(ptype, token);
	dcl();
	strcat(out, tqual);
	strcat(out, ptype);
	while (tokentype == ',') {
		strcat(out, " and");
		strcpy(tqual, tq_chk());
		strcpy(ptype, " ");
		strcat(ptype, token);
		dcl();
		strcat(out, tqual);
		strcat(out, ptype);
	}
}

char *tq_chk(void) {
	char *ret = malloc(MAXTOKEN);
	*ret = '\0';
	gettoken();
	if (!strcmp(token, "const")
		|| !strcmp(token, "volatile")) {
		strcpy(ret, " ");
		strcat(ret, token);
		gettoken();
	}
	return ret;	
}

int gettoken(void) {
	int c, getch(void);
	void ungetch(int);
	char *p = token;
	
	while ((c = getch()) == ' ' || c == '\t');
	
	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']';);
		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	} else
		return tokentype = c;
}

int main() {
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';
		dcl();
		printf("%s: %s %s\n", name, out, datatype);
	}
	return 0;
}
