#include <stdio.h>

void reverse(char *, int, int);
void rotate(char *v, int i, int j, int n) {
	reverse(v, 0, i-1);
	reverse(v, i, n-j-1);
	reverse(v, n-j, n-1);
	reverse(v, 0, n-1);
}

void reverse(char *v, int i, int j) {
	char tmp;
	for (; i < j; i++, j--) {
		tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
	}
}

int main() {
	/* Example usage */
	char str[] = "Hello, world. This is an example.";
	rotate(str, 4, 11, 33);
	/* Expected result:
	   an example.o, world. This is Hell
	*/
	printf("%s\n", str);
	return 0;
}
