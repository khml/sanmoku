//
// Created by KHML on 2019-09-15.
//

#ifndef SANMOKU_BOARD_HPP
#define SANMOKU_BOARD_HPP

#include "BoardCore.hpp"


#define CIRCLE_SIGN "o"
#define CROSS_SIGN "x"
#define EMPTY_SIGN "."


namespace sanmoku
{
    std::string toSign(Color color);

    class Board : public core::BoardCore
    {
    public:
        Board();

        Board(const Board& org);

        virtual ~Board();

        void printBoard();
    };

}


#endif //SANMOKU_BOARD_HPP
