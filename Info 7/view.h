#ifndef VIEW
#define VIEW

#include "type.h"

void print_square_color(char piece, int color);
void print_board(type_board board);
void print_board(type_board board, type_mask mask);
void set_background(int color);
void set_foreground(char piece);

#endif