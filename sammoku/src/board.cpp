//
// Created by KHML  on 2019-09-15.
//

#include <iostream>
#include <string>

#include <sammoku/board.hpp>

namespace sanmoku
{
    std::string toSign(const Color color)
    {
        if (color == Empty)
            return EMPTY_SIGN;
        else if (color == Cross)
            return CROSS_SIGN;
        else if (color == Circle)
            return CIRCLE_SIGN;
        else
            return "";
    }

    Board::Board()
    {
        clear();
    }

    Board::Board(const Board& orig)
    = default;

    Board::~Board()
    = default;

    void Board::printBoard() const
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            std::cerr << toSign(board[i]) << ", ";

            if ((i + 1) % BOARD_LENGTH == 0)
                std::cerr << std::endl;
        }
        std::cerr << std::endl;
    }

}

