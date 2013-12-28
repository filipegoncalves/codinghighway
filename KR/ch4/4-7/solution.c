#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];
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

void ungets(char s[]) {
	int i;
	for (i = 0; s[i]; i++);
	i--;
	while (i >= 0)
		ungetch(s[i--]);
}

int main() {
	/* Example usage */
	char c;
	ungets("hello");
	while ((c = getch()) != 'o')
		putchar(c);
	putchar(c);
	return 0;
}
