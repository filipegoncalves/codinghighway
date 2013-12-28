#include <stdio.h>
#define MAXLINE 10000

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];
	
	max = 0;
	while ((len = my_getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)
		printf("Length: %d\n%s", max, longest);
	return 0;
}

int my_getline(char s[], int lim) {
	int c, i;
	
	for (i = 0; (c=getchar()) != EOF && c != '\n'; ++i) {
		if (i < lim-1)
			s[i] = c;
	}
	s[i < lim-1 ? i+1 : lim-1] = '\0';
	return i;
}

void copy(char to[], char from[]) {
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
