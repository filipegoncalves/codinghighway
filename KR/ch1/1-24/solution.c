#include <stdio.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) > (b)) ? (b) : (a))
#define abs(x) ((x) > 0 ? (x) : (-(x)))

int main() {
	int c, l = EOF;
	int in_string = 0;
	int in_comment = 0;
	int opening_char;
	int line = 1, braces = 0, brackets = 0, parens = 0;
	c = getchar();
	while (c != EOF) {
		if (c == '\n')
			line++;
		if (!in_comment) {
			if (c == '\\') {
				getchar();
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
				c = getchar();
				continue;
			}
			l = getchar();
			if (c == '/' && l != EOF && l == '*' && !in_string) {
				in_comment = 1;
				c = getchar();
			}
			else {
				/* Not in a comment, not in a string - parsing REAL CODE!!! */
				if (c == '(')
					parens++;
				else if (c == '[')
					brackets++;
				else if (c == '{')
					braces++;
				else if (c == '}')
					braces--;
				else if (c == ']')
					brackets--;
				else if (c == ')')
					parens--;
				/* Check for unbalanced stuff */
				if (braces < 0 || parens < 0 || brackets < 0) {
					printf("Syntax error on line %d. Unbalanced close char: %c\n", line, c);
					braces = max(0, braces);
					parens = max(0, parens);
					brackets = max(0, brackets);
				}
				c = l;
			}
		}
		else {
			/* Ignore comments */
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
	/* Check for stuff that was not closed */
	if (braces != 0)
		printf("Prematurely reached end of file - expected %d closing braces\n", abs(braces));
	if (brackets != 0)
		printf("Prematurely reached end of file - expected %d closing brackets\n", abs(brackets));
	if (parens != 0)
		printf("Prematurely reached end of file - expected %d closing parentheses\n", abs(parens));
	return 0;
}
