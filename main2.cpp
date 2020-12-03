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
/*
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
*/

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

  while (running) {
    int ch = getch();
    getyx(stdscr, cy, cx);
    switch (ch) {
      case 'q': // quit
        running = false;
        break;
      //cursor movement
      case KEY_UP:
        if (cy)
          --cy;
        break;
      case KEY_DOWN:
        if (cy != LINES - 1)
          ++cy;
        break;
      case KEY_LEFT:
        if (cx)
          --cx;
        break;
      case KEY_RIGHT:
        //TODO: update to stop cursor at border of split
        if (cx != COLS - 1)
          ++cx;
        break;
    }
    move(cy, cx); //move cursor
    refresh();
  }
/*
	// Initial world draw
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			showGrov(i ,j, map.getAt(i, j));
		}
	}
	drawsplit(whiffles, energy, binoculars, boat);

	attron(COLOR_PAIR(6));
	mvaddch(playerx, playery, '@');
	attroff(COLOR_PAIR(6));

	refresh();



	// set values, due to possibility of changing viewport
//	int Cols = COLS;
//	int Rows = LINES;

	while (running) {
		int ch = getch();
		getyx(stdscr, cy, cx);
		// Redraw if the user has given a key input
		// A key input is likely to draw something on screen.
		if(energy <= 0)
		{
			break;
		}
		if (ch != -1) {
			move(cy, cx);
			showGrov(cy, cx, map.getAt(cy, cx));
			// hero display
		}

		// User input, always considered
		switch (ch) {
		  case 'q': //press q to quit
			  running = false;
				break;
      case 'l'://moves player left
        if (playerx ==  0) {
          playerx = 0;
        } 
        --energy;
        ++playerx;
        break;
      case 'j'://move play right
        if (playerx ==  COLS-1) {
          playerx = COLS-1;
        } 
        --energy;
        --playerx;
        break;
      case 'i': //move player up
        if (playery ==  0) {
          playery = 0;
        } 
        --energy;
        --playery;
        break;
      case 'm': //move player down
        if (playery ==  LINES - 1) {
          playery = LINES -1;
        } 
            --energy;
        ++playery;
        break;
      default:
        break;
      }

		  drawsplit(whiffles, energy, binoculars, boat);
      attron(COLOR_PAIR(6));
	    mvaddch(playery, playerx, '@');
	    attroff(COLOR_PAIR(6));
		    


		  nodelay(stdscr, FALSE);
		  switch(ch)
			{
				case KEY_UP: //move up
					if(cy)
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
					if(cx)
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
					running = false;
					break;
				default:
					break;
			}
			move(cy,cx);//move the cursor
		}

		refresh();
		if(energy <= 0)
		  print_lose();

*/
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





