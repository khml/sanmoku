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

    Move Player::getRandomPos ()
    {
        return {toPlayColor, (int) rand () % BOARD_SIZE};
    }

    bool Player::play (Board& board)
    {
        if (board.isFinished ())
            return false;

        while (true)
        {
            Move move = getRandomPos ();
            if (board.isLegal (move))
            {
                board.put (move);
                break;
            }
        }
        toPlayColor = (toPlayColor == Cross ? Cycle : Cross);
        return true;
    }
}
