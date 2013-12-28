#include <stdio.h>

int main() {
	int c = EOF;
	printf("%d\n", c != EOF);
	c = 'a';
	printf("%d\n", c != EOF);
	return 0;
}
