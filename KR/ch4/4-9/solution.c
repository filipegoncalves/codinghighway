#include <stdio.h>
#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0;

int getch(void) {
	return (bufp > 0 ? buf[--bufp] : getchar());
}

void ungetch(int c) {
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

int main() {
	/* Example usage */
	int c;
	ungetch(EOF); /* To show it works with EOF */
	ungetch('x');
	while ((c = getch()) != EOF)
		putchar(c);
	return 0;
}
