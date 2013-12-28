#include <stdio.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

int main() {
	int maxsum(int [], int);
	int x[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	printf("%d\n", maxsum(x, (int) sizeof(x)/sizeof(x[0])));
	return 0;
}

int maxsum(int x[], int n) {
	int neg, maxendinghere, maxsofar, maxneg;
	int i;
	if (n <= 0)
		return 0;
	maxendinghere = maxsofar = neg = 0;
	maxneg = x[0];
	for (i = 0; i < n; i++) {
		if (x[i] < 0) {
			neg++;
			maxneg = (maxneg > 0 ? x[i] : max(maxneg, x[i]));
		}
		maxendinghere = max(maxendinghere+x[i], 0);
		maxsofar = max(maxsofar, maxendinghere);
	}
	return neg == n ? maxneg : maxsofar;
}
