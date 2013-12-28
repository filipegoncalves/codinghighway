#include <stdio.h>
#include <stdlib.h>
#define NDETAB 5
#define flushblanks(t,s) { for (; t > 0; t--) putchar('\t'); for (; s > 0; s--) putchar(' '); }

int get_next_tab_stop(int, char *[], int);

int main(int argc, char *argv[]) {
	int c, t, s, pos, next_stop, index;
	
	t = s = pos = 0;
	index = 1;
	next_stop = get_next_tab_stop(argc, argv, index++);
	
	while ((c = getchar()) != EOF) {
		if (pos == next_stop) {
			pos = 1;
			next_stop = get_next_tab_stop(argc, argv, index++);
		} else {
			pos++;
		}
		if (c == ' ') {
			if (pos == next_stop) {
				t++;
				pos = 0;
				s = 0;
				next_stop = get_next_tab_stop(argc, argv, index++);
			}
			else {
				s++;
			}
		}
		else {
			if (c == '\t') {
				s = 0;
				pos = 0;
				next_stop = get_next_tab_stop(argc, argv, index++);
			}
			flushblanks(t, s);
			putchar(c);
			if (c == '\n') {
				t = s = pos = 0;
				index = 1;
				next_stop = get_next_tab_stop(argc, argv, index++);
			}
		}
	}
	/* If file ends without \n, ensure that missing blanks are printed anyway */
	flushblanks(t, s);
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
