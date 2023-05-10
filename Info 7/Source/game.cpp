#include "../Header/game.h"
#include "../Header/board.h"
#include "../Header/type.h"
#include "../Header/mask.h"
#include <iostream>

using namespace std;

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