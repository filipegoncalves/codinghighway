#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10000000
#define M 1000000

int arr[N];

int randint(int, int);
void swap(int, int);

int main() {
	int i;
	srand(time(NULL));
	for (i = 0; i < N; i++)
		arr[i] = i;
	for (i = 0; i < M; i++)
		swap(i, randint(i, N-1));
	for (i = 0; i < M; i++)
		printf("%d\n", arr[i]);
	return 0;
}

int randint(int from, int to) {
	return from + (rand()%(to-from+1));
}

void swap(int i, int j) {
	int t = arr[i];
	arr[i] = arr[j];
	arr[j] = t;
}
