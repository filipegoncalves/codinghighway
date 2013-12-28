#include <ctype.h>
#include <stdio.h>
#define NUMBER '0'
#define ASSIGN -2
#define VAR 'a'

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int i, c;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	i = 0;
	if (c == '&') {
		if (isalpha(c = getch())) {
			s[++i] = tolower(c);
			s[++i] = '\0';
			return ASSIGN;
		}
		else {
			ungetch(c);
			return '&';
		}
	}
	if (isalpha(c) || c == '_') {
		s[0] = tolower(c);
		return VAR;
	}
	if (!isdigit(c) && c != '.')
		return c;
	if (isdigit(c)) {
		while (isdigit(c = getch())) {
			s[++i] = c;
		}
		s[++i] = c;
	}
	if (c == '.') {
		while (isdigit(c = getch())) {
			s[++i] = c;
		}
		s[++i] = c;
	}
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
