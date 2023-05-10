#include "../Header/mask.h"
#include "../Header/board.h"
#include <iostream>

using namespace std;

/**
 * \brief Create and return a mask set to 0
 * \return type_mask, a mask set to 0
 */
type_mask empty_mask() {const type_mask mask; return mask;}

/**
 * \brief Set all cases of a mask to 0
 * \param mask The mask to clear
 */
void clear_mask(const type_mask mask) {for (int i = 0; i < 64; i++) mask.set_mask(i/8, i%8, 0);}

/**
 * \brief Highlight all possible moves of a piece
 * \param x The column of the piece
 * \param y The row of the piece
 * \param mask The mask to highlight
 * \param board The board
 */
void highlight_possible_moves(int x, int y, type_mask *mask, type_board board)
{
    if (board.get_piece(x, y) == 'K' or board.get_piece(x, y) == 'k') {highlight_possible_moves_king(x, y, mask, board);}
    if (board.get_piece(x, y) == 'R' or board.get_piece(x, y) == 'r') {highlight_possible_moves_rook(x, y, mask, board);}
	if (board.get_piece(x, y) == 'B' or board.get_piece(x, y) == 'b') {highlight_possible_moves_bishop(x, y, mask, board);}
}

/**
 * \brief Highlight all possible moves of a king
 * \n The king can move in all directions, but only one case at a time
 * \param x the column of the king
 * \param y the row of the king
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_possible_moves_king(const int x, const int y, type_mask *mask, type_board board)
{
    for (int i = 1; i > -2; i--) // i = column
    {
        for (int j = -1; j < 2; j++) // j = row
        {
            if (i == 0 and j == 0) {mask->set_mask(x, y, 5);} // Check if the position is the king
            else if (board.get_piece(x+i, y+j) == ' ') {mask->set_mask(x+i, y+j, 4);} // Set mask to blue
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1);} // Set mask to red
        }
    }
}

/**
 * \brief Highlight all possible moves of a rook
 * \n The rook can move in horizontal and vertical directions, as many cases as it wants
 * \param x the column of the rook
 * \param y the row of the rook
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_possible_moves_rook(const int x, const int y, type_mask* mask, type_board board)
{
    for (int direction = 0; direction < 4; direction++)
    {
        int i = 0, j = 0; // i = column, j = row
        while (true)
        {
            switch (direction)
            {
                case 0: i++; break; // Right
                case 1: i--; break; // Left
                case 2: j++; break; // Up
                case 3: j--; break; // Down
                default: break;
            }
            if (board.get_piece(x+i, y+j) == ' ') mask->set_mask(x+i, y+j, 4);
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1); break;}
            else break;
        }
    }
    mask->set_mask(x, y, 5);
}

void highlight_possible_moves_bishop(const int x, const int y, type_mask* mask, type_board board)
{
    for (int direction = 0; direction < 4; direction++)
    {
        int i = 0, j = 0;
        while (true)
        {
            switch (direction)
            {
                case 0: i++; j++; break;
                case 1: i++; j--; break;
                case 2: i--; j++; break;
                case 3: i--; j--; break;
                default: break;
            }
            if (board.get_piece(x+i, y+j) == ' ') mask->set_mask(x+i, y+j, 4);
            else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1); break;}
            else break;
        }
    }
	mask->set_mask(x, y, 5);
}

void highlight_possible_moves_queen(int x, int y, type_mask* mask, type_board board)
{
    highlight_possible_moves_rook(x,y, mask,board);
    highlight_possible_moves_bishop(x,y, mask,board);
}

void highlight_possible_moves_knight(int x, int y, type_mask* mask, type_board board)
{
    for (int direction = 0; direction < 4; direction++)
    {
        int i = 0, j = 0; // i = column, j = row
        switch (direction)
        {
            case 0: i=i+2; break; // Right
            case 1: i=i-2; break; // Left
            case 2: j=j+2; break; // Up
            case 3: j=j-2; break; // Down
            default: break;
        }
        switch (direction) 
        {
            case 0: j = 1; break; 
            case 1: j = 1; break; 
            case 2: i = 1; break; 
            case 3: i = 1; break; 
            default: break;
            }
        if (board.get_piece(x+i, y+j) == ' ') mask->set_mask(x+i, y+j, 4);
        else if (is_enemy(board.get_piece(x, y), board.get_piece(x+i, y+j)) == true) {mask->set_mask(x+i, y+j, 1); break;}
        if (board.get_piece(x-i, y-j) == ' ') mask->set_mask(x-i, y-j, 4);
        else if (is_enemy(board.get_piece(x, y), board.get_piece(x-i, y-j)) == true) {mask->set_mask(x-i, y-j, 1); break;}
        else break;
    }
    mask->set_mask(x, y, 5);
}

void highlight_possible_moves_pawn(int x, int y, type_mask* mask, type_board board)
{
    mask->set_mask(x, y, 5);
    int j = 1, k = 1;
    if(board.get_piece(x, y) != 'P')
    {
        j = -1, k = 6;
    }
    if (board.get_piece(x, y + j) == ' ')
    {
        mask->set_mask(x, y + j, 4);
        if(y == k and (board.get_piece(x, y + j + j) == ' '))
        {
            mask->set_mask(x, y + (2*j), 4);
        }
    }
    if (is_enemy(board.get_piece(x, y), board.get_piece(x + j, y + j)) == true) {mask->set_mask(x + j, y + j, 1);}
    if (is_enemy(board.get_piece(x, y), board.get_piece(x - j, y + j)) == true) {mask->set_mask(x - j, y + j, 1);}
}

void mask_choices_menu(type_board board, type_mask mask)
{
    int choix = 0;
    choix = sous_mask_choices(choix);
    sous_mask_choices(choix,  board, &mask);

}

int sous_mask_choices(int choix)
{
    cout << "Voici les differents affichages possibles :" << endl << "    1.Les pieces qui peuvent se deplacer" << endl << "    2.Les pieces ennemies pouvant etre prises" << endl << "    3.Les pieces ennemies pouvant mettre en danger l'une des votres"
    << endl << "    4.Les actions possibles d'une piece specifique" << endl << "Votre choix : ";
    cin >> choix;
    while (choix < 0 or choix > 4)
    {
        cout << "Reessayez : ";
        cin >> choix;
    }
    return choix;
}

void sous_mask_choices(int choix, type_board board, type_mask* mask)
{
    int  x, y;
    switch (choix)
    {
    case 1: ; break; 
    case 2: ; break; 
    case 3: ; break; 
    case 4:
        {
            cout << "Choisissez la piece (x,y) : ";
            cin >> x >> y;
            x = x - 1;
            y = y - 1;
            while(board.get_piece(x,y) == ' ')
            {
                cout << "La case est vide, reessayez : ";
                cin >> x >> y;
            }
            highlight_possible_moves(x, y, mask, board); 
            print_board(board, *mask); break;
        }
        default: break;
    }    
}

void mask_choices(type_board board, type_mask mask)
{
    int choix = 0, x, y;
    choix = sous_mask_choices(choix);
    string end;
    while(end != "Non")
    {
        sous_mask_choices(choix, board, &mask);
        cout << "Voulez vous continuer ? (Oui/Non) : ";
        cin >> end;
        while(end != "Oui" and end != "Non")
        {
            cout << "Reponse incorrecte, veillez recommencer (Oui/Non) : ";
            cin >> end;
        }
        if(end == "Oui")
        {
            cout << "Rechoisissez la catégorie (1,2,3,4) : ";
            cin >> choix;
        }    
    }

}
