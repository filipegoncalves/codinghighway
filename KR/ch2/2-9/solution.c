#include <stdio.h>

int bitcount(unsigned x) {
	int i;
	for (i = 0; x; i++, x &= (x-1));
	return i;
}

int main() {
	/* Example usage */
	printf("%d\n", bitcount((unsigned int) 857028)); /* prints 9 (857028 = 11010001001111000100) */
	return 0;
}
