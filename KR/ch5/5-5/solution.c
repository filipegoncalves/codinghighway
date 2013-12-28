#include <stdio.h>

char *strncpy(char *s, char *ct, int n) {
	int i;
	char *p = s;
	for (i = 0; i < n && *ct != '\0'; i++)
		*p++ = *ct++;
	for (; i < n; i++)
		*p++ = '\0';
	return s;
}

char *strncat(char *s, char *ct, int n) {
	char *p = s;
	int i;
	for (; *p; p++);
	for (i = 0; i < n && *ct != '\0'; i++)
		p[i] = *ct++;
	p[i] = '\0';
	return s;
}

int strncmp(char *cs, char *ct, int n) {
	int i;
	for (i = 0; (i < n) && (*cs == *ct); cs++, ct++, i++) {
		if (*cs == '\0')
			return 0;
	}
	return i == n ? 0 : *cs-*ct;
}

int main() {
	/* Example usage */
	char a[100] = "Hello";
	char b[] = ", world!";
	char c[sizeof(b)] = { 0 };
	strncpy(c, b, 7);
	printf("c: %s\n", c);
	strncat(a, c, 100);
	printf("a: %s\n", a);
	strncat(a, c, 3);
	printf("a: %s\n", a);
	printf("%d\n", strncmp(b, ", wor", 5));
	printf("%d\n", strncmp(b, ", wor", 500));
	return 0;
}
