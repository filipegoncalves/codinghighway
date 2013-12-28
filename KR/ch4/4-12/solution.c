#include <stdio.h>

int itoa(int n, char s[]) {
	int i;
	if (!(n/10)) {
		i = 0;
		if (n < 0) {
			n = -n;
			s[i++] = '-';
		}
		s[i++] = n + '0';
	}
	else {
		s[i = itoa(n/10, s)] = (n < 0 ? -(n%10) : n%10) + '0';
		i++;
	}
	s[i] = '\0';
	return i;
}

int main() {
	/* Example usage */
	char s[20]; /* this is probably big enough */
	itoa(-((unsigned int) ~0 >> 1)-1, s); /* shows that it works for INT_MIN */
	printf("%s\n", s);
	return 0;
}
