/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include "Board.hpp"
#include "Player.hpp"

using std::cerr;
using std::cin;
using std::endl;
using std::string;

using sanmoku::Board;
using sanmoku::Player;

#define CYCLE_SYMBOL "o"
#define CROSS_SYMBOL "x"

#define MODEL_NAME "model.pt"

/*
 * 
 */

void printResult(Board &board)
{
    string result;
    if (board.result == sanmoku::Empty)
        result = "Draw";
    else
    {
        result = board.result == sanmoku::Cycle ? CYCLE_SYMBOL : CROSS_SYMBOL;
    }
    cerr << "game finished! result : " << result << endl;
}

sanmoku::Color stringToColor(string strColor)
{
    sanmoku::Color color;
    if (strColor == CYCLE_SYMBOL)
        color = sanmoku::Cycle;
    else if (strColor == CROSS_SYMBOL)
        color = sanmoku::Cross;
    else
        color = sanmoku::OutOfRange;
    return color;
}

void play(int argc, char **argv)
{
    string modelPath;
    if (argc == 3)
        modelPath = argv[2];
    else
        modelPath = MODEL_NAME;

    Board board;
    Player player;
    player.loadModel(modelPath);

    cerr << "Pos index" << endl;
    cerr << "0 1 2" << endl << "3 4 5" << endl << "6 7 8" << endl;

    cerr << "color(o or x),pos (e.g. o3)" << endl << endl;

    string cmd, strColor;
    sanmoku::Color color;
    int pos;
    while (true)
    {
        cerr << "input = ";
        cin >> cmd;

        if (cmd.substr(0, 3) == "gen")
        {
            strColor = cmd.substr(3, 1);
            pos = -1;
        } else
        {
            strColor = cmd.substr(0, 1);
            pos = stoi(cmd.substr(1, 1));
        }

        color = stringToColor(strColor);
        if (color == sanmoku::OutOfRange)
        {
            cerr << "Illegal color" << endl;
            continue;
        }

        if (pos >= 0)
        {
            if (board.put(sanmoku::Move(color, pos)))
                board.printBoard();
            else
                cerr << "Ilegal move" << endl;
        } else
        {
            player.toPlayColor = color;
            if (player.play(board))
                board.printBoard();
            else
                cerr << "Ilegal move" << endl;
        }

        if (board.isFinished())
        {
            printResult(board);
            break;
        }
    }
}

void train(int argc, char **argv)
{
    int trainingTimes;
    string modelPath;
    if (argc < 3)
    {
        cerr << "required more args" << endl;
        cerr << "./sanmoku train TrainingTimes(required) modelPath(option)" << endl;
        exit(0);
    }

    try
    {
        trainingTimes = std::stoi(argv[2]);
    }
    catch (const char *errMsg)
    {
        cerr << errMsg << endl;
        exit(0);
    }

    if (argc == 4)
        modelPath = argv[3];
    else
        modelPath = MODEL_NAME;

    Board board;
    Player player;
    player.loadModel(modelPath);

    for (int i = 0; i < trainingTimes; i++)
    {
        board.clear();
        while (true)
        {
            player.play(board);
            board.printBoard();
            if (board.isFinished())
            {
                printResult(board);
                break;
            }
        }
        player.train(board);
    }
    player.saveModel(modelPath);
}

int main(int argc, char **argv)
{
    string mode;

    if (argc < 2)
    {
        cerr << "please select mode. train or play" << endl;
        cerr << "./sanmoku train TrainingTimes(required) modelPath(option)" << endl;
        cerr << "./sanmoku play modelPath(option)" << endl;
        exit(0);
    }

    mode = argv[1];

    if (mode == "train")
        train(argc, argv);
    else if (mode == "play")
        play(argc, argv);
    else
    {
        cerr << "not exist such a mode " << mode << endl;
        exit(0);
    }

    return 0;
}

