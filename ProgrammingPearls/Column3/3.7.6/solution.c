#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_BLOCK_SIZE 1000
#define open(n, f) if (((f) = fopen((n), "r")) == NULL) { \
		fprintf(stderr, "Error: could not open file %s\n", (n)); \
		return 0; \
	}

struct schema_block {
	char *text;
	int variable; /* variable to print after this block */
};

struct schema_block *blocks;
char **variables;
	
void parse_schema(FILE *);
void read_next_record(FILE *, int);
void dump_schema(void);

int main(int argc, char *argv[]) {
	FILE *db, *schema;
	int records, fields;
	if (argc != 3) {
		fprintf(stderr, "Usage: %s database-file schema-file\n", argv[0]);
		return 0;
	}
	open(argv[1], db);
	open(argv[2], schema);
	parse_schema(schema);
	fclose(schema);
	fscanf(db, "%d%d", &records, &fields);
	variables = (char **) malloc(sizeof(char *)*fields);
	while (records--) {
		read_next_record(db, fields); /* Populates the variables array */
		dump_schema();
		putchar('\n');
	}
	return 0;
}

int parse_schema_aux(int, FILE *);
void parse_schema(FILE *s) {
	parse_schema_aux(1, s);
}

int parse_schema_aux(int cnt, FILE *f) {
	char buf[MAX_BLOCK_SIZE];
	int c, i, v, pos;
	i = 0;
	pos = -1;
	
	while ((c = getc(f)) != EOF && i < MAX_BLOCK_SIZE) {
		if (c == '\\') {
			buf[i++] = getc(f);
			continue;
		}
		if (c == '$') {
			fscanf(f, "%d", &v);
			pos = parse_schema_aux(cnt+1, f);
			buf[i] = '\0';
			blocks[pos].text = (char *) malloc(i+1);
			strcpy(blocks[pos].text, buf);
			blocks[pos].variable = v;
			return pos-1;
		}
		else
			buf[i++] = c;
	}
	
	if (i == MAX_BLOCK_SIZE) {
		fprintf(stderr, "Oh crap, this schema is too big for me to handle. I'm going down, sorry!\n");
		exit(0);
	}
	
	if (c == EOF) {
		blocks = (struct schema_block *) malloc(sizeof(struct schema_block)*cnt);
		buf[i] = '\0';
		blocks[cnt-1].text = (char *) malloc(i+1);
		strcpy(blocks[cnt-1].text, buf);
		blocks[cnt-1].variable = -1;
		return cnt-2;
	}
	return -1; /* Never reached, needed or gcc will complain */
}

void read_next_record(FILE *db, int fields) {
	int i, j, c;
	char buf[MAX_BLOCK_SIZE];
	i = j = 0;
	/* Previous record ends with newline */
	if (!((c = getc(db)) == '\n' || (c == '\r' && getc(db) == '\n')))
		fprintf(stderr, "Oops, something went terribly wrong! Couldn't reach end of record, new line characters not found.");
	while (i < fields) {
		while ((c = getc(db)) != ';' && j < MAX_BLOCK_SIZE-1) {
			if (c == '\\')
				buf[j++] = getc(db);
			else 
				buf[j++] = c;
		}
		buf[j] = '\0';
		if (j == MAX_BLOCK_SIZE-1)
			fprintf(stderr, "Record \"%s\" is too big for me to handle, resizing it to fit in my buffer.\n", buf);
		variables[i] = (char *) malloc(j+1);
		strcpy(variables[i], buf);
		i++;
		j = 0;
	}
}

void dump_schema(void) {
	int i;
	for (i = 0; blocks[i].variable != -1; i++)
		printf("%s%s", blocks[i].text, variables[blocks[i].variable]);
	printf("%s", blocks[i].text);
}
