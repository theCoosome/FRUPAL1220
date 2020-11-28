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


void World::fileRead() {
	//Read the map data
	ifstream inf;

	inf.open("map.txt");
	char input[256];
	char xval[1];

	//Read each line
	for (int y=0; y < height; ++y) {
		inf.get(input, width, '\n');
		inf.ignore(width, '\n');

		//Interpret each value
		for (int x=0; x < width; ++x) {
			xval[0] = input[x];
			tiles[x][y].terrain = atoi(xval);
		}
	}
	inf.close();

	//Read the data for points of interest
	int x;
	int y;
	int t;
	inf.open("mapdata.txt");
	inf.peek();
	while (!inf.eof()) {
		inf >> x;
		inf.ignore(5, ' ');
		inf >> y;
		inf.ignore(5, ' ');
		inf >> t;
		inf.ignore(5, ' ');

		// Read the remaining data
		switch (t) {
			case 1: // treasure: Returned value
				int cost;
				inf >> cost;
				tiles[x][y].poi = new treasure(cost, false);
				break;

			case 2: // food: cost, value, name
				int cost;
				inf >> cost;
				inf.ignore(100, ' ');
				int value;
				inf >> value;
				inf.ignore(100, ' ');

				inf.get(input, 256, '\n');
				tiles[x][y].poi = new food(cost, input, value);
				break;

			case 3: // tools: cost, power, obstype, name
				int cost;
				inf >> cost;
				inf.ignore(100, ' ');
				int power;
				inf >> power;
				inf.ignore(100, ' ');
				int type;
				inf >> type;
				inf.ignore(100, ' ');

				inf.get(input, 256, '\n');
				tiles[x][y].poi = new tool(cost, input, power, type);
				break;

			case 4: // clues
				//tiles[x][y].poi = new 
				break;

			case 5: // ship
				//tiles[x][y].poi = new 
				break;

			case 6: // Binoculars
				//tiles[x][y].poi = new 
				break;

			case 7: // Obsticle: cost, type
				int cost;
				inf >> cost;
				inf.ignore(100, ' ');
				int type;
				inf >> type;
				tiles[x][y].poi = new obstacle(cost, type);
				break;
		}
		inf.ignore(256, '\n'); // Ignore to the next line
		inf.peek();
	}
	inf.close();
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
