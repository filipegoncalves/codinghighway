#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define NDETAB 5
#define flushblanks(t,s) { for (; t > 0; t--) putchar('\t'); for (; s > 0; s--) putchar(' '); }
#define get_next_tab_stop(total_pos, start_column, custom_stops) ((total_pos) >= (start_column) ? (custom_stops) : (NDETAB))

int main(int argc, char *argv[]) {
	int c, t, s, pos, i, start_column = 0, custom_stops = NDETAB, next_stop, total_pos = 0;
	
	t = s = pos = 0;
	
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-' && isdigit((unsigned char) argv[i][1])) {
			start_column = atoi(argv[i]+1);
		}
		else if (argv[i][0] == '+' && isdigit((unsigned char) argv[i][1])) {
			custom_stops = atoi(argv[i]+1);
		}
		else {
			printf("Can't understand \"%s\", ignoring...\n", argv[i]);
		}
	}
	
	next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
	
	while ((c = getchar()) != EOF) {
		total_pos++;
		if (pos == next_stop) {
			pos = 1;
			next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
		} else {
			pos++;
		}
		if (c == ' ') {
			if (pos == next_stop) {
				t++;
				pos = 0;
				s = 0;
				next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
			}
			else {
				s++;
			}
		}
		else {
			if (c == '\t') {
				s = 0;
				pos = 0;
				next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
			}
			flushblanks(t, s);
			putchar(c);
			if (c == '\n') {
				t = s = pos = total_pos = 0;
				next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
			}
		}
	}
	/* If file ends without \n, ensure that missing blanks are printed anyway */
	flushblanks(t, s);
	return 0;
}
