#include <stdio.h>

int fibonacci(int n);

int main(void) {
	int nth;
	while(scanf("%d", &nth) != EOF) {
		printf("%d\n", fibonacci(nth));
	}
	return 0;
}

int fibonacci(int n) {
	if (n <= 1) 
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}
