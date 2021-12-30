#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <string.h>
//#include <strings.h>
//#include <strings.h>
#include <ctype.h>

const int max_word_length = 28;
typedef struct node {
	char word[28];
	struct node *next;
}
node;
// prototypes
void store_hash(char current_word[max_word_length], node *head, int position, bool is_check);
void compare_lists(void);
void free_memory(void);

node *buckets[26];
node *check_buckets[26];
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
	
	bool is_check = false;
	char current_word[max_word_length];
	
	// allocate memory for each node in buckets array and insert head node
	for(int i = 0; i < buckets_length; i++) {
		node *head = malloc(sizeof(node));
		if(head == NULL) {
			printf("failed, out of memory\n");
			free_memory();
			return 1;
		}
		head->next = NULL;
		buckets[i] = head;
		check_buckets[i] = head;
	}

	// store each word from dictionary into buckets[] as linked lists
	int position;
	while(fscanf(dict, "%s", current_word) != EOF) {
		// determine index which current_word should be stored in buckets[]
		position = ((int)tolower(current_word[0]) - 97);
		store_hash(current_word, buckets[position], position, is_check);
	}

	// store each word from spellcheck.txt into check_buckets[] as linked lists
	is_check = true;
	while (fscanf(check_spelling, "%s", current_word) != EOF) {
		position = ((int)tolower(current_word[0]) - 97);
		store_hash(current_word, check_buckets[position], position, is_check);
	}

	// call funtion that will compare lists
	compare_lists();
	free_memory();
	fclose(dict);
	fclose(check_spelling);
}

void store_hash(char current_word[], node *head, int position, bool is_check) {
	
	if(is_check == false) {
		// create new node and give value of current_word
		node *curr_word = malloc(sizeof(node));
		if(curr_word == NULL) {
			printf("failed, out of memory\n");
			free_memory();
			exit(1);
		}
		strcpy(curr_word->word, current_word);
		curr_word->next = head; // point new node to current head
		buckets[position] = curr_word; // assign index 0 to new node

		return;
	}
	else {
		// create new node and give value of current_word
		node *curr_word = malloc(sizeof(node));
		if(curr_word == NULL) {
			printf("failed, out of memory\n");
			free_memory();
			exit(1);
		}
		strcpy(curr_word->word, current_word);
		curr_word->next = head; // point new node to current head
		check_buckets[position] = curr_word; // assign index 0 to new node

		return;
	}
}

void compare_lists(void) {
	// todo:
	// 1. check each word in check_buckets[i] against every word in buckets[i]
	// loop each word in check_buckets[i] * buckets[i].length

	// print all words from linked lists
	// int word_count = 0;
	// for(int i = 0; i < buckets_length; i++) {
	// 	for(node *tmp = check_buckets[i]; tmp != NULL; tmp = tmp->next) {
	// 		printf("%s\n", tmp->word);
	// 		word_count++;
	// 	}
	// }
	// printf("word cound: %i", word_count - buckets_length);
}


void free_memory(void) {

	// free memory allocted to buckets array (which contains nodes)
	for(int i = 0; i < buckets_length; i++) {
		while(buckets[i] != NULL) {
			node *temp = buckets[i]->next;
			free(buckets[i]);
			buckets[i] = temp;
		}
	}
	for(int i = 0; i < buckets_length; i++) {
		while(check_buckets[i] != NULL) {
			node *temp = check_buckets[i]->next;
			free(check_buckets[i]);
			check_buckets[i] = temp;
		}
	}
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
