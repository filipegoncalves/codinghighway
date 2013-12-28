#include <stdio.h>

char lower(char c) {
	return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}

int main() {
	/* Example usage */
	printf("%c%c\n", lower('A'), lower('x')); /* prints ax */
	return 0;
}
