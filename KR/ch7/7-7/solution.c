#include <stdio.h>
#include <string.h>
#define MAXLINE 10000

void search_file(char *, char *, FILE *);

int main(int argc, char *argv[]) {
	int file_index;
	FILE *fp;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s pattern [file1] [file2] ...\n", argv[0]);
		return 0;
	}
	
	if (argc == 2) {
		search_file(argv[1], "<STDIN>", stdin);
	}
	else {
		for (file_index = 2; file_index < argc; file_index++) {
			if ((fp = fopen(argv[file_index], "r")) == NULL) {
				fprintf(stderr, "%s: Could not open file %s\n", argv[0], argv[file_index]);
				continue;
			}
			search_file(argv[1], argv[file_index], fp);
			fclose(fp);
		}
	}
	return 0;
}

void search_file(char *pattern, char *filename, FILE *fp) {
	char line[MAXLINE];
	int line_number = 0;
	while (fgets(line, MAXLINE, fp)) {
		line_number++;
		if (strstr(line, pattern)) {
			printf("[%s] line %d: %s\n", filename, line_number, line);
		}
	}
}
