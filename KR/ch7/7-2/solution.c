#include <stdio.h>
#include <ctype.h>
#define LINELENGTH 120

int main() {
	int c, read = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n' || read == LINELENGTH) {
			read = 0;
			putchar('\n');
			continue;
		}
		else
			read++;
		if (!isgraph(c))
			read += printf("0x%x", c) - 1; /* We subtract one because we have already incremented "read" before */
		else
			putchar(c);
	}
	return 0;
}
