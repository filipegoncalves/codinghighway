#include <stdio.h>
#define MAXLINE 10000

int my_getline(char line[], int maxline);

int main() {
	int len, j, i;
	char line[MAXLINE];
	while ((len = my_getline(line, MAXLINE)) > 0) {
		for (j = 0; line[j]; j++) {
			if (line[j] == '\n') {
				line[j] = '\0';
				break;
			}
			if (line[j] == '\t' || line[j] == ' ') {
				i = j;
				for (j++; line[j] == '\t' || line[j] == ' '; j++);
				if (line[j] == '\0' || line[j] == '\n') {
					line[i] = '\0';
					j = i;
				}
				j--;
			}
		}
		if (line[0] != '\0') /* newline is always removed after processing current line */
			printf("%s\n", line);
	}
	return 0;
}

int my_getline(char s[], int lim) {
	int c, i;
	
	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
