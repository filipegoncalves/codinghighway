#include <ctype.h>
#include <stdio.h>
#define NUMBER '0'
#define OPERATION 1

int getch(void);
void ungetch(int);

int getop(double *dptr, char *cptr) {
	int doubleres = 0;
	int charres = 0;
	doubleres = scanf("%lf", dptr);
	if (doubleres == 1)
		return NUMBER;
	charres = scanf(" %c", cptr);
	if (charres == 1)
		return OPERATION;
	return EOF;
}
