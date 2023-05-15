#include "../Header/board.h"
#include "../Header/game.h"
#include "../Header/mask.h"
#include "../Header/type.h"
#include "../Header/view.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * \brief The main function for a turn of the game
 * \n This function increments the full move number if it is the black player's turn, changes the turn, and prints the board
 * \param player_type The type of the player (1 for computer, 2 for human)
 * \param board The board of the game
 */
void one_run(const int player_type, type_board *board, int *param)
{
    if (player_type == 1) {one_run_computer(*board, param);}
    else {one_run_human(*board, param);}

    // Set the turn to the other player, increment the full move number if it is the black player's turn, and print the board
    type_mask mask = empty_mask();
    print_board(*board, mask);
    board->set_turn(board->get_turn() == 'w' ? 'b' : 'w');
    if (board->get_turn() == 'b') {board->set_fullmove(board->get_fullmove() + 1);}
}

#pragma region Computer player
/**
 * \brief The main function for a turn of the game for computer player
 * \n This function chooses a move for the computer player, and moves the piece
 * \param board The board of the game
 */
void one_run_computer(type_board board, int *param)
{
    if (*param == 2) {if (random(1, 2) == 1) {*param = 3; return;} else {*param = 0; return;}}// 1/2 chance to play accept null game
    
    int i1, j1, i2, j2;
    choose_mouvement_computer(board, &i1, &j1, &i2, &j2);
    move_piece(i1, j1, i2, j2, board);
}

/**
 * \brief This function returns all moves of a specific type
 * \param mask_value The value of the mask to search (1 for attacked pieces, 2 for movable pieces, ...)
 * \param mask The mask to search in
 * \return A list of all the moves of the specified type
 */
type_maillon* search_moves_with_value(const int mask_value, const type_mask mask) // search all the moves with a specific value
{
    type_maillon* maillon = new type_maillon("tete");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (mask.get_mask(i, j) == mask_value) {maillon->add(to_string(i) + to_string(j) + to_string(mask_value));} // The last digit of the string is the value of the mask
        }
    }
    return maillon;
}

/**
 * \brief This highlights all the pieces that can be moved in this turn and returns them in a chained list
 * \n If at least one piece can attack an opponent piece, only the pieces that can attack are highlighted
 * \n Otherwise, all the pieces that can be moved are highlighted
 * \param board The board of the game
 * \return A list of all the pieces that can be moved
 */
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

/**
 * \brief Complete the move of a piece in function of the type of movement
 * \n If the movement type is 1, highlight all the pieces that can take the piece at the position (i, j)
 * \n If the movement type is 2, highlight all the possible moves of the piece at the position (i, j)
 * \param board The board of the game
 * \param i The column of the piece
 * \param j The row of the piece
 * \param movement_type The type of movement (1 for take, 2 for move)
 * \return A list of all the possible moves of the piece
 */
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

/**
 * \brief This function chooses a move for the computer player
 * \n If there is no piece that can be moved, the function returns -1 (pat)
 * \param board The board of the game
 * \param i1 The column of the piece to move
 * \param j1 The row of the piece to move
 * \param i2 The column of the destination
 * \param j2 The row of the destination
 */
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
#pragma endregion

#pragma region Human player
/**
 * \brief This function manages a turn of a human player
 * \param board The board of the game
 */
void one_run_human(type_board board, int *param)
{
    type_mask mask = empty_mask();
    int c = 0;

    if (*param == 2) {cout << "Votre adversaire a proposé une nulle, voulez vous l'accepter ? (1 pour oui, 0 pour non) : "; cin >> c; if (c == 1) {*param = 3; return;} else {*param = 0; return;}}
    *param = 0;

    while(c != 1)
    {
        cout << "C'est au tour des " << (board.get_turn() == 1 ? "blancs" : "noirs") << " de jouer, voici vos options :" << endl;
        cout <<"\t1.Bouger une piece" << endl << "\t2.Visualliser une chose" << endl <<
                "\t3.Visualliser plusieurs choses" << endl << "\t4.Abandonner" << endl <<
                "\t5.Proposer une nulle" << endl << "\t6.Sauvegarder la partie et quitter" << endl;
        cout << "Que choisissez vous : "; cin >> c; int i1 = -1, j1 = 0, i2 = 0, j2 = 0;
        
        switch (c)
        {
            case 1: choose_mouvement_human(&board, &i1, &j1, &i2, &j2, param); break;
            case 2: mask_choices_menu (board, mask); clear_mask(mask); break;
            case 3: mask_choices(board, mask); clear_mask(mask); break;
            case 4: char c; cout << "Etes vous sur de vouloir abandonner ? (y/n) : "; cin >> c; if (c == 'y') {*param = 1;} return;
            case 5: cout << "Etes vous sur de vouloir proposer une nulle ? (y/n) : "; cin >> c; if (c == 'y') {*param = 2;} return;;
            case 6: cout << "Etes vous sur de vouloir sauvegarder la partie et quitter ? (y/n) : "; cin >> c; if (c == 'y') {*param = 4;} return;
            default: break;
        }
        // If the player wants to move a piece and the move is possible, move the piece
        if (c == 1 and i1 != -1) {move_piece(i1, j1, i2, j2, board);}
        else if (c == 1) {cout << "Ce mouvement n'est pas possible" << endl;}
    }
}

/**
 * \brief Verifies if a move is possible
 * \param col The column of the piece to move
 * \param lig The row of the piece to move
 * \param f_col The column of the destination
 * \param f_lig The row of the destination
 * \param board The board of the game
 * \param mask The mask of the game
 * \return True if the move is possible, false otherwise
 */
bool test_run(const int col, const int lig, const int f_col, const int f_lig, type_board board, const type_mask mask)
{
    type_mask nmask = mask; //nmask = mask;
    if(highlight_possible_moves(col, lig,&nmask, board) > 0 and nmask.get_mask(f_col, f_lig) > 0)
        {clear_mask(nmask); mask.set_mask(f_col, f_lig, 6); mask.set_mask(col, lig, 5); print_board(board, nmask); clear_mask(nmask); return true;} 
    return false;
}

/**
 * \brief This function chooses a move for the human player
 * \n If there is no piece that can be moved, the function returns -1 (pat)
 * \param board The board of the game
 * \param i1 The column of the piece to move
 * \param j1 The row of the piece to move
 * \param i2 The column of the destination
 * \param j2 The row of the destination
 */
void choose_mouvement_human(type_board *board,  int *i1, int *j1, int *i2, int *j2, int *param)
{
    type_mask mask = empty_mask();
    int lig, col, f_lig, f_col;
    char s;

    cout << "Etes vous sur de vouloir deplacer une piece ? (y/n) : "; cin >> s;
    if (s == 'n') {one_run_human(*board, param); *i1 = -1; return;}
    
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
        else {cout << "Mouvement annule." << endl; *i1 = -1; choose_mouvement_human(board, i1, j1, i2, j2, param);}
    }
    else {cout << "Mouvement impossible, veuillez saisir un nouveau mouvement." << endl; *i1 = -1; choose_mouvement_human(board, i1, j1, i2, j2, param);}
}
#pragma endregion 