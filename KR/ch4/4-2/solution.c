#include <stdio.h>

double atof(char s[]) {
	double val = 0.0, power = 1.0;
	int i = 0, sign, esign, exponent = 0;
	sign = (s[i] == '-' ? -1 : 1);
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (; s[i] >= '0' && s[i] <= '9'; i++) {
		val = val*10.0 + s[i] - '0';
	}
	if (s[i] == '.')
		i++;
	for (; s[i] >= '0' && s[i] <= '9'; i++) {
		val = val*10.0 + s[i] - '0';
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E')
		i++;
	esign = (s[i] == '-' ? -1 : 1);
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] != '\0') {
		exponent = exponent*10 + s[i] - '0';
		i++;
	}
	while (exponent > 0) {
		if (esign < 0)
			power *= 10.0;
		else
			val *= 10.0;
		exponent--;
	}
	return sign * val / power;
}

int main() {
	/* Example usage */
	printf("%f\n", atof("125.34e4"));
	printf("%f\n", atof("0.00024E+5"));
	printf("%f\n", atof("2.45"));
	printf("%f\n", atof("2.45e0"));
	printf("%f\n", atof("2569e-3"));
	return 0;
}
