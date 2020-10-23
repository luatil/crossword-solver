#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list_of_words.h"

list_of_words * create_empty_list_of_words(int number_of_words, int max_word_size) {
    // note, is it useless to check for max_word_size?
    if(number_of_words < 0) {
        fprintf(stderr, "create_empty_list_of_words requires a positive argument\n");
        exit(-1);
    }
    list_of_words * word_list = malloc(sizeof(list_of_words));
    if (word_list == NULL) {
        fprintf(stderr, "Failed to allocate %ld bytes\n", sizeof(list_of_words));
        exit(-1);
    }
    word_list->lst = malloc(number_of_words * sizeof(word));
    if (word_list->lst == NULL) {
        fprintf(stderr, "Failed to allocate word_list->lst\n");
        exit(-1);
    }

    for(int i = 0; i < number_of_words; i++) {
        word_list->lst[i].ch = malloc(max_word_size * sizeof(char));
        word_list->lst[i].is_used = false;
    }

    word_list->list_length = number_of_words;
    word_list->max_word_size = max_word_size;
    return word_list;
}

// Reads a list of N words from stdin
// Beware this is not tested
void read_list_of_words(list_of_words * word_list) {
    for(int i = 0; i < word_list->list_length; i++) {
        scanf("%s", word_list->lst[i].ch);
        word_list->lst[i].word_length = strlen(word_list->lst[i].ch);
        word_list->lst[i].is_used = 0;
    }

}

// This is also not tested, I think to way to do it is with valgrind after production 
void free_list_of_words(list_of_words * word_list) {
    for(int i = 0; i < word_list->list_length; i++) {
        free(word_list->lst[i].ch);
    }
    free(word_list->lst);
    free(word_list);
}

int find_word_of_size(list_of_words * word_list, int initial_position, int size) {
    if(initial_position == -1) return -1;
    int i = initial_position;
    while(i < word_list->list_length) {
       if(word_list->lst[i].is_used != 1 && word_list->lst[i].word_length == size) 
           return i;
       i++;
    }
    return -1;
}
