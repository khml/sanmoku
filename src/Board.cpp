//
// Created by KHML  on 2019-09-15.
//

#include <iostream>
#include <string>

#include "Board.hpp"

#define CIRCLE_SIGN "o"
#define CROSS_SIGN "x"
#define EMPTY_SIGN "."

using std::cerr;
using std::endl;
using std::string;

namespace sanmoku
{

    string toSign(Color color)
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
    {}

    Board::~Board()
    {}

    void Board::printBoard()
    {
        for(int i=0; i < BOARD_SIZE; i++)
        {
            cerr << toSign(board[i]) << ", ";

            if ((i + 1) % BOARD_LENGTH == 0)
                cerr << endl;
        }
        cerr << endl;
    }

}

