#include <stdio.h>
#include <stdlib.h>
#include "game_board.h"

game_board * create_empty_game_board(int M, int N) {
    game_board *game = malloc(sizeof(game_board));
    game->line_num = M;
    game->col_num = N;
    game->table = malloc(M * sizeof(square*));
    for(int i = 0; i < M; i++) 
        game->table[i] = malloc(N * sizeof(square));
    game->is_allocated = 1;
    return game;
}

void read_game_board(game_board * game) {
    int aux;
    for(int i = 0; i < game->line_num; i++)
        for(int j = 0; j < game->col_num; j++) {
            scanf("%d", &aux);
            if(aux == 0) {
                game->table[i][j].is_used = 0;
                game->table[i][j].c = '-';
            } else  {
                game->table[i][j].member_of_horizontal_move = -1;
                game->table[i][j].member_of_vertical_move = -1;
                game->table[i][j].is_black = 1;
                game->table[i][j].c = '*';
            }
        }
}

void print_game_board(game_board * game) {
    for(int i = 0; i < game->line_num; i++) {
        for(int j = 0; j < game->col_num; j++) 
            printf("%c ", game->table[i][j].c);
        printf("\n");
    }
}

void free_game_board(game_board * game) {
    if(!game->is_allocated) return;
    for(int i = 0; i < game->line_num; i++) 
        free(game->table[i]);
    free(game->table);
    free(game);
}
