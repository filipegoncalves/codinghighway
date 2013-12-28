#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXLINE 10000

struct line_list {
	int line_no;
	struct line_list *next;
};

struct tnode {
	char *word;
	struct line_list *lines;
	struct tnode *left;
	struct tnode *right;
};


struct tnode *process_line(char *, int, struct tnode *);
void treeprint_lines(struct tnode *);

int main() {
	size_t n = MAXLINE;
	char *line = malloc(MAXLINE);
	struct tnode *root = NULL;
	int linecounter = 0;
	
	while (getline(&line, &n, stdin) != -1) {
		linecounter++;
		root = process_line(line, linecounter, root);
	}
	
	treeprint_lines(root);
	return 0;
}

struct tnode *addtree_line(char *, int, struct tnode *);

struct tnode *process_line(char *line, int lineno, struct tnode *root) {
	char *word = line, *ptr, erased;
	while (*word != '\n' && *word != '\r') {
		while (*word != '\n' && *word != '\r' && *word != '\'' && !isalnum((unsigned char) *word))
			word++;
		ptr = word;
		while (isalnum((unsigned char) *ptr) || *ptr == '\'') {
			ptr++;
		}
		if (ptr != word) {
			erased = *ptr;
			*ptr = '\0';
			root = addtree_line(word, lineno, root);
			*ptr = erased;
			word = ptr;
		}
	}
	return root;
}

struct tnode *addtree_line(char *word, int line, struct tnode *p) {
	int cond;
	struct line_list *l;
	if (p == NULL) {
		p = (struct tnode *) malloc(sizeof(struct tnode));
		p->word = strdup(word);
		p->left = p->right = NULL;
		p->lines = (struct line_list *) malloc(sizeof(struct line_list));
		p->lines->next = NULL;
		p->lines->line_no = line;
	} else if ((cond = strcasecmp(word, p->word)) == 0) {
		l = (struct line_list *) malloc(sizeof(struct line_list));
		l->line_no = line;
		l->next = p->lines;
		p->lines = l;
	} else if (cond < 0) {
		p->left = addtree_line(word, line, p->left);
	} else {
		p->right = addtree_line(word, line, p->right);
	}
	return p;
}

void treeprint_lines(struct tnode *root) {
	struct line_list *lst;
	
	if (root == NULL)
		return;
	
	treeprint_lines(root->left);
	
	lst = root->lines;
	printf("%s\n", root->word);
	while (lst) {
		printf("\t%d\n", lst->line_no);
		lst = lst->next;
	}
	
	treeprint_lines(root->right);
}
