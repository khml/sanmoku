//
// Created by KHML on 2020/07/31.
//

#ifndef SANMOKU_PY_BOARD_HPP
#define SANMOKU_PY_BOARD_HPP

#include <vector>

#include <sammoku/core/board_core.hpp>

class PyBoard : public sanmoku::core::BoardCore
{
public:
    PyBoard();

    ~PyBoard() override;

    std::vector<int> getBoard();
};

#endif //SANMOKU_PY_BOARD_HPP
