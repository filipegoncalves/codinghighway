#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))

struct key {
	char *word;
	int count;
} keytab[] = {
	{ "auto", 0 },
	{ "break", 0 },
	{ "case", 0 },
	{ "char", 0 },
	{ "const", 0 },
	{ "continue", 0 },
	{ "default", 0 },
	/* ... */
	{ "unsigned", 0 },
	{ "void", 0 },
	{ "volatile", 0 },
	{ "while", 0 }
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

/* count C keywords */
int main() {
	int n;
	char word[MAXWORD];
	
	while (getword(word, MAXWORD) != EOF)
		if (isalpha((unsigned char) word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n",
				keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
	int cond;
	int low, high, mid;
	
	low = 0;
	high = n-1;
	while (low <= high) {
		mid = (low+high)/2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid-1;
		else if (cond > 0)
			low = mid+1;
		else
			return mid;
	}
	return -1;
}

int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	short in_comment = 0;
	
	*w = '\0';
	
	while (isspace(c = getch()));
	
	if (c != EOF)
		*w++ = c;
	else
		return EOF;
	if (isalpha(c) || c == '_' || c == '#') {
		for ( ; --lim > 0; w++)
			if (!isalnum((unsigned char) (*w = getch())) && *w != '_') {
				ungetch(*w);
				break;
			}
	} else if (c == '\'' || c == '"') {
		for ( ; --lim > 0; w++) {
			if ((*w = getch()) == '\\') {
				*++w = getch();
			} else if (*w == c) {
				w++;
				break;
			}
		}
	} else if (c == '/') {
		if ((*w = getch()) == '*') {
			in_comment = 1;
			while (in_comment) {
				while (getch() != '*');
				if ((c = getch()) == '/')
					in_comment = 0;
				else
					ungetch(c);
			}
			return getword(word, lim); /* Makes it so that comments are as if they didn't exist at all */
		}
		else {
			ungetch(*w);
		}
	}
	*w = '\0';
	return word[0];
}

