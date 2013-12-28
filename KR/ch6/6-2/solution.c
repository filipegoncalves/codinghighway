#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
#define NCHARDEF 6
#define istype(w) (!strcmp((w), "int") || !strcmp((w), "char") || !strcmp((w), "float") || !strcmp((w), "double"))

struct tnode {
	char *word;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int main(int argc, char *argv[]) {
	struct tnode *root;
	char word[MAXWORD];
	int n = -1;
	if (argc == 2 && isdigit((unsigned char) argv[1][0])) {
		n = atoi(argv[1]);
	}
	if (n <= 0)
		n = NCHARDEF;
	
	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if ((isalpha((unsigned char) word[0]) || word[0] == '_') && !istype(word) && strlen(word) >= n)
			root = addtree(root, word);
	treeprint(root);
	return 0;
}

struct tnode *talloc(void);
struct tnode *addtree(struct tnode *p, char *w) {
	int cond;
	
	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) < 0)
		p->left = addtree(p->left, w);
	else if (cond > 0) 
		p->right = addtree(p->right, w);
	return p;
}

struct tnode *talloc(void) {
	return (struct tnode *) malloc(sizeof(struct tnode));
}

void treeprint(struct tnode *p) {
	if (p != NULL) {
		treeprint(p->left);
		printf("%s\n", p->word);
		treeprint(p->right);
	}
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
