// Jonnie Herrera
// Second map implementation that includes the object.h file
// object.h functions need to be implemented in order to work

//#include <iostream>
//#include <cstring> 
//#include <cctype>
#include "object.h"

struct grovnik
{
	int item;
	//object * item; // object class needs helper functions to get 'type' information
	int visited; // will return 1 or 0, depending if the player has visited that grovnik
};

class map
{
	public:
		map();
		~map();	
		grovnik ** getMap(); // creates the map reading from textfile
		void displayMap(); // displays map
		
	private:
		grovnik ** worldMap; // 2D array of grovnik objects
};

