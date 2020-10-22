#ifndef CROSSWORD_SOLVER_H
#define CROSSWORD_SOLVER_H
#include "game_board.h"
#include "list_of_words.h"
#include "game_move.h"
#include "pilha.h"

bool crossword_solver(game_board * game, list_of_words * word_list, game_move * list_of_horizontal_moves, game_move * list_of_vertical_moves);
bool is_move_possible(game_board* game, list_of_words * word_list, game_move *current_game_move);
bool check_if_the_word_fits_on_the_board(game_board * game, list_of_words * word_list, game_move * current_game_move);
void make_move(game_board* game, list_of_words *word_list, game_move * current_game_move, pilha* stack_of_moves);
void unmake_move(game_board* game, list_of_words *word_list, game_move * current_game_move, pilha* stack_of_moves);
game_move next_game_move(game_board * game, game_move current_move, game_move * list_of_horizontal_moves, game_move * list_of_vertical_moves);

#endif // CROSSWORD_SOLVER_H
