#include <stdio.h>
#define BUFSIZE 20
#define N 4000

#ifdef DECODE_VERSION
int main() {
	char buf[BUFSIZE];
	while (scanf("%*d %*d %s", buf) != EOF)
		printf("%s\n", buf);
	return 0;
}
#else
int main() {
	char buf[BUFSIZE];
	int c = 0, r = 0;
	while (scanf("%s", buf) != EOF) {
		printf("%d %d %s\n", c, r, buf);
		if (!(c = (c+1)%N))
			r++;
	}
	return 0;
}
#endif
