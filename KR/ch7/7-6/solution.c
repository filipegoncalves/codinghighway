#include <stdio.h>
#include <string.h>
#define MAXLINE 10000
	
int main(int argc, char *argv[]) {
	FILE *fp1, *fp2;
	char line1[MAXLINE], line2[MAXLINE];
	char *f1 = NULL, *f2 = NULL;
	int line_cnt;
	
	if (argc != 3) {
		fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
		return 1;
	}
	
	line_cnt = 1;
	
	if ((fp1 = fopen(argv[1], "r")) == NULL || (fp2 = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "%s: Error: could not open file %s\n", argv[0], (!fp1 ? argv[1] : argv[2]));
		return 1;
	}
	
	/* Both files are opened at this point, and ready to be compared */
	for (f1 = fgets(line1, MAXLINE, fp1), f2 = fgets(line2, MAXLINE, fp2);
		 f1 && f2;
		 f1 = fgets(line1, MAXLINE, fp1), f2 = fgets(line2, MAXLINE, fp2), line_cnt++) {
		if (strcmp(f1, f2))
			break;
	}
	if (f1)
		printf("[%s] line %d: %s\n", argv[1], line_cnt, line1);
	if (f2)
		printf("[%s] line %d: %s\n", argv[2], line_cnt, line2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
