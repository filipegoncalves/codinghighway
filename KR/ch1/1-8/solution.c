#include <stdio.h>

int main() {
	int c;
	int bl, t, nl;
	bl = 0;
	t = 0;
	nl = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			bl++;
		else if (c == '\t')
			t++;
		else if (c == '\n')
			nl++;
	}
	
	printf("Blanks: %d\n", bl);
	printf("Tabs: %d\n", t);
	printf("Newlines: %d\n", nl);
	
	return 0;
}
