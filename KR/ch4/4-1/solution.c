#include <stdio.h>

int strrindex(char s[], char t[]) {
	int i, j, k, x;
	k = -1;
	for (i = 0; s[i] != '\0'; i++) {
		for (x = i, j = 0; (t[j] != '\0') && (s[x] == t[j]); x++, j++);
		if (t[j] == '\0') {
			k = i;
		}
	}
	return k;
}

int main() {
	/* Example usage */
	char s[] = "Hello, this is a test case. Hello again!";
	char t[] = "Hello";
	printf("%d\n", strrindex(s,t)); /* Should print 28 */
	return 0;
}
