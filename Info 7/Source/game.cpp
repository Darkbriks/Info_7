#include "../Header/game.h"
#include "../Header/board.h"
#include "../Header/type.h"
#include "../Header/mask.h"
#include <iostream>
#include <string>

#include "../Header/view.h"

using namespace std;

void one_run(const int player_type, type_board *board)
{
    if (player_type == 1) {one_run_computer(*board);}
    else {one_run_human(*board);}

    // Set the turn to the other player, increment the full move number if it is the black player's turn, and print the board
    type_mask mask = empty_mask();
    print_board(*board, mask);
    board->set_turn(board->get_turn() == 'w' ? 'b' : 'w');
    if (board->get_turn() == 'b') {board->set_fullmove(board->get_fullmove() + 1);}
}

void one_run_computer(type_board board)
{
    int i1, j1, i2, j2;
    choose_mouvement_computer(board, &i1, &j1, &i2, &j2);
    move_piece(i1, j1, i2, j2, board);
}

type_maillon* search_moves_with_value(const int mask_value, const type_mask mask) // search all the moves with a specific value
{
    type_maillon* maillon = new type_maillon("tete");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (mask.get_mask(i, j) == mask_value) {maillon->add(to_string(i) + to_string(j) + to_string(mask_value));}
        }
    }
    return maillon;
}

type_maillon* highlight_possible_moves(type_board board) // highlight all the pieces that can be moved
{
    type_mask mask = empty_mask();
    
    highlight_attacked_pieces(board.get_turn(), &mask, board); // highlight all the pieces that can be attacked by the opponent
    type_maillon* maillon = search_moves_with_value(1, mask);

    if (maillon->size() <= 1) // if there is no piece that can be attacked by the opponent, highlight all the pieces that can be moved
    {
        highlight_movable_pieces(board.get_turn(), &mask, board);
        maillon = search_moves_with_value(2, mask);
    }
    return maillon;
}

type_maillon* complete_move(type_board board, const int i, const int j, const int movement_type) // highlight all the possible moves for a piece
{
    type_maillon* maillon = new type_maillon("tete");
    type_mask mask = empty_mask();
    
    if (movement_type == 1) {highlight_take_pieces(i, j, &mask, board);}
    else if (movement_type == 2) {highlight_possible_moves(i, j, &mask, board);}
    else {return maillon;}
    maillon = search_moves_with_value(movement_type == 1 ? 5 : 4, mask);
    return maillon;
}

void choose_mouvement_computer(type_board board, int *i1, int *j1, int *i2, int *j2)
{
    type_maillon* maillon = highlight_possible_moves(board);
    if (maillon->size() <= 1) {*i1 = -1; return;} // if there is no piece that can be moved, return -1 (pat)
    
    string move1 = maillon->get_val(random(1, maillon->size() - 1));

    delete maillon;
    maillon = complete_move(board, move1[0]-48, move1[1]-48, move1[2]-48);

    string move2 = maillon->get_val(random(1, maillon->size() - 1));

    if (move1[2] == '1') {*i1 = move2[0]-48; *j1 = move2[1]-48; *i2 = move1[0]-48; *j2 = move1[1]-48;}
    else {*i1 = move1[0]-48; *j1 = move1[1]-48; *i2 = move2[0]-48; *j2 = move2[1]-48;}
}

void one_run_human(type_board board)
{
    type_mask mask = empty_mask();
    int c = 0;

    while(c != 1)
    {
        cout << "Que voulez vous faire ?" << endl << "\t1.Bouger une piece" << endl << "\t2.Visualliser une chose" << endl << "\t3.Visualliser plusieurs choses" << endl << "Votre choix : ";
        cin >> c; int i1 = -1, j1 = 0, i2 = 0, j2 = 0;
        switch (c)
        {
            case 1: choose_mouvement_human(&board, &i1, &j1, &i2, &j2); break;
            case 2: mask_choices_menu (board, mask); clear_mask(mask); break;
            case 3: mask_choices(board, mask); clear_mask(mask); break; 
            default: break;
        }
        if (i1 == -1) {return;}
        move_piece(i1, j1, i2, j2, board);
    }
}

bool test_run(const int col, const int lig, const int f_col, const int f_lig, type_board board, const type_mask mask)
{
    type_mask nmask = mask; //nmask = mask;
    if(highlight_possible_moves(col, lig,&nmask, board) > 0 and nmask.get_mask(f_col, f_lig) > 0)
        {print_board(board, nmask); clear_mask(nmask); return true;} 
    return false;
}

void choose_mouvement_human(type_board *board/*, type_mask *mask*/,  int *i1, int *j1, int *i2, int *j2)
{
    type_mask mask = empty_mask();
    int lig, col, f_lig, f_col;
    char s;

    cout << "Etes vous sur de vouloir deplacer une piece ? (y/n) : "; cin >> s;
    if (s == 'n') {one_run_human(*board); *i1 = -1; return;}
    
    while(true)
    {
        cout << "Choisissez une piece a deplacer (colonne/ligne) : "; cin >> col >> lig;
        lig = lig - 1; col = col - 1;

        // Si il n'y a pas de piece a cet endroit ou si la piece est de la mauvaise couleur
        if (board->get_piece(col,lig) == ' ' or board->get_turn() == 'w' ? board->get_piece(col,lig) == toupper(board->get_piece(col, lig)) : board->get_piece(col,lig) == tolower(board->get_piece(col, lig))) {break;}
        cout << "La case est vide ou la piece est de la mauvaise couleur, veuillez recommencer." << endl;
    }
    
    cout << "Quelle est sa case d'arivee ? (colonne/ligne) : "; cin >> f_col >> f_lig;
    f_lig = f_lig -1; f_col = f_col -1;
    
    if(test_run(col, lig , f_col, f_lig, *board, mask))
    {
        cout << "Le mouvement est legal." << endl;
        while(true)
        {
            cout << "Souhaitez vous le realiser ? (y/n) :"; cin >> s;
            if (s == 'y' or  s =='n') {break;}
            cout << "Erreur, veuillez reessayer." << endl;
        }
        
        if(s == 'y') {*i1 = col; *j1 = lig; *i2 = f_col; *j2 = f_lig;}
        else {cout << "Mouvement annule." << endl; *i1 = -1; choose_mouvement_human(board, i1, j1, i2, j2);}
    }
    else {cout << "Mouvement impossible, veuillez saisire un nouveau mouvement." << endl; *i1 = -1; choose_mouvement_human(board, i1, j1, i2, j2);}
}