#include <stdio.h>
#define max(a,b) ((a) > (b) ? (a) : (b))

struct solution {
	int maxl;
	int maxu;
	int total;
	int maxsum;
};

int main() {
	int maxsum(int [], int);
	int x[] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84};
	printf("%d\n", maxsum(x, (int) sizeof(x)/sizeof(x[0])));
	return 0;
}

void maxsum_aux(int [], int, int, struct solution *);
int maxsum(int x[], int n) {
	struct solution s;
	maxsum_aux(x, 0, n-1, &s);
	return s.maxsum;
}

void maxsum_aux(int x[], int l, int u, struct solution *s) {
	struct solution left;
	struct solution right;
	int m;
	if (l >= u) {
		s->maxsum = s->maxu = s->maxl = (l > u ? 0 : max(x[l], 0));
		s->total = (l > u ? 0 : x[l]);
		return;
	}
	m = (l+u)/2;
	maxsum_aux(x, l, m, &left);
	maxsum_aux(x, m+1, u, &right);
	s->maxl = max(left.total+right.maxl, left.maxl);
	s->maxu = max(left.maxu+right.total, right.maxu);
	s->total = left.total + right.total;
	s->maxsum = max(max(left.maxsum, right.maxsum), left.maxu+right.maxl);
}
