#include <stdio.h>
#include <string.h> 
#define MAXLEN 1000
#define MAXLINES 100

int my_getline(char[], int);

int readlines(char *lineptr[], char *p, int length, int maxlines) {
	int len, nlines;
	char line[MAXLEN];
	
	nlines = 0;
	
	while ((len = my_getline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || len+1 > length || len+1 > MAXLEN)
			return -1;
		else {
			/* Lines with more than MAXLEN chars do not contain trailing newline */
			if (line[len-1] == '\n')
				line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len+1;
			length -= len+1;
		}
	}
	return nlines;
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

int main() {
	/* Example usage */
	char *lineptr[MAXLINES];
	char p[MAXLEN*MAXLINES];
	int i, j;
	printf("Reading lines, terminate with EOF...\n");
	j = readlines(lineptr, p, MAXLEN*MAXLINES, MAXLINES);
	printf("Dumping lines...\n");
	for (i = 0; i < j; i++)
		printf("%s\n", lineptr[i]);
	return 0;
}
