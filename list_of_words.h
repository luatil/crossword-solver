#ifndef LIST_OF_WORDS_H
#define LIST_OF_WORDS_H
#include <stdbool.h>

typedef struct {
    // word_length;
    int word_length;
    bool is_used;
    char *ch;
} word;

typedef struct {
    int list_length;
    int max_word_size;
    word * lst;
} list_of_words;

list_of_words * create_empty_list_of_words(int number_of_words, int max_word_size);
void read_list_of_words(list_of_words * word_list);
void free_list_of_words(list_of_words * word_list);

int find_word_of_size(list_of_words * word_list, int initial_position, int size);


#endif // LIST_OF_WORDS_H
