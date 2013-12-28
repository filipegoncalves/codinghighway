#include <stdio.h>

void escape(char s[], char t[]) {
	int i, j;
	for (i = j = 0; t[i]; i++, j++) {
		switch (t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j] = 't';
				break;
			default:
				s[j] = t[i];
				break;				
		}
	}
	s[j] = t[i];
}
void escapeback(char s[], char t[]) {
	int i, j;
	for (i = j = 0; t[i]; i++, j++) {
		if (t[i] == '\\' && (t[i+1] == 'n' || t[i+1] == 't')) {
			if (t[i+1] == 'n')
				s[j] = '\n';
			else
				s[j] = '\t';
			i++;
		}
		else
			s[j] = t[i];
	}
	s[j] = t[i];
}

int main() {
	/* Example usage */
	char t[] = "Hello, world.\nThis is a test.\t\n";
	char s[sizeof(t)+4];
	char a[sizeof(t)+1];
	escape(s,t);
	printf("Escaped:\n%s\n", s);
	escapeback(a, s);
	printf("Escaped back:\n%s\n", a);
	return 0;
}
