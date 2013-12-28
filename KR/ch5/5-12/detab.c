#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define NDETAB 5
#define get_next_tab_stop(total_pos, start_column, custom_stops) ((total_pos) >= (start_column) ? (custom_stops) : (NDETAB))

int main(int argc, char *argv[]) {
	int c, i, pos = 0, total_pos = 0;
	int start_column = 0, custom_stops = NDETAB, next_stop;
	
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
		if (c == '\t') {
			while (pos <= next_stop-1) {
				putchar(' ');
				pos++;
			}
			pos = 0;
			next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
		}
		else {
			putchar(c);
			if (c == '\n') {
				pos = 0;
				total_pos = 0;
				next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
			}
			else if (++pos == next_stop) {
				pos = 0;
				next_stop = get_next_tab_stop(total_pos, start_column, custom_stops);
			}
		}
	}
	return 0;
}
