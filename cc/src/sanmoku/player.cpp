//
// Created by KHML on 2019/12/30.
//

#include <sammoku/player.hpp>

namespace sanmoku
{
    Player::Player()
    = default;

    Player::Player(const Player& orig)
    = default;

    Player::~Player()
    = default;

    RandomPlayer::RandomPlayer()
    = default;

    RandomPlayer::RandomPlayer(sanmoku::RandomPlayer& orig)
    {}

    RandomPlayer::~RandomPlayer()
    = default;

    Move RandomPlayer::genMove(sanmoku::Board& board, Color color)
    {
        return {color, (int) (rand() % BOARD_SIZE)};
    }
}