#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ALPHABET_SIZE 26
#define C_RULES_SIZE ((int) (sizeof(c_rules)/sizeof(c_rules[0])))

char *c_rules[] = {
	"et-ic",
	"al-is-tic",
	"s-tic",
	"p-tic",
	"-lyt-ic",
	"ot-ic",
	"an-tic",
	"n-tic",
	"c-tic",
	"at-ic",
	"h-nic",
	"n-ic",
	"m-ic",
	"l-lic",
	"b-lic",
	"-clic",
	"l-ic",
	"h-ic",
	"f-ic",
	"d-ic",
	"-bic",
	"a-i",
	"-mac",
	"i-ac"
};

char **rules[ALPHABET_SIZE] = { NULL };
char *hyphenizer(char *word);
int main(int argc, char *argv[]) {
	/* Fill the rules array with known rules */
	int i;
	char *str;
	rules['c'-'a'] = (char **) malloc(sizeof(char *)*(C_RULES_SIZE+1));
	for (i = 0; i < C_RULES_SIZE; i++)
		rules['c'-'a'][i] = c_rules[i];
	rules['c'-'a'][i] = NULL; /* signalizes end of rules */
	
	/* Print hyphenizers for the words in argv */
	for (i = 1; i < argc; i++)
		printf("%s: %s\n", argv[i], ((str = hyphenizer(argv[i])) == NULL ? "[no match]" : str));
	return 0;
}

int suffix_match(char *, char *);
char *hyphenizer(char *word) {
	char **p;
	
	for (p = rules[word[strlen(word)-1]-'a']; *p; p++)
		if (suffix_match(word, *p))
			return *p;
	
	return NULL;	
}

int suffix_match(char *word, char *suffix) {
	int i, j;	
	for (i = strlen(word)-1, j = strlen(suffix)-1; word[i] == suffix[j]; i--, j -= 1+(suffix[j-1] == '-'))
		if (!i || j < 0)
			break;
	return j < 0;
}
