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

void playMode ()
{
  Board board;

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
        pos = stoi(cmd.substr(1, 1));
        strColor = cmd.substr(0, 1);

        if (strColor == CYCLE_SYMBOL)
            color = sanmoku::Cycle;
        else if (strColor == CROSS_SYMBOL)
            color = sanmoku::Cross;
        else
        {
            cerr << "Illegal color" << endl;
            continue;
        }

        if (board.put(sanmoku::Move(color, pos)))
            board.printBoard();
        else
            cerr << "Ilegal move" << endl;

        if (board.isFinished())
        {
            printResult(board);
            break;
        }
    }
}

void selfMode ()
{
  Board board;
  Player player;

  while (true)
    {
      player.play (board);
      board.printBoard ();
      if (board.isFinished ())
        {
            printResult(board);
          break;
        }
    }
  player.train(board);
}

void selectMode (string mode)
{
  if (mode == "play")
    playMode ();
  else if (mode == "self")
    selfMode ();
  else
    cerr << "no exist such a mode : " << mode;

}

int main (int argc, char** argv)
{
  string mode;
  if (argc > 2)
    {
      cerr << "too many args" << endl;
      exit (0);
    }

  if (argc == 2)
    mode = argv[1];

  if (argc == 1)
    {
      cerr << "choice mode (self or play) = ";
      cin >> mode;
    }

  selectMode (mode);

  return 0;
}

