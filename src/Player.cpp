//
// Created by KHML on 2019/12/30.
//

#include "Player.hpp"

namespace sanmoku
{
    Player::Player(){}

    Player::Player(const Player& orig)
    {}

    Player::~Player()
    {}


    RandomPlayer::RandomPlayer()
    {}

    RandomPlayer::RandomPlayer(sanmoku::RandomPlayer& orig)
    {}

    RandomPlayer::~RandomPlayer()
    {}

    Move RandomPlayer::genMove(sanmoku::Board& board, Color color)
    {
        return {color, (int) (rand() % BOARD_SIZE)};
    }
}