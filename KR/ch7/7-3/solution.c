#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFFERSIZE 25
#define min(a,b) ((a) > (b) ? (b) : (a))

int prettyprint(char, int, int, int, ...);
int minprintf(char *fmt, ...) {
	va_list ap;
	char *p;
	int ival;
	double dval;
	int printed = 0;
	short lalign = 0, width = 0, precision = -1;
	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			printed++;
			continue;
		}
		p++;
		if (*p == '-') {
			lalign = 1;
			p++;
		}
		if (isdigit((unsigned char) *p)) {
			width = atoi(p);
			for (; isdigit((unsigned char) *p); p++);
		}
		if (*p == '.') {
			if (*++p == '*') {
				precision = va_arg(ap, int);
				p++;
			}
			else {
				precision = atoi(p);
				for (; isdigit((unsigned char) *p); p++);
			}
		}
		switch (*p) {
			case 'd':
				ival = va_arg(ap, int);
				printed += prettyprint('d', lalign, width, precision, ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printed += prettyprint('f', lalign, width, precision, dval);
				break;
			case 's':
				printed += prettyprint('s', lalign, width, precision, va_arg(ap, char *));
				break;
			default:
				putchar(*p);
				printed++;
				break;
		}
	}
	va_end(ap);
	return printed;
}

int prettyprint(char c, int is_leftalign, int width, int precision, ...) {
	va_list ap;
	int to_print, pad, printed = 0;
	char buffer[BUFFERSIZE], *str = buffer, *s;
	va_start(ap, precision);
	switch (c) {
		case 'd':
			if (precision != -1)
				to_print = sprintf(buffer, "%.*d", precision, va_arg(ap, int));
			else
				to_print = sprintf(buffer, "%d", va_arg(ap, int));
			break;
		case 'f':
			if (precision != -1)
				to_print = sprintf(buffer, "%.*f", precision, va_arg(ap, double));
			else
				to_print = sprintf(buffer, "%f", va_arg(ap, double));
			break;
		case 's':
			s = va_arg(ap, char*);
			to_print = (precision != -1 ? min(precision, strlen(s)) : strlen(s));
			str = s;
			break;
		default:
			to_print = 0;
			break;
	}
	if (!is_leftalign && width > 0 && to_print < width) {
		for (pad = width - to_print; pad > 0; pad--) {
			putchar(' ');
		}
	}
	for (; printed < to_print && *str; printed++, str++)
		putchar(*str);
	if (is_leftalign && width > 0 && to_print < width) {
		for (pad = width - to_print; pad > 0; pad--) {
			putchar(' ');
		}
	}
	if (width - to_print > 0)
		printed += width - to_print;
	return printed;
}

int main() {
	/* Example usage */
	minprintf("%d\n", 4459);
	minprintf("%10.2f\n", 4458933215.22236598745);
	/* Examples from the book */
	minprintf("%s\n", "hello, world");
	minprintf("%10s\n", "hello, world");
	minprintf("%.10s\n", "hello, world");
	minprintf("%.15s\n", "hello, world");
	minprintf("%-15s\n", "hello, world");
	minprintf("%15.10s\n", "hello, world");
	minprintf("%-15.10s\n", "hello, world");
	return 0;
}
