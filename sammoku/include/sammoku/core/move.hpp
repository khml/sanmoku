//
// Created by KHML on 2020/07/31.
//

#ifndef SANMOKU_MOVE_HPP
#define SANMOKU_MOVE_HPP

#include <sammoku/core/color.hpp>

namespace sanmoku
{
    struct Move
    {
        Move(Color color, int pos);
        const Color color;
        const int pos;
    };
}

#endif //SANMOKU_MOVE_HPP
