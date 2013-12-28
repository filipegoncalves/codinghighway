#include <stdio.h>

char pushed = 0;

int getch(void) {
	char x;
	if (pushed != 0) {
		x = pushed;
		pushed = 0;
		return (unsigned char) x;
	}
	return getchar();
}

void ungetch(char c) {
	pushed = c;
}

int main () {
	/* Example usage */
	ungetch('x');
	ungetch('a'); /* x was lost */
	putchar(getch());
	return 0;	
}
