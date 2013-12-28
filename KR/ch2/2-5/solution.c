#include <limits.h>
#include <stdio.h>

int any(char s1[], char s2[]) {
	int i;
	short buffer[UCHAR_MAX+1] = { 0 };
	for (i = 0; s2[i]; i++)
		buffer[(unsigned char) s2[i]] = 1;
	for (i = 0; s1[i]; i++)
		if (buffer[(unsigned char) s1[i]])
			return i;
	return -1;
}

int main() {
	/* Example usage */
	char s1[] = "Hello, world!\"";
	char s2[] = "\"!,ow";
	printf("%d\n", any(s1, s2));
	return 0;
}
