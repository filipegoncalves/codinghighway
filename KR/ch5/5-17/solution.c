#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLINE 1000
#define FIELDELIM '|'
#define issymbol(c) (!isupper(c) && !islower(c) && !isblank(c) && !isdigit(c))

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *, ...)) {
	int i, last;
	void swap(void *v[], int, int);
	
	if (left >= right)
		return;
		
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	my_qsort(v, left, last-1, comp);
	my_qsort(v, last+1, right, comp);
}

/* Comparison functions */
int numcmp(char *s1, char *s2, ...) {
	double v1, v2;
	
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int reverse_order(void *v1, void *v2, ...) {
	static int (*original)(void *, void *, ...) = NULL;
	if (!v1 && !v2) {
		va_list argp;
		va_start(argp, v2);
		original = va_arg(argp, int (*)(void*, void*, ...));
		va_end(argp);
		return 0;
	}
	return -(*original)(v1, v2);
}

int strcmp_wrapper(char *v1, char *v2, ...) {
	return strcmp(v1, v2);
}

int strcasecmp_wrapper(char *s1, char *s2, ...) {
	return strcasecmp(s1, s2);
}

int dcmp(char *s1, char *s2, ...) {
	int i = 0, j = 0;
	
	for (; s1[i] && issymbol((unsigned char) s1[i]); i++);
	for (; s2[j] && issymbol((unsigned char) s2[j]); j++);
	
	while(s1[i] == s2[j]) {
		if (s1[i] == '\0')
			return 0;
		while (s1[++i] && issymbol((unsigned char) s1[i]));
		while (s2[++j] && issymbol((unsigned char) s2[j]));
	}
	return s1[i]-s2[j];
}

int dcasecmp(char *s1, char *s2, ...) {
	int i = 0, j = 0;
	
	for (; s1[i] && issymbol((unsigned char) s1[i]); i++);
	for (; s2[j] && issymbol((unsigned char) s2[j]); j++);
	
	while(tolower((unsigned char) s1[i]) == tolower((unsigned char) s2[j])) {
		if (s1[i] == '\0')
			return 0;
		while (s1[++i] && issymbol((unsigned char) s1[i]));
		while (s2[++j] && issymbol((unsigned char) s2[j]));
	}
	return s1[i]-s2[j];
}

int fieldcomp(char *s1, char *s2, ...) {
	char *delim_pos(char *, int, char **);
	static int (*original)(void *, void *, ...) = NULL;
	static int field = 0;
	char *ptr_begin_s1, *ptr_begin_s2, *ptr_end_s1, *ptr_end_s2, original_end_s1, original_end_s2;
	int return_value;
	
	if (!s1 && !s2) {
		va_list argp;
		va_start(argp, s2);
		original = va_arg(argp, int (*)(void*, void*, ...));
		field = va_arg(argp, int);
		va_end(argp);
		return 0;
	}
	
	/* Find field n on each string s1 and s2 */
	ptr_begin_s1 = delim_pos(s1, field, &ptr_end_s1);
	ptr_begin_s2 = delim_pos(s2, field, &ptr_end_s2);
	original_end_s1 = *ptr_end_s1;
	original_end_s2 = *ptr_end_s2;
	*ptr_end_s1 = *ptr_end_s2 = '\0';
	/* Compare the fields - original must be some function that compares pairs of char * */
	return_value = (*original)(ptr_begin_s1, ptr_begin_s2);
	/* Restore what we changed in the original strings */
	*ptr_end_s1 = original_end_s1;
	*ptr_end_s2 = original_end_s2;
	return return_value;
}

/* End of comparison functions */

int main(int argc, char *argv[]) {
	int nlines;
	int i, fold = 0, dir = 0, num = 0, reverse = 0, field = 0;
	int (*comp_function)(void *, void *, ...) = (int (*)(void*, void*, ...)) strcmp_wrapper;
	
	/* Read arguments */
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0) {
			num = 1;
		} else if (strcmp(argv[i], "-r") == 0) {
			reverse = 1;
		} else if (strcmp(argv[i], "-f") == 0) {
			fold = 1;
		} else if (strcmp(argv[i], "-d") == 0) {
			dir = 1;
		} else if (strcmp(argv[i], "-x") == 0) {
			if (i+1 < argc && isdigit((unsigned char) argv[i+1][0])) {
				field = atoi(argv[i+1]);
				if (field < 1) {
					printf("Invalid field identifier, ignoring...\n");
					field = 0;
				}
				i++;
			} else {
				printf("Expecting positive integer after -x, ignoring entered value...\n");
			}
		}
	}
	
	/* Search for non-sense combined options */
	if (num && (fold || dir)) {
		printf("Warning: overriding -f and -d with -n\n");
	}
	
	/* Process arguments */
	if (fold && dir) {
		comp_function = (int (*)(void*, void*, ...)) dcasecmp;
	} else if (fold) {
		comp_function = (int (*)(void*, void*, ...)) strcasecmp_wrapper;
	} else if (dir) {
		comp_function = (int (*)(void*, void*, ...)) dcmp;
	}
	if (num) {
		comp_function = (int (*)(void*, void*, ...)) numcmp;
	}

	if (field != 0) {
		/* Initialize fieldcomp */
		fieldcomp(NULL, NULL, comp_function, field);
		/* And set new comp_function! */
		comp_function = (int (*)(void*, void*, ...)) fieldcomp;
	}
	
	if (reverse) {
		/* Initialize reverser... */
		reverse_order(NULL, NULL, comp_function);
		/* ... and set new comp_function */
		comp_function = reverse_order;
	}
	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		my_qsort((void **) lineptr, 0, nlines-1, comp_function);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}


void swap(void *v[], int i, int j) {
	void *temp;
	
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLINE];
	int my_getline(char [], int);
	
	nlines = 0;
	while ((len = my_getline(line, MAXLINE)) > 0)
		if (nlines >= maxlines || (p = malloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
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

/* Returns a pointer to the beginning of field p in string s. Stores the end of the field in *end. */
char *delim_pos(char *s, int p, char ** end) {
	char *begin_ptr = s;
	char *ptr = s;
	
	while (p) {
		while (*ptr && *ptr != FIELDELIM) {
			ptr++;
		}
		if (!--p) {
			*end = ptr;
		} else {
			if (!*ptr) {
				*end = ptr;
				return begin_ptr;
			}
			else {
				ptr++;
				begin_ptr = ptr;
			}
		}
	}
	return begin_ptr;
}
