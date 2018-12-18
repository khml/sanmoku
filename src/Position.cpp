/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Position.hpp"

Position::Position () { }

Position::Position (int color, int pos) : colorValue(color), positionValue(pos) {}

Position::Position (const Position& orig) : colorValue(orig.colorValue), positionValue(orig.positionValue) { }

Position::~Position () { }

int Position::color ()
{
  return colorValue;
}

int Position::position ()
{
  return positionValue;
}

