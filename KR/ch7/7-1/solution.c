#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	int (*f)(int) = toupper, c;
	char *name;
	
	/* Remove program path */
	for (name = *argv + strlen(*argv)-1; name != *argv && *name != '/'; name--);
	
	if (name != *argv)
		name++;
	
	if (!strcmp("lower", name)) {
		f = tolower;
	}

	while ((c = getchar()) != EOF)
		putchar((*f)(c));
	return 0;
}
