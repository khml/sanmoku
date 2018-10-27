/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include "Board.hpp"

#define CYCLE_SUM CYCLE *3
#define CROSS_SUM CROSS *3
#define CYCLE_SIGN "o"
#define CROSS_SIGN "x"
#define EMPTY_SIGN "."

Board::Board () { }

Board::Board (const Board& orig) { }

Board::~Board () { }

void Board::printBoard ()
{
  int id;
  std::string sign;

  for (int pos = 0; pos < BOARD_SIZE; pos++)
    {
      id = board[pos];
      if (id == EMPTY)
        sign = EMPTY_SIGN;
      else if (id == CYCLE)
        sign = CYCLE_SIGN;
      else if (id == CROSS)
        sign = CROSS_SIGN;
      else
        {
          std::cerr << "id error" << std::endl;
          break;
        }
      std::cerr << sign << ", ";

      if ((pos + 1) % 3 == 0)
        std::cerr << std::endl;
    }
  std::cerr << std::endl;
}

int Board::isAny (int pos, int id)
{
  if (board[pos] == id)
    return 1;
  return 0;
}

int Board::isEmpty (int pos)
{
  return isAny (pos, EMPTY);
}

int Board::isCross (int pos)
{
  return isAny (pos, CROSS);
}

int Board::isCycle (int pos)
{
  return isAny (pos, CYCLE);
}

int Board::isLegal (int pos)
{
  if (isEmpty (pos))
    return 1;
  return 0;
}

int Board::isFinished ()
{
  return finishedFlag;
}

int Board::put (int pos, int color)
{
  if (finishedFlag)
    return 0;

  if (!isLegal (pos))
    return 0;

  board[pos] = color;
  checkFinishedOrNot ();
  return 1;
}

int Board::put (int pos, string color)
{
  int color_id;
  if (color == CYCLE_SIGN)
    color_id = CYCLE;
  else if (color == CROSS_SIGN)
    color_id = CROSS;
  else
    {
      std::cerr << "no exist such a color : " << color << std::endl;
      return 0;
    }

  return put (pos, color_id);
}

int Board::isFull ()
{
  for (int i=0; i < BOARD_SIZE; i++)
    {
      if (board[i] == EMPTY)
        return 0;
    }
  return 1;
}

void Board::checkFinishedOrNot ()
{
  int i, j, sum;
  for (i = 0; i < CHECK_ID_ARRAY_SIZE; i++)
    {
      sum = 0;
      for (j = 0; j < CHECK_ID_ARRAY_SIDE_SIZE; j++)
        {
          sum += board[checkIdArray[i][j]];
        }
      //std::cerr << i << ": " << sum << std::endl;
      if ((sum == CYCLE_SUM) || (sum == CROSS_SUM))
        {
          finishedFlag = 1;
          break;
        }
    }
  if (isFull ())
    finishedFlag = 1;
}
