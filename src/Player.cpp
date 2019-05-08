/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <random>
#include "Player.hpp"
#include "Board.hpp"

namespace sanmoku
{
    Player::Player () { }

    Player::Player (const Player& orig) { }

    Player::~Player () { }

    int Player::getRandomPos ()
    {
        return rand () % BOARD_SIZE;
    }

    int Player::play (Board& board)
    {
        int pos;

        if (board.isFinished ())
            return 0;

        while (true)
        {
            pos = getRandomPos ();
            if (board.isLegal (pos))
                break;
        }

        board.put (pos, toPlayColor);
        toPlayColor = toPlayColor == CROSS ? CYCLE : CROSS;

        return 1;
    }
}
