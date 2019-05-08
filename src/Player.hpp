/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <random>
#include "Board.hpp"

namespace sanmoku
{
    class Player
    {
    public:
        Player ();
        Player (const Player& orig);
        virtual ~Player ();
        Color toPlayColor = Cross;
        bool play (Board& board);
    private:
        std::random_device rand;
        Move getRandomPos ();

    };
}


#endif /* PLAYER_HPP */

