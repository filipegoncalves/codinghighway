#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main() {
	/* Example usage */
	struct nlist *l;
	install("HASHSIZE", "101");
	if ((l = lookup("HASHSIZE")) != NULL)
		printf("Found HASHSIZE: %s\n", l->defn);
	undef("HASHSIZE");
	printf("Removed, looking up again...\n");
	printf("%s\n", ((l = lookup("HASHSIZE")) != NULL ? "Oops! Found it again..?!" : "Not found, as expected."));
	return 0;
}
