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

#define CYCLE_SYMBOL "o"
#define CROSS_SYMBOL "x"

/*
 * 
 */

void playMode ()
{
  Board board;

  cerr << "Pos index" << endl;
  cerr << "0 1 2" << endl << "3 4 5" << endl << "6 7 8" << endl;

  cerr << "color(o or x),pos (e.g. o3)" << endl << endl;

  string cmd, color;
  int pos;
  while (true)
    {
      cerr << "input = ";
      cin >> cmd;
      pos = stoi (cmd.substr (1, 1));
      color = cmd.substr (0, 1);

      if (board.put (pos, color))
        board.printBoard ();
      else
        cerr << "Ilegal move" << endl;

      if (board.isFinished ())
        {
          cerr << "game finished" << endl;
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
        break;
    }
}

int main (int argc, char** argv)
{
  string cmd;
  cerr << "choice mode (self or play) = ";
  cin >> cmd;
  if (cmd == "play")
    playMode ();
  else if (cmd == "self")
    selfMode ();
  else
    cerr << "no exist such a mode : " << cmd;

  return 0;
}

