/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include "Board.hpp"

#define CYCLE_SIGN "o"
#define CROSS_SIGN "x"
#define EMPTY_SIGN "."

namespace sanmoku
{
    Board::Board () { }

    Board::Board (const Board& orig) { }

    Board::~Board () { }

    void Board::printBoard ()
    {
        int id;
        std::string sign;

        for (int pos = 0; pos < BOARD_SIZE; pos++)
        {
            id = board[pos];
            if (id == Empty)
                sign = EMPTY_SIGN;
            else if (id == Cycle)
                sign = CYCLE_SIGN;
            else if (id == Cross)
                sign = CROSS_SIGN;
            else
            {
                std::cerr << "id error" << std::endl;
                break;
            }
            std::cerr << sign << ", ";

            if ((pos + 1) % 3 == 0)
                std::cerr << std::endl;
        }
        std::cerr << std::endl;
    }


    bool Board::isAny(int pos, sanmoku::Color color)
    {
        return board[pos] == color;
    }

    bool Board::isEmpty (const int pos)
    {
        return isAny (pos, Empty);
    }

    bool Board::isCross (const int pos)
    {
        return isAny (pos, Cross);
    }

    bool Board::isCycle (const int pos)
    {
        return isAny (pos, Cycle);
    }

    bool Board::isLegal (const Move move)
    {
        return isEmpty (move.pos);
    }

    bool Board::isFinished ()
    {
        return finishedFlag;
    }

    bool Board::put (const Move move)
    {
        if (finishedFlag)
            return false;

        if (!isLegal (move))
            return false;

        board[move.pos] = move.color;
        checkFinishedOrNot ();
        return true;
    }

    bool Board::isFull ()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (isEmpty(i))
                return false;
        }
        return true;
    }

    void Board::checkFinishedOrNot ()
    {
        int cycleSum = 3 * (int) Cycle;
        int crossSum = 3 * (int) Cross;
        int i, j, sum;
        for (i = 0; i < CHECK_ID_ARRAY_SIZE; i++)
        {
            sum = 0;
            for (j = 0; j < CHECK_ID_ARRAY_SIDE_SIZE; j++)
            {
                sum += board[checkIdArray[i][j]];
            }

            if ((sum == cycleSum) || (sum == crossSum))
            {
                finishedFlag = true;
                result = (sum == cycleSum ? Cycle : Cross);
                break;
            }
        }
        if (isFull ())
        {
            result = Empty;
            finishedFlag = true;
        }
    }
}
