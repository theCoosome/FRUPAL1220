// Written by Colton Jelsema
// Content definition for the grovnik storage

#include "world.h"

using namespace std;


World::World() {
	tiles = new grovnik[128][128];
}

World::~World() {
	delete [][] tiles;
}

World::setGrovnik(int x, int y, int terr_type, object * data) {
	tiles[x][y].setData(terr_type, data);
}



grovnik::grovnik() {
	terrain = 0;
	poi = NULL;
}


grovnik::~grovnik() {
	// Object pointers are to be handled by their handler
}


grovnik::grovnik(const grovnik & copy) {
	terrain = copy.terrain;
}


// if there is nothing of interest on this tile, set data to null
grovnik::grovnik(int terr_type, object * data) {
	terrain = terr_type;
	poi = data;
}

grovnik::setData(int terr_type, object * data) {
	terrain = terr_type;
	poi = data;
}
