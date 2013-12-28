#include <ctype.h>
#include <stdio.h>
#define NUMBER '0'

int getop(char s[]) {
	int i, c;	
	static int buf = 0;
	if (buf != 0) {
		c = buf;
		buf = 0;
	}
	else
		c = getchar();
	
	for (; c == ' ' || c == '\t'; c = getchar());
	s[0] = c;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c)) {
		while (isdigit(c = getchar())) {
			s[++i] = c;
		}
		s[++i] = c;
	}
	if (c == '.') {
		while (isdigit(c = getchar())) {
			s[++i] = c;
		}
	}
	s[i] = '\0';
	if (c != EOF)
		buf = c;
	return NUMBER;
}
