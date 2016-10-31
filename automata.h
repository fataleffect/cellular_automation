#ifndef _AUTOMATA
#define _AUTOMATA

#include<vector>
#include<string>

using namespace std;

//The class containing the one dimensional automata
class Automata
{
 private:
  unsigned int currentGen;
  unsigned int cellLimit;
  unsigned int genLimit;
  unsigned int ruleSet;
  vector<bool> cells;
  unsigned int initCellLimit;
  unsigned int initGenLimit;
  vector<bool> initCells;
  bool rule[8];
  bool initRule[8];
 
  //applies the rule to the current cell using its neigbours
  bool applyRule(bool prev, bool curr, bool next); 

  //generates the next generation of cells.
  void step();
  
 public:
  Automata();
  Automata(vector<bool> newCells, unsigned int newCellLimit, unsigned int newGenLimit);
  void setRule(string rule);
  void seedCells(vector<bool> newCells);
  void setCellLimit(unsigned int newCellLimit);
  void setGenLimit(unsigned int newGenLimit);
  void startTime();
  void stopTime();
  void menu();
  void initialise();
  void createRuleSet();
  void convertBinary();
  void reset();
  ~Automata();  
};
#endif
