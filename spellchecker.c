#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int max_word_length = 28;
typedef struct node {
	char word[28];
	struct node *next;
} 
node;

node *buckets[26];
node *check_buckets[26];
node *misspelled_buckets;
int buckets_length = sizeof(buckets) / sizeof(*buckets);

// prototypes
void store_hash(char current_word[max_word_length], node *head, int position, bool is_check);
void compare_lists(void);
void compare_words(char word_to_check[max_word_length], int index);
void free_memory(void);


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

	// allocate memory for each node
	for(int i = 0; i < buckets_length; i++) {
		buckets[i] = malloc(sizeof(node));
		check_buckets[i] = malloc(sizeof(node));
		if(buckets[i] == NULL)  {
			printf("failed, out of memory\n");
			free_memory();
			return 1;
		}
		else if(check_buckets[i] == NULL) {
			printf("failed, out of memory\n");
			free_memory();
			return 1;
		}
		buckets[i]->next = NULL;
		check_buckets[i]->next = NULL;
	}
	misspelled_buckets = malloc(sizeof(node));
	if(misspelled_buckets == NULL) {
		printf("failed, out of memory\n");
		free_memory();
		return 1;
	}
	misspelled_buckets->next = NULL;


	// send words in dictionary.txt to be put into linked lists
	int position;
	while(fscanf(dict, "%s", current_word) != EOF) {
		// determine index which current_word should be stored in buckets[]
		position = ((int)tolower(current_word[0]) - 97);
		store_hash(current_word, buckets[position], position, is_check);
	}

	// send words in spellchecker.txt to be put into linked lists
	is_check = true;
	while (fscanf(check_spelling, "%s", current_word) != EOF) {
		position = ((int)tolower(current_word[0]) - 97);
		store_hash(current_word, check_buckets[position], position, is_check);
	}

	// this funtion will compare lists which will then call a function to compare words
	compare_lists();

	// printf out misspelled words
	for(node *tmp = misspelled_buckets; tmp->next != NULL; tmp = tmp->next) {
		printf("misspelled words: %s\n", tmp->word);
	}

	free_memory();
	fclose(dict);
	fclose(check_spelling);
}


void store_hash(char current_word[], node *head, int position, bool is_check) {
	// put all words in dictionary.txt into array of linked lists
	if(is_check == false) {
		
		// create new node and give value of current_word
		node *curr_word = malloc(sizeof(node));
		if(curr_word == NULL) {
			printf("failed, out of memory\n");
			free_memory();
			exit(1);
		}
		// convert to lowercase
		int word_len = strlen(current_word);
		char tmp_word[max_word_length];

		for(int i = 0; i < word_len; i++) {
			tmp_word[i] = tolower(current_word[i]);
		}
		tmp_word[word_len] = '\0';

		// add new node to beginning of linked list
		strcpy(curr_word->word, tmp_word);
		curr_word->next = head; // point new node to current head
		buckets[position] = curr_word; // assign index 0 to new node

		return;
	}

	// put all words from spellchecker.txt into array of linked lists
	else {
		// create new node and give value of current_word
		node *curr_word = malloc(sizeof(node));
		if(curr_word == NULL) {
			printf("failed, out of memory\n");
			free_memory();
			exit(1);
		}

		// convert to lowercase
		int word_len = strlen(current_word);
		char tmp_word[max_word_length];

		for(int i = 0; i < word_len; i++) {
			tmp_word[i] = tolower(current_word[i]);
		}

		tmp_word[word_len] = '\0';
		strcpy(curr_word->word, tmp_word);
		curr_word->next = head; // point new node to current head
		check_buckets[position] = curr_word; // assign index 0 to new node

		return;
	}
}


void compare_lists(void) {
	
	for(int i = 0; i < buckets_length; i++) {
		// check to see if array position is empty. if so continue to next iteration
		if(check_buckets[i]->next == NULL) {
			continue;
		}
		else {
			for(node *tmp = check_buckets[i]; tmp->next != NULL; tmp = tmp->next) {
				compare_words(tmp->word, i);
			}
		}
	}
	return;
}


void compare_words(char word_to_check[], int index) {
	// iterate through every word of dictionary in int index position to look for a match
	for(node *tmp = buckets[index]; tmp->next != NULL; tmp = tmp->next) {
		if(strcmp(word_to_check, tmp->word) == 0) {
			return;
		}	
	}
	// if no word match, create new node and link it to the list
	node *misspelled = malloc(sizeof(node));
	if(misspelled == NULL) {
		printf("failed, out of memory\n");
		free_memory();
		exit(1);
	}
	strcpy(misspelled->word, word_to_check);
	misspelled->next = misspelled_buckets; // point new node to head of linked list
	misspelled_buckets = misspelled; // linked list is now = to new node, which is pointing to linked list, and therefore is now complete linked list
	return;
}


void free_memory(void) {
	node *temp;
	// free memory allocted of all buckets arrays (which contains nodes)
	for(int i = 0; i < buckets_length; i++) {
		while(buckets[i] != NULL) {
			temp = buckets[i];
			buckets[i] = buckets[i]->next;
			free(temp);
		}
	}

	for(int i = 0; i < buckets_length; i++) {
		while(check_buckets[i] != NULL) {
			temp = check_buckets[i];
			check_buckets[i] = check_buckets[i]->next;
			free(temp);
		}
	}
	while(misspelled_buckets != NULL) {
		temp = misspelled_buckets;
		misspelled_buckets = misspelled_buckets->next;
		free(temp);
	}
	return;
}
