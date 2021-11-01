#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool isUpperCase(int c);

int main (void) {
	
	for (int c = getchar(); c != EOF; c = getchar()) {
		if (isUpperCase(c))
			c = tolower(c);
		putchar(c);
	}

	return 0;
}

bool isUpperCase(int c) {
	if (c >= 'A' && c <= 'Z') 
		return 1;
	return 0;
}
