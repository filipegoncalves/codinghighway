#include <stdio.h>

void itoa(int n, char s[]) {
	void reverse(char [], int);
	int i, sign;
	sign = (n < 0 ? -1 : 1);
	i = 0;
	do {
		s[i++] = (n%10)*sign + '0';
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s, i);
}

void reverse(char s[], int last) {
	int j;
	char a;
	last--;
	j = 0;
	while (j < last) {
		a = s[last];
		s[last] = s[j];
		s[j] = a;
		last--;
		j++;
	}
}

int main() {
	/* Example usage */
	char s[20];
	itoa(-((unsigned int) ~0 >> 1)-1, s);
	printf("%s\n", s); /* shows that we solved the problem with INT_MIN */
	return 0;
}
