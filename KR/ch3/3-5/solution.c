#include <stdio.h>

void itob(int n, char s[], int b) {
	int i, sign, aux;
	void reverse(char [], int);
	sign = (n < 0 ? -1 : 1);
	i = 0;
	do {
		aux = (n%b)*sign;
		if (aux <= 9)
			aux += '0';
		else
			aux += 'A' - 10;
		s[i++] = aux;
	} while ((n /= b) != 0);
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
	itob(-((unsigned int) ~0 >> 1)-1, s, 16);
	printf("%s\n", s);
	return 0;
}
