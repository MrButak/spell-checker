#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

const int max_word_length = 28;
typedef struct node {
	char word[28];
	struct node *next;
}
node;
// prototypes
void store_hash(char current_word[max_word_length], node *head, int position);

node *buckets[26];
int buckets_length = sizeof(buckets) / sizeof(*buckets);

int main(int argc, char *argv[]) {
	
	if(argc != 3) {
		printf("usage: ./spellchecker dictionary.txt checkspelling.txt\n");
		return 1;
	}
	FILE *dict = fopen(argv[1], "r");
	FILE *check_spelling = fopen(argv[2], "r");
	if(dict == NULL) {
		printf("could not open file %s\n", argv[1]);
		return 1;
	}
	else if(check_spelling == NULL) {
		printf("could not open file %s\n", argv[2]);
		return 1;
	}
	
	
	char current_word[max_word_length];
	
	// allocate memory for each node in buckets array and insert head node
	for(int i = 0; i < buckets_length; i++) {
		node *head = malloc(sizeof(node));
		if(head == NULL) {
			printf("failed, out of memory\n");
			return 1;
		}
		head->next = NULL;
		buckets[i] = head;
	}

	// store each word from dictionary into buckets[] as a linked list
	int position;
	while(fscanf(dict, "%s", current_word) != EOF) {
		// determine index which current_word should be stored in buckets[]
		position = ((int)tolower(current_word[0]) - 97);
		store_hash(current_word, buckets[position], position);
	}
	

	// free memory allocted to buckets array (which contains nodes)
	for(int i = 0; i < buckets_length; i++) {
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

// print all words from linked lists
// int word_count = 0;
// 	for(int i = 0; i < buckets_length; i++) {
// 		for(node *tmp = buckets[i]; tmp != NULL; tmp = tmp->next) {
		
// 			printf("%s\n", tmp->word);
// 			word_count++;
		
// 		}
// 	}
// 	printf("word cound: %i", word_count - buckets_length);
