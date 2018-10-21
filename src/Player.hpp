/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <random>
#include "Board.hpp"

class Player
{
public:
  Player ();
  Player (const Player& orig);
  virtual ~Player ();
  int toPlayColor = CROSS;
  int play (Board& board);
private:
  std::random_device rand;
  int getRandomPos ();

};

#endif /* PLAYER_HPP */

