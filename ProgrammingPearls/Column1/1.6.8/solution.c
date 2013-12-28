#include <stdio.h>
#include <limits.h>
#define MAXINT 10000000
#define AREACODES_BASE 800
#define AREACODES 100
#define CHAR_BIT_LOG 3 /* assumes that CHAR_BIT == 8, so log_2(8) = 3 */
#define MASK (~(~0 << CHAR_BIT_LOG))
#define setbit(a, x) ((a)[(x) >> CHAR_BIT_LOG] |= 1 << ((x) & MASK))
#define isset(a, x) ((a)[(x) >> CHAR_BIT_LOG] & (1 << ((x) & MASK)))
#define clear(a) { int i; for (i = 0; i < sizeof(a)/sizeof((a)[0]); i++) (a)[i] = 0; }

char arr[(MAXINT-1)/CHAR_BIT+1];
int counters[AREACODES];

int main(int argc, char *argv[]) {
	int code, n, i;
	FILE *f;
	
	if (argc != 2) {
		fprintf(stderr, "[%s] Usage: %s input-file\n", argv[0], argv[0]);
		return 1;
	}
	
	if ((f = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "[%s] Could not open file %s\n", argv[0], argv[1]);
		return 1;
	}
	
	while (fscanf(f, "%d-%*d", &n) == 1)
		counters[n-AREACODES_BASE]++;
		
	for (i = 0; i < AREACODES; i++) {
		if (counters[i] == 0)
			continue;
		clear(arr);
		rewind(f);
		while (counters[i] > 0) {
			fscanf(f, "%d-%d", &code, &n);
			if (code == AREACODES_BASE+i) {
				counters[i]--;
				setbit(arr, n);
			}
		}
		for (n = 0; n < MAXINT; n++)
			if (isset(arr, n))
				printf("%d-%d\n", AREACODES_BASE+i, n);
	}
	return 0;
}
