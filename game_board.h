#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <stdbool.h>

typedef struct {
    char c;
    bool is_used;
    bool is_black;
    int member_of_horizontal_move;
    int member_of_vertical_move;
} square;

typedef struct {
    int line_num;
    int col_num;
    int horizontal_move_num;
    int vertical_move_num;
    square **table; 
    bool is_allocated;
    bool is_solved;
} game_board;

game_board * create_empty_game_board(int M, int N);
void read_game_board(game_board * game);
void free_game_board(game_board * game);

void print_game_board(game_board * game);
#endif // GAME_BOARD_H
