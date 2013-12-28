#include <stdio.h>
#define IN 1
#define OUT 0

int main() {
	int state = OUT;
	int c;
	
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN)
				putchar('\n');
			state = OUT;
		}
		else {
			if (state == OUT) {
				state = IN;
			}
			putchar(c);
		}
	}
	return 0;
}
