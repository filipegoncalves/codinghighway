#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXTOK 1000
#define MAXLN 2000
#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s) {
	unsigned hashval;
	
	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

void undef(char *name) {
	unsigned hashval = hash(name);
	struct nlist *prev = hashtab[hashval], *to_free = NULL;
	if (!prev)
		return;
	if (!strcmp(prev->name, name)) {
		hashtab[hashval] = prev->next;
		to_free = prev;
	}
	else {
		for (to_free = prev->next; to_free; prev = to_free, to_free = to_free->next) {
			if (!strcmp(to_free->name, name)) {
				prev->next = to_free->next;
				break;
			}
		}
	}
	if (to_free) {
		free(to_free->name);
		free(to_free->defn);
		free(to_free);
	}
}

struct nlist *lookup(char *s) {
	struct nlist *np;
	
	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;
	return NULL;
}

struct nlist *install(char *name, char *defn) {
	struct nlist *np;
	unsigned hashval;
	
	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

int getnexttoken(char *, int);
int getch(void);
void ungetch(int);
void process_define(void);
void process_undef(void);

int main() {
	char token[MAXTOK];
	int c;
	struct nlist *entry;
	
	while ((c = getnexttoken(token, MAXTOK)) != EOF) {
		switch (c) {
			case '#':
				if (!strcmp(token, "#define"))
					process_define();
				else if (!strcmp(token, "#undef"))
					process_undef();
				else {
					printf("%s", token);
				}
				break;
			default:
				if (!isalnum(c) && c != '_')
					printf("%s", token);
				else {
					if ((entry = lookup(token))) {
						printf("%s", entry->defn);
					}
					else {
						printf("%s", token);
					}
				}
		}
	}
	
	return 0;
}

void get_rest_of_line(char *, int);
void process_define(void) {
	int c;
	char token[MAXTOK], name[MAXTOK], defn[MAXLN];
	while (c != '\n' && isspace(c = getnexttoken(token, MAXTOK)));
	strcpy(name, token);
	get_rest_of_line(defn, MAXLN);
	install(name, defn);
}

void process_undef(void) {
	int c;
	char token[MAXTOK];
	while (c != '\n' && isspace(c = getnexttoken(token, MAXTOK)));
	undef(token);
}

void get_rest_of_line(char *s, int lim) {
	int c;
	while ((c = getch()) != '\n' && isspace(c));
	while (--lim > 0 && c != '\n' && c != '\r' && c != EOF) {
		*s++ = c;
		c = getch();
	}
	*s = '\0';
	ungetch(c);
}

int getnexttoken(char *word, int lim) {
	int c;
	char *w = word;
	short in_comment = 0;

	*w = '\0';
	
	if ((c = getch()) != EOF)
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
			return getnexttoken(word, lim); /* Makes it so that comments are as if they didn't exist at all */
		}
		else {
			ungetch(*w);
		}
	}
	*w = '\0';
	return word[0];
}

