/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Player.hpp"

namespace sanmoku
{
    Player::Player () { }

    Player::Player (const Player& orig) { }

    Player::~Player () { }

    Move Player::getRandomPos ()
    {
        return {toPlayColor, (int) rand () % BOARD_SIZE};
    }

    Move Player::genMove(sanmoku::Board &board)
    {
        auto policy = model.infer(board.getBoard());

        while (true)
        {
            std::discrete_distribution<std::size_t> dist(policy.begin(), policy.end());
            std::mt19937 engine(rand());
            std::size_t pos = dist(engine);
            Move move(toPlayColor, (int) pos);
            if (board.isLegal(move))
                return move;
            policy.erase(policy.begin() + pos);
        }

    }

    bool Player::play (Board& board)
    {
        if (board.isFinished ())
            return false;

        while (true)
        {
            Move move = genMove (board);
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
