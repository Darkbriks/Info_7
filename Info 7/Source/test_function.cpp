#include "../Header/test_function.h"
#include <iostream>
#include <random>

#include "../Header/view.h"

using namespace std;

/**
 * @brief Return a random number between a and b
 * @param a the minimum number
 * @param b the maximum number
 * @return int, a random number between a and b
 */
int random(const int a, const int b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(a, b);
    return dis(gen);
}


/**
 * @brief Test all getters of type_board
 * @param board 
 */
void test_all_type_board_getters(type_board board)
{
    cout << "Test all getters of type_board" << endl << endl;
    cout << "Test get_piece" << endl;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << "\tCase " << "(" << i+1 << ", " << j+1 << ") : " << board.get_piece(i, j) << endl;
        }
        system("pause");
    }
    cout << endl << "Test get_piece when i or j is out of range" << endl;
    cout << "\tCase " << "(" << 10 << ", " << 1 << ") : " << board.get_piece(9, 0) << endl;

    cout << endl << "Test get_turn" << endl;
    cout << "\tTurn : " << board.get_turn() << endl;

    cout << endl << "Test get_castling" << endl;
    cout << "\tCastling : " << board.get_castling() << endl;

    cout << endl << "Test get_castling when it is surchaged with a color" << endl;
    cout << "\tCastling with color 'w' : " << board.get_castling('w') << endl;
    cout << "\tCastling with color 'b' : " << board.get_castling('b') << endl;

    cout << endl << "Test get_en_passant" << endl;
    cout << "\tEn passant : " << board.get_en_passant() << endl;

    cout << endl << "Test get_halfmove" << endl;
    cout << "\tHalfmove : " << board.get_halfmove() << endl;

    cout << endl << "Test get_fullmove" << endl;
    cout << "\tFullmove : " << board.get_fullmove() << endl;

    cout << endl << "Test get_fen" << endl;
    cout << "\tFen : " << board.get_fen() << endl << endl;
}

/**
 * @brief Test all setters of type_board
 * \n WARNING : for display results, we use the getters. Make sure that the getters work before testing the setters.
 * @param board 
 */
void test_all_type_board_setters(type_board board)
{
    cout << "Test all setters of type_board" << endl << endl;
    cout << "Test set_piece with five aleatory cases. The piece is '*'" << endl;
    for (int i = 0; i < 5; i++)
    {
        int x = random(0, 7);
        int y = random(0, 7);
        char piece = '*';
        cout << "\tCase " << "(" << x+1 << ", " << y+1 << ") : " << piece << endl;
        board.set_piece(x, y, piece);

        cout << "\t\tPiece : " << board.get_piece(x, y) << endl;
    }

    cout << endl << "Test set_piece when i or j is out of range" << endl;
    cout << "\tCase " << "(" << 10 << ", " << 1 << ") : " << '*' << endl;
    board.set_piece(9, 0, '*');
    cout << "\t\tPiece : " << board.get_piece(9, 0) << endl;

    cout << endl << "Test set_turn with black primary, and white secondary" << endl;
    cout << "\tTurn : " << 'b' << endl; board.set_turn('b');
    cout << "\t\tTurn : " << board.get_turn() << endl;
    cout << "\tTurn : " << 'w' << endl; board.set_turn('w');
    cout << "\t\tTurn : " << board.get_turn() << endl;

    cout << endl << "Test set_castling with 'KQkq' primary, and 'kq' secondary" << endl;
    cout << "\tCastling : " << "KQkq" << endl; board.set_castling('K', true); board.set_castling('Q', true); board.set_castling('k', true); board.set_castling('q', true);
    cout << "\t\tCastling : " << board.get_castling() << endl;
    cout << "\tCastling : " << "kq" << endl; board.set_castling('K', false); board.set_castling('Q', false); board.set_castling('k', true); board.set_castling('q', true);
    cout << "\t\tCastling : " << board.get_castling() << endl;

    system("pause");

    cout << endl << "Test set_en_passant with 'e3' primary, and '-' secondary" << endl;
    cout << "\tEn passant : " << "e3" << endl; board.set_en_passant("e3");
    cout << "\t\tEn passant : " << board.get_en_passant() << endl;
    cout << "\tEn passant : " << "-" << endl; board.set_en_passant("--");
    cout << "\t\tEn passant : " << board.get_en_passant() << endl;

    cout << endl << "Test set_halfmove with 10 primary, and 0 secondary" << endl;
    cout << "\tHalfmove : " << 10 << endl; board.set_halfmove(10);
    cout << "\t\tHalfmove : " << board.get_halfmove() << endl;
    cout << "\tHalfmove : " << 0 << endl; board.set_halfmove(0);
    cout << "\t\tHalfmove : " << board.get_halfmove() << endl;

    cout << endl << "Test set_fullmove with 10 primary, and 1 secondary" << endl;
    cout << "\tFullmove : " << 10 << endl; board.set_fullmove(10);
    cout << "\t\tFullmove : " << board.get_fullmove() << endl;
    cout << "\tFullmove : " << 1 << endl; board.set_fullmove(1);
    cout << "\t\tFullmove : " << board.get_fullmove() << endl;

    cout << endl << "Test set_board_whith_fen with an inverted board" << endl;
    cout << "\tBoard : " << endl; board.set_board_with_fen("RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr w KQkq - 0 1");
    for (int i = 0; i < 8; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < 8; j++)
        {
            cout << board.get_piece(i, j) << " ";
        }
        cout << endl;
    }

    cout << endl << "Test set_board_whith_array with an inverted board" << endl;
    char board_array[64] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
                            'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                            'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                            'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    cout << "\tBoard : " << endl; board.set_board_with_array(board_array);
    for (int i = 0; i < 8; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < 8; j++)
        {
            cout << board.get_piece(i, j) << " ";
            
        }
        cout << endl;
    }
}
/**
 * @brief Test random getter of type_mask
 * @param mask the mask
 */
void test_all_type_mask_getters(type_mask mask)
{
    type_board B;
    B.set_board_with_fen("rnbqkbnr/pppppppp/8/8/3R3P/8/PPPPPPPP/RNBKQBNR w KQkq - 0 1");
    print_board(B,mask);
    int x = random(7,7),y = random(8,9);
    for(int C =0; C < 10;C++)
    {
        cout <<x<<','<<y<< " : " <<mask.get_mask(x,y)<< endl;
        x = random(0,7);
        y = random(0,9);
    }
}
/**
 * @brief Test random setters of type_mask
 * @param mask the mask
 */
void test_all_type_mask_setters(type_mask mask)
{
    type_board B;
    B.set_board_with_fen("rnbqkbnr/pppppppp/8/8/3R3P/8/PPPPPPPP/RNBKQBNR w KQkq - 0 1");
    int x = random(7,7),y = random(8,9);
    for(int C =0; C < 10;C++)
    {
        mask.set_mask(x,y,random(0,9));
        cout <<x<<','<<y<< " : " <<mask.get_mask(x,y)<< endl;
        x = random(0,7);
        y = random(0,9);
    }
    print_board(B,mask);
}
