/*
1.2
What does double print when it sees three or more identical words in its input? Change double to fix this "feature."
--
Looking at the code, it is easy to see that for each additional occurrence of the same word, there is one more double word report. In other words, a given word repeated N times is reported N-1 times (1 for the first duplication, and then once for each additional occurrence).

This can be fixed by reusing "prev". When a word duplication is found, we don't really care about the word anymore - there is no use in storing it again in prev to compare to the next word, because it is either the same word (in which case we don't care), or it is an entirely new word, and therefore we know it will not compare equal to the previous word.

Thus, after a double word is found, we can keep getting words and storing them in prev until a different word is found. We keep reading to prev, because when we find a different word, it is as if this different word is the previous word - the original loop will read into word, and the whole process kicks again. That's just what we want.

It may sound confusing here, but the code speaks by itself.
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

int linenum;

int getword(FILE *, char *, int);
void doubleword(char *name, FILE *fp);

int main(int argc, char *argv[]) {
  int i;

  for (i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      fprintf(stderr, "%s: can't open '%s' (%s)\n",
	      argv[0], argv[i], strerror(errno));
      return EXIT_FAILURE;
    } else {
      doubleword(argv[i], fp);
      fclose(fp);
    }
  }
  if (argc == 1) doubleword(NULL, stdin);
  return EXIT_SUCCESS;
}

int getword(FILE *fp, char *buf, int size) {
  int c;

  c = getc(fp);
  for ( ; c != EOF && isspace(c); c = getc(fp))
    if (c == '\n')
      linenum++;
  {
    int i = 0;
    for ( ; c != EOF && !isspace(c); c = getc(fp))
      if (i < size - 1)
	buf[i++] = tolower(c);
    if (i < size)
      buf[i] = '\0';
  }
  if (c != EOF)
    ungetc(c, fp);
  return buf[0] != '\0';
}

void doubleword(char *name, FILE *fp) {
  char prev[128], word[128];

  linenum = 1;
  prev[0] = '\0';
  while (getword(fp, word, sizeof word)) {
    if (isalpha(word[0]) && strcmp(prev, word) == 0) {
      if (name)
	printf("%s:", name);
      printf("%d: %s\n", linenum, word);
      /* UPDATE: do not report three or more identical words */
      for ( ; strcmp(prev, word) == 0; getword(fp, prev, sizeof prev));
    }
    else {
      /* This must now be inside an else */
    strcpy(prev, word);
    }
  }
}
