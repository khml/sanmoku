//
// Created by KHML on 2020/07/31.
//

#include <sammoku/core/config.hpp>
#include <py_board.hpp>

PyBoard::PyBoard()
= default;

PyBoard::~PyBoard()
= default;

std::vector<int> PyBoard::getBoard()
{
    std::vector<int> boardData;
    boardData.reserve(sanmoku::BOARD_SIZE);
    for(const sanmoku::Color color : board)
        boardData.emplace_back((int)color);
    return boardData;
}
