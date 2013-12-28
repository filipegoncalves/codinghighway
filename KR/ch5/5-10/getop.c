#include <ctype.h>
#include <stdio.h>
#define NUMBER '0'

int getop(char s[]) {
	return isdigit((unsigned char) s[0]) ||
	       (s[0] == '.' && isdigit((unsigned char) s[1])) || 
		   (s[0] == '-' && (isdigit((unsigned char) s[1]) || (s[1] == '.' && isdigit((unsigned char) s[2])))) ? NUMBER : s[0];
}
