#ifndef _AUTOMATA
#define _AUTOMATA

#include<vector>
#include<string>

using namespace std;

//The class containing the one dimensional automata
class Automata
{
 private:
  unsigned int cellLimit;
  unsigned int genLimit;
  vector<bool> cells;
  unsigned int initCellLimit;
  unsigned int initGenLimit;
  vector<bool> initialCells;
  string rule;
  string initRule;
  
  //applies the rule to the current cell using its neigbours
  bool applyRule(bool prev, bool curr, bool next); 

  //generates the next generation of cells.
  void step();
  
 public:
  Automata();
  Automata(vector<bool> newCells, unsigned int newCellLimit);
  void setRule(unsigned int rule);
  void seedCells(vector<bool> newCells);
  void setGenLimit(unsigned int newGenLimit);
  void reset();
  ~Automata();  
};
#endif
