// Jonnie Herrera
// Second map implementation that includes the object.h file
// object.h functions need to be implemented in order to work

#include "object.h"

struct grovnik
{
	int item;
	bool visited;
};

class Map
{
	public:
		Map();
		~Map();
		grovnik ** getMapFromFile();
		void displayMap(); 

	private:
		grovnik ** worldMap;
};

