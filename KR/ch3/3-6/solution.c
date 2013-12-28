#include <stdio.h>

void itoa(int n, char s[], int width) {
	int i, sign;
	void reverse(char [], int);
	sign = (n < 0 ? -1 : 1);
	i = 0;
	do {
		s[i++] = (n%10)*sign + '0';
	} while ((n /= 10) != 0);
	if (sign < 0)
		s[i++] = '-';
	while (i < width) {
		s[i++] = ' ';
	}	
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
	char s[30];
	itoa(-((unsigned int) ~0 >> 1)-1, s, 25);
	printf("%s\n", s);
	return 0;
}
