// Jonnie Herrera
// Unfinished map sample, need object class functions implementations

#include "map.h"
#include <fstream>

// constructor
map::map()
{
	worldMap = getMap(); // worldMap catches the getMap value which will be a 2D array
	
// Original 2D array initialization
/*	
	for(int r = 0; r < 128; r++)
	{
		worldMap[r] = new grovnik[128];
	}

	for(int r = 0; r < 128; r++)
	{
		for(int c = 0; c < 128; c++)
		{
			worldMap[r][c].item = NULL;
			worldMap[r][c].visited = 0;
		}
	}
*/
}

// Destructor: still need to check for memory leaks
map::~map()
{
	if(worldMap)
	{

		for(int c = 0; c < 128; c++)
		{
			delete [] worldMap[c];
		}
		
		delete [] worldMap;
	}
	
	
}

// function reads a text file filled with numbers, representing the items
grovnik** map::getMap()
{
	ifstream in_file;

	in_file.open("map.txt");

	if(!in_file)
	{
		cout << "Failed to open file!" << endl;
		return 0;
	}

	grovnik ** Map = new grovnik * [128];
	
	for(int r = 0; r < 128; r++)
	{
		Map[r] = new grovnik[128];
	}

	for(int r = 0; r < 128; r++)
	{
		for(int c = 0; c < 128; c++)
		{
			in_file >> Map[r][c].item;	
			//Map[r][c].item = in_file.get(); // need a set type function from object class
			Map[r][c].visited = 0;
		}
	}
			
	return Map; // returns 2D array, need to ask if its okay
}

// displays the map
void map::displayMap()
{
	if(!worldMap)
	{
		cout << "No map created!";
		return;
	}

	for(int r = 0; r < 128; r++)
	{
		for(int c =0; c < 128; c++)
		{
			cout << worldMap[r][c].item;
		}
		cout << endl;
	}

	//cout << "3, 3: " << worldMap[3][3].item << endl; // was testing whether it displayed correctly
}
		
// test main function to see if it worked
int main()
{
	map obj;
	
	obj.displayMap();
	
	return 0;
}

