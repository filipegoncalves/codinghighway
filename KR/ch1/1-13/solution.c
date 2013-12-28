#include <stdio.h>
#define MAXLENGTH 60

int main() {
	int state = OUT, l = 0;
	int lengths[MAXLENGTH] = { 0 };
	int c;
	
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN) {
				lengths[l-1]++;
				l = 0;
			}
			state = OUT;
		}			
		else {
			if (state == OUT) {
				state = IN;
			}
			l++;
		}
	}
	/* Handle special case when input ends without newline */
	if (l > 0)
		lengths[l-1]++;
		
	printf("Word length histogram:\n");
	int i, j;
	for (i = 0; i < MAXLENGTH; i++) {
		if (lengths[i]) {
			printf("%4d\t\t", i+1);
			for (j = lengths[i]; j > 0; j--)
				putchar('|');
			printf("\n");
		}
	}
	return 0;
}
