#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void randselect(int, int);

int main(int argc, char *argv[]) {
	int m, n;
	srand(time(NULL));
	sscanf(argv[1], "%d", &m);
	sscanf(argv[2], "%d", &n);
	randselect(m, n);
	return 0;
}

void randselect(int m, int n) {
	if (m > 0) {
		if (rand() % n < m) {
			randselect(m-1, n-1);
			printf("%d\n", n-1);
		}
		else
			randselect(m, n-1);
	}
}
