#include <stdio.h>

int binsrch(int x[], int t) {
	int l = -1;
	int p;
	if (x[511] < t)
		l = 1000 - 512;
	if (x[l+256] < t)
		l += 256;
	if (x[l+128] < t)
		l += 128;
	if (x[l+64] < t)
		l += 64;
	if (x[l+32] < t)
		l += 32;
	if (x[l+16] < t)
		l += 16;
	if (x[l+8] < t)
		l += 8;
	if (x[l+4] < t)
		l += 4;
	if (x[l+2] < t)
		l += 2;
	if (x[l+1] < t)
		l += 1;
	p = l+1;
	if (p >= 1000 || x[p] != t)
		p = -1;
	return p;
}

int main() {
	/* Example usage */
	int v[1000] = { 0 };
	printf("%d\n", binsrch(v, 1));
	return 0;
}
