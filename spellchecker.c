#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int main(void) {
	FILE *dict = fopen("dictionary.txt", "r");
	const int max_word_length = 18;
	const int alpa_length = 26;

	char current_word[max_word_length];
	char alpha[alpa_length];
	
	
	// create array of ints wich represent the ascii lowercase alphabet
	for(int i = 97, j = 0; i < 123; i++) {
		alpha[j] = i;
		j++;
	}

	for(int j = 0; j < 6; j++) {
		fscanf(dict, "%s", current_word);
		for(int i = 0; i < 26; i++) {
			if(alpha[i] == tolower(current_word[0])) {
				printf("Found: %c\n", (char)alpha[i]);
				continue;
			}
		}
	}
	
	fclose(dict);
	
}

void store_hash(char current_word) {
    return;
}