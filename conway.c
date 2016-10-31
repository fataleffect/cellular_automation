#include "conway.h"



Conway::Conway()
{

}

Conway::Conway(vector<vector<bool>> newCells, unsigned int newCellLimit, unsigned int newGenLimit)
{

}

//override step method of base class
Conway::step()
{
  vector<vector<bool>> newCells;
  //iterate through our outer vector
  for(vector<vector<bool>::iterator x = cells.begin(); it != cells.end(); it++)
    {
      //Iterate through the entire inner vector stored at outer vector[x]
      for(vector<bool>::iterator y = *x.begin(); y != *x.end(); it++)
	{
	  
	}
    }
  cells = newCells;
  currentGen++
  printGen();
}

//override applyRule to apply conway rules.
Conway::applyRule(vector<vector<bool>> x, vector<bool> y)
{
  int sum = 0;
  for(int i = -1; i <=1; i++)
    {
      for(int j = -1; i <=1; j++)
	{
	  if(x == cells.begin())
	    {
	      
	    }
	  else if (x == cells.end()-1 && i == 1)
	    
	    if(y == cells.begin())
	      {
		
	      }
	    else if (y == cells.end()-1 && j == 1)

	      if()
	  *(x+i) *(y+j);
	}
    }
  
}
