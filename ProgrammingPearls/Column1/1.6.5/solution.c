#include <stdio.h>
#include <limits.h>
#include <fcntl.h>

#define MAXINT 10000000
#define CHAR_BIT_LOG 3 /* assumes that CHAR_BIT == 8, so log_2(8) = 3 */
#define MASK (~(~0 << CHAR_BIT_LOG))
#define setbit(a, x) ((a)[(x) >> CHAR_BIT_LOG] |= 1 << ((x) & MASK))
#define isset(a, x) ((a)[(x) >> CHAR_BIT_LOG] & (1 << ((x) & MASK)))

char arr[(MAXINT-1)/2+1];

void readnumbers(int, int, int, FILE *);
void printnumbers(int, int, int);

int main(int argc, char *argv[]) {
	int i;
	FILE *f;
	
	if (argc != 2) {
		fprintf(stderr, "[%s] Usage: %s input-file\n", argv[0], argv[0]);
		return 1;
	}
	
	if ((f = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "[%s] Could not open file %s\n", argv[0], argv[1]);
		return 1;
	}
	
	/* 1st pass, reading from 0 to MAXINT/2-1 */
	readnumbers(0, MAXINT/2-1, 0, f);
	printnumbers(0, MAXINT/2-1, 0);
	
	/* Clear the array */
	for (i = 0; i <= sizeof(arr)/sizeof(arr[0]); i++)
		arr[i] = 0;
	
	/* 2nd pass, reading from MAXINT/2 to MAXINT */
	rewind(f);
	readnumbers(MAXINT/2, MAXINT, f);
	printnumbers(MAXINT/2, MAXINT);
	
	fclose(f);

	return 0;
}

void readnumbers(int from, int to, FILE *fp) {
	int n;
	while (fscanf(fp, "%d", &n) == 1)
		if (n >= from && n <= to)
			setbit(arr, n-from);
}

void printnumbers(int from, int to) {
	int i;
	
	for (i = from; i <= to; i++)
		if (isset(arr, i))
			printf("%d\n", i+from);
}
