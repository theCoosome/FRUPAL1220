#include "fog.h"

fog::fog(): width(0), height(0), arr(NULL) {}


// Init fog[src_h][src_w] to false
fog::fog(unsigned int src_w, unsigned int src_h): width(src_w), height(src_h) {
	arr = new bool*[height];
	for(unsigned int y = 0; y < height; y++) {
		arr[y] = new bool[width];
		for(unsigned int x = 0; x < width; x++) {
			arr[y][x] = false;
		}
	}
}

fog::fog(const fog& src): width(src.width), height(src.height) {
	arr = new bool*[height];
	for(unsigned int y = 0; y < height; y++) {
		arr[y] = new bool[width];
		for(unsigned int x = 0; x < width; x++) {
			arr[y][x] = src.arr[y][x];
		}
	}
}


fog::~fog() {
	for(unsigned int y = 0; y < height; y++) {
		delete [] arr[y];
	}
	delete [] arr;
}

bool** fog::get_arr() {
	return arr;
}

// Clear arr[src_h][src_w] from false to true
// Basecase bounds check to avoid segfault
void fog::clear(unsigned int src_w, unsigned int src_h) {
	if(src_w >= width || src_h >= height) {
		return;
	}
	arr[src_h][src_w] = true;
	return;
}

// Call clear for a square radius centered on arr[src_h][src_w]
void fog::clear_rad(unsigned int src_w, unsigned int src_h, unsigned int radius) {
	for(int y = (int)radius * -1; y <= (int)radius; y++) {
		for(int x = (int)radius * -1; x <= (int)radius; x++) {
			clear(src_w + x, src_h + y);
		}
	}
	return;
}
