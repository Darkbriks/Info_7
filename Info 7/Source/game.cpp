#include "../Header/game.h"
#include "../Header/board.h"
#include "../Header/type.h"
#include "../Header/mask.h"
#include <iostream>

using namespace std;

void on_run(char Joueur, type_board *board, type_mask *mask)
{
    if(Joueur == 'O')
    {
        one_run_human(board);
    }
}

void choose_mouvement_computer(type_game game)
{
    highlight_attacked_pieces(game.board.get_turn(), &game.mask, game.board);
    // Si une piece est attaquee, on la prend
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j< 8; j++)
        {
            if (game.mask.get_mask(i, j) == 1)
            {
                highlight_take_pieces(i, j, &game.mask, game.board); // Les pieces qui peuvent prendre la piece attaquee sont mises en evidence
                return;
            }
        }
    }
    // Sinon, on bouge une piece
    highlight_movable_pieces(game.board.get_turn(), &game.mask, game.board);
}

void one_run_human(type_board *board)
{
    type_mask mask = empty_mask();
    int c = 0;

    while(c != 1)
    {
        cout << "Que voulez vous faire ?" << endl << "\t1.Bouger une piece" << endl << "\t2.Visualliser une chose" << endl << "\t3.Visualliser plusieurs choses" << endl << "Votre choix : ";
        cin >> c;
        switch (c)
        {
        case 1: choose_mouvement_human(board, &mask); break;
        case 2: mask_choices_menu (*board, mask); clear_mask(mask); break;
        case 3: mask_choices(*board, mask); clear_mask(mask); break; 
        default: break;
        }
    }
}

void choose_mouvement_human(type_board *board, type_mask *mask)
{
    int lig, col, f_lig, f_col;
    char s;
    cout << "Choisissez le pion a bouger (colonne/ligne) : ";
    cin >> col >> lig;
    lig = lig - 1;
    col = col - 1;
    while(board->get_piece(col,lig) == ' ')
    {
        cout << "La case est vide, reessayez : ";
        cin >> col >> lig;
        lig = lig - 1;
        col = col - 1;
    }
    cout << "Ou doit elle aller ? (colonne/ligne) : ";
    cin >> f_col >> f_lig;
    f_lig = f_lig -1;
    f_col = f_col -1;
    if(test_run(col, lig , f_col, f_lig, *board, *mask))
    {
        cout << "Le mouvement est possible, voulez vous vraiment le faire ? (y/n) :";
        cin >> s;
        while(s != 'y' and s !='n')
        {
            cout << "Erreur, veuillez reessayer : ";
            cin >> s;
        }
        if(s == 'y')
        {
            move_piece(col, lig, f_col, f_lig, *board);
            print_board(*board, *mask);
            clear_mask(*mask);
        }
    }
    else
    {
        "Mouvement impossible, veuillez saisire de nouvelles coordonnées :";
        cin >> f_col >> f_lig;
        f_lig = f_lig -1;
        f_col = f_col -1;
    }
}

bool test_run(int col, int lig, int f_lig, int f_col, type_board board, type_mask mask)
{
    type_mask nmask;
    nmask = mask;
    if(highlight_possible_moves(col, lig,&nmask, board) > 0 and nmask.get_mask(f_lig,f_col) > 0)
    {
        print_board(board, nmask);
        clear_mask(nmask);
        return true;
    } 
    return false;
 }
