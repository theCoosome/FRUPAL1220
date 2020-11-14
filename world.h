//Author of header: Colton Jelsema
// Header for the matrix that stores information about the game world

#include "object.h"

// Stores information about a single Grovnik tile.
class grovnik {
	public:
	grovnik();
	grovnik(const grovnik & copy); // Copy constructor
	grovnik(int terr_type, object * data); // complex constructor

	~grovnik();

	setData(int terr_type, object * data);

	//private: 'proper' structure dictates use of private variables,
	// but having a manager for the data makes that unwieldly and unnessecary.
	int terrain; // type of terrain
	object * poi; // Point of interest on this tile
};

class World {
	public:
	World();
	// The world should never by directly copied.
	
	~World();

	// grovnik builder for use by world builders
	setGrovnik(int x, int y, int terr_type, object * data);

	private:
	grovnik ** tiles;
};
