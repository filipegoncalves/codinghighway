#include <stdio.h>
#define MAXLINE 10000
#define PAGELIM 60

int main(int argc, char *argv[]) {
	int i;
	void print_file(char *, FILE *);
	FILE *fp;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s file1 [file2] [file3] ...\n", argv[0]);
		return 0;
	}
	
	for (i = 1; i < argc; i++) {
		if ((fp = fopen(argv[i], "r")) == NULL) {
			fprintf(stderr, "[%s]: Could not open file %s\n", argv[0], argv[i]);
			continue;
		}
		print_file(argv[i], fp);
		fclose(fp);
	}
	return 0;
}

void print_file(char *filename, FILE *fp) {
	int line_cnt = 0, page_cnt = 1;
	char line[MAXLINE];
	
	printf("%s - PAGE %d\n", filename, page_cnt);
	while (fgets(line, MAXLINE, fp)) {
		if (++line_cnt == PAGELIM+1) {
			printf("%s - PAGE %d\n", filename, ++page_cnt);
			line_cnt = 0;
		}
		printf("%s", line);
	}
}
