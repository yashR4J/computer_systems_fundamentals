#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool vowelCheck(char c);

int main (void) {
	
	char input;
	
	while (scanf("%c", &input) != EOF) {
		if (!vowelCheck(input))
			printf("%c", input);
	}
	
	return 0;
}

bool vowelCheck(char c) {
	c = tolower(c);
	if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') 
		return 0;
	
	return 1;
}
