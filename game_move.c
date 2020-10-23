#include <stdlib.h>
#include "game_move.h"

game_move * horizontal_moves_builder(game_board * game, int number_of_horizontal_moves) {
    game_move * horizontal_moves = malloc(number_of_horizontal_moves * sizeof(game_move));

    int index_of_horizontal_move = 0;
    int game_move_size;
    game_move temp_game_move;

    for(int i = 0; i < game->line_num; i++) {
        for(int j = 0; j < game->col_num; j++) {
            
            if(j == game->col_num -1 || game->table[i][j].is_black || game->table[i][j+1].is_black) {
                game->table[i][j].member_of_horizontal_move = -1;
                continue;
            }
            
            else  {
                game_move_size = 0;
                int aux_j = j;
                while(j < game->col_num && !game->table[i][j].is_black)  {
                    game->table[i][j].member_of_horizontal_move = index_of_horizontal_move;
                    j++;
                    game_move_size++;
                }
                // I think I could make this better in some way 
                temp_game_move.move_size = game_move_size;
                temp_game_move.filled = false;
                temp_game_move.alignment = 0;
                temp_game_move.initial_line = i;
                temp_game_move.initial_column = aux_j;
                temp_game_move.word_index = 0;
                temp_game_move.index = index_of_horizontal_move;

                horizontal_moves[index_of_horizontal_move] = temp_game_move;
                index_of_horizontal_move++;
                // why is this working them?
                if(j < game->col_num && game->table[i][j].is_black) game->table[i][j].member_of_horizontal_move = -1;
            }
        }

    }
    game->horizontal_move_num = index_of_horizontal_move;
    return horizontal_moves;
}

game_move * vertical_moves_builder(game_board * game, int number_of_vertical_moves) {
    game_move * vertical_moves = malloc(number_of_vertical_moves * sizeof(game_move));

    int index_of_vertical_move = 0;
    int game_move_size;
    game_move temp_game_move;

    for(int j = 0; j < game->col_num; j++) {
        for(int i = 0; i < game->line_num; i++) {
            
            if(i == game->line_num -1 || game->table[i][j].is_black || game->table[i+1][j].is_black) {
                game->table[i][j].member_of_vertical_move = -1;
                continue;
            }
            
            else  {
                game_move_size = 0;
                int aux_i = i;
                while(i < game->line_num && !game->table[i][j].is_black)  {
                    game->table[i][j].member_of_vertical_move = index_of_vertical_move;
                    i++;
                    game_move_size++;
                }
                // I think I could make this better in some way 
                temp_game_move.move_size = game_move_size;
                temp_game_move.filled = false;
                temp_game_move.alignment = 1;
                temp_game_move.initial_line = aux_i;
                temp_game_move.initial_column = j;
                temp_game_move.word_index = 0;
                temp_game_move.index = index_of_vertical_move;

                vertical_moves[index_of_vertical_move] = temp_game_move;
                index_of_vertical_move++;
                if(i < game->line_num && game->table[i][j].is_black) game->table[i][j].member_of_vertical_move = -1;

            }
        }

    }
    game->vertical_move_num = index_of_vertical_move;
    return vertical_moves;
}

void free_list_of_game_moves(game_move * list_of_moves) {
    free(list_of_moves);
}

bool is_horizontal(game_move gm) {
    if(gm.alignment == 0) return true; 
    return false;
}

void fill_game_move(game_board * game, game_move gm, list_of_words * word_list) {
    int w_index = gm.word_index;
    int i = gm.initial_line;
    int j = gm.initial_column;
    for(int aux = 0; aux < gm.move_size; aux++) {
        if(is_horizontal(gm)) {
            game->table[i][j+aux].c = word_list->lst[w_index].ch[aux];
         } 
        else if(!is_horizontal(gm)) {
            game->table[i+aux][j].c = word_list->lst[w_index].ch[aux];
        }
    }
}

