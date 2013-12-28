#include <stdio.h> /* for NULL definition */

void *my_malloc(unsigned);
void *my_calloc(unsigned nmemb, unsigned size) {
	int i;
	char *ptr = (char *) my_malloc(nmemb*size);
	if (ptr == NULL)
		return NULL;
	for (i = 0; i < nmemb*size; i++)
		ptr[i] = 0;
	return (void *) ptr;
}

int main() {
	/* Example usage */
	int *a = (int *) my_calloc(7, sizeof(int));
	int i;
	for (i = 0; i < 7; i++)
		printf("%d\n", a[i]);
	return 0;
}
