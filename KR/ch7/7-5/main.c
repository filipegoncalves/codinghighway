#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'
#define OPERATION 1

int getop(double *, char *);
void push(double);
double pop(void);
void clear_stack(void);

int main() {
	double value, type, denominator, subtractor;
	char operation;
	
	while ((type = getop(&value, &operation)) != EOF) {
		if (type == NUMBER)
			push(value);
		else {
			switch (operation) {
				case 'q':
					return 0;
				case ';':
					printf("%f\n", pop());
					clear_stack();
					break;
				case '+':
					push(pop()+pop());
					break;
				case '*':
					push(pop()*pop());
					break;
				case '/':
					denominator = pop();
					if (denominator == 0)
						printf("Warning: division by zero\n");
					else
						push(pop()/denominator);
					break;
				case '-':
					subtractor = pop();
					push(pop()-subtractor);
					break;
				default:
					printf("Unknown operation: %c\n", operation);
					break;
			}
		}
	}
	return 0;
}
