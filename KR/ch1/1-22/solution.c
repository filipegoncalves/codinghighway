#include <stdio.h>
#define MAXLINE 80

int main() {
	char buf[MAXLINE+2];
	int c, pos, i;
	pos = i = 0;
	
	while ((c = getchar()) != EOF) {
		if ((buf[pos++] = c) != ' ' && c != '\t')
			i = pos;
		if (c == '\n' || pos == MAXLINE) {
			if (pos == MAXLINE) {
				pos = i;
				buf[pos] = '\n';
			}
			else {
				pos--;
			}
			buf[pos+1] = '\0';
			if (pos)
				printf("%s", buf);
			pos = i = 0;
		}
	}
	return 0;
}
