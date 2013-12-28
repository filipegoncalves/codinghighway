#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

int my_getline(char *s, int lim) {
	int c, i;
	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		*(s + i++) = c;
	if (c == '\n')
		*(s + i++) = c;
	*(s+i) = '\0';
	return i;
}

int my_atoi(char *s) {
	int val = 0, sign;
	for (; isspace((unsigned char) *s); s++);
	sign = (*s == '-' ? -1 : 1);
	if (*s == '-' || *s == '+')
		s++;
	while (isdigit((unsigned char) *s)) {
		val = val * 10 + *s - '0';
		s++;
	}
	return sign*val;
}

char *my_itoa(int n, char *s) {
	char *my_reverse(char *);
	char *p = s;
	int sign;
	sign = (n < 0 ? -1 : 1);
	do {
		*s++ = ((n % 10) * sign) + '0';
	} while ((n /= 10));
	if (sign == -1)
		*s++ = '-';
	*s = '\0';
	my_reverse(p);
	return p;
}

char *my_reverse(char *s) {
	char *a = s, *b = s, c;
	for (; *b; b++);
	b--;
	while (b > a) {
		c = *a;
		*a = *b;
		*b = c;
		b--;
		a++;
	}
	return s;
}

int strindex(char *s, char *t) {
	int i, j, k;
	
	for (i = 0; *(s+i) != '\0'; i++) {
		for (j = i, k = 0; *(t+k) != '\0' && *(s+j)==*(t+k); j++,  k++);
		if (k > 0 && *(t+k) == '\0')
			return i;
	}
	return -1;
}

int getop(char *s) {
	int getch(void);
	void ungetch(int);
	int i, c;
	while ((*s = c = getch()) == ' ' || c == '\t');
	*(s+1) = '\0';
	if (!isdigit(c) && c != '.')
		return c;
	i = 0;
	if (isdigit(c)) {
		while (isdigit(c = getch())) {
			*(s + ++i) = c;
		}
		*(s + ++i) = c;
	}
	if (c == '.') {
		while (isdigit(c = getch())) {
			*(s + ++i) = c;
		}
		*(s + ++i) = c;
	}
	*(s+i) = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int main() {
	/* Example usage 
	   You can easily test getop's pointer version by replacing its original version with this one in exercise 4-3
	*/
	char b[100];
	char c[] = "!dlrow ,olleH";
	printf("%s %d\n", my_itoa(55689, b), my_atoi("-668"));
	printf("%s\n", my_reverse(c));
	printf("%d\n", strindex(c, "world!"));
	return 0;
}
