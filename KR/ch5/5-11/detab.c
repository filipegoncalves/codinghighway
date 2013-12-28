#include <stdio.h>
#include <stdlib.h>
#define NDETAB 5

int get_next_tab_stop(int, char *[], int);

int main(int argc, char *argv[]) {
	int index;
	int next_stop;
	int c, pos = 0;
	
	index = 1;
	next_stop = get_next_tab_stop(argc, argv, index++);
	
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			while (pos <= next_stop-1) {
				putchar(' ');
				pos++;
			}
			pos = 0;
			next_stop = get_next_tab_stop(argc, argv, index++);
		}
		else {
			putchar(c);
			if (c == '\n') {
				pos = 0;
				index = 1;
				next_stop = get_next_tab_stop(argc, argv, index++);
			}
			else if (++pos == next_stop) {
				pos = 0;
				next_stop = get_next_tab_stop(argc, argv, index++);
			}
		}
	}
	return 0;
}

int get_next_tab_stop(int argc, char *argv[], int index) {
	static int last;
	int x, ret;
	
	if (index == 1)
		last = 0;
	if (index < argc) {
		x = atoi(argv[index]);
		ret = x - last;
		last = x;
		return ret;
	} else
		return NDETAB;
}
