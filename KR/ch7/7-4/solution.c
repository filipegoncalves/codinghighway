#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#define BUFSIZE 100

void skipblanks(void);
int getch(void);
void ungetch(int);

int minscanf(char *fmt, ...) {
	va_list ap;
	int matched = 0, c, i, sign, done = 0;
	char *p, buffer[BUFSIZE], *s, *initial;
	
	va_start(ap, fmt);
	
	for (p = fmt; !done && *p; p++) {
		if (isspace((unsigned char) *p)) {
			skipblanks();
			continue;
		}
		else if (*p != '%') {
			/* Not a space, not a modifier, match characters */
			if ((c = getch()) != *p) {
				ungetch(c);
				done = 1;
			}
			continue;
		}
		p++;
		/* Modifiers */
		switch (*p) {
			case 'd':
				skipblanks();
				if ((c = getch()) == '-')
					sign = -1;
				else {
					sign = 1;
					ungetch(c);
				}
				i = 0;
				while ((c = getch()) != EOF && isdigit((unsigned char) c))
					buffer[i++] = c;
				ungetch(c);
				buffer[i] = '\0';
				if (i > 0) {
					matched++;
					*va_arg(ap, int *) = sign*atoi(buffer);
				}
				else {
					if (sign == -1)
						ungetch('-');
					done = 1;
				}
				break;
			case 'f':
				skipblanks();
				i = 0;
				if ((c = getch()) == '-')
					sign = -1;
				else {
					sign = 1;
					ungetch(c);
				}
				while ((c = getch()) != EOF && isdigit((unsigned char) c))
					buffer[i++] = c;
				if (c == '.')
					buffer[i++] = '.';
				else
					ungetch(c);
				while ((c = getch()) != EOF && isdigit((unsigned char) c))
					buffer[i++] = c;
				ungetch(c);
				if (buffer[i-1] == '.') { /* Cannot finish with single dot */
					ungetch('.');
					i--;
				}
				buffer[i] = '\0';
				/* Allow for leading '.' in float string */
				if (i > 1 ||
				   (i == 1 && isdigit((unsigned char) buffer[0]))) {
					matched++;
					*va_arg(ap, float *) = sign*atof(buffer);
				}
				else {
					if (sign == -1)
						ungetch('-');
					done = 1;
				}
				break;
			case 's':
				skipblanks();
				for (s = initial = va_arg(ap, char *), c = getch(); c != EOF && !isspace((unsigned char) c); s++, c = getch())
					*s = c;
				ungetch(c);
				if (s != initial) {
					matched++;
					*s = '\0';
				}
				else
					done = 1;
				break;
			case 'c':
				/* %c does not skip blanks */
				*va_arg(ap, char *) = getch();
				matched++;
				break;
		}
	}
	va_end(ap);
	return matched;
}

void skipblanks(void) {
	int c;
	while ((c = getch()) != EOF && isspace((unsigned char) c));
	ungetch(c);
}

int main() {
	/* Example usage */
	char a[100];
	int b;
	float c;
	
	minscanf("%s%d%f", a, &b, &c); /* Input: hello 123 33.3 */
	
	printf("%s\n%d\n%f\n", a, b, c);
	
	return 0;
}
