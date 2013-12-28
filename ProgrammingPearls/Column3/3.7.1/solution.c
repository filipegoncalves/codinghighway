#include <stdio.h>

struct tax_descriptor {
	unsigned long long income;
	unsigned long long base;
	float increment;
};

struct tax_descriptor taxes[] = {
	{ 0ULL, 0ULL, 0.0f }, 
	{ 2200ULL, 0ULL, 0.0f },
	{ 2700ULL, 0ULL, 0.14f },
	{ 3200ULL, 70ULL, .15f },
	{ 3700ULL, 145ULL, .16f },
	{ 4200ULL, 225ULL, .17f },
	{ 0ULL, 53090ULL, .70f }
};

int get_position(unsigned long long income) {
	int i;
	int lim = (int) sizeof(taxes)/sizeof(taxes[0]) - 1;
	for (i = 0; i < lim && income > taxes[i].income; i++);
	return i;
}

long double calculate_tax(unsigned long long income) {
	int pos;
	struct tax_descriptor tax = taxes[pos = get_position(income)];
	return tax.base + (long double) tax.increment*(income - taxes[pos-1].income);
}

int main(int argc, char *argv[]) {
	int i;
	unsigned long long income;
	for (i = 1; i < argc; i++) {
		sscanf(argv[i], "%llu", &income);
		printf("%llu\t%.2Lf\n", income, calculate_tax(income));
	}
	return 0;
}
