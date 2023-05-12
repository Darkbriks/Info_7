#include <iostream>
#include <sstream>
#include <array>
#include <string>
#include <cstdlib>
#include "Header/board.h"
#include "Header/game.h"
#include "Header/mask.h"
#include "Header/type.h"
#include "Header/view.h"
#include "Header/test_function.h"

using namespace std;

int main(int argc, char* argv[])
{
    type_board board;
    reset_board(board);
    type_mask mask = empty_mask();
    /*cout << king_in_check(board, 'w') << endl;
    print_board(board, mask);
    cout << endl;*/

    /*int i1, j1, i2, j2;
    choose_mouvement_computer(board, &i1, &j1, &i2, &j2);
    cout << i1 << j1 << ' ' << i2 << j2 << endl;
    move_piece(i1, j1, i2, j2, board);
    print_board(board);

    board.set_turn('b'); cout << board.get_turn() << endl;
    choose_mouvement_computer(board, &i1, &j1, &i2, &j2);
    cout << i1 << j1 << ' ' << i2 << j2 << endl;
    move_piece(i1, j1, i2, j2, board);
    print_board(board);*/

    while (true)
    {
        one_run(2, &board);
        cout << endl;
        system("pause");

        one_run(2, &board);
        cout << endl;
        system("pause");
    }

    /*string positionCommand = "position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    string goCommand = "go depth 10";

    string positionOutput = communicate_with_stockfish(positionCommand);
    string goOutput = communicate_with_stockfish(goCommand);

    cout << positionOutput << endl;
    cout << goOutput << endl;*/
    
    system("pause");
    
    return 0;
}
