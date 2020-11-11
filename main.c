#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_board.h"
#include "list_of_words.h"
#include "game_move.h"
#include "crossword_solver.h"

#define MAX(a, b) (a > b ? a : b);
#define NUMBER_OF_MOVES(a, b) ((a * b) / 3 + 1);

int main() {

    int number_of_lines, number_of_columns, number_of_words;
    int iteration_index = 1;
    while(true) {
        scanf("%d %d", &number_of_lines, &number_of_columns);
        if(number_of_lines == 0 && number_of_columns == 0)
            return 0;

        // Create and read game board
        game_board * game = create_empty_game_board(number_of_lines, number_of_columns);
        read_game_board(game);

        scanf("%d", &number_of_words);

        // Create and read list of words
        int max_word_size = MAX(number_of_lines, number_of_columns)
        list_of_words * word_list = create_empty_list_of_words(number_of_words, max_word_size);
        read_list_of_words(word_list);

        // Build horizontal and vertical layers of game board
        int max_number_of_moves = NUMBER_OF_MOVES(number_of_lines, number_of_columns)
        game_move * list_of_horizontal_moves = horizontal_moves_builder(game, max_number_of_moves);
        game_move * list_of_vertical_moves = vertical_moves_builder(game, max_number_of_moves);


        // Build horizontal and vertical adjacency lists
        horizontal_adjacency_list_builder(game, list_of_horizontal_moves);
        vertical_adjacency_list_builder(game, list_of_vertical_moves);

        // Run the algorithm 
        crossword_solver(game, word_list, list_of_horizontal_moves, list_of_vertical_moves);

        // Print the board if solvable
        printf("Instancia %d\n", iteration_index);
        if(game->is_solved) {
            print_game_board(game);
        }
        else 
            printf("nao ha solucao\n");

        printf("\n");

        iteration_index++;

        // Deallocate structures after each iteration
        free_adjacency_list(list_of_horizontal_moves, game->horizontal_move_num);
        free_adjacency_list(list_of_vertical_moves, game->vertical_move_num);
        free_list_of_game_moves(list_of_horizontal_moves);
        free_list_of_game_moves(list_of_vertical_moves);
        free_list_of_words(word_list);
        free_game_board(game);
    } 

    return 0;
}
