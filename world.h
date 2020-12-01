// Author of header: Colton Jelsema and Vincent Vermilya
// Header for the matrix that stores information about the game world

#include "object.h"

// Stores information about a single Grovnik tile.
class grovnik {
	public:
	grovnik();
	grovnik(const grovnik & copy); // Copy constructor
	grovnik(int terr_type, object * data); // complex constructor

	~grovnik();

	void setData(int terr_type, object * data);

	//private: 'proper' structure dictates use of private variables,
	// but having a manager for the data makes that unwieldly and unnessecary.
	int terrain; // type of terrain
	object * poi; // Point of interest on this tile
};

class World {
	public:
	World();
	World(unsigned int width1, unsigned int length1);
	// The world should never by directly copied.

	~World();

	// grovnik builder for use by world builders
	void setGrovnik(int x, int y, int terr_type, object * data);
	void clearfog(unsigned int x1, unsigned int y1);
	void clearfog_rad(unsigned int x1, unsigned int y1, unsigned int radius);
	void fileRead();
	grovnik * getAt(unsigned int x, unsigned int y);
#ifdef TEST
	bool ** get_fog();
#endif

	private:
	unsigned int width, height;
	grovnik ** tiles;
	bool ** fog; // false is fog, true is clear
};
