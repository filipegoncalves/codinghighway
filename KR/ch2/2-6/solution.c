#include <stdio.h>

int setbits(int x, int p, int n, int y) {
	return (x & ~(~(~0 << n) << (p-n+1))) | ((y & ~(~0 << n)) << (p-n+1));
}

int main() {
	/* Example usage */
	printf("%d\n", setbits(512, 5, 4, 127)); /* Prints 572 = 1000111100 */
	return 0;
}
