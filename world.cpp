// Written by Colton Jelsema and Vincent Vermilya
// Content definition for the grovnik storage

#include "world.h"

using namespace std;


World::World(): width(128), height(128) {
	tiles = new grovnik*[height];
	for(unsigned int y = 0; y < height; y++) {
		tiles[y] = new grovnik[width];
		for(unsigned int x = 0; x < width; x++) {
			tiles[y][x] = grovnik();
		}
	}

	fog = new bool*[height];
	for(unsigned int y = 0; y < height; y++) {
		fog[y] = new bool[width];
		for(unsigned int x = 0; x < width; x++) {
			fog[y][x] = false;
		}
	}
}

World::World(unsigned int width1, unsigned int length1): width(width1), height(length1) {
	tiles = new grovnik*[height];
	for(unsigned int y = 0; y < height; y++) {
		tiles[y] = new grovnik[width];
		for(unsigned int x = 0; x < width; x++) {
			tiles[y][x] = grovnik();
		}
	}

	fog = new bool*[height];
	for(unsigned int y = 0; y < height; y++) {
		fog[y] = new bool[width];
		for(unsigned int x = 0; x < width; x++) {
			fog[y][x] = false;
		}
	}
}

World::~World() {
	for(unsigned int y = 0; y < height; y++) {
		delete [] tiles[y];
	}
	delete [] tiles;

	for(unsigned int y = 0; y < height; y++) {
		delete [] fog[y];
	}
	delete [] fog;
}

void World::setGrovnik(int x, int y, int terr_type, object * data) {
	tiles[x][y].setData(terr_type, data);
}

// Clear fog[y1][x1] from false to true
// Basecase bounds check to avoid segfault
void World::clearfog(unsigned int x1, unsigned int y1) {
	if(x1 >= width || y1 >= height) {
		return;
	}
	fog[y1][x1] = true;
	return;
}

// Call clearfog for a square radius centered on fog[y1][x1]
void World::clearfog_rad(unsigned int x1, unsigned int y1, unsigned int radius) {
	for(int y = (int)radius * -1; y <= (int)radius; y++) {
		for(int x = (int)radius * -1; x <= (int)radius; x++) {
			clearfog(x1 + x, y1 + y);
		}
	}
	return;
}

#ifdef TEST
bool ** World::get_fog() {
	return fog;
}
#endif



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

void grovnik::setData(int terr_type, object * data) {
	terrain = terr_type;
	poi = data;
}
