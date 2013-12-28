#include <ctype.h>
#include <stdio.h>
#define NUMBER '0'

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int i, c;
	
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
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
