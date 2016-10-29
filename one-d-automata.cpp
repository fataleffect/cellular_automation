#include "automata.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

Automata::Automata()
{
  currentGen = 1;
  cellLimit = 80;
  genLimit = 0;
  rule[0] = 0;
  rule[1] = 1;
  rule[2] = 1;
  rule[3] = 1;
  rule[4] = 1;
  rule[5] = 0;
  rule[6] = 0;
  rule[7] = 0;
    
  while(cells.size() < cellLimit)
    {
      cells.push_back(rand()%2);
    }
}

Automata::Automata(vector<bool> newCells, unsigned int newCellLimit)
{
  currentGen = 1;
  cellLimit = newCellLimit;
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
  for(string::iterator it = stringRule.end(); it != stringRule.begin(); it--)
    {
      rule[distance(stringRule.begin(), it)] = *it != '0';
    }
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
  //cout << "Prev: "<< prev <<"Curr: " << curr <<"Next: "<< next << " Rule is: " << concat.str()<< " Rule Index is: " << ruleToApply << " Rule Value is: " << rule[ruleToApply] << endl;
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
      if(it == cells.begin())
	{
	  prev = cells.back();
	}
      else
	{
	  prev = *(it-1);	  
	}
      
      curr = *it;
      
      //wrap the last cell's next neighbour to the first in the vector
      if(it != cells.end()-1)
	{
	  next = *(it+1);
	}
      else
	{
	next = *cells.begin();
	}
      //Push the result of applyRule to the back of our vector.
      newGen.push_back(applyRule(prev, curr, next));
    }
    //our new generation then becomes the current generation.
  cells = newGen; 
  currentGen++;

  //print the stuff
  for (vector<bool>::iterator it = cells.begin(); it != cells.end(); it++)
    {
      //█ is 1, ░ is 0
      string s = *it?"█":"░";
      cout << s << ' ';
    }
  cout << endl;
}

void Automata::setGenLimit(unsigned int newGenLimit)
{
  genLimit = newGenLimit;
}

void Automata::setCellLimit(unsigned int newCellLimit)
{
  cellLimit = newCellLimit;
}

void Automata::startTime()
{
  while (currentGen != genLimit)
    {
      chrono::milliseconds timespan(500);
      step();
      this_thread::sleep_for(timespan);
    }
}

void Automata::reset()
{
  cellLimit = initCellLimit;
  genLimit = initGenLimit;
  cells = initCells; 
}

void Automata::menu()
{
	int selection;
	do 
	{
		cout << "\033[2J\033[1;1H";
		cout << "========================================\n";
		cout << "WELCOME TO THE CELLULAR AUTOMATA PROGRAM\n";
		cout << "========================================\n";
		cout << "\n";
		cout << "Please chooose a menu option:\n";
		cout << "1 - Start the cellular automata\n";
		cout << "2 - Convert a binary value to a decimal number\n";
		cout << "3 - Load a cellular automata from a save file\n";
		cout << "0 - Quit\n";
		cout << "\n";
		cout << "========================================\n";
		cin >> selection;
		switch (selection) 
		{
			case 1:
			startTime();
			cout << "\n";
			cout << "Please press Enter to continue.\n";
			cin.ignore();
			break;

			case 2:
			cout << "\n";
			cout << "Please press Enter to continue.\n";
			cin.ignore();
			break;

			case 3:
			cout << "\n";
			cout << "Please press Enter to continue.\n";
			cin.ignore();
			break;

			case 0:
			cout << "Goodbye!\n";
			cin.ignore();
			break;

			default:
			cout << selection << "is not a valid menu selection!\n";
		}
	} while (selection != 0);

} 

Automata::~Automata()
{
  
}

int main()
{
  Automata autom = Automata();

  autom.menu();
}

