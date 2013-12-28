#include <stdlib.h>
#include <stdio.h>
#define MAXINT 10000000

int comparator(const void *, const void *);
int arr[MAXINT];
int main() {
	int i = 0, j;
	
	/* Read and store every number */
	while (scanf("%d", arr+i) == 1)
		i++;
		
	/* Sort... */
	qsort(arr, i, sizeof(arr[0]), comparator);
	
	/* ... and print the sorted result */
	for (j = 0; j < i; j++)
		printf("%d\n", arr[j]);
	
	return 0;
}

int comparator(const void *a, const void *b) {
	const int v1 = *(const int *) a;
	const int v2 = *(const int *) b;
	return v1 < v2 ? -1 : (v1 > v2 ? 1 : 0);
}
