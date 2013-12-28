#include <stdio.h>

/* Computes how many bits are in a size_t unit */
size_t size_t_unit(void) {
	/* sizeof(char) is always 1 */
	size_t res = 0;
	unsigned char c = ~0;
	for (; c; res++, c >>= 1);
	return res;
}

int is_bigendian(void) {
	unsigned char i[sizeof(int)] = { 0 };
	i[sizeof(int)-1] = 1;
	int *p = (int *) i;
	return *p == 1;
}

int wordlength(void) {
	unsigned int i = (unsigned) ~0;
	int res;
	for (res = 0; i >>= 1; res++);
	return res+1;
}

void printbinary(int n) {
	int i;
	size_t bits = sizeof(int)*size_t_unit();
	unsigned int j = 1 << (bits-1);
	for (i = 0; i < bits; i++, j >>= 1) {
		printf("%d", (j&n ? 1 : 0));
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	printf("Ok dude, let's take a look at this machine...\n");
	printf("I see that there are %d bits in a char\n", (int) size_t_unit());
	printf("Woooha, this is a %s architecture!\n", is_bigendian() ? "big endian" : "little endian");
	printf("It looks like there are %d bits in a machine word\n", wordlength());
	printf("Let's see how -1 is represented: ");
	printbinary(-1);
	printf("Nice! What about %d (INT_MAX)?\n", ((unsigned int) ~0) >> 1);
	printbinary((int) (((unsigned int) ~0) >> 1));
	printf("What about %d (INT_MIN)?\n", -(((unsigned int) ~0) >> 1)-1);
	printbinary((int) -(((unsigned int) ~0) >> 1)-1);
	printf("What about abs(INT_MIN)?\n");
	printbinary((int) -(-(((unsigned int) ~0) >> 1)-1));
	printf("Oops! That's the case where x = -x for x != 0, which theoretically and mathematically speaking can't happen, but it does in real world!\n");
	return 0;
}
