#include <stdio.h>
#include <errno.h>
#define SEGMENTS 5
#define MAX_VAL 65535
#define UP 0x4
#define MIDDLE 0x2
#define DOWN 0x1
#define UPPER_LEFT 0x8
#define UPPER_RIGHT 0x10
#define LOWER_LEFT 0x20
#define LOWER_RIGHT 0x40

char numbers[] = {
	UP | DOWN | UPPER_LEFT | LOWER_LEFT | UPPER_RIGHT | LOWER_RIGHT, /* 0 */
	UPPER_RIGHT | LOWER_RIGHT, /* 1 */
	UP | DOWN | MIDDLE | UPPER_RIGHT | LOWER_LEFT, /* 2 */
	UP | MIDDLE | DOWN | UPPER_RIGHT | LOWER_RIGHT, /* 3 */
	UPPER_LEFT | MIDDLE | UPPER_RIGHT | LOWER_RIGHT, /* 4 */
	UP | MIDDLE | DOWN | UPPER_LEFT | LOWER_RIGHT, /* 5 */
	UP | MIDDLE | DOWN | LOWER_LEFT | UPPER_LEFT | LOWER_RIGHT, /* 6 */
	UP | UPPER_RIGHT | LOWER_RIGHT, /* 7 */
	UP | DOWN | MIDDLE | UPPER_LEFT | LOWER_LEFT | UPPER_RIGHT | LOWER_RIGHT, /* 8 */
	UP | MIDDLE | UPPER_LEFT | UPPER_RIGHT | LOWER_RIGHT  /* 9 */
};

char rep[SEGMENTS];

void print_representation(char [], int);
char *get_representation(unsigned short);
int main() {
	unsigned short val;
	
	while (1) {
		errno = 0;
		printf("Enter a number: ");
		if (scanf("%hu", &val) != 1)
			break;
		if (errno == ERANGE) {
			printf("Value is too large, max. allowed is %d\n", MAX_VAL);
			continue;
		}
		printf("\nSeven-segment representation:\n");
		print_representation(get_representation(val), SEGMENTS);
	}
	return 0;
}

char *get_representation(unsigned short v) {
	int i = SEGMENTS-1;
	while (v) {
		rep[i--] = numbers[v%10];
		v /= 10;
	}
	while (i >= 0)
		rep[i--] = numbers[0];
	return rep;
}

void print_representation(char repr[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("Segment %d:\n", i);
		printf("%s\n", repr[i] & UP ? " __ " : "");
		printf("%s%s%s\n", (repr[i] & UPPER_LEFT ? "|" : " "), (repr[i] & MIDDLE ? "__" : "  "), (repr[i] & UPPER_RIGHT ? "|" : ""));
		printf("%s%s%s\n", (repr[i] & LOWER_LEFT ? "|" : " "), (repr[i] & DOWN ? "__" : "  "), (repr[i] & LOWER_RIGHT ? "|" : ""));
	}
}
