#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

const int max_word_length = 18;
typedef struct node {
	char word[18];
	struct node *next;
}
node;
// prototypes
void store_hash(char current_word[max_word_length], node *head, int position);

node *buckets[25];

int main(void) {
	
	FILE *dict = fopen("dictionary.txt", "r");
	char current_word[max_word_length];
	
	// allocate memory for each node in buckets array and insert head node
	for(int i = 0; i < 25; i++) {
		node *head = malloc(sizeof(node));
		if(head == NULL) {
			printf("failed, out of memory\n");
			return 1;
		}
		head->next = NULL;
		buckets[i] = head;
	}

	int position;
	while(fscanf(dict, "%s", current_word) != EOF) {
		position = ((int)tolower(current_word[0]) - 97);
		store_hash(current_word, buckets[position], position);
	}
	
	
	
	

	printf("%s\n", buckets[12]->word);
	// printf("%s\n", buckets[0]->next->word);
	// printf("%s\n", buckets[0]->next->next->word);
	

	
	// free memory allocted to buckets array (which contains nodes)
	for(int i = 0; i < 25; i++) {
		while(buckets[i] != NULL) {
			node *temp = buckets[i]->next;
			free(buckets[i]);
			buckets[i] = temp;
		}
	}
	fclose(dict);
}

void store_hash(char current_word[], node *head, int position) {
	
	// create new node and give value of current_word
	node *curr_word = malloc(sizeof(node));
	if(curr_word == NULL) {
		printf("failed, out of memory\n");
		return;
	}
	strcpy(curr_word->word, current_word);
	curr_word->next = head; // point new node to current head
	buckets[position] = curr_word; // assign index 0 to new node

    return;
}





















// char alpha[alpa_length];
// const int alpa_length = 26;
// // create array of ints wich represent the ascii lowercase alphabet
	// for(int i = 97, j = 0; i < 123; i++) {
	// 	alpha[j] = i;
	// 	j++;
	// }
