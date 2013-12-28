#include <stdio.h>
#define NDETAB 5
#define flushblanks(t,s) { for (; t > 0; t--) putchar('\t'); for (; s > 0; s--) putchar(' '); }

int main() {
	int c, t, s, pos;
	t = s = pos = 0;
	
	while ((c = getchar()) != EOF) {
		pos += (pos == NDETAB ? 1-NDETAB : 1);
		if (c == ' ') {
			if (pos == NDETAB) {
				t++;
				pos = 0;
				s = 0;
			}
			else {
				s++;
			}
		}
		else {
			if (c == '\t') {
				s = 0;
				pos = 0;
			}
			flushblanks(t, s);
			putchar(c);
			if (c == '\n') {
				t = s = pos = 0;
			}
		}
	}
	/* If file ends without \n, ensure that missing blanks are printed anyway */
	flushblanks(t, s);
	return 0;
}
