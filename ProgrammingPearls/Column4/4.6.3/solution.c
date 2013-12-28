#include <stdio.h>

int binsrch(int [], int, int);
int main() {
	/* Example usage */
	int x[] = { 1, 2, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 22, 13, 54321, 22223 };
	printf("%d %d %d\n", binsrch(x, 2, 16), binsrch(x, 20, 16), binsrch(x, 54321, 16));
	return 0;
}

int binsrch_aux(int [], int, int, int);
int binsrch(int x[], int t, int n) {
	return binsrch_aux(x, t, 0, n-1);
}

int binsrch_aux(int x[], int t, int l, int u) {
	int m;
	if (l > u)
		return -1;
	m = (l+u)/2;
	if (x[m] < t)
		return binsrch_aux(x, t, m+1, u);
	else if (x[m] > t)
		return binsrch_aux(x, t, l, m-1);
	else
		return m;
}
