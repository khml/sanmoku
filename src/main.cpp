//
// Created by KHML on 2019-09-13.
//

#include <iostream>
#include <string>

#include <Board.hpp>

using sanmoku::Board;

sanmoku::Color stringToColor(const std::string& strColor)
{
    sanmoku::Color color;
    if (strColor == CIRCLE_SIGN)
        color = sanmoku::Circle;
    else if (strColor == CROSS_SIGN)
        color = sanmoku::Cross;
    else
        color = sanmoku::OutOfRange;
    return color;
}

void play()
{
    Board board;

    std::cerr << "color(o or x),pos (e.g. o3)" << std::endl << std::endl;

    std::string cmd, strColor;
    sanmoku::Color color;
    int pos;
    while (true)
    {
        std::cerr << "input = ";
        std::cin >> cmd;

        if (cmd.length() == 1)
        {
            if (cmd == "p")
            {
                board.printBoard();
                continue;
            }
        }

        strColor = cmd.substr(0, 1);
        pos = stoi(cmd.substr(1, 1));

        color = stringToColor(strColor);
        if (color == sanmoku::OutOfRange)
        {
            std::cerr << "Illegal color" << std::endl;
            continue;
        }

        if (pos >= 0)
        {
            if (board.put(sanmoku::Move(color, pos)))
                board.printBoard();
            else
                std::cerr << "Ilegal move" << std::endl;
        }

        if (board.isFinished())
        {
            std::cerr << "Win : " << sanmoku::toSign(board.result()) << std::endl;
            break;
        }
    }
}

int main()
{
    play();
    return 0;
}
