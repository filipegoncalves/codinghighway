#include <limits.h>
#include <stdio.h>

void squeeze(char s1[], char s2[]) {
	int i, j;
	short buffer[UCHAR_MAX+1] = { 0 };
	for (i = 0; s2[i]; i++)
		buffer[(unsigned char) s2[i]] = 1;
	for (i = j = 0; s1[i]; i++)
		if (!buffer[(unsigned char) s1[i]])
			s1[j++] = s1[i];
	s1[j] = '\0';
}

int main() {
	/* Example usage */
	char s1[] = "Hello, world!\"";
	char s2[] = "lw,o\"";
	squeeze(s1, s2);
	printf("%s\n", s1);
	return 0;
}
