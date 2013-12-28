#include <stdio.h>
#include <limits.h>
#include <float.h>

#define getpos(base, p) ((base) != 0 ? ((base)-(p)) : (p))
#define setbit(arr,b,p,x) ((arr)[getpos(b,p)] |= (unsigned char) 1 << (x))
#define unsetbit(arr,b,p,x) ((arr)[getpos(b,p)] &= ~((unsigned char) 1 << (x)))
#define compute_ranges(type) { \
	int be = is_bigendian(), base = 0, i; \
	unsigned int m = 0; \
	unsigned char my_type[sizeof(type)] = { 0 }; \
	type *f = (type *) my_type; \
	if (!be) \
		base = sizeof(type)-1; \
	type a = 1.0; \
	type b = 0.5; \
	type c = a+b; \
	while (c != a) { \
		m++; \
		b /= 2; \
		c = a+b; \
	} \
	my_type[getpos(base, sizeof(type)-1)] = 1; \
	printf( #type "\n\tLowest possible number with precision loss (only 1 precision bit): %g\n", *f); \
	my_type[getpos(base, sizeof(type)-1)] = 0; \
	setbit(my_type,base,sizeof(type)-m/CHAR_BIT-1,m%CHAR_BIT); \
	printf("\tWithout precision loss: %g", *f); \
	for (i = 0; i < sizeof(type); i++) \
		my_type[i] = ~my_type[i]; \
	unsetbit(my_type,base,0,CHAR_BIT-1); \
	printf(" TO %g\n", *f); }

int is_bigendian();
void read_ranges(void);
void calculate_ranges(void);

int main() {
	#ifdef COMPUTE_DIRECTLY
	calculate_ranges();
	#else
	read_ranges();
	#endif
	return 0;
}

void calculate_ranges(void) {
	printf("The output will have the following syntax:\n");
	printf("TYPE\n\tunsigned: max-value\n\tsigned: min-value TO max-value\n\n");
	printf("CHAR\n\tunsigned: %u\n\tsigned: %d TO %d\n\n", ((unsigned char) ~0), -((char)(((unsigned char) ~0)>>1))-1, ((char)(((unsigned char) ~0)>>1)));
	printf("SHORT\n\tunsigned: %u\n\tsigned: %d TO %d\n\n", ((unsigned short) ~0), -((short)(((unsigned short) ~0)>>1))-1, ((short)(((unsigned short) ~0)>>1)));
	printf("INT\n\tunsigned: %u\n\tsigned: %d TO %d\n\n", ((unsigned int) ~0), -((int)(((unsigned int) ~0)>>1))-1, ((int)(((unsigned int) ~0)>>1)));
	printf("LONG\n\tunsigned: %lu\n\tsigned: %ld TO %ld\n\n", ((unsigned long) ~0), -((long)(((unsigned long) ~0)>>1))-1, ((long)(((unsigned long) ~0)>>1)));
	compute_ranges(float);
	compute_ranges(double);
}

void read_ranges(void) {
	printf("The output will have the following syntax:\n");
	printf("TYPE\n\tunsigned: max-value\n\tsigned: min-value TO max-value\n\n");
	printf("CHAR\n\tunsigned: %u\n\tsigned: %d TO %d\n\n", UCHAR_MAX, SCHAR_MIN, SCHAR_MAX);
	printf("SHORT\n\tunsigned: %u\n\tsigned: %d TO %d\n\n", USHRT_MAX, SHRT_MIN, SHRT_MAX);
	printf("INT\n\tunsigned: %u\n\tsigned: %d TO %d\n\n", UINT_MAX, INT_MIN, INT_MAX);
	printf("LONG\n\tunsigned: %lu\n\tsigned: %ld TO %ld\n\n", ULONG_MAX, LONG_MIN, LONG_MAX);
	printf("FLOAT\n\t%g TO %g (%d precision digits)\n\n", FLT_MIN, FLT_MAX, FLT_DIG);
	printf("DOUBLE\n\t%g TO %g (%d precision digits)\n\n", DBL_MIN, DBL_MAX, DBL_DIG);
}

int is_bigendian() {
	unsigned char i[sizeof(int)] = { 0 };
	i[sizeof(int)-1] = 1;
	int *p = (int *) i;
	return *p == 1;
}
