#include <limits.h>
#include <stdio.h>

int main() {
	int c;
	int freq[UCHAR_MAX] = { 0 };
	while ((c = getchar()) != EOF) {
		freq[(unsigned char) c]++;
	}
	unsigned char i;
	int j;
	for (i = 0; i < UCHAR_MAX; i++) {
		if (freq[i]) {
			if ((char) i == '\n')
				printf("\\n");
			else if ((char) i == '\t')
				printf("\\t");
			else if ((char) i == '\\')
				printf("\\");
			else if ((char) i == '\r')
				printf("\\r");
			else if ((char) i == ' ')
				printf("SPACE");
			else
				printf("%c", (char) i);
			printf("\t\t");
			for (j = freq[i]; j > 0; j--)
				putchar('|');
			printf("\n");
		}
	}
	return 0;
}
