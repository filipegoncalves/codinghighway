#include <stdio.h>
#include <limits.h>
#define MAXINT 10000000
#define CHAR_BIT_LOG 3 /* assumes that CHAR_BIT == 8, so log_2(8) = 3 */
#define MASK (~(~0 << CHAR_BIT_LOG))
#define setbit(a, x) ((a)[(x) >> CHAR_BIT_LOG] |= 1 << ((x) & MASK))
#define isset(a, x) ((a)[(x) >> CHAR_BIT_LOG] & (1 << ((x) & MASK)))

char arr[(MAXINT-1)/CHAR_BIT+1];

int main() {
	/* Example usage */
	int t[] = { MAXINT/2, MAXINT-1, 0, MAXINT };
	int i;
	
	for (i = 0; i < sizeof(t)/sizeof(t[0]); i++)
		setbit(arr, t[i]);
	
	for (i = 0; i < sizeof(t)/sizeof(t[0]); i++)
		if (!isset(arr, t[i]))
			printf("Oops! %d wasn't correctly stored\n", t[i]);
	
	if (isset(arr, MAXINT/3))
		printf("Oops! Got %d stored, but never did so!\n", MAXINT/3);
	
	return 0;
}
