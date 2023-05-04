#include <iostream>
#include <sstream>
#include "board.h"
#include "type.h"
#include "view.h"
#include "mask.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Test board functions
    type_board type_board;
    type_mask mask = empty_mask();
    clear_mask(mask);
    for(int i=7;i>=0;i--)
    {
        mask.set_mask(i,7,1);
        mask.set_mask(i,6,2);
        mask.set_mask(i,5,3);
        mask.set_mask(i,4,4);
        mask.set_mask(i,3,5);
        mask.set_mask(i,2,6);
        mask.set_mask(i,1,7);
    }
    type_board.set_board_with_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    print_board(type_board, mask);
    
    system("pause");
    move_piece(1, 5, 3, 5, type_board);
    print_board(type_board, mask);
    print_fen(type_board);
    cout << endl;
    system("pause");
    move_piece(6, 5, 4, 5, type_board);
    print_board(type_board, mask);
    print_fen(type_board);
    cout << endl;


    /*char16_t c1{0x2654};
    wcout << c1 << endl;
    cout << c1 << endl;

    cout << "\0xE2 \0x99 \0x9E" << endl;
    cout << "\0x265E" << endl;
    cout << "\0x0000265E" << endl;
    cout << '\u265E' << endl;*/
    
    system("pause");
    
    return 0;
}
