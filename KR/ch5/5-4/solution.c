#include <stdio.h>

int strend(char *s, char *t) {
	char *p, *q;
	for (p = s; *p; p++);
	for (q = t; *q; q++);
	while (q > t && p > s && *q-- == *p--);
	return q == t ? *q == *p : 0;
}

int main() {
	/* Example usage */
	printf("%d\n", strend("Hello, world!", "world!"));
	printf("%d\n", strend("Hello", "HHHHHello"));
	printf("%d\n", strend("", "Hello"));
	printf("%d\n", strend("Hello", ""));
	printf("%d\n", strend("Hello", "Hello"));
	/* Should print:
		1
		0
		0
		1
		1
	*/
	return 0;
}
