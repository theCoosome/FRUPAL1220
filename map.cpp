// Jonnie Herrera
// Unfinished map sample, need object class functions implementations

#include "map-sample.h"
#include <fstream>

Map::Map() {
	worldMap = getMapFromFile(); 
}

Map::~Map() {
	if(worldMap) {
		for(int c = 0; c < 5; c++) {
			delete [] worldMap[c];
		}
    delete [] worldMap;
	}
}

// function reads a text file filled with numbers, representing the items
grovnik ** Map::getMapFromFile() {
	ifstream in_file;
	in_file.open("map.txt");
	if(!in_file) {
		cout << "Failed to open file!" << endl;
		return 0;
	}

	grovnik ** grovnikMap = new grovnik * [5];

	for(int row = 0; row < 5; row++) {
		grovnikMap[row] = new grovnik[5];
	}

	for(int row = 0; row < 5; row++) {
		for(int column = 0; column < 5; column++) {
			in_file >> grovnikMap[row][column].item;
			grovnikMap[row][column].visited = False;
		}
	}
	return grovnikMap;
}

void Map::displayMap() {
	if(!worldMap) {
		cout << "No map created!";
		return;
	}

	for(int row = 0; row < 5; row++) {
		for(int column = 0; column < 5; column++) {
			cout << worldMap[row][column].item;
		}
		cout << endl;
	}
}

//
int main()
{
	map obj;

	obj.displayMap();

	return 0;
}

