#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define ASSIGN -2
#define VAR 'a'

int getop(char []);
void push(double);
double pop(void);

int main() {
	int type;
	double op2, last_printed;
	char s[MAXOP];
	double vars[(unsigned char) ('z'-'a'+1)];
	
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case ASSIGN:
			vars[(unsigned char) (s[1]-'a')] = op2 = pop();
			push(op2);
			break;
		case VAR:
			push(s[0] == '_' ? last_printed : vars[(unsigned char) (s[0]-'a')]);
			break;
		case '\n':
			printf("\t%.8g\n", last_printed = pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}
