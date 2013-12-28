#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn) {
	int c, sign, next;
	
	while (isspace(c = getch()));
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-' ? -1 : 1);
	if (c == '+' || c == '-') {
		next = getch();
		if (!isdigit(next)) {
			if (next != EOF) {
				ungetch(next);
				return 0;
			}
			else
				return EOF;
		}
		else
			c = next;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main() {
	/* Example usage */
	int a;
	
	if (getint(&a)) {
		printf("You entered %d\n", a);
	}
	else {
		printf("You did not enter a valid number\n");
	}
	return 0;
}
