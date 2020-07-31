//
// Created by KHML on 2019-09-13.
//

#include <sammoku/core/board_core.hpp>

namespace sanmoku
{
    Color turnColor(Color color)
    {
        return color == Circle ? Circle : Cross;
    }

    namespace core
    {
        /* Array for checking game is finish or not
         *
         * 0 1 2
         * 3 4 5
         * 6 7 8
         */
        constexpr int checkIdArray[CHECK_ID_ARRAY_SIZE][CHECK_ID_ARRAY_SIDE_SIZE] =
            {
                {0, 1, 2}, //rows
                {3, 4, 5}, //rows
                {6, 7, 8}, //rows
                {0, 3, 6}, //columns
                {1, 4, 7}, //columns
                {2, 5, 8}, //columns
                {0, 4, 8}, // diagonal
                {2, 4, 6}, // diagonal
            };

        BoardCore::BoardCore()
        {
            clear();
        }

        BoardCore::BoardCore(const BoardCore& orig) :gameResult(orig.gameResult), finishedFlag(orig.finishedFlag)
        {
            int idx = 0;
            for (const Color& color: orig.board)
            {
                board[idx++] = color;
            }
        }

        BoardCore::~BoardCore()
        = default;

        void BoardCore::clear()
        {
            finishedFlag = false;
            gameResult = Empty;
            for (sanmoku::Color& elem : board)
                elem = Empty;
        }

        bool BoardCore::isAny(int pos, sanmoku::Color color) const
        {
            return board[pos] == color;
        }

        bool BoardCore::isEmpty(const int pos) const
        {
            return isAny(pos, Empty);
        }

        bool BoardCore::isCross(const int pos) const
        {
            return isAny(pos, Cross);
        }

        bool BoardCore::isCycle(const int pos) const
        {
            return isAny(pos, Circle);
        }

        bool BoardCore::isLegal(const Move move) const
        {
            return isEmpty(move.pos);
        }

        bool BoardCore::isFinished() const
        {
            return finishedFlag;
        }

        Color BoardCore::result() const
        {
            return gameResult;
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

        bool BoardCore::isFull() const
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