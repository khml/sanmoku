/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "History.hpp"

History::History () { }

History::History (const History& orig) : hisotorySize(orig.hisotorySize)
{
  for (int i=0; i<hisotorySize; i++)
    {
      hisotoryArray[i] = orig.fetchPos (i);
    }
}

History::~History () { }

void History::put (const Position pos)
{
  hisotoryArray[hisotorySize++] = pos;
}

void History::put (const int color, const int pos)
{
  Position position = Position (color, pos);
  put (position);
}

int History::size () const
{
  return hisotorySize;
}

Position History::fetchPos (int index) const
{
  return hisotoryArray[index];
}
