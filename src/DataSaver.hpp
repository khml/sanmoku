/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef DATASAVER_HPP
#define DATASAVER_HPP

#include "History.hpp"
#include "Board.hpp"

class DataSaver
{
public:
  DataSaver ();
  DataSaver (const DataSaver& orig);
  virtual ~DataSaver ();
  void save (History history, int result);
private:
  Board board;
  int isWinner(Position pos, int result);
};

#endif /* DATASAVER_HPP */

