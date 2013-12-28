#include <stdio.h>

int binsearch(int x, int v[], int n) {
	int low, high, mid;
	low = 0;
	high = n-1;
	mid = high/2;
	while ((low <= high) && (x != v[mid])) {
		if (x < v[mid])
			high = mid-1;
		else
			low = mid+1;
		mid = (low+high)/2;
	}
	if (x == v[mid])
		return mid;
	return -1;
}

int main() {
	/* Example usage */
	int v[] = { 2, 6, 9, 12, 15, 21, 25, 30, 55, 60, 61, 62, 63, 64, 65 };
	printf("30: %d\n", binsearch(30, v, sizeof(v)/sizeof(v[0]))); /* prints 30: 7 */
	printf("100: %d\n", binsearch(100, v, sizeof(v)/sizeof(v[0]))); /* prints 100: -1 */
	return 0;
}
