#include <stdio.h>

void strcat_ptr(char *s, char *t) {
	char *p = s, *q = t;
	for (; *p; p++);
	while ((*p++ = *q++));
}

int main() {
	/* Example usage */
	char s[20] = "Hello";
	char t[] = ", world!";
	strcat_ptr(s,t);
	printf("%s\n", s);
	return 0;
}
