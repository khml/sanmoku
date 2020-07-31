//
// Created by KHML on 2019-09-13.
//

#include <sammoku/board_core.hpp>

namespace sanmoku
{
    Color turnColor(Color color)
    {
        return color == Circle ? Circle : Cross;
    }

    namespace core
    {
        BoardCore::BoardCore()
        {
            clear();
        }

        BoardCore::BoardCore(const BoardCore& orig)
        {}

        BoardCore::~BoardCore()
        {}

        void BoardCore::clear()
        {
            finishedFlag = false;
            gameResult = Empty;
            for (int i = 0; i < BOARD_SIZE; i++)
                board[i] = Empty;
        }

        bool BoardCore::isAny(int pos, sanmoku::Color color)
        {
            return board[pos] == color;
        }

        bool BoardCore::isEmpty(const int pos)
        {
            return isAny(pos, Empty);
        }

        bool BoardCore::isCross(const int pos)
        {
            return isAny(pos, Cross);
        }

        bool BoardCore::isCycle(const int pos)
        {
            return isAny(pos, Circle);
        }

        bool BoardCore::isLegal(const Move move)
        {
            return isEmpty(move.pos);
        }

        bool BoardCore::isFinished()
        {
            return finishedFlag;
        }

        bool BoardCore::put(const Move move)
        {
            if (finishedFlag)
                return false;

            if (!isLegal(move))
                return false;

            board[move.pos] = move.color;
            checkFinishedOrNot();
            return true;
        }

        bool BoardCore::isFull()
        {
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                if (isEmpty(i))
                    return false;
            }
            return true;
        }

        void BoardCore::checkFinishedOrNot()
        {
            int cycleSum = 3 * (int) Circle;
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
                    gameResult = (sum == cycleSum ? Circle : Cross);
                    return;
                }
            }
            if (isFull())
            {
                gameResult = Empty;
                finishedFlag = true;
            }
        }

    }

}