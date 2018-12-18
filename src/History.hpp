/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef HISTORY_HPP
#define HISTORY_HPP

#include "Position.hpp"

#define HISTORY_SIZE 9

class History
{
public:
  History ();
  History (const History& orig);
  virtual ~History ();
  void put (const Position pos);
  void put (const int color, const int pos);
  int size () const;
  Position fetchPos(int index);
private:
  int hisotorySize = 0;
  Position hisotoryArray[HISTORY_SIZE];

};

#endif /* HISTORY_HPP */

