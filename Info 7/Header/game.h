#ifndef GAME
#define GAME

#include "type.h"

void one_run(int player_type, type_board *board, int *param);

void one_run_computer(type_board board, int *param);
void choose_mouvement_computer(type_board board, int *i1, int *j1, int *i2, int *j2);

void one_run_human(type_board board, int *param);
void choose_mouvement_human(type_board *board, int *i1, int *j1, int *i2, int *j2, int *param);

#endif 
