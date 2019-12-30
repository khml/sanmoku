//
// Created by KHML on 2019/12/30.
//

#ifndef SANMOKU_PLAYER_HPP
#define SANMOKU_PLAYER_HPP

#include <random>

#include "Board.hpp"

namespace sanmoku
{
    class Player
    {
    public:
        Player();

        Player(const Player &orig);

        virtual ~Player();

        virtual Move genMove(Board &board, Color color) = 0;
    };

    class RandomPlayer : public Player
    {
    public:
        RandomPlayer();

        RandomPlayer(RandomPlayer &orig);

        virtual ~RandomPlayer();

        Move genMove(Board &board, Color color) override;

    protected:
        std::random_device rand;
    };
}


#endif //SANMOKU_PLAYER_HPP
