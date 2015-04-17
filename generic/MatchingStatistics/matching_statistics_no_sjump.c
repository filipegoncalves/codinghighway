/* Compile away asserts() and debugging functions. */
//#define NDEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stddef.h>

/* Doubly linked list implementation
 * Based off the linux kernel
 */
struct list_head {
	struct list_head *next, *prev;
};

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * list_next_entry - get the next element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_struct within the struct.
 */
#define list_next_entry(pos, member) \
	list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 * list_last_entry - get the last element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_last_entry(ptr, type, member) \
	list_entry((ptr)->prev, type, member)

/**
 * list_prev_entry - get the prev element in list
 * @pos:	the type * to cursor
 * @member:	the name of the list_struct within the struct.
 */
#define list_prev_entry(pos, member) \
	list_entry((pos)->member.prev, typeof(*(pos)), member)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

static inline void __list_add(struct list_head *new,
			      struct list_head *prev,
			      struct list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

/**
 * list_add - add a new entry
 * @new: new entry to be added
 * @head: list head to add it after
 *
 * Insert a new entry after the specified head.
 * This is good for implementing stacks.
 */
static inline void list_add(struct list_head *new, struct list_head *head)
{
	__list_add(new, head, head->next);
}


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
	__list_add(new, head->prev, head);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void list_del(struct list_head *entry)
{
	__list_del(entry->prev, entry->next);
}

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
	return head->next == head;
}

/**
 * list_entry - get the struct for this entry
 * @ptr:	the &struct list_head pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/**
 * list_for_each	-	iterate over a list
 * @pos:	the &struct list_head to use as a loop cursor.
 * @head:	the head for your list.
 */
#define list_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * list_for_each_entry	-	iterate over list of given type
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)				\
	for (pos = list_first_entry(head, typeof(*pos), member);	\
	     &pos->member != (head);					\
	     pos = list_next_entry(pos, member))

/**
 * list_for_each_entry_reverse - iterate backwards over list of given type.
 * @pos:	the type * to use as a loop cursor.
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_reverse(pos, head, member)			\
	for (pos = list_last_entry(head, typeof(*pos), member);		\
	     &pos->member != (head); 					\
	     pos = list_prev_entry(pos, member))

/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_entry_safe(pos, n, head, member)			\
	for (pos = list_first_entry(head, typeof(*pos), member),	\
		n = list_next_entry(pos, member);			\
	     &pos->member != (head); 					\
	     pos = n, n = list_next_entry(n, member))

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
		pos = n, n = pos->next)

static inline void __list_splice(const struct list_head *list,
				 struct list_head *prev,
				 struct list_head *next)
{
	struct list_head *first = list->next;
	struct list_head *last = list->prev;

	first->prev = prev;
	prev->next = first;

	last->next = next;
	next->prev = last;
}

/**
 * list_splice - join two lists, this is designed for stacks
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice(const struct list_head *list,
				struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head, head->next);
}

/**
 * list_splice_tail - join two lists, each list being a queue
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void list_splice_tail(struct list_head *list,
				struct list_head *head)
{
	if (!list_empty(list))
		__list_splice(list, head->prev, head);
}


/* Suffix tree implementation */

#define TERMINAL_CHAR '\0'

struct st_node {
	int path_start;
	int string_depth;
	struct st_node *suffix_link;
	struct list_head children;
	struct list_head siblings;
};

struct suffix_tree {
	struct st_node *nodes;
	size_t next_node;
	size_t nodes_sz;
	char *text;
	size_t text_sz;
	struct st_node *root;
	struct st_node *last_internal_added;
};

struct st_point {
	struct st_node *above;
	struct st_node *below;
	int string_depth;
};

struct st_node *get_free_node(struct suffix_tree *tree, int path_start,
			      int string_depth)
{
	struct st_node *ret;
	assert(tree->next_node < tree->nodes_sz);

	ret = &tree->nodes[tree->next_node++];
	ret->path_start = path_start;
	ret->string_depth = string_depth;
	ret->suffix_link = NULL;
	INIT_LIST_HEAD(&ret->children);
	INIT_LIST_HEAD(&ret->siblings);

	return ret;
}

void make_suffix_link(struct st_node *from, struct st_node *to)
{
	from->suffix_link = to;
}

int is_node(struct st_point *p)
{
	return p->above == p->below;
}

struct st_node *can_descend(struct suffix_tree *tree, struct st_point *point,
			    char letter)
{
	struct st_node *child;
	int next_i;

	if (!is_node(point)) {
		next_i = point->below->path_start + point->string_depth;
		assert(next_i < tree->text_sz);
		return tree->text[next_i] == letter ? point->below : NULL;
	}

	if (point->above == tree->root->suffix_link)
		return tree->root;
	if (list_empty(&point->above->children))
		return NULL;

	list_for_each_entry(child, &point->above->children, siblings) {
		next_i = child->path_start + point->string_depth;
		assert(next_i < tree->text_sz);
		if (tree->text[next_i] == letter)
			return child;
	}

	return NULL;
}

