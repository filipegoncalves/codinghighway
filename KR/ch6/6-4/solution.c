#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 10000

struct node_t {
	char *word;
	int count;
	struct node_t *left;
	struct node_t *right;
	struct node_t *next;
	struct node_t *prev;
};

struct node_lst {
	struct node_t *head;
	struct node_t *tail;
};

struct node_t *processline(char *, struct node_t *, struct node_lst *);
void listprint(struct node_lst *);

int main() {
	size_t n = MAXLINE;
	char *line = malloc(MAXLINE);
	struct node_t *root = NULL;
	struct node_lst *list = (struct node_lst *) malloc(sizeof(struct node_lst));
	list->head = list->tail = NULL;
	
	while (getline(&line, &n, stdin) != -1) {
		root = processline(line, root, list);
	}
	
	listprint(list);
	return 0;
}

struct node_t *addtree(char *, struct node_t *, struct node_lst *);

struct node_t *processline(char *line, struct node_t *root, struct node_lst * list) {
	char *word = line, *ptr, erased;
	while (*word != '\n' && *word != '\r') {
		while (*word != '\n' && *word != '\r' && *word != '\''&& !isalnum((unsigned char) *word)) {
			word++;
		}
		ptr = word;
		while (isalnum((unsigned char) *ptr) || *ptr == '\'') {
			ptr++;
		}
		if (ptr != word) {
			erased = *ptr;
			*ptr = '\0';
			root = addtree(word, root, list);
			*ptr = erased;
			word = ptr;
		}
	}
	return root;
}

void list_append(struct node_t *, struct node_lst *);
void list_update(struct node_t *, struct node_lst *);
struct node_t *addtree(char *word, struct node_t *p, struct node_lst *list) {
	int cond;
	if (p == NULL) {
		p = (struct node_t *) malloc(sizeof(struct node_t));
		p->word = strdup(word);
		p->count = 1;
		p->left = p->right = NULL;
		list_append(p, list);
	} else if ((cond = strcasecmp(word, p->word)) == 0) {
		p->count++;
		list_update(p, list);
	} else if (cond < 0) {
		p->left = addtree(word, p->left, list);
	} else {
		p->right = addtree(word, p->right, list);
	}
	return p;
}

void list_append(struct node_t *n, struct node_lst *l) {
	n->next = NULL;
	n->prev = l->tail;
	if (l->tail)
		l->tail->next = n;
	else
		l->head = n;
	l->tail = n;
}

void list_update(struct node_t *n, struct node_lst *l) {
	struct node_t *p;
	
	for (p = n->prev; p && p->count < n->count; p = p->prev);
	/* Remove n from list, and update head and tail accordingly */
	if (n->prev)
		n->prev->next = n->next;
	else
		l->head = n->next;
	if (n->next)
		n->next->prev = n->prev;
	else
		l->tail = n->prev;
	/* Insert n in new location */
	n->prev = p;
	if (!p) {
		n->next = l->head;
		if (l->head)
			l->head->prev = n;
	} else {
		n->next = p->next;
		if (p->next)
			p->next->prev = n;
		p->next = n;
	}
	if (!n->prev)
		l->head = n;
	if (!n->next)
		l->tail = n;
}

void listprint(struct node_lst *list) {
	struct node_t *n;
	
	for (n = list->head; n; n = n->next) {
		printf("%4d %s\n", n->count, n->word);
	}
}
