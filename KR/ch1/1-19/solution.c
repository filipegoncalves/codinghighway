#include <stdio.h>
#define MAXLINE 10000

void reverse(char s[]);
int my_getline(char s[], int lim);

int main() {
	int len;
	char line[MAXLINE];
	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (line[len-1] == '\n')
			line[len-1] = '\0';
		reverse(line);
		printf("%s\n", line);
	}
	return 0;
}

void reverse(char s[]) {
	int i, j;
	char a;
	for (i = 0; s[i]; i++);
	i--;
	j = 0;
	while (j < i) {
		a = s[i];
		s[i] = s[j];
		s[j] = a;
		i--;
		j++;
	}
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
