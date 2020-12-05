// Written by Vincent Vermilya

#include "world.h"

int main(int argc, char* argv[]) {
	bool err = false;
	const int width = 9;
	const int length = 9;
	// Expected result of fog test
	const bool expected[length][width] = {
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
	};
	World test = World(width, length);
	test.clearfog_rad(4, 4, 1);
	// Show off bounds check
	test.clearfog_rad(0, 0, 1);
	test.clearfog_rad(0, 8, 1);
	test.clearfog_rad(8, 8, 1);
	// Show off getter function
	bool** tmp = test.get_fog();
	for(int y = 0; y < length; y++) {
		for(int x = 0; x < width; x++) {
			if(tmp[y][x] != expected[y][x]) {
				err = true;
				goto end;
			}
		}
	}
	end:
	if(err == true) {
		cerr << "Fog test failed" << endl;
		cerr << "What test expected | What test got" << endl;
		// Output 2D arrays
		for(int y = 0; y < length; y++) {
			for(int x = 0; x < width; x++) {
				cerr << (int)expected[y][x];
			}
			cerr << "          | ";
			for(int x = 0; x < width; x++) {
				cerr << (int)tmp[y][x];
			}
			cerr << endl;
		}
		return 1;
	}
	cout << "Fog test passed" << endl;
	return 0;
}
