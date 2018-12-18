/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <fstream>
#include <string>

#include "DataSaver.hpp"

using std::string;
using std::to_string;

DataSaver::DataSaver () { }

DataSaver::DataSaver (const DataSaver& orig) { }

DataSaver::~DataSaver () { }

int DataSaver::isWinner (Position pos, int result)
{
  if (pos.color () == result)
    return 1;
  return 0;
}

void DataSaver::save (History history, int result)
{
  std::ofstream fileStream ("result.txt", std::ios::app);
  Position position;
  string resultData = "result:" + to_string (result) + ":";
  string boardString, policy, data;

  int historySize = history.size ();
  for (int i = 0; i < historySize; i++)
    {
      position = history.fetchPos (i);
      if (isWinner (position, result))
        {
          boardString = "board:" + board.asString () + ":";
          policy = "policy:" + std::to_string (position.position ()) + ":";
          fileStream << resultData << policy << boardString << std::endl;
        }
      board.put (position.position (), position.color ());
    }
}
