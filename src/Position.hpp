/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef POSITION_HPP
#define POSITION_HPP

class Position
{
public:
  Position ();
  Position (int color, int pos);
  Position (const Position& orig);
  virtual ~Position ();
  int color();
  int position();
private:
  int colorValue = 0;
  int positionValue = -1;

};

#endif /* POSITION_HPP */

