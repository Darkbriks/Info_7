#include "../Header/mask.h"
#include "../Header/board.h"
#include "../Header/view.h"
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
 * \brief Set case color in function of the piece color and possible moves
 * \param x The column of the case
 * \param y The row of the case
 * \param piece The piece to check
 * \param mask The mask to set
 * \param board The board
 * \param n number of moves
 * \return bool, true if can continue, false if not
 */
bool set_case_color(const int x, const int y, const char piece, type_mask *mask, type_board board, int *n)
{
    if (board.get_piece(x, y) == ' ') {mask->set_mask(x, y, 4); *n+=1; return true;}
    if (is_enemy(piece, board.get_piece(x, y)) == true) {mask->set_mask(x, y, 1); *n+=1;}
    return false;
}

/**
 * \brief Highlight all possible moves of a piece
 * \param x The column of the piece
 * \param y The row of the piece
 * \param mask The mask to highlight
 * \param board The board
 * \return int, number of moves
 */
int highlight_possible_moves(const int x, const int y, type_mask *mask, type_board board)
{
    char type_piece = toupper(board.get_piece(x, y)); int n = 0;
    
    switch (type_piece)
    {
        case 'K': n += highlight_possible_moves_king(x, y, mask, board); break; // Right
        case 'Q': n += highlight_possible_moves_queen(x, y, mask, board); break; // Right
        case 'B': n += highlight_possible_moves_bishop(x, y, mask, board); break; // Right
        case 'N': n += highlight_possible_moves_knight(x, y, mask, board); break; // Right
        case 'R': n += highlight_possible_moves_rook(x, y, mask, board); break; // Right
        case 'P': n += highlight_possible_moves_pawn(x, y, mask, board); break; // Right
        default: break;
    }
    return n;
}

/**
 * \brief Highlight all possible moves of a king
 * \n The king can move in all directions, but only one case at a time
 * \param x the column of the king
 * \param y the row of the king
 * \param mask the mask to highlight
 * \param board the board
 * \return int, number of moves
 */
int highlight_possible_moves_king(const int x, const int y, type_mask *mask, type_board board)
{
    int n = 0;
    for (int i = 1; i > -2; i--) // i = column
    {
        for (int j = -1; j < 2; j++) // j = row
        {
            if (i == 0 and j == 0) {mask->set_mask(x, y, 5);} // Check if the position is the king
            set_case_color(x+i, y+j, board.get_piece(x, y), mask, board, &n);
        }
    }
    return n;
}

/**
 * \brief Highlight all possible moves of a rook
 * \n The rook can move in horizontal and vertical directions, as many cases as it wants
 * \param x the column of the rook
 * \param y the row of the rook
 * \param mask the mask to highlight
 * \param board the board
 * \return int, number of moves
 */
int highlight_possible_moves_rook(const int x, const int y, type_mask* mask, type_board board)
{
    int i = 0, j = 0, n =0; // i = column, j = row, n = number of move
    while (true) {i++; if (!set_case_color(x+i, y, board.get_piece(x, y), mask, board, &n)) break;} i = 0;
    while (true) {i--; if (!set_case_color(x+i, y, board.get_piece(x, y), mask, board, &n)) break;} i = 0;
    while (true) {j++; if (!set_case_color(x, y+j, board.get_piece(x, y), mask, board, &n)) break;} j = 0;
    while (true) {j--; if (!set_case_color(x, y+j, board.get_piece(x, y), mask, board, &n)) break;} j = 0;
    mask->set_mask(x, y, 5); return n;
}

/**
 * \brief Highlight all possible moves of a bishop
 * \n The bishop can move in diagonal directions, as many cases as it wants
 * \param x the column of the bishop
 * \param y the row of the bishop
 * \param mask the mask to highlight
 * \param board the board
 * \return int, number of moves
 */
int highlight_possible_moves_bishop(const int x, const int y, type_mask* mask, type_board board)
{
    int n = 0;
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
            if (!set_case_color(x+i, y+j, board.get_piece(x, y), mask, board, &n)) break;
        }
    }
	mask->set_mask(x, y, 5); return n;
}

/**
 * \brief Highlight all possible moves of a queen
 * \param x the column of the queen
 * \param y the row of the queen
 * \param mask the mask to highlight
 * \param board the board
 * \return int, number of moves
 */
int highlight_possible_moves_queen(const int x, const int y, type_mask* mask, type_board board)
{
    
    int n = highlight_possible_moves_rook(x,y, mask,board);
    n += highlight_possible_moves_bishop(x,y, mask,board);
    return n;
}

/**
 * \brief Highlight all possible moves of a knight
 * \n The knight can move in L shape, 2 cases in one direction and 1 case in the other
 * \param x the column of the knight
 * \param y the row of the knight
 * \param mask the mask to highlight
 * \param board the board
 * \return int, number of moves
 */