void descend(struct suffix_tree *tree, struct st_point *point, char letter)
{
	struct st_node *new_below = can_descend(tree, point, letter);

	assert(new_below != NULL);
	if (new_below->string_depth != point->string_depth+1)
		point->below = new_below;
	else
		point->above = point->below = new_below;
	point->string_depth++;
}

void add_suffix(struct suffix_tree *tree, struct st_point *point,
		size_t start)
{
	struct st_node *new_leaf, *new_node, *father;

	if (!is_node(point)) {
		/* We need to create a new internal node */
		new_node = get_free_node(tree, start, point->string_depth);
		list_del(&point->below->siblings);
		list_add(&new_node->siblings, &point->above->children);
		list_add(&point->below->siblings, &new_node->children);

		if (tree->last_internal_added != NULL)
			make_suffix_link(tree->last_internal_added, new_node);
		tree->last_internal_added = new_node;
		father = new_node;
	} else {
		father = point->above;
	}

	new_leaf = get_free_node(tree, start, tree->text_sz-start);
	list_add(&new_leaf->siblings, &father->children);
}

void suffix_jump(struct suffix_tree *tree, struct st_point *point)
{
	struct st_point old_point = *point;
	int text_i, diff1, diff2;

	assert(old_point.above->suffix_link != NULL);

	point->above = point->below = old_point.above->suffix_link;
	point->string_depth = point->above->string_depth;

	assert(point->string_depth == old_point.above->string_depth-1);

	while (point->string_depth != old_point.string_depth-1) {
		text_i = old_point.below->path_start+point->string_depth+1;
		point->below = can_descend(tree, point, tree->text[text_i]);

		assert(point->below != NULL);

		diff1 = point->below->string_depth - point->above->string_depth;
		diff2 = old_point.string_depth - 1 - point->above->string_depth;

		if (diff1 <= diff2) {
			point->string_depth += diff1;
			point->above = point->below;
		} else {
			point->string_depth += diff2;
		}
	}

	/* Now on the new spot. Any suffix links to create? */
	if (is_node(point) && tree->last_internal_added != NULL) {
		make_suffix_link(tree->last_internal_added, point->above);
		tree->last_internal_added = NULL;
	}
}

void build_stree_core(struct suffix_tree *tree)
{
	size_t text_i = 0;
	size_t curr_start = 0;
	struct st_point curr_point = { tree->root, tree->root, 0 };
	struct st_node *next_node;

	while (text_i < tree->text_sz) {

		next_node = can_descend(tree, &curr_point, tree->text[text_i]);
		while (next_node == NULL) {
			add_suffix(tree, &curr_point, curr_start);
			suffix_jump(tree, &curr_point);
			curr_start++;
			next_node = can_descend(tree, &curr_point,
						tree->text[text_i]);
		}

		descend(tree, &curr_point, tree->text[text_i]);
		text_i++;
	}
}

struct suffix_tree *build_suffix_tree(char *text, size_t text_len)
{
	struct suffix_tree *ret = NULL;
	struct st_node *root_slink;

	assert(text[text_len-1] == TERMINAL_CHAR);

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
		return NULL;

	/* Text of size n:
	 * There are n leaves; at most n-1 internal nodes, 1 root,
	 * and 1 pseudo-node to serve as root's suffix link
	 * n+n-1+1+1 = 2*n+1
	 */
	ret->nodes_sz = 2*text_len+1;
	ret->next_node = 0;
	ret->nodes = malloc(ret->nodes_sz * sizeof(*ret->nodes));
	ret->text_sz = text_len;
	ret->text = strdup(text);
	ret->root = NULL;
	ret->last_internal_added = NULL;

	if (ret->nodes == NULL || ret->text == NULL) {
		free(ret->nodes);
		free(ret->text);
		return NULL;
	}

	ret->root = get_free_node(ret, 0, 0);
	root_slink = get_free_node(ret, 0, -1);
	make_suffix_link(ret->root, root_slink);

	build_stree_core(ret);

	return ret;
}

void destroy_suffix_tree(struct suffix_tree *tree)
{
	if (tree != NULL) {
		free(tree->nodes);
		free(tree->text);
	}
	free(tree);
}

#define MAX_TEXT_SZ 10000000

/* Matching statistics implementation */

/* The terminal char for input strings to matching statistics.
 * This character cannot be part of sigma, the alphabet.
 * This *MUST* be different from TERMINAL_CHAR, defined above for
 * the suffix tree text, because we can't reach a leaf when computing
 * matching statistics.
 */
#define MATCH_STATS_TERM_CHAR '#'
static size_t ms_values[MAX_TEXT_SZ+1];

