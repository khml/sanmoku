//
// Created by KHML on 2019-09-13.
//

#ifndef SANMOKU_BOARD_CORE_HPP
#define SANMOKU_BOARD_CORE_HPP

#include <sammoku/core/config.hpp>

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

            bool isLegal(Move move) const;

            bool isFinished() const;

            Color result() const;

        protected:
            Color board[BOARD_SIZE] = {
                Empty, Empty, Empty,
                Empty, Empty, Empty,
                Empty, Empty, Empty
            };

            bool isEmpty(int pos) const;

            bool isCycle(int pos) const;

            bool isCross(int pos) const;

            bool isFull() const;

            void checkFinishedOrNot();

        private:

            Color gameResult = Empty;
            bool finishedFlag = false;

            bool isAny(int pos, Color color) const;

        };
    }
}

#endif //SANMOKU_BOARD_CORE_HPP
