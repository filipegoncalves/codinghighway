#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
	int c, sign, next;
	int exp = 1;
	
	while (isspace(c = getch()));
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
		return 0;
	sign = (c == '-' ? -1 : 1);
	if (c == '+' || c == '-') {
		next = getch();
		if (!isdigit(next) && next != '.') {
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
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0'); /* 10 * *pn needs space because of the compiler's maximal munch strategy */
	if (c == '.' && !isdigit(c = getch())) {
		if (c != EOF) {
			ungetch(c);
			return 0;
		}
		else
			return EOF;
	}
	while (isdigit(c)) {
		*pn = 10 * *pn + (c - '0');
		exp *= 10;
		c = getch();
	}
	*pn /= exp;
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

int main() {
	/* Example usage */
	float a;
	
	if (getfloat(&a)) {
		printf("You entered %f\n", a);
	}
	else {
		printf("You did not enter a valid number\n");
	}
	return 0;
}
