#include "automata.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <bitset>

using namespace std;

Automata::Automata()
{
  currentGen = 0;
  cellLimit = 40;
  genLimit = 0;
  ruleSet = 0;
  rule[0] = 0;
  rule[1] = 1;
  rule[2] = 1;
  rule[3] = 1;
  rule[4] = 1;
  rule[5] = 0;
  rule[6] = 0;
  rule[7] = 0;

  //While the vector is smaller than the cell limit 
  while(cells.size() < (cellLimit/2))
    {
      cells.push_back(0);
      //cells.push_back(rand()%2);
    }

  cells.push_back(1);
  
  while(cells.size() < cellLimit)
    {
      cells.push_back(0);
      //cells.push_back(rand()%2);
    }
  
  initCellLimit = 80;
  initGenLimit = 0;
  initCells = cells;
}

Automata::Automata(vector<bool> newCells, unsigned int newCellLimit, unsigned int newGenLimit)
{
  currentGen = 1;

  initCellLimit = newCellLimit;
  initGenLimit = newGenLimit;
  initCells = newCells;

  cellLimit = newCellLimit;
  genLimit = newGenLimit;
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
  //if this is the first time we called start time print the first generation
  if(currentGen == 1)
    {
      for (vector<bool>::iterator it = cells.begin(); it != cells.end(); it++)
	{
	  //█ is 1, ░ is 0
	  string s = *it?"█":"░";
	  cout << s << ' ';
	}
      cout << endl;
    }
  
  //if the genlimit is 0 run forever, otherwise run until we hit the genlimit
  while (genLimit == 0 || currentGen != genLimit)
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

void Automata::initialise() 
{
	cout << "Please make sure to maximise the size of your terminal window to ensure readable output!\n";
	cout << "Select the parameters for the cellular automata.\n";
	cout << "Cell limit per generation:\n";
  	cin >> cellLimit;
  	cout << "Generation limit:\n";
  	cin >> genLimit;
  	cout << "Rule set:\n";
  	createRuleSet();
	startTime();
}

void Automata::createRuleSet()
{
	cin >> ruleSet;
	std::string binary = std::bitset<8>(ruleSet).to_string(); 
	cout << binary;
	for (int i = 0; i < 8; i++)
	{
		rule[i] = binary[i] - '0';
	}
	cout << "\n";
	cout << "this is the ruleset:\n";
	for (int i = 0; i < 8; i++) {
    	cout << rule[i];
	}
	cout << "\n";
}

void Automata::convertBinary()
{
	int binary;
	cout << "Please enter the binary value you would like to convert to a decimal number:\n";
	cin >> binary;
	unsigned long decimal = std::bitset<8>(binary).to_ulong();
	std::cout<< decimal <<" is the decimal conversion of the binary value.\n";
}

void Automata::menu()
{
	int selection;
	cout << "\033[2J\033[1;1H";
	do 
	{
		cout << "============================================\n";
		cout << "  WELCOME TO THE CELLULAR AUTOMATA PROGRAM  \n";
		cout << "============================================\n";
		cout << "\n";
		cout << "Please choose a menu option:\n";
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
			initialise();
			cout << "\n";
			cout << "Please press Enter to continue.\n";
			while(getchar()!='\n'); 
        	getchar(); 
        	cout << "\033[2J\033[1;1H";
			break;

			case 2:
			convertBinary();
			cout << "\n";
			cout << "Please press Enter to continue.\n";
			while(getchar()!='\n'); 
        	getchar();
        	cout << "\033[2J\033[1;1H";
			break;

			case 3:
			cout << "\n";
			cout << "Please press Enter to continue.\n";
			while(getchar()!='\n');
        	getchar();
        	cout << "\033[2J\033[1;1H";
			break;

			case 0:
			cout << "Goodbye!\n";
			while(getchar()!='\n'); 
        	getchar(); 
        	cout << "\033[2J\033[1;1H";
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
  srand(time(NULL));

  Automata autom = Automata();

  autom.menu();
}

