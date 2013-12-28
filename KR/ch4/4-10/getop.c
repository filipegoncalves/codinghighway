#include <ctype.h>
#include <stdio.h>
#define MAXLINE 101
#define NUMBER '0'

char line[MAXLINE] = { 0 };
int lindex = 0;

int get_line(char s[], int lim);
int getop(char s[]) {
	int i;
	if (line[lindex] == '\0') {
		lindex = 0;
		if (get_line(line, MAXLINE) == 0)
			return EOF;
	}
	for (; (s[0] = line[lindex]) == ' ' || line[lindex] == '\t'; lindex++);
	s[1] = '\0';
	if (!isdigit((unsigned char) line[lindex]) && line[lindex] != '.')
		return line[lindex++];
	i = 0;
	if (isdigit((unsigned char) line[lindex])) {
		while (isdigit((unsigned char) line[++lindex])) {
			s[++i] = line[lindex];
		}
		s[++i] = line[lindex];
	}
	if (line[lindex] == '.') {
		while (isdigit((unsigned char) line[++lindex])) {
			s[++i] = line[lindex];
		}
	}
	s[i] = '\0';
	return NUMBER;
}

int get_line(char s[], int lim) {
	int c, i;
	
	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
