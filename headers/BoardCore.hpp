//
// Created by KHML on 2019-09-13.
//

#ifndef SANMOKU_BOARDCORE_HPP
#define SANMOKU_BOARDCORE_HPP

#include "BoardConfig.hpp"

namespace sanmoku
{
    Color turnColor(Color color);

    namespace core
    {
        class BoardCore
        {
        public:
            BoardCore();

            BoardCore(const BoardCore& orig);

            virtual ~BoardCore();

            void clear();

            bool put(Move move);

            bool isLegal(Move move);

            bool isFinished();

            Color result()
            { return gameResult; };

        protected:
            Color board[BOARD_SIZE] = {
                    Empty, Empty, Empty,
                    Empty, Empty, Empty,
                    Empty, Empty, Empty
            };

            bool isEmpty(int pos);

            bool isCycle(int pos);

            bool isCross(int pos);

            bool isFull();

            void checkFinishedOrNot();

        private:

            Color gameResult = Empty;


            /* Array for checking game is finish or not
             *
             * 0 1 2
             * 3 4 5
             * 6 7 8
             */
            const int checkIdArray[CHECK_ID_ARRAY_SIZE][CHECK_ID_ARRAY_SIDE_SIZE] =
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

            bool finishedFlag = false;

            bool isAny(int pos, Color color);

        };
    }
}


#endif //SANMOKU_BOARDCORE_HPP
