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

void showGrov(int x, int y, grovnik * show) {
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
	mvaddch(x, y, atpoint);
	attroff(COLOR_PAIR(show -> terrain));
}

int main() {
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	//noecho();
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
	map.fileRead(herox, heroy);

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
	//Draw the splitscreen split

	// Initial world draw
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < Cols * 3/4; j++) {
			showGrov(i, j, map.getAt(i, j));
		}
	}

	attron(COLOR_PAIR(6));
	mvaddch(playery, playerx, '@');
	attroff(COLOR_PAIR(6));


	mvvline(0, splitPos, '|', Rows);
	while (running) {
		//move(cy,cx);//move the cursor
		int ch = getch();

		//nodelay(stdscr, FALSE);

		//Player movement pre-draw
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
			showGrov(playery, playerx, map.getAt(playery, playerx));
		}

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

		// If the user types something, draw over it
		if (ch != -1) {
			if (cx < splitPos){ // Redraw map info
				showGrov(cy, cx, map.getAt(cy, cx));
				// hero display. Always attempt redraw
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

		refresh();

		if (energy <= 0)
			running = false;
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





