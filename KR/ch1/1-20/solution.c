#include <stdio.h>
#define NDETAB 5

int main() {
	int c, pos = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			while (pos <= NDETAB-1) {
				putchar(' ');
				pos++;
			}
			pos = 0;		
		}
		else {
			putchar(c);
			if (c == '\n')
				pos = 0;
			else
				pos = (pos+1)%NDETAB;
		}
	}
	return 0;
}
