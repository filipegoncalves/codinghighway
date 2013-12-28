#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define TAILDEF 10
#define MAXLINE 1000

int my_getline(char s[], int lim);

int main(int argc, char *argv[]) {
	int total_lines = TAILDEF, n;
	char **lines, line[MAXLINE];
	int first = 0, len, i;
	
	/* Argument parsing */
	if (argc == 2 && argv[1][0] == '-' && isdigit((unsigned char) argv[1][1])) {
		n = atoi(argv[1]+1);
		if (n > 0)
			total_lines = n;
		else
			printf("Invalid numerical value, falling back to default...\n");
	}
	
	lines = calloc(total_lines, sizeof(char *));
	
	while ((len = my_getline(line, MAXLINE)) > 0) {
		if (lines[first])
			free(lines[first]);
		lines[first] = malloc(len+1);
		strcpy(lines[first], line);
		first = (first+1)%total_lines;
	}
	
	for (i = 0; i < total_lines; i++, first = (first+1)%total_lines)
		if (lines[first])
			printf("%s", lines[first]);

	return 0;
}

int my_getline(char s[], int lim) {
	int c, i;
	
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
