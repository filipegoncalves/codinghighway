#include <stdio.h>
#define abs(x) ((x) < 0 ? -(x) : (x))

int bestsum_m(int x[], int n, int m) {
	int sum = 0, i, bestmatch, besti;
	for (i = 0; i <= m; i++)
		sum += x[i];
	bestmatch = abs(sum);
	besti = 0;
	for (i = 1; i < n-m; i++) {
		sum = sum - x[i-1] + x[i+m];
		if (abs(sum) < bestmatch) {
			bestmatch = abs(sum);
			besti = i;
		}
	}
	return besti;
}

int main() {
	int x[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	int m;
	int n = (int) (sizeof(x)/sizeof(x[0]));
	for (m = 1; m < n-1; m++)
		printf("[%d]\t%d\n", m, bestsum_m(x, n, m));
	return 0;
}
