#include "automata.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <bitset>
#include <fstream>

using namespace std;

Automata::Automata()
{
  // default values
  currentGen = 0;
  cellLimit = 40;
  genLimit = 0;
  ruleSet = 0;
  string fileName;
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
  currentGen = 0;

  initCellLimit = newCellLimit;
  initGenLimit = newGenLimit;
  initCells = newCells;

  cellLimit = newCellLimit;
  genLimit = newGenLimit;
  cells = newCells;
}

//Sets the binary rule for future generations of the automaton.
void Automata::setRule(string newRule)
{
  //Convert to a string
  string stringRule = newRule;

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
  
  //The value at the index of the rule array will become the state of the child cell
  return rule[ruleToApply];
}
 
void Automata::step(bool saveAutomata){
  // if there is a file to save to, open it to write to it
  ofstream outputFile;
  if(saveAutomata == true)
  {
    outputFile.open(fileName, fstream::app);
  }

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
      if(saveAutomata == true)
      {
        outputFile << s << ' ';
      }
    }
  cout << endl;
  if(saveAutomata == true)
  {
    outputFile << endl;
    outputFile.close(); // close the save file
  }
}

void Automata::setGenLimit(unsigned int newGenLimit)
{
  genLimit = newGenLimit;
}

void Automata::setCellLimit(unsigned int newCellLimit)
{
  cellLimit = newCellLimit;
}

 void Automata::startTime(bool saveAutomata)
{
  // if there is a file to save to, open it to write to it
  ofstream outputFile;
  if(saveAutomata == true)
  {
    cout << "\n";
    cout << "Enter a name for your file:\n";
    cin >> fileName;
    cout << "\n";
    outputFile.open(fileName);
    outputFile << "Here is a saved cellular automata.\n";
    outputFile << "The cell limit is " << cellLimit << "\n";
    outputFile << "The generation limit is " <<  genLimit << "\n";
    outputFile << "The rule set is " <<  ruleSet << "\n";
    outputFile << "\n";
  }
  
  //if this is the first time we called start time print the first generation
  if(currentGen == 0)
    {
      for (vector<bool>::iterator it = cells.begin(); it != cells.end(); it++)
    	{
    	  //█ is 1, ░ is 0
    	  string s = *it?"█":"░";
    	  cout << s << ' ';
        if(saveAutomata == true)
        {
          outputFile << s << ' ';
        }
    	}
      cout << endl;
      if(saveAutomata == true)
        {
          outputFile << endl;
        }
    }
  
  //if the genlimit is 0 run forever, otherwise run until we hit the genlimit
  while (genLimit == 0 || currentGen != genLimit)
    {
      chrono::milliseconds timespan(500);
      step(saveAutomata);
      this_thread::sleep_for(timespan);
    }
  if(saveAutomata == true)
  {
    outputFile.close(); // close the save file
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
  bool saveAutomata = false; 
  bool input = false;
  int selection;
  cout << "\n";
	cout << "Please make sure to maximise the size of your terminal window to ensure readable output!\n";
  cout << "\n";
	cout << "Select the parameters for the cellular automata.\n";
	cout << "Cell limit per generation:\n";
  cin >> cellLimit;
  cout << "Generation limit:\n";
  cin >> genLimit;
  cout << "Rule set:\n";
  createRuleSet(); // converts the rule set decimal number to a binary number and stores it in the array
  cout << "\033[2J\033[1;1H";
  while(input == false)
  {
    cout << "Would you like to save your cellular automata to a text file?\n";
    cout << "1- Yes\n";
    cout << "2- No\n";
    cin >> selection;
    if(selection == 1)
    {
      saveAutomata = true; 
      startTime(saveAutomata);
      input = true; // to exit the loop
    }
    else 
    {
      if(selection == 2)
      {
        startTime(saveAutomata); // saveAutomata is false as the user does not want to save the automata to a file
        input = true; // to exit the loop
      }
      else 
      {
        cout << "Invalid entry!\n";
      }
    }
  }
}

void Automata::createRuleSet()
{
	cin >> ruleSet;
	std::string binary = std::bitset<8>(ruleSet).to_string(); 
	setRule(binary);
	cout << "\n";
}

void Automata::convertBinary()
{
	int binary;
  cout << "\n";
	cout << "Please enter the binary value you would like to convert to a decimal number:\n";
	cin >> binary;
	unsigned long decimal = std::bitset<8>(binary).to_ulong(); // converts the binary value to a long decimal value
	std::cout << decimal <<" is the decimal conversion of the binary value.\n";
}

void Automata::readFile()
{
  string fileName;
  cout << "\n";
  cout << "Please enter the name of the file you would like to read the cellular automata from:\n";
  cin >> fileName;
  try
  {
    ifstream file(fileName);
    string line;
    while (getline(file, line))
    {
        cout << line << "\n"; // read line by line
    }
  }
  catch(...) // if the file name is invalid
  {
    cout << "Invalid file name!";
  }
}

void Automata::menu()
{
	int selection;
	cout << "\033[2J\033[1;1H"; // clears terminal
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
      {
        Automata newAutom = Automata(); // create a new Automata object so that the user can create several of them
        newAutom.initialise();
  			cout << "\n";
  			cout << "Please press Enter to continue.\n";
  			while(getchar()!='\n'); 
        getchar(); 
        cout << "\033[2J\033[1;1H";
    		break;
      }

			case 2:
      {
  			convertBinary();
  			cout << "\n";
  			cout << "Please press Enter to continue.\n";
  			while(getchar()!='\n');
        getchar(); 
        cout << "\033[2J\033[1;1H";
  			break;
      }

			case 3:
      {
  			readFile();
        cout << "\n";
  			cout << "Please press Enter to continue.\n";
  			while(getchar()!='\n');
        getchar(); 
        cout << "\033[2J\033[1;1H";
  			break;
      }

			case 0:
        {
  			cout << "Goodbye!\n";
  			while(getchar()!='\n');
        getchar(); 
        cout << "\033[2J\033[1;1H";
  			break;
      }

			default:
      {
  			cout << selection << " is not a valid menu selection!\n";
        cout << "\n";
        cout << "Please press Enter to continue.\n";
        while(getchar()!='\n');
        getchar(); 
        cout << "\033[2J\033[1;1H";
      }
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

