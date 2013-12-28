#include <stdio.h>
#include <limits.h>

unsigned int rightrot(unsigned int x, unsigned int n) {
	return (unsigned int) ((x >> n) | ((~(~0 << n) & x) << (sizeof(int)*CHAR_BIT-n)));
}

int main() {
	/* Example usage */
	printf("%u\n", rightrot(2487,5)); /* prints 3087007821 if ints are 32 bits */
	return 0;
}
