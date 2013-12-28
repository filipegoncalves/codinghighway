#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define MAXLINES 5000
#define MAXLINE 1000

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

/* End of comparison functions */

int main(int argc, char *argv[]) {
	int nlines;
	int reverse = 0;
	int i;
	int (*comp)(void *, void *, ...) = (int (*)(void*,void*,...)) strcmp_wrapper;
	
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-n") == 0)
			comp = (int (*)(void*,void*,...)) numcmp;
		else if (strcmp(argv[i], "-f") == 0)
			comp = (int (*)(void*,void*,...)) strcasecmp_wrapper;
		else if (strcmp(argv[i], "-r") == 0)
			reverse = 1;
	}
	
	if (reverse) {
		reverse_order(NULL, NULL, comp);
		comp = (int (*)(void*,void*,...)) reverse_order;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		my_qsort((void **) lineptr, 0, nlines-1, comp);
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
