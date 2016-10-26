#include "automata.h"
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std;

Automata::Automata()
{
  
}

Automata::Automata(vector<bool> newCells, unsigned int newCellLimit)
{
  cells = newCells;
}

//Sets the binary rule for future generations of the automaton.
void Automata::setRule(unsigned int newRule)
{
  //Convert to a string
  string stringRule = to_string(newRule);

  //Left pad to 8 bits.
  while (stringRule.length() < 8)
    {
      stringRule.insert(0, "0");
    }

  //remove extra bits
  while (stringRule.length() > 8)
    {
      stringRule.pop_back();
    }

  //reverse the rule for use with applyRule.
  reverse(stringRule.begin(), stringRule.end());

  //store the reversed rule.
  rule = stringRule;
}

void Automata::seedCells(vector<bool> newCells)
{
  cells = newCells;
}

//Applies the rule to the current cells and its neighbours
bool Automata::applyRule(bool prev, bool curr, bool next)
{
  //concatenate the three booleans to get rule they represent.
  stringstream concat;
  concat << prev << curr << next;

  //the decimal value of the concatenated booleans is equal to their index in the rule.
  unsigned int ruleToApply = stoul(concat.str(), NULL, 2);

  //The value at the index of the rule array will become the state of the child cell
  return rule[ruleToApply];
}
 
void Automata::step(){
  vector<bool> newGen;
  //iterate from the beginning until the end of our vector.
  for(vector<bool>::iterator it = cells.begin(); it !=cells.end(); it++)
    {
      bool prev, curr, next;

      //wrap the first cell's previous neighbour to the last item in the vector
      if(it != cells.begin())
	prev = *it-1;
      else
	prev = *cells.end();
      
      curr = *it;
      
      //wrap the last cell's next neighbour to the first in the vector
      if(it != cells.end())
	next = *it+1;
      else
	next = *cells.begin();

      //Push the result of applyRule to the back of our vector.
      newGen.push_back(applyRule(prev, curr, next)); 
    }

  //our new generation then becomes the current generation.
  cells = newGen;
}

Automata::setGenLimit(unsigned int newGenLimit)
{
  genlimit = newGenLimit;
}

Automata::setCellLimit(unsigned int newCellLimit)
{
  cellLimit = newCellLimit;
}

Automata::reset()
{
  cellLimit = initCellLimit;
  genLimit = initGenLimit;
  cells = initCells; 
}

Automata::~Automata()
{
  
}

int main()
{
  Automata autom = Automata();
}

