#include <stdio.h>

int invert(int x, int p, int n) {
	return x ^ (~(~0 << n) << (p-n+1));
}

int main() {
	/* Example usage */
	printf("%d\n", invert(512, 8, 9)); /* Prints 1023 = 1111111111 */
	return 0;
}
