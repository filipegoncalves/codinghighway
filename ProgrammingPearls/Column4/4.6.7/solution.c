#include <stdio.h>

struct line {
	double a;
	double b;
};

double getvalue(struct line *, double x);
void binsrch(struct line v[], int n, double x, double y, int *l1, int *l2) {
	int m;
	double val;
	*l1 = -1;
	*l2 = n;
	while (*l1 < *l2-1) {
		m = (*l1+*l2)/2;
		val = getvalue(v+m, x);
		if (y < val)
			*l2 = m;
		else if (y > val)
			*l1 = m;
		else
			*l1 = *l2 = m;
	}
	if (*l1 == -1 || *l2 == n)
		*l1 = *l2 = -1;
}

double getvalue(struct line *l, double x) {
	return l->a*x+l->b;
}

void testbinsrch(struct line v[], int n, double x, double y) {
	int line1, line2;
	binsrch(v, n, x, y, &line1, &line2);
	printf("(%f, %f) between %d and %d\n", x, y, line1, line2);
}

int main() {
	struct line lines[] = {
		{ 0, -10 },
		{ 1, -9 },
		{ 0.25, -6 },
		{ -1, -3 },
		{ 0.5, -2 },
		{ -1, 0 },
		{ 1, 1 },
		{ 0.5, 4 },
		{ 0, 6 },
		{ -1, 8 }
	};
	int n = (int) sizeof(lines)/sizeof(lines[0]);
	testbinsrch(lines, n, 0.5, -8); /* 1, 2 */
	testbinsrch(lines, n, 0.001, -8); /* 1, 2 */
	testbinsrch(lines, n, 1, -8.1); /* 0, 1 */
	testbinsrch(lines, n, 1, -10); /* 0, 0 */
	testbinsrch(lines, n, 1, 10); /* -1, -1 */
	testbinsrch(lines, n, 0.3, 0.5); /* 5, 6 */
	testbinsrch(lines, n, 0, 0); /* 5, 5 */
	testbinsrch(lines, n, 1, 1); /* 5, 6 */
	testbinsrch(lines, n, 1, -1.45); /* 4, 5 */
	testbinsrch(lines, n, 0.5, 5); /* 7, 8 */
	testbinsrch(lines, n, 0, 40); /* -1, -1 */
	testbinsrch(lines, n, 1, -50); /* -1, -1 */
	testbinsrch(lines, n, 0, 6); /* 8, 8 */
	testbinsrch(lines, n, 0.3, -0.5); /* 4, 5 */
	return 0;
}
