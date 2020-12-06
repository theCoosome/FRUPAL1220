// Written by Colton Jelsema and Vincent Vermilya
// Content definition for the grovnik storage

#include "world.h"
#include <fstream>

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


void World::fileRead(int * heroy, int * herox) {
	//Read the map data
	ifstream inf;

	inf.open("map.txt");
	char* input = new char[width + 1];

	//Read each line
	for (unsigned int y=0; y < height; ++y) {
		inf.get(input, width + 1, '\n');
		inf.ignore(width + 1, '\n');

		//Interpret each value
		for (unsigned int x=0; x < width; ++x) {
			tiles[y][x].terrain = input[x] - 48;
		}
		inf.peek();
		if (inf.eof())
			y = height + 1;
	}
	delete [] input;
	inf.close();

	//Read the data for points of interest
	int x;
	int y;
	int t;

	int cost;
	int value;
	int power;
	int type;
	inf.open("mapdata.txt");
	inf.peek();
	while (!inf.eof()) {
		inf >> y;
		inf.ignore(5, ' ');
		inf >> x;
		inf.ignore(5, ' ');
		inf >> t;
		inf.ignore(5, ' ');

		// Read the remaining data
		switch (t) {
			case 0: // Hero.
				*herox = x;
				*heroy = y;
				break;

			case 1: // treasure: Returned value
				inf >> cost;
				tiles[y][x].poi = new treasure(cost, false);
				break;

			case 2: // food: cost, value, name
				inf >> cost;
				inf.ignore(100, ' ');
				inf >> value;
				inf.ignore(100, ' ');

				inf.get(input, 256, '\n');
				tiles[y][x].poi = new food(cost, input, value);
				break;

			case 3: // tools: cost, power, obstype, name
				inf >> cost;
				inf.ignore(100, ' ');
				inf >> power;
				inf.ignore(100, ' ');
				inf >> type;
				inf.ignore(100, ' ');

				inf.get(input, 256, '\n');
				tiles[y][x].poi = new tool(cost, input, power, type);
				break;

			case 4: // clues
				inf.get(input, 256, '\n');
				tiles[y][x].poi = new clue(input);
				break;

			case 5: // ship
				inf >> cost;
				tiles[y][x].poi = new object(5, cost);
				break;

			case 6: // Binoculars
				inf >> cost;
				tiles[y][x].poi = new object(6, cost);
				break;

			case 7: // Obsticle: cost, type
				inf >> cost;
				inf.ignore(100, ' ');
				inf >> type;
				tiles[y][x].poi = new obstacle(cost, type);
				break;
		}
		inf.ignore(2048, '\n'); // Ignore to the next line
		inf.peek();
	}
	inf.close();
}

void World::setGrovnik(unsigned int y, unsigned int x, int terr_type, object * data) {
	if(y > height || x > width) {
		return;
	}
	tiles[y][x].setData(terr_type, data);
}

grovnik * World::getAt(unsigned int y, unsigned int x) {
	if(y > height || x > width) {
		return NULL;
	}
	return & tiles[y][x];
}

// Clear fog[y1][x1] from false to true
// Basecase bounds check to avoid segfault
void World::clearfog(unsigned int y1, unsigned int x1) {
	if(x1 >= width || y1 >= height) {
		return;
	}
	fog[y1][x1] = true;
	return;
}

// Call clearfog for a square radius centered on fog[y1][x1]
void World::clearfog_rad(unsigned int y1, unsigned int x1, unsigned int radius) {
	for(int y = (int)radius * -1; y <= (int)radius; y++) {
		for(int x = (int)radius * -1; x <= (int)radius; x++) {
			clearfog(y1 + x, x1 + y);
		}
	}
	return;
}

bool World::getfog(unsigned int y1, unsigned int x1) {
	if(x1 >= width || y1 >= height) {
		return false;
	}
	return fog[y1][x1];
}

#ifdef TEST
bool ** World::getfog() {
	return fog;
}
#endif



grovnik::grovnik() {
	terrain = 0;
	poi = NULL;
}


grovnik::~grovnik() {
	if(poi) {
		delete poi;
	}
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
