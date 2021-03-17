
#include "object.h"

class Grovnik {
	public:
    Grovnik();
    Grovnik(const Grovnik & copy); // Copy constructor
    Grovnik(int terr_type, object * data); // complex constructor
    ~Grovnik();

	  void setData(int terr_type, object * data);

    int terrain; 
    object * pointOfInterest;
};

class World {
	public:
    World();
    World(unsigned int width1, unsigned int length1);
    ~World();

    // grovnik builder for use by world builders
    void setGrovnik(unsigned int line, unsigned int column, int terr_type, object * data);
    void clearfog(unsigned int line, unsigned int column);
    void clearfogOfRadius(unsigned int line, unsigned int column, unsigned int radius);
    char ** fileRead(int * heroy, int * herox);
    Grovnik * getAt(unsigned int line, unsigned int column);
    bool getfog(unsigned int line, unsigned int column);
    bool clearPOI(int line, int column);

#ifdef TEST
    bool ** getfog();
#endif

	private:
    unsigned int width, height;
    Grovnik ** tiles;
    bool ** fog; // false is fog, true is clear
};
