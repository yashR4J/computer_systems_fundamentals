#include <stdio.h>
#include <stdlib.h>

int findMin(int argc, char** argv);
int findMax(int argc, char** argv);
int findSum(int argc, char** argv);
int findProd(int argc, char** argv);
int findMean(int argc, char** argv);

int main(int argc, char** argv) {
	
	if (argc <= 1) {
		printf("Usage: %s NUMBER [NUMBER ...]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	printf("MIN:  %d\n", findMin(argc, argv));
	printf("MAX:  %d\n", findMax(argc, argv));
	printf("SUM:  %d\n", findSum(argc, argv));
	printf("PROD: %d\n", findProd(argc, argv));
	printf("MEAN: %d\n", findMean(argc, argv));
	
	return 0;
}

int findMin(int argc, char** argv) {
	int min = atoi(argv[1]);
	for (int i = 2; i != argc; i++) {
		if (atoi(argv[i]) < min) 
			min = atoi(argv[i]);
	}
	return min;
}
int findMax(int argc, char** argv) {
	int max = atoi(argv[1]);
	for (int i = 2; i != argc; i++) {
		if (atoi(argv[i]) > max) 
			max = atoi(argv[i]);
	}
	return max;
}
int findSum(int argc, char** argv) {
	int sum = 0;
	for (int i = 1; i != argc; i++) {
		sum += atoi(argv[i]);
	}
	return sum;
}
int findProd(int argc, char** argv) {
	int product = 1;
	for (int i = 1; i != argc; i++) {
		product *= atoi(argv[i]);
	}
	return product;
}
int findMean(int argc, char** argv) {
	int mean = findSum(argc, argv) / (argc - 1);
	return mean;
}
