#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

int main(int argc, char *argv[]) {
	int type;
	int i = 1, j = 0;
	double op2;
	
	while (i < argc) {
		
		type = getop(argv[i]);
		
		switch (type) {
		case NUMBER:
			push(atof(argv[i]));
			j++;
			break;
		case '+':
			push(pop() + pop());
			j--;
			break;
		case '*':
			push(pop() * pop());
			j--;
			break;
		case '-':
			op2 = pop();
			push(pop() - op2);
			j--;
			break;
		case '/':
			op2 = pop();
			j--;
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		default:
			printf("error: unknown command %s\n", argv[i]);
			break;
		}
		
		i++;
	}
	
	if (j > 0)	
		printf("\t%.8g\n", pop());
	
	return 0;
}
