#include <stdio.h>
#include <limits.h>
#define MAXINT 10000000
#define CHAR_BIT_LOG 3 /* assumes that CHAR_BIT == 8, so log_2(8) = 3 */
#define MASK (~(~0 << CHAR_BIT_LOG))
#define setbit(a, x) ((a)[(x) >> CHAR_BIT_LOG] |= 1 << ((x) & MASK))
#define isset(a, x) ((a)[(x) >> CHAR_BIT_LOG] & (1 << ((x) & MASK)))

char arr[(MAXINT-1)/CHAR_BIT+1];

int main() {
	int n;
	
	/* Read and store every number */
	while (scanf("%d", &n) == 1)
		setbit(arr, n);
	
	/* Print sorted result */
	for (n = 0; n < MAXINT; n++)
		if (isset(arr, n))
			printf("%d\n", n);
	
	return 0;
}
