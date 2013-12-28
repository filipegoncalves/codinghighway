#include <stdio.h>
#include <string.h>

void reverse_aux(char s[], int left, int right) {
	char tmp;
	if (left >= right)
		return;
	tmp = s[left];
	s[left] = s[right];
	s[right] = tmp;
	reverse_aux(s, left+1, right-1);
}

void reverse(char s[]) {
	reverse_aux(s, 0, strlen(s)-1);
}

int main() {
	/* Example usage */
	char s[] = "Hello, world!";
	reverse(s);
	printf("%s\n", s);
	return 0;
}
