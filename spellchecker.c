#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct node {
	char word[18];
	struct node *next;
}
node;
const int max_word_length = 18;
// prototypes
void store_hash(char current_word[max_word_length], node *head);



node *buckets[25];

int main(void) {
	

	FILE *dict = fopen("dictionary.txt", "r");
	const int alpa_length = 26;
	char current_word[max_word_length];
	char alpha[alpa_length];
	

	// allocate memory for each node in buckets array
	for(int i = 0; i < 25; i++) {
		node *head = malloc(sizeof(node));
		head->next = NULL;
		buckets[i] = head;
		// buckets[i] = malloc(sizeof(node));
		// buckets[i]->next = NULL;
	}
	
	

	 
	
	
	// create array of ints wich represent the ascii lowercase alphabet
	for(int i = 97, j = 0; i < 123; i++) {
		alpha[j] = i;
		j++;
	}

	// for(int j = 0; j < 6; j++) {
		fscanf(dict, "%s", current_word);

		int position = ((int)tolower(current_word[0]) - 97);
		

		store_hash(current_word, buckets[position]);
		printf("%s\n", buckets[position]->word);

		
		// for(int i = 0; i < 26; i++) {
		// 	if(alpha[i] == tolower(current_word[0])) {
				// store_hash(current_word);
				// continue;
			//}
		//}
	// }
	
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

void store_hash(char current_word[], node *head) {
	// I need to place each word in appopriate position in buckets[].
	// Then I need to point the "head" of that linked list to current_word node,
		// then point new word node to "head". Then new word will become the "head".
	node *curr_word = malloc(sizeof(node));
	if(curr_word == NULL) {
		printf("failed, out of memory");
		return;
	}
	
	strcpy(curr_word->word, current_word);
	curr_word = head->next;
	curr_word = head;

	// curr_word->next = buckets[position];
	
	
	
	
	
	// printf("%s\n", buckets[position]->word);
	

	

	
    return;
}