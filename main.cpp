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
void setDisplayRange(int herox, int heroy, int cols, int lines, int & xMax, int & xMin, int & yMax, int & yMin);

using namespace std;

int main() {
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
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
	map.fileRead(herox, heroy);

	bool running = true; // program running conditional

	// player variables
	int energy = 100;
	int  whiffles = 1000;
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

  //display variables
  int displayXMax = 0;
  int displayXMin = 0;
  int displayYMax = 0;
  int displayYMin = 0;

  WINDOW* infoWindow = newwin(LINES, COLS/4, 0, COLS * 3/4);
  WINDOW* gameWindow = newwin(LINES, COLS * 3/4, 0, 0);
  for (int i = 0; i < 128; i++) {
    mvwprintw(infoWindow, i, 0, "|");
  }
	refresh();
  wrefresh(gameWindow);
  wrefresh(infoWindow);



	// set values, due to possibility of changing viewport
//	int Cols = COLS;
//	int Rows = LINES;

	while (running) {
		int ch = getch();
		getyx(stdscr, cy, cx);
		// Redraw if the user has given a key input
		// A key input is likely to draw something on screen.

		switch (ch) {
		  case 'q': //press q to quit
			  running = false;
				break;
      case KEY_UP: //move up
        if(cy)
          --cy;
        break;
      case KEY_DOWN: //move down
        if(cy != LINES-1) {
          ++cy;
        }
        break;
      case KEY_LEFT: //move left
        if(cx)
          --cx;
        break;
      case KEY_RIGHT: //move right
        if(cx != COLS-1)
          ++cx;
        break;
    }
    move(cy, cx);
    refresh();

  }

  delete gameWindow;
  delete infoWindow;
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
	getch();
	endwin();
	refresh();
}

void setDisplayRange(int herox, int heroy, int cols, int lines, int & xMax, int & xMin, int & yMax, int & yMin) {
  return;
}




