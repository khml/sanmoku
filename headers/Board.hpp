//
// Created by KHML on 2019-09-15.
//

#ifndef SANMOKU_BOARD_HPP
#define SANMOKU_BOARD_HPP

#include "BoardCore.hpp"


namespace sanmoku
{
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
