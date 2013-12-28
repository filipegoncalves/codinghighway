#include <stdio.h>

#define swap(t,x,y) { t __z; __z = x; x = y; y = __z; }

int main() {
	/* Example usage */
	int a = 4;
	int b = 9;
	swap(int, a, b);
	printf("a: %d b: %d\n", a, b);
	return 0;
}
