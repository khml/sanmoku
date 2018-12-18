/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

#include "History.hpp"

#define BOARD_SIZE 9
#define EMPTY 0
#define CYCLE -1
#define CROSS 1 
#define CHECK_ID_ARRAY_SIZE 8
#define CHECK_ID_ARRAY_SIDE_SIZE 3

#define NONE_RESULT 0
#define DRAW 0
#define CYCLE_WIN CYCLE
#define CROSS_WIN CROSS

using std::string;

class Board
{
public:
  Board ();
  Board (const Board& orig);
  virtual ~Board ();
  int put (const int pos, const int color);
  int put (const int pos, const string color);
  int isLegal (const int pos);
  int isFinished ();
  void printBoard ();
  int result = NONE_RESULT;
  History history;
private:
  int board[BOARD_SIZE] ={
    EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY,
    EMPTY, EMPTY, EMPTY
  };
  
  /*
   * 0 1 2
   * 3 4 5
   * 6 7 8
   */
  int checkIdArray[CHECK_ID_ARRAY_SIZE][CHECK_ID_ARRAY_SIZE] =
  {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, //rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, //columns
    {0, 4, 8}, {2, 4, 6} // diagonal
  };
  int finishedFlag = 0;
  void checkFinishedOrNot();
  int isAny (const int pos, const int id);
  int isEmpty (const int pos);
  int isCycle (const int pos);
  int isCross (const int pos);
  int isFull();
};

#endif /* BOARD_HPP */

