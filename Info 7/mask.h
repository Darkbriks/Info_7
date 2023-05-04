#ifndef MASK
#define MASK

#include "type.h"

// Methods
type_mask empty_mask();
int get_mask(type_mask mask);
void clear_mask(type_mask mask);

// Higlihts functions
void highlight_possible_moves(int x, int y, type_mask *mask, type_board board);
void highlight_possible_moves_king(int x, int y, type_mask *mask, type_board board);
void highlight_possible_moves_rook(int x, int y, type_mask *mask, type_board board);

#endif