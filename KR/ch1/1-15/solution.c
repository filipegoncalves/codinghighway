#include <stdio.h>

float celsius_to_fahr(float c) {
	return (9.0/5.0)*c+32;
}

int main() {
	float celsius;
	int lower, upper, step;
	
	lower = 0;
	upper = 300;
	step = 20;
	
	printf("Celsius-Fahrenheit table\n");
	
	celsius = lower;
	while (celsius <= upper) {
		printf("%3.0f %6.1f\n", celsius, celsius_to_fahr(celsius));
		celsius = celsius + step;
	}
	
	return 0;
}
