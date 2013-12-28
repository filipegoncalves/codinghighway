#include <stdio.h>

int binsrch(int [], int, int);
int main() {
	/* Example usage */
	int x[] = { 1, 2, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 22, 13, 54321, 22223 };
	printf("%d %d %d\n", binsrch(x, 2, 16), binsrch(x, 20, 16), binsrch(x, 54321, 16));
	return 0;
}

int binsrch(int x[], int t, int n) {
	int l = -1, u = n, m;
	while (l+1 != u) {
		/* invariant: x[l] < t <= x[u] */
		m = (l+u)/2;
		if (x[m] < t)
			l = m;
		else
			u = m;
	}
	/* assert: l+1 == u && x[l] < t <= x[u] */
	if (u >= n || x[u] != t)
		return -1;
	return u;
}
