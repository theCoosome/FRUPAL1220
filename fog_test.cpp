#include "fog.h"

int main(int argc, char* argv[]) {
	bool err = false;
	const int len_x = 9;
	const int len_y = 9;
	// Expected result of fog test
	const bool expected[len_y][len_x] = {
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 0, 0, 0, 1, 1},
	};
	fog test = fog(len_x, len_y);
	test.clear_rad(4, 4, 1);
	// Show off bounds check
	test.clear_rad(0, 0, 1);
	test.clear_rad(8, 8, 1);
	// Show off copy constructor
	fog test2 = fog((const fog&)test);
	// Show off getter function
	bool** tmp = test2.get_arr();
	for(int y = 0; y < len_y; y++) {
		for(int x = 0; x < len_x; x++) {
			if(tmp[y][x] != expected[y][x]) {
				err = true;
				break;
			}
		}
	}
	if(err == true) {
		cerr << "Test failed" << endl;
		cerr << "What test expected | What test got" << endl;
		// Output 2D arrays
		for(int y = 0; y < len_y; y++) {
			for(int x = 0; x < len_x; x++) {
				cerr << (int)expected[y][x];
			}
			cerr << "          | ";
			for(int x = 0; x < len_x; x++) {
				cerr << (int)tmp[y][x];
			}
			cerr << endl;
		}
		return 1;
	}
	cout << "Test passed" << endl;
	return 0;
}
