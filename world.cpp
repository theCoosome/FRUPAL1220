// Written by Colton Jelsema
// Content definition for the grovnik storage

#include "world.h"
#include <fstream>

using namespace std;


World::World() {
	tiles = new grovnik[128][128];


	//Read the map data
	ifstream inf;

	inf.open("map.txt");
	char input[256];

	//Read each line
	for (int y=0; y < 128; ++y) {
		inf.get(input, 128, '\n');
		inf.ignore(128, '\n');

		//Interpret each value
		for (int x=0; x < 128; ++x) {
			tiles[x][y].terrain = atoi(input[x]);
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

		switch (t) {
			case 1: // treasure
				int cost;
				tiles[x][y].poi = new treasure();
				break;

			case 2: // food
				tiles[x][y].poi = new food();
				break;

			case 3: // tools
				tiles[x][y].poi = new tool();
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

			case 7: // Obsticle
				tiles[x][y].poi = new obstacle();
				break;
		}
		inf.ignore(256, '\n'); // Ignore to the next line
		inf.peek();
	}
	inf.close();

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
