#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ((a) > (b) ? (b) : (a))
#define abs(x) ((x) < 0 ? -(x) : (x))
#define closest(t, x, y) (abs((x)-(t)) < abs((y)-(t)) ? (x) : (y))
#define max(a,b) ((a) > (b) ? (a) : (b))

struct cumelement {
	int index;
	int value;
};

int main() {
	int closest_zero(int [], int);
	int closest_to(int [], int, int);
	int x[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	printf("%d\n", closest_zero(x, (int) sizeof(x)/sizeof(x[0])));

	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 10000000)); /* 187 - x[2..6] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), -4000000)); /* -116 - x[7..8] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 53)); /* 53 - x[1..7] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), -53)); /* -53 - x[4..4] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 110)); /* 114 - x[1..9] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 25)); /* 26 - x[3..3] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 26)); /* 26 - x[3..3] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 49)); /* 49 - x[2..4] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 65)); /* 65 - x[4..9] */
	printf("%d\n", closest_to(x, (int) sizeof(x)/sizeof(x[0]), 100)); /* 102 - x[4..6] */
	return 0;
}

int compare(const void *n1, const void *n2) {
	return *(const int *) n1 - *(const int *) n2;
}

/* This runs in O(n log(n)) because of the sorting */
int closest_zero(int x[], int n) {
	int *cum = malloc(sizeof(int)*n);
	int res;
	int i;
	cum[0] = x[0];
	for (i = 1; i < n; i++)
		cum[i] = cum[i-1] + x[i];
	qsort((void *) cum, (size_t) n, sizeof(int), compare);
	res = abs(cum[0]);
	for (i = 1; i < n; i++)
		res = min(res, abs(cum[i] - cum[i-1]));
	return res;
}

int compare_elements(const void *e1, const void *e2) {
	return ((const struct cumelement *)e1)->value - ((const struct cumelement *)e2)->value;
}

/* This runs in O(n log(n)), although it tends to be more like O(2n log(n)) because we sort and then we make n binary searches */
int closest_to(int x[], int n, int t) {
	struct cumelement *search(struct cumelement *, int, int);
	int bestvalue = 0, needed, i;
	struct cumelement *cum = (struct cumelement *) malloc(sizeof(struct cumelement)*n);
	struct cumelement *bestmatch;
	cum[0].value = x[0];
	cum[0].index = 0;
	for (i = 1; i < n; i++) {
		cum[i].value = cum[i-1].value + x[i];
		cum[i].index = i;
	}
	qsort((void *) cum, (size_t) n, sizeof(struct cumelement), compare_elements);
	for (i = 0; i < n; i++) {
		needed = cum[i].value - t;
		if (needed == 0)
			return cum[i].value;
		bestmatch = search(cum, n, needed);
		bestvalue = closest(t, bestvalue, (bestmatch->index > cum[i].index ? bestmatch->value - cum[i].value : cum[i].value - bestmatch->value));
		
		/* Debug info to find cum[] limits for each bestvalue. Intentionally left here for future reference
		
		if (bestvalue == (bestmatch->index > cum[i].index ? bestmatch->value - cum[i].value : cum[i].value - bestmatch->value))
			printf("new bestvalue for %d,%d\n", max(cum[i].index, bestmatch->index), min(cum[i].index, bestmatch->index));
			
		*/
		
	}
	return bestvalue;
}

/* Traditional linear sequential search. Uncommenting this (and commenting the binary search function) will make closest_to() run in O(n^2) time

struct cumelement *search(struct cumelement *x, int n, int v) {
	struct cumelement *r = x+n-1;
	while (n--)
		if (closest(v, r->value, x[n].value) == x[n].value)
			r = x+n;
	return r;
}
*/

/* Modified binary search. Returns pointer to array element closest to v */
struct cumelement *search(struct cumelement *x, int n, int v) {
	int l = -1, u = n;
	int m;
	while (l+1 != u) {
		/* invariant: x[l] < v <= x[u] */
		m = (l+u)/2;
		if (x[m].value < v)
			l = m;
		else
			u = m;
	}
	/* assert: l+1 == u && x[l] < v <= x[u] */
	if (u >= n)
		return x+n-1;
	else if (l == -1)
		return x;
	else
		return x+l+(closest(v, x[l].value, x[l+1].value) == x[l+1].value);
}
