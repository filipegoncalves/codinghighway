#include <stdio.h>

int main() {	
	int c;
	int read_blank;
	read_blank = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			read_blank = 1;
		}
		else {
			if (read_blank) {
				putchar(' ');
				read_blank = 0;
			}
			putchar(c);
		}
	}
	if (read_blank) { 
		/* File ended with series of blanks */
		putchar(' ');
	}
	return 0;
}
