#ifndef GAME_MOVE_H
#define GAME_MOVE_H
#include <stdbool.h>
#include <string.h>
#include "game_board.h"
#include "list_of_words.h"


typedef struct {
    // 0 mens horizontal 1 means vertical
    bool alignment;
    int move_size;
    int initial_line;
    int initial_column;
    int word_index;
    int *list_of_intersecting_moves;
    // this allows for a vector like push_back
    int index_of_last_intersecting_move;
    bool filled;
    int index;
} game_move;

bool is_horizontal(game_move gm);

game_move * horizontal_moves_builder(game_board * game, int number_of_horizontal_moves);
game_move * vertical_moves_builder(game_board * game, int number_of_vertical_moves);

void free_list_of_game_moves(game_move * list_of_moves);

void fill_game_move(game_board * game, game_move gm, list_of_words * word_list);
void empty_game_move(game_board * game, game_move gm);

void horizontal_adjacency_list_builder(game_board * game, game_move * list_of_moves);
void vertical_adjacency_list_builder(game_board * game, game_move * list_of_moves);

void free_adjacency_list(game_move * list_of_allocated_moves, int number_of_moves);

// For debugging 
void print_move(game_move gm);
void print_move_vector(game_move * gms, int size);
#endif // GAME_MOVE_H
