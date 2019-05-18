/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>

#define BOARD_SIZE 9
#define CHECK_ID_ARRAY_SIZE 8
#define CHECK_ID_ARRAY_SIDE_SIZE 3

using std::string;

namespace sanmoku
{
    enum Color
    {
        Empty = 0,
        Cycle = -1,
        Cross = 1,
        OutOfRange = 2,
    };

    Color turnColor(Color color);

    struct Move
    {
        Move(Color color, int pos) : color(color), pos(pos)
        {};
        const Color color;
        const int pos;
    };

    template<typename T>
    class MoveHistory
    {
    public:
        MoveHistory();

        MoveHistory(const MoveHistory &orig);

        virtual ~MoveHistory();

        void add(std::vector<T> board, Move move);

        void clear();

        std::vector<std::tuple<std::vector<T>, Move>> data(Color color);

    protected:
        std::vector<std::vector<T>> boards;
        std::vector<Move> moves;
    };

    class Board
    {
    public:
        Board();

        Board(const Board &orig);

        virtual ~Board();

        void clear();

        bool put(Move move);

        bool isLegal(Move move);

        bool isFinished();

        void printBoard();

        Color result = Empty;
        MoveHistory<float> history;

        std::vector<float> getBoard();

    private:
        Color board[BOARD_SIZE] = {
                Empty, Empty, Empty,
                Empty, Empty, Empty,
                Empty, Empty, Empty
        };

        /* Array for checking game is finish or not
         *
         * 0 1 2
         * 3 4 5
         * 6 7 8
         */
        int checkIdArray[CHECK_ID_ARRAY_SIZE][CHECK_ID_ARRAY_SIZE] =
                {
                        {0, 1, 2},
                        {3, 4, 5},
                        {6, 7, 8}, //rows
                        {0, 3, 6},
                        {1, 4, 7},
                        {2, 5, 8}, //columns
                        {0, 4, 8},
                        {2, 4, 6} // diagonal
                };
        bool finishedFlag = false;

        void checkFinishedOrNot();

        bool isAny(int pos, Color color);

        bool isEmpty(int pos);

        bool isCycle(int pos);

        bool isCross(int pos);

        bool isFull();
    };
}


#endif /* BOARD_HPP */

