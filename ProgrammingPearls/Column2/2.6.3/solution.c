#include <stdio.h>
void swap(char *, int, int, int);
void reverse(char *, int, int);
void rotate(char *v, int i, int n) {
#ifdef USE_REVERSE
	reverse(v, 0, i-1);
	reverse(v, i, n-1);
	reverse(v, 0, n-1);
#else
	if (n == i)
		return;
	if (i == n-i) {
		swap(v, 0, n-i, i);
		return;
	}
	if (i < n-i) {
		swap(v, 0, n-i, i);
		rotate(v, i, n-i);
	}
	else if (i > n-i) {
		swap(v, i-n+i, i, n-i);
		rotate(v, i-n+i, i);
	}
#endif
}

void reverse(char *v, int i, int j) {
	char tmp;
	for (; i < j; i++, j--) {
		tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
	}
}

void swap(char *v, int p1, int p2, int l) {
	char t;
	while (l--) {
		t = v[p1];
		v[p1++] = v[p2];
		v[p2++] = t;
	}
}

int main() {
	/* Example usage */
	char tst[] = "hello, world";
	rotate(tst, 9, 12);
	printf("%s\n", tst); /* Expected: rldhello, wo */
	return 0;
}
