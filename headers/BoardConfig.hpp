//
// Created by KHML on 2019/12/29.
//

#ifndef SANMOKU_BOARDCONFIG_HPP
#define SANMOKU_BOARDCONFIG_HPP

namespace sanmoku
{
    const unsigned int BOARD_SIZE = 9;
    const unsigned int BOARD_LENGTH = 3;
    const unsigned int CHECK_ID_ARRAY_SIZE = 8;
    const unsigned int CHECK_ID_ARRAY_SIDE_SIZE = 3;

    enum Color
    {
        Empty = 0,
        Circle = -1,
        Cross = 1,
        OutOfRange = 2,
    };

    struct Move
    {
        Move(Color color, int pos) : color(color), pos(pos)
        {};
        const Color color;
        const int pos;
    };
}

#endif //SANMOKU_BOARDCONFIG_HPP