void matching_statistics(struct suffix_tree *tree, struct suffix_tree *tree_r,
			 char *text, size_t text_sz)
{
	size_t i, j, head;
	struct st_point cursor = { tree->root, tree->root, 0 };

	for (i = 0; i < text_sz; i++)
		ms_values[i] = 0;

	i = 0;
	head = 0;

	while (i < text_sz) {

		while (can_descend(tree, &cursor, text[i]) != NULL) {
			descend(tree, &cursor, text[i]);
			i++;
		}

		ms_values[head] = cursor.string_depth;
		if (ms_values[head] == 0)
			i++;

		head = i;
		cursor.above = cursor.below = tree->root;
		cursor.string_depth = 0;
	}

	for (i = 1; i < text_sz; i++) {
		if (ms_values[i] == 0)
			continue;

		j = i;
		cursor.above = cursor.below = tree_r->root;
		cursor.string_depth = 0;

		printf("descending with %c\n", text[j]);
		descend(tree_r, &cursor, text[j]);

		while (j > 0 && can_descend(tree_r, &cursor, text[j-1])) {
			ms_values[j-1] = cursor.string_depth+ms_values[i];
			descend(tree_r, &cursor, text[j-1]);
			j--;
		}
	}

	for (i = 0; i < text_sz; i++)
		printf("%zu ", ms_values[i]);
}

#ifndef NDEBUG

#define OUT_TERMINAL_CHAR '$'

void print_stree_node(struct suffix_tree *tree, struct st_node *node,
		      unsigned depth);
void print_suffix_tree(struct suffix_tree *tree)
{
	printf("*** SUFFIX TREE ***\n");
	printf("Text:\t\t%s\n", tree->text);
	printf("Nodes in use:\t%zu\n", tree->next_node);
	printf("(Nodes in use include the sentinel, the root, internal nodes, and leaves\n");

	printf("Printing suffix tree; root is node 0\n");
	print_stree_node(tree, tree->root, 0);
}

void print_stree_node(struct suffix_tree *tree, struct st_node *node,
		      unsigned depth)
{
	char spaces[4*depth+1];
	size_t i;
	struct list_head *pos;
	struct st_node *child;
	char *substr;
	int substr_sz;

	for (i = 0; i < sizeof(spaces)-1; i++)
		spaces[i] = ' ';
	spaces[i] = '\0';

	printf("%s*** Node %td; ", spaces, node - tree->nodes);
	if (node->suffix_link != NULL)
		printf("suffix link = %td\n", node->suffix_link - tree->nodes);
	else
		printf("no suffix link.\n");

	list_for_each(pos, &node->children) {
		child = list_entry(pos, struct st_node, siblings);

		substr = tree->text + child->path_start + node->string_depth;
		substr_sz = child->string_depth - node->string_depth;
		printf("%s%.*s", spaces, substr_sz, substr);

		if (substr[substr_sz-1] == TERMINAL_CHAR)
			printf("%c", OUT_TERMINAL_CHAR);

		printf(" -> %td\n", child - tree->nodes);

		print_stree_node(tree, child, depth+1);
	}

	printf("%s*** End of node %td\n", spaces, node - tree->nodes);
}

#endif /* NDEBUG */

void reverse_str(char *begin, char *end) {
	while (begin < end) {
		char tmp = *begin;
		*begin = *end;
		*end = tmp;
		begin++;
		end--;
	}
}

static char text_buff[MAX_TEXT_SZ+1];
int main(void)
{
	size_t text_sz;
	struct suffix_tree *stree = NULL, *stree_r = NULL;
	int ret = 0;
	int op;

	if (scanf("T %zu ", &text_sz) != 1) {
		fprintf(stderr, "Invalid input (line %d)\n", __LINE__);
		ret = -EINVAL;
		goto end;
	}

	assert(text_sz > 0 && text_sz <= MAX_TEXT_SZ);

	fgets(text_buff, text_sz+1, stdin);
	stree = build_suffix_tree(text_buff, text_sz+1);
	reverse_str(text_buff, text_buff+text_sz-1);
	stree_r = build_suffix_tree(text_buff, text_sz+1);

	if (stree == NULL || stree_r == NULL) {
		fprintf(stderr, "Out of memory (line %d)\n", __LINE__);
		ret = -ENOMEM;
		goto end;
	}

#ifndef NDEBUG
	print_suffix_tree(stree);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	print_suffix_tree(stree_r);
#endif

	getchar();
	while ((op = getchar()) != 'E') {
		if (op != 'P' || scanf("%zu ", &text_sz) != 1) {
			fprintf(stderr, "Invalid input (line %d)\n", __LINE__);
			ret = -EINVAL;
			goto end;
		}

		assert(text_sz > 0 && text_sz <= MAX_TEXT_SZ);

		fgets(text_buff, text_sz+1, stdin);
		text_buff[text_sz] = MATCH_STATS_TERM_CHAR;
		matching_statistics(stree, stree_r, text_buff, text_sz+1);
		printf("\n");
		getchar();
	}

end:
	destroy_suffix_tree(stree);
	return ret;
}
