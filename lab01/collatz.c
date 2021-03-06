#include <stdio.h>
#include <stdlib.h>

void findCollatzChain(int num);

int main(int argc, char** argv) {
	if (argc <= 1 || argc > 2) {
		printf("Usage: %s NUMBER\n", argv[0]);
		exit(EXIT_FAILURE);
	} else {
		int num = atoi(argv[1]);
		printf("%d\n", num);
		findCollatzChain(num);
	}
	return 0;
}

void findCollatzChain(int num) {
	if (num == 1) {
		return;
	} else if (num % 2 == 0) {
		num /= 2;
		printf("%d\n", num);
		findCollatzChain(num);
	} else {
		num = (num * 3) + 1;
		printf("%d\n", num);
		findCollatzChain(num);
	}
}
