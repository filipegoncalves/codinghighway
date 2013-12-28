#include <stdio.h>
#include <limits.h>

#define MAXINT 10000000
#define INTBITS 4 /* says how many bits each number uses */
#define incr(a, x) ((a)[(x)/(CHAR_BIT/INTBITS)] += 1 << ((x)%(CHAR_BIT/INTBITS))*INTBITS)
#define getcnt(a, x) (((a)[(x)/(CHAR_BIT/INTBITS)] >> (((x)%(CHAR_BIT/INTBITS))*INTBITS)) & MASK)

unsigned char arr[(MAXINT*INTBITS-1)/CHAR_BIT+1];

int main() {
	int n;
	unsigned char c;
	
	/* Read and store every number */
	while (scanf("%d", &n) == 1)
		incr(arr, n);
	
	/* Print sorted result */
	for (n = 0; n < MAXINT; n++)
		for (c = getcnt(arr, n); c > 0; c--)
			printf("%d\n", n);
	
	return 0;
}
