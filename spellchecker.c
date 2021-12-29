#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


const int max_word_length = 18;
// prototypes
void store_hash(char current_word[max_word_length]);



int main(void) {
	typedef struct node {
	char word[18];
	struct node *next;
	}
	node;

	FILE *dict = fopen("dictionary.txt", "r");
	const int alpa_length = 26;
	char current_word[max_word_length];
	char alpha[alpa_length];
	node *buckets[25];

	// allocate memory for each node in buckets array
	for(int i = 0; i < 25; i++) {
		buckets[i] = malloc(sizeof(node));
		buckets[i]->next = NULL;
	}
	
	

	 
	
	
	// create array of ints wich represent the ascii lowercase alphabet
	for(int i = 97, j = 0; i < 123; i++) {
		alpha[j] = i;
		j++;
	}

	for(int j = 0; j < 6; j++) {
		fscanf(dict, "%s", current_word);
		for(int i = 0; i < 26; i++) {
			if(alpha[i] == tolower(current_word[0])) {
				//printf("Found: %c\n", (char)alpha[i]);
				store_hash(current_word);
				continue;
			}
		}
	}
	
	fclose(dict);
	// free memory allocted to buckets array (which contains nodes)
	for(int i = 0; i < 25; i++) {
		while(buckets[i] != NULL) {
			node *temp = buckets[i]->next;
			free(buckets[i]);
			buckets[i] = temp;
		}
	}
	
}

void store_hash(char current_word[]) {
	//printf("%s\n", current_word);
    return;
}