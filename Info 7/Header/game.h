#ifndef GAME
#define GAME

#include "type.h"

//void one_run(int Joueur);

//void one_run_human();
void one_run(char Joueur, type_board* board, type_mask* mask);
void one_run_human(type_board* board);
void one_run_computer(type_board* board, type_mask* mask);
void choose_mouvement_human(type_board* board, type_mask* mask);
bool test_run(int lig, int col, int f_lig, int f_col, type_board board, type_mask mask);

void one_run_computer();
void choose_mouvement_computer();

#endif 
