#include <ncurses.h>
#include <vector>
#include <fstream>

#include "object.h"
#include "world.h"
#include "split.h"

//color definitions
#define MEADOW_PAIR 1
#define SWAMP_PAIR 2
#define WATER_PAIR 3
#define WALL_PAIR 4
#define DIAMOND_PAIR 5
#define HERO_PAIR 6

void print_lose();

using namespace std;

void showGrov(int y, int x, grovnik * show) {
	if (x < 0 || y < 0 || x > 127 || y > 127) return;
	char atpoint = ' ';
	if (show -> poi) {
		switch (show -> poi -> get_type()) {
			case 1: //treasure
				atpoint = '$';
				break;
			case 2: //food
				atpoint = 'F';
				break;
			case 3: //tool
				atpoint = 'T';
				break;
			case 7: //obstacle
				atpoint = '!';
				break;
		}
	}
	if (show -> terrain == DIAMOND_PAIR) {
		atpoint = '$';
	}
	attron(COLOR_PAIR(show -> terrain));
	mvaddch(y, x, atpoint);
	attroff(COLOR_PAIR(show -> terrain));
}

int main() {
	initscr();
	keypad(stdscr, true);
	noecho();
	clear();

	//initialize color stuff
	start_color();
	init_pair(MEADOW_PAIR, COLOR_BLACK, COLOR_GREEN);
	init_pair(SWAMP_PAIR, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(WATER_PAIR, COLOR_BLACK, COLOR_BLUE);
	init_pair(WALL_PAIR, COLOR_BLACK, COLOR_WHITE);
	init_pair(DIAMOND_PAIR, COLOR_WHITE, COLOR_CYAN);
	init_pair(HERO_PAIR, COLOR_YELLOW, COLOR_RED);


	// initialize variables
	World map;
	int * herox = new int;
	int * heroy = new int;
	*heroy = 2;
	*herox = 2;
	map.fileRead(heroy, herox);

	bool running = true; // program running conditional

	// player variables
	int energy = 100;
	int whiffles = 1000;
	bool binoculars = false;
	bool boat = false;
	// vector<object> inventory;

	// cursor position
	int cx = 2;
	int cy = 2;
	int playerx = *herox;
	int playery = *heroy;
	delete herox;
	delete heroy;


	// set values, due to possibility of changing viewport
	int Cols = COLS;
	int Rows = LINES;
	int splitPos = min(128, Cols * 3 / 4);


	map.clearfog_rad(playery, playerx, 1);

	// Initial world draw
	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < Cols * 3/4; x++) {
			if(map.getfog(y, x)) {
				showGrov(y, x, map.getAt(y, x));
			} else {
				mvaddch(y, x, ' ');
			}
		}
	}

	//Draw the splitscreen split
	mvvline(0, splitPos, '|', Rows);
	drawsplit(whiffles, energy, binoculars, boat);

	// Clear map for debugging file reader
	//map.clearfog_rad(0, 0, 128);
	while (running) {

		int ch = getch();

		// User input
		switch(ch) {
			case 'q': //press q to quit
				running = false;
				break;

			//Player movement
			case 'w': //move player up
				if (playery) {
					--playery;
				}
				--energy;
				break;
			case 's': //move player down
				if (playery < 128) {
					++playery;
				}
				--energy;
				break;
			case 'a': //move player left
				if (playerx) {
					--playerx;
				}
				--energy;
				break;
			case 'd': //move player right
				if (playerx < 128) {
					++playerx;
				}
				--energy;
				break;

			// Cursor movement
			case KEY_UP: //move up
				if(cy) {
					--cy;
				}
				break;
			case KEY_DOWN: //move down
				if(cy < Rows - 1) {
					++cy;
				}
				break;
			case KEY_LEFT: //move left
				if(cx) {
					--cx;
				}
				break;
			case KEY_RIGHT: //move right
				if(cx < Cols - 1) {
					++cx;
				}
				break;
			default:
				break;
		}

		//Player movement post-draw
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
			showGrov(playery, playerx, map.getAt(playery, playerx));

			int radius;
			if(binoculars) {
				map.clearfog_rad(playery, playerx, 2);
				radius = 2;
			} else {
				map.clearfog_rad(playery, playerx, 1);
				radius = 1;
			}
			for(int y = playery - radius; y <= playery + radius; y++) {
				for(int x = playerx - radius; x <= playerx + radius; x++) {
					showGrov(y, x, map.getAt(y, x));
				}
			}

			// hero display post-move
			attron(COLOR_PAIR(6));
			mvaddch(playery, playerx, '@');
			attroff(COLOR_PAIR(6));
		}

		// If the user types something, draw over it
		if (ch != -1) {
			if (cx < splitPos){ // Redraw map info
				if(map.getfog(cy, cx)) {
					showGrov(cy, cx, map.getAt(cy, cx));
				} else {
					mvaddch(cy, cx, ' ');
				}
				// hero display. In case you typed over it
				attron(COLOR_PAIR(6));
				mvaddch(playery, playerx, '@');
				attroff(COLOR_PAIR(6));
			}
			if (cx == splitPos) { //Redraw the screen split
				mvaddch(cy, splitPos, '|');
			}
			if (cx > splitPos){ // Redraw splitscreen blank background
				mvaddch(cy, cx, ' ');
			}
		}

		drawsplit(whiffles, energy, binoculars, boat);
		//After the mvaddch, because they move the cursor as well
		move(cy, cx);

		if(energy <= 0)
			running = false;

		refresh();
	}

	if(energy <= 0)
		print_lose();

	return endwin();
}

void print_lose()
{
	wrefresh(stdscr);
	initscr();
	noecho();
	mvprintw((LINES/2), (COLS/2)-8, "YOU LOSE");
	move(0,0);
	refresh();
	getch();
	endwin();
	refresh();


}





