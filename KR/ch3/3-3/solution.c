#include <stdio.h>

void expand(char s1[], char s2[]) {
	s2[0] = s1[0];
	if (!s2[0])
		return;
	int x = 1;
	int y = 1;
	char z;
	while (s1[x]) {
		if (s1[x] == '-' && 
			isalnum((unsigned char) s1[x-1]) &&
			isalnum((unsigned char) s1[x+1])) {
				for (z = s1[x-1]+1; s2[y-1] != s1[x+1]; z++) {
					s2[y++] = z;
				}
				x++;
			 }
		else {
			s2[y++] = s1[x];
		}
		x++;
	}
	s2[y] = '\0';
}

int main() {
	/* Example usage */
	char s1[] = "-a-c-kke0-9p-z-";
	char s2[100]; /* 100 is surely big enough */
	expand(s1, s2);
	printf("%s\n", s2);
	return 0;
}
