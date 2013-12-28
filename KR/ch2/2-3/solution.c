#include <stdio.h>

int htoi(char s[]) {
	int i = 0, val, n = 0;
	if (s[0] == '\0')
		return 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		i = 2;
	while (s[i]) {
		if (s[i] >= '0' && s[i] <= '9')
			val = s[i]-'0';
		else if (s[i] >= 'A' && s[i] <= 'Z')
			val = s[i]-'A'+10;
		else if (s[i] >= 'a' && s[i] <= 'z')
			val = s[i]-'a'+10;
		else
			val = 0; /* Never reached for well-formed input */
		n = n*16 + val;
		i++;
	}
	return n;
}

int main() {
	/* Example usage */
	printf("%d\n", htoi("AF58"));
	printf("%d\n", htoi(""));
	printf("%d\n", htoi("0xAA4"));
	printf("%d\n", htoi("0XA"));
	printf("%d\n", htoi("512"));
	return 0;
}
