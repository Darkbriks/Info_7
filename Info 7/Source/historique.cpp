#include "../Header/historique.h"
#include <iostream>
#include <string>
#include "../Header/board.h"
#include "../Header/type.h"
#include "../Header/view.h"

/**
 * @brief Print board with each move one by one
 * \n WARNING : not tested
 * @param history 
 */

void play_historique(type_history history)
{
    
    type_board board;
    type_mask mask;
    print_board(board, mask);
    system("pause");
    while(history.move_history != NULL and history.move_history != NULL)
    {
        move_piece(std::stoi(history.move_history[0].get_val()),std::stoi(history.move_history[1].get_val()),std::stoi(history.move_history[2].get_val()),std::stoi(history.move_history[3].get_val()),board);
        print_board(board,mask);
        system("pause");
        history.board_history = history.board_history->next;
        history.move_history = history.move_history->next;
    }
}
