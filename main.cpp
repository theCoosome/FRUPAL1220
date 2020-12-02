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

using namespace std;


int main() {
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
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
	map.fileRead();

	bool running = true; // program running conditional

	// player variables
	int energy = 100;
	int  whiffles = 1000;
	bool binoculars = false;
	bool boat = false;
	// vector<object> inventory;


	// test world
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			grovnik * temp = map.getAt(i, j);
			attron(COLOR_PAIR(temp -> terrain));
			mvaddch(i, j, ' ');
			attroff(COLOR_PAIR(temp -> terrain));
		}
	}
	drawsplit(whiffles, energy, binoculars, boat);

	refresh();


	// cursor position
	int cx = 2;
	int cy = 2;
	int playerx = 3;
	int playery = 3;
	int ch;

	// set values, due to possibility of changing viewport
	int Cols = COLS;
	int Rows = LINES;
/*
	while (running) {
		int ch = getch();
		getyx(stdscr, cy, cx);
		// Redraw if the user has given a key input
		// A key input is likely to draw something on screen.
		if (ch != -1) {
			move(cy, cx);
		}

		// User input, always considered
		   switch (ch) {
		   case 'q':
		//press q to quit
		running = false;
		break;
		case KEY_LEFT:
		if (cx ==  0) {
		move(cy, COLS - 1);
		} else {
		move(cy, cx - 1);
		}
		// refresh();
		break;
		case KEY_RIGHT:
		if (cx ==  COLS-1) {
		move(cy, 0);
		} else {
		move(cy, cx + 1);
		}
		//refresh();
		break;
		case KEY_UP:
		if (cy ==  0) {
		move(LINES - 1, cx);
		} else {
		move(cy - 1, cx);
		}
		// refresh();
		break;
		case KEY_DOWN:
		if (cy ==  LINES - 1) {
		move(0, cx);
		} else {
		move(cy + 1, cx);
		}
		//refresh();
		break;
		}
		refresh();

		}
		 */
		nodelay(stdscr, FALSE);
//alternative cursor movement
		do //user input pause loop
		{	switch(ch)
			{
				case KEY_UP: //move up
					if(cy == 0)
					{
						cy= 1;

					}
					else
						--cy;
					break;
				case KEY_DOWN: //move down
					if(cy == LINES-1) {
						cy = LINES -1;
					}
					else
						++cy;
					break;
				case KEY_LEFT: //move left
					if(cx == 0)
					{
						cx = 1;
					}
					else
						--cx;
					break;
				case KEY_RIGHT: //move right
					if(cx == COLS-1)
					{
						cx = COLS -1;
					}
					else
						++cx;
					break;
			case 'q': //quit the game
					break;
			}
			--energy;
			drawsplit(whiffles, energy, binoculars, boat);
			move(cy,cx);//move the cursor
			ch = mvgetch(cy,cx); //grab the new spot
			curs_set(1);//place cursor in prior postition
		}while(ch != 'q');


		return endwin();
}







