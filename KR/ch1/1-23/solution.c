#include <stdio.h>

int main() {
	int c, l = EOF;
	int in_string = 0;
	int in_comment = 0;
	int opening_char;
	c = getchar();
	while (c != EOF) {
		if (!in_comment) {
			if (c == '\\') {
				putchar(c);
				putchar(getchar());
				c = getchar();
				continue;
			}
			if (c == '"' || c == '\'') {
				if (in_string == 0) {
					opening_char = c;
					in_string = 1;
				}
				else if (c == opening_char) {
					in_string = 0;
				}
			}
			if (in_string) {
				putchar(c);
				c = getchar();
				continue;
			}
			l = getchar();
			if (c == '/' && l != EOF && l == '*' && !in_string) {
				in_comment = 1;
				c = getchar();
			}
			else {
				putchar(c);
				c = l;
			}
		}
		else {
			l = getchar();
			if (c == '*' && l != EOF && l == '/') {
				in_comment = 0;
				c = getchar();
			}
			else {
				c = l;
			}
		}	
	}
	return 0;
}
