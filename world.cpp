// Written by Colton Jelsema and Vincent Vermilya
// Content definition for the grovnik storage

#include "world.h"
#include <fstream>

using namespace std;


World::World(): width(128), height(128) {
	tiles = new Grovnik*[height];
	for(unsigned int y = 0; y < height; y++) {
		tiles[y] = new Grovnik[width];
		for(unsigned int x = 0; x < width; x++) {
			tiles[y][x] = Grovnik();
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
	tiles = new Grovnik*[height];
	for(unsigned int y = 0; y < height; y++) {
		tiles[y] = new Grovnik[width];
		for(unsigned int x = 0; x < width; x++) {
			tiles[y][x] = Grovnik();
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


char ** World::fileRead(int * heroy, int * herox) {
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

	//Prepare obstacle type definition
	char ** obstypes = new char*[10];
	for (int i=0; i<10; ++i){
		obstypes[i] = new char[128];
	}

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

		// Read the remaining data
		switch (t) {
			case 0: // Hero.
				*herox = x;
				*heroy = y;
				break;

			case 1: // treasure: Returned value
				inf.ignore(5, ' ');
				inf >> cost;
				tiles[y][x].pointOfInterest = new treasure(cost, false);
				break;

			case 2: // food: cost, value, name
				inf.ignore(5, ' ');
				inf >> cost;
				inf.ignore(100, ' ');
				inf >> value;
				inf.ignore(100, ' ');

				inf.get(input, 256, '\n');
				tiles[y][x].pointOfInterest = new food(cost, input, value);
				break;

			case 3: // tools: cost, power, obstype, name
				inf.ignore(5, ' ');
				inf >> cost;
				inf.ignore(100, ' ');
				inf >> power;
				inf.ignore(100, ' ');
				inf >> type;
				inf.ignore(100, ' ');

				inf.get(input, 256, '\n');
				tiles[y][x].pointOfInterest = new tool(cost, input, power, type);
				break;

			case 4: // clues
				inf.ignore(5, ' ');
				inf.get(input, 256, '\n');
				tiles[y][x].pointOfInterest = new clue(input);
				break;

			case 5: // ship
				inf.ignore(5, ' ');
				inf >> cost;
				tiles[y][x].pointOfInterest = new object(5, cost);
				break;

			case 6: // Binoculars
				inf.ignore(5, ' ');
				inf >> cost;
				tiles[y][x].pointOfInterest = new object(6, cost);
				break;

			case 7: // Obsticle: cost, type
				inf.ignore(5, ' ');
				inf >> cost;
				inf.ignore(100, ' ');
				inf >> type;
				tiles[y][x].pointOfInterest = new obstacle(cost, type);
				break;

			case 9: //define an obstacle type
				inf.ignore(5, ' ');
				inf.get(obstypes[x], 128, '\n');
				break;
		}
		inf.ignore(2048, '\n'); // Ignore to the next line
		inf.peek();
	}
	inf.close();

	return obstypes;
}

void World::setGrovnik(unsigned int line, unsigned int column, int terrain_type, object * data) {
	if(line > height || column > width) {
		return;
	}
	tiles[line][column].setData(terrain_type, data);
}

Grovnik * World::getAt(unsigned int line, unsigned int column) {
	if(line > height || column > width) {
		return NULL;
	}
	return & tiles[line][column];
}

bool World::clearPOI(int line, int column) {
	if (tiles[line][column].pointOfInterest) {
		delete tiles[line][column].pointOfInterest;
		tiles[line][column].pointOfInterest = NULL;
		return true;
	}
	return false;
}

void World::clearfog(unsigned int line, unsigned int column) {
	if(column >= width || line >= height) {
		return;
	}
	fog[line][column] = true;
	return;
}

void World::clearfogOfRadius(unsigned int line, unsigned int column, unsigned int radius) {
	for(int y = (int)radius * -1; y <= (int)radius; y++) {
		for(int x = (int)radius * -1; x <= (int)radius; x++) {
			clearfog(line + x, column + y);
		}
	}
	return;
}

bool World::getfog(unsigned int line, unsigned int column) {
	if(column >= width || line >= height) {
		return false;
	}
	return fog[line][column];
}

#ifdef TEST
bool ** World::getfog() {
	return fog;
}
#endif



Grovnik::Grovnik() {
	terrain = 0;
	pointOfInterest = NULL;
}


Grovnik::~Grovnik() {
	if(pointOfInterest) {
		delete pointOfInterest;
	}
}


Grovnik::Grovnik(const Grovnik & copy) {
	terrain = copy.terrain;
}


// if there is nothing of interest on this tile, set data to null
Grovnik::Grovnik(int terr_type, object * data) {
	terrain = terr_type;
	pointOfInterest = data;
}

void Grovnik::setData(int terr_type, object * data) {
	terrain = terr_type;
	pointOfInterest = data;
}