int highlight_possible_moves_knight(const int x, const int y, type_mask* mask, type_board board)
{
    int n = 0;
    for (int direction = 0; direction < 4; direction++)
    {
        int i = 0, j = 0; // i = column, j = row
        switch (direction)
        {
            case 0: i+=2; break; // Right
            case 1: i-=2; break; // Left
            case 2: j+=2; break; // Up
            case 3: j-=2; break; // Down
            default: break;
        }
        if (direction < 2) // Right or Left
        {
                set_case_color(x+i, y+j + 1, board.get_piece(x, y), mask, board, &n);
                set_case_color(x+i, y+j - 1, board.get_piece(x, y), mask, board, &n);
        }
        else // Up or Down
        {
                set_case_color(x+i + 1, y+j, board.get_piece(x, y), mask, board, &n);
                set_case_color(x+i - 1, y+j, board.get_piece(x, y), mask, board, &n);
        }
    }
    mask->set_mask(x, y, 5); return n;
}

/**
 * \brief Highlight all possible moves of a pawn
 * \n The pawn can move in vertical direction, 1 case in front of him, and 2 cases if he is on his starting position
 * \param x the column of the pawn
 * \param y the row of the pawn
 * \param mask  the mask to highlight
 * \param board the board
 * \return int, number of moves
 */
int highlight_possible_moves_pawn(const int x, const int y, type_mask* mask, type_board board)
{
    mask->set_mask(x, y, 5); int n = 0;
    int j = 1, k = 1;
    if(board.get_piece(x, y) != 'P')
    {
        j = -1; k = 6;
    }
    if (board.get_piece(x, y + j) == ' ')
    {
        mask->set_mask(x, y + j, 4); n++;
        if(y == k and (board.get_piece(x, y + j + j) == ' '))
        {
            mask->set_mask(x, y + (2*j), 4); n++;
        }
    }
    if (is_enemy(board.get_piece(x, y), board.get_piece(x + j, y + j)) == true) {mask->set_mask(x + j, y + j, 1); n++;}
    if (is_enemy(board.get_piece(x, y), board.get_piece(x - j, y + j)) == true) {mask->set_mask(x - j, y + j, 1); n++;}
    return n;
}

/**
 * \brief Highlight all pieces that can be moved
 * \param color the color of the player
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_movable_pieces(const char color, type_mask *mask, type_board board)
{
    for (int i = 0; i < 8; i++) // i = column
    {
        for (int j = 0; j < 8; j++) // j = row
        {
            if (board.get_piece(i, j) != ' ')
            {
                type_mask temp_mask = empty_mask();
                if (board.get_piece(i, j) == toupper(board.get_piece(i, j)) and color == 'w' and highlight_possible_moves(i, j, &temp_mask, board) > 0) {mask->set_mask(i, j, 2);}
                else if (color == 'b' and highlight_possible_moves(i, j, &temp_mask, board) > 0) {mask->set_mask(i, j, 2);}
            }
        }
    }
}

/**
 * \brief Return true if the piece is attacked
 * \param piece the piece to check
 * \param x the column of the piece
 * \param y the row of the piece
 * \param board the board
 * \return bool, true if the piece is attacked
 */
bool attacked_piece(const char piece, const int x, const int y, type_board board)
{
    for (int i = 0; i < 8; i++) // i = column
    {
        for (int j = 0; j < 8; j++) // j = row
        {
            if (board.get_piece(i, j) != ' ' and is_enemy(piece, board.get_piece(i, j)))
            {
                type_mask temp_mask = empty_mask();
                highlight_possible_moves(i, j, &temp_mask, board);
                if (temp_mask.get_mask(x, y) == 1) {return true;}
            }
        }
    }
    return false;
}

/**
 * \brief Highlight all pieces that can be attacked
 * \param color the color of the player
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_attacked_pieces(const char color, type_mask *mask, type_board board)
{
    for (int i = 0; i < 8; i++) // i = column
    {
        for (int j = 0; j < 8; j++) // j = row
        {
            if (board.get_piece(i, j) != ' ' and attacked_piece(board.get_piece(i, j), i, j, board)) mask->set_mask(i, j, 1);
        }
    }
}

/**
 * \brief Highlights all pieces that can take a piece
 * \param x the column of the piece
 * \param y the row of the piece
 * \param mask the mask to highlight
 * \param board the board
 */
void highlight_take_pieces(const int x, const int y, type_mask *mask, type_board board)
{
    for (int i = 0; i < 8; i++) // i = column
    {
        for (int j = 0; j < 8; j++) // j = row
        {
            if (board.get_piece(i, j) != ' ' and is_enemy(board.get_piece(x, y), board.get_piece(i, j)))
            {
                type_mask temp_mask = empty_mask();
                highlight_possible_moves(i, j, &temp_mask, board);
                if (temp_mask.get_mask(x, y) == 1) {mask->set_mask(i, j, 5);}
            }
        }
    }
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