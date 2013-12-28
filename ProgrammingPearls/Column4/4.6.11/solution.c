#include <stdio.h>
typedef int DataType;

int binarysearch(DataType x[], int n, int t);

int main() {
	DataType v[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("%d %d %d %d\n", binarysearch(v, 10, -1), binarysearch(v, 10, 11), binarysearch(v, 10, 2), binarysearch(v, 10, 9));
	return 0;
}

int binarysearch(DataType x[], int n, int t) {
	int m = n/2, p;
	if (n == 0)
		return -1;
	else if (x[m] < t) {
		p = binarysearch(x+m+1, n-m-1, t);
		return p == -1 ? -1 : p+m+1;
	}
	else if (x[m] > t)
		return binarysearch(x, m, t);
	else
		return m;
}