void empty_game_move(game_board * game, game_move gm) {
    int i = gm.initial_line;
    int j = gm.initial_column;
    for(int aux = 0; aux < gm.move_size; aux++) {
        if(is_horizontal(gm)) {
            game->table[i][j+aux].c = '-';
        } 
        else if(!is_horizontal(gm)) {
            game->table[i+aux][j].c = '-';
        }
    }
}



void horizontal_adjacency_list_builder(game_board * game, game_move * list_of_moves) {
    bool is_vertical = list_of_moves[0].alignment;
    // the maximum amount of intersections will never be greater than the number of columns if the move
    // is horizontal, and it will never be greater than the number of lines if it's vertical. 
    int size_of_allocation = (is_vertical ? game->line_num : game->col_num) * sizeof(int);
    int number_of_moves = (is_vertical ? game->vertical_move_num : game->horizontal_move_num);
    for(int i = 0; i < number_of_moves; i++)  {
        list_of_moves[i].list_of_intersecting_moves = malloc(size_of_allocation);
        memset(list_of_moves[i].list_of_intersecting_moves, -1, size_of_allocation);
        list_of_moves[i].index_of_last_intersecting_move = 0;
    }

    int index_of_horizontal_move, index_of_vertical_move;
    for(int i = 0; i < game->line_num; i++) {
        for(int j = 0; j < game->col_num; j++) {
            index_of_horizontal_move = game->table[i][j].member_of_horizontal_move; 
            index_of_vertical_move = game->table[i][j].member_of_vertical_move; 
            if(index_of_horizontal_move != -1 && index_of_vertical_move != -1) {
                // This is done to simulate a push back without implementing a vector. 
                int k = list_of_moves[index_of_horizontal_move].index_of_last_intersecting_move;
                list_of_moves[index_of_horizontal_move].list_of_intersecting_moves[k] = index_of_vertical_move;
                list_of_moves[index_of_horizontal_move].index_of_last_intersecting_move++;
            }
        }
    }
}

void vertical_adjacency_list_builder(game_board * game, game_move * list_of_moves) {

    for(int i = 0; i < game->vertical_move_num; i++)  {
        list_of_moves[i].list_of_intersecting_moves = malloc(game->line_num * sizeof(int));
        memset(list_of_moves[i].list_of_intersecting_moves, -1, game->line_num * sizeof(int));
        list_of_moves[i].index_of_last_intersecting_move = 0;
        list_of_moves[i].alignment = 1;
    }

    int index_of_horizontal_move, index_of_vertical_move;
    for(int i = 0; i < game->col_num; i++) {
        for(int j = 0; j < game->line_num; j++) {
            index_of_vertical_move = game->table[j][i].member_of_vertical_move; 
            index_of_horizontal_move = game->table[j][i].member_of_horizontal_move; 
            if(index_of_horizontal_move != -1 && index_of_vertical_move != -1) {
                // This is done to simulate a push back without implementing a vector. 
                int k = list_of_moves[index_of_vertical_move].index_of_last_intersecting_move;
                list_of_moves[index_of_vertical_move].list_of_intersecting_moves[k] = index_of_horizontal_move;
                list_of_moves[index_of_vertical_move].index_of_last_intersecting_move++;
            }
        }
    }

}


void free_adjacency_list(game_move * list_of_allocated_moves, int number_of_moves) {
    for(int i = 0; i < number_of_moves; i++) {
        free(list_of_allocated_moves[i].list_of_intersecting_moves);
    }
}

void print_move(game_move gm) {
    printf("Game Move Size: %d\n", gm.move_size);
    printf("Game Move Align: %d\n", gm.alignment);
    printf("Game Move i: %d\n", gm.initial_line);
    printf("Game Move j: %d\n", gm.initial_column);
    printf("Game Move Filled: %d\n", gm.filled);
    printf("Game Move Word Index: %d\n", gm.word_index);
}

void print_move_vector(game_move * gms, int size) {
    for(int i = 1; i < size; i++) {
        printf("Game Move Index: %d\n", i);
        print_move(gms[i]);
        printf("\n");
    }
}