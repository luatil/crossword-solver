#include "crossword_solver.h"


#define debug(x) printf("Alignment: %d\n", x.alignment); printf("Move size: %d\n", x.move_size); for(int i = 0; i < x.index_of_last_intersecting_move; i++) { printf("%d ", x.list_of_intersecting_moves[i]);} printf("\n");
#define here printf("here\n");


game_move next_game_move(game_board * game, game_move current_move, game_move * list_of_horizontal_moves, game_move * list_of_vertical_moves) {
    if(!current_move.filled) 
        return current_move;

    int index_of_intersecting_move;
    for(int i = 0; i < current_move.index_of_last_intersecting_move; i++) {

        index_of_intersecting_move = current_move.list_of_intersecting_moves[i];

        if(is_horizontal(current_move) && list_of_vertical_moves[index_of_intersecting_move].filled == false) 
            return list_of_vertical_moves[index_of_intersecting_move];

        if(!is_horizontal(current_move) && list_of_horizontal_moves[index_of_intersecting_move].filled == false) 
            return list_of_horizontal_moves[index_of_intersecting_move];
    }

    // If all the intersecting moves with the current are filled, we search for the first non filled horizontal move
    for(int i = 0; i < game->horizontal_move_num; i++) {
        if(!list_of_horizontal_moves[i].filled) 
            return list_of_horizontal_moves[i];
    }

    // If all the horizontal moves are also filled, we search for the first non filled vertical move
    for(int i = 0; i < game->horizontal_move_num; i++) {
        if(!list_of_horizontal_moves[i].filled) 
            return list_of_horizontal_moves[i];
    }

    // If all of them are filled it means that the board is solved
    game->is_solved = true;

    return current_move; 

}
bool check_if_the_word_fits_on_the_board(game_board * game, list_of_words * word_list, game_move * current_game_move) {

    int initial_line = current_game_move->initial_line;
    int initial_column = current_game_move->initial_column;
    char table_char, word_char;

    for(int i = 0; i < current_game_move->move_size; i++) {

        if(is_horizontal(*current_game_move))
            table_char = game->table[initial_line][initial_column+i].c;
        else 
            table_char = game->table[initial_line+i][initial_column].c;

        word_char = word_list->lst[current_game_move->word_index].ch[i];

        if(table_char != '-' && table_char != word_char) 
            return false;
    }

    return true;
}

bool is_move_possible(game_board* game, list_of_words * word_list, game_move *current_game_move) {
    int index_of_current_word = current_game_move->word_index;
    bool finished_search = false;
    bool move_is_possible;
    while(!finished_search) {
        index_of_current_word = find_word_of_size(word_list, index_of_current_word, current_game_move->move_size);
        current_game_move->word_index = index_of_current_word;
        if(index_of_current_word == -1) {
            finished_search = true;
            move_is_possible = false;
        }
        else if(check_if_the_word_fits_on_the_board(game, word_list, current_game_move)) {
            finished_search = true;
            move_is_possible = true;
        } 
        else
            index_of_current_word++;
    }
    return move_is_possible;
}

void make_move(game_board* game, list_of_words *word_list, game_move * current_game_move, pilha* stack_of_moves) {
    fill_game_move(game, *current_game_move, word_list);
    current_game_move->filled = true;
    word_list->lst[current_game_move->word_index].is_used = true;
    empilha(stack_of_moves, *current_game_move);
}

void unmake_move(game_board* game, list_of_words *word_list, game_move * current_game_move, pilha* stack_of_moves) {
    empty_game_move(game, *current_game_move);
    current_game_move->filled = false;
    current_game_move->word_index = 0;
    word_list->lst[current_game_move->word_index].is_used = false;
    *current_game_move = desempilha(stack_of_moves);
    current_game_move->word_index++;
}

bool crossword_solver(game_board * game, list_of_words * word_list, game_move * list_of_horizontal_moves, game_move * list_of_vertical_moves) {

    int total_number_of_moves = game->horizontal_move_num + game->vertical_move_num;
    pilha * stack_of_moves = criaPilha(total_number_of_moves);

    bool finished_searching = false;

    game_move current_move = list_of_horizontal_moves[0];

    int count = 0;

    while(!finished_searching && count < 100) {
        count++;

        current_move = next_game_move(game, current_move, list_of_horizontal_moves, list_of_vertical_moves);
        if(game->is_solved == true) 
            finished_searching = true;

        else if(is_move_possible(game, word_list, &current_move)) {
            make_move(game, word_list, &current_move, stack_of_moves);
        }
        // If I tested all the words on the first position and none of them were able to solve the board. The board is not solvable.
        else if(pilhaVazia(stack_of_moves)) {
            finished_searching = true;
            game->is_solved = false;
        }
        else if(current_move.word_index == -1){
            unmake_move(game, word_list, &current_move, stack_of_moves);
        }
    }

    return game->is_solved; 
}
