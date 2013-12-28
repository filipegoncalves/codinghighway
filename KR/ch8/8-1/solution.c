#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void error(char *, ...);
void filecopy(int, int);

int main(int argc, char *argv[]) {
	int i, fd;
	if (argc == 1) {
		filecopy(0, 1);
		return 0;
	}
	for (i = 1; i < argc; i++) {
		if ((fd = open(argv[i], O_RDONLY, 0)) == -1) {
			error("[%s]: Could not open file %s, aborting...\n", argv[0], argv[i]);
		}
		filecopy(fd, 1);
		close(fd);
	}
	return 0;
}

void filecopy(int from, int to) {
	int n;
	char buf[BUFSIZ];
	while ((n = read(from, buf, BUFSIZ)) > 0) {
		write(to, buf, n);
	}
}

void error(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "error :");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}
