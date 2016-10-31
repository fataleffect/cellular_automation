#ifndef _CONWAY
#define _CONWAY
#include "automata.h"

class Conway : Automata
{
 private:
  vector<vector<bool>> cells;
  vector<vector<bool>> initCells;
 public:
  Conway();
  Conway(vector<vector<bool>> newCells, unsigned int newCellLimit, unsigned int newGenLimit);
  void seedCells(vector<vector<bool>> newCells);
}
#endif
