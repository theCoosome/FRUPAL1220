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

void printCenter(WINDOW *window, int cols, int line, const char *toPrint);
void print_lose();
void setDisplayRange(int herox, int heroy, int cols, int lines, int & xMax, int & xMin, int & yMax, int & yMin);
void showGrov(WINDOW *window, int x, int y, grovnik* show);
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
  bool **fog = map.get_fog1();
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
  int gameCols = COLS * 3/4;
  int infoCols = COLS / 4;
  setDisplayRange(playerx, playery, gameCols, LINES, displayXMax, displayXMin, displayYMax, displayYMin);

  //create windows for display
  WINDOW* infoWindow = newwin(LINES, COLS/4, 0, COLS * 3/4);
  WINDOW* gameWindow = newwin(LINES, COLS * 3/4, 0, 0);

  //draw info window
  //border
  for (int i = 0; i < 128; i++) {
    mvwprintw(infoWindow, i, 0, "|");
  }

  //internal
  char *bino = (char*)"off";
  char *bote = (char*)"off";
  string temp = to_string(energy);
  const char *energy_balance = temp.c_str();
  string temp1 = to_string(whiffles);
  const char *whiffle_balance = temp1.c_str();
  printCenter(infoWindow, infoCols, 2, "Hero's Bag:");
  printCenter(infoWindow, infoCols, LINES - 13, "Whiffles:"); 
  printCenter(infoWindow, infoCols, LINES - 12, whiffle_balance); 
  printCenter(infoWindow, infoCols, LINES - 10, "Energy:"); 
  printCenter(infoWindow, infoCols, LINES - 9, energy_balance); 
  printCenter(infoWindow, infoCols, LINES - 7, "Binoculars:"); 
  printCenter(infoWindow, infoCols, LINES - 6, bino); 
  printCenter(infoWindow, infoCols, LINES - 4, "Boat:"); 
  printCenter(infoWindow, infoCols, LINES - 3, bote); 


  //initial clear fog around starting position
  map.clearfog_rad(playerx, playery, 1); 
  fog = map.get_fog1();

  /*/test prints
  string temp2 = to_string(displayXMax);
  const char *one = temp2.c_str();
  string temp3 = to_string(displayYMax);
  const char *two = temp3.c_str();
  string temp4 = to_string(playerx);
  const char *three = temp4.c_str();
  string temp5 = to_string(playery);
  const char *four = temp5.c_str();
  printCenter(infoWindow, infoCols, 4, one);
  printCenter(infoWindow, infoCols, 5, two);
  printCenter(infoWindow, infoCols, 6, three);
  printCenter(infoWindow, infoCols, 7, four);

  */

  //initial game draw
  for (int col = displayXMin; col <= displayXMax; col++) {
    for (int line = displayYMin; line <= displayYMax; line++) {
      if (fog[col][line] == 0) {
        mvwaddch(gameWindow, line, col, ' ');
      } else {
        showGrov(gameWindow, col, line, map.getAt(col, line));
      }
    }
  }
  wattron(gameWindow, COLOR_PAIR(HERO_PAIR));
  mvwaddch(gameWindow, playery, playerx, '@');
  wattroff(gameWindow, COLOR_PAIR(HERO_PAIR));
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
        if(cx != gameCols - 1)
          ++cx;
        break;
      case 'j': //move player left
        if (playerx > 0) {
          --playerx;
        }
        --energy;
        break;
      case 'l': //move player right
        if (playerx < 127) {
          ++playerx; 
        }
        --energy;
        break;
      case 'i': //move player up
        if (playery > 0) {
          --playery;
        }
        --energy;
        break;
      case 'k': //move player down
        if (playery < 127) {
          ++playery;
        }
        --energy;
        break;
    }
    
    setDisplayRange(playerx, playery, gameCols, LINES, displayXMax, displayXMin, displayYMax, displayYMin);
    /*
  string temp2 = to_string(displayXMin);
  const char *one = temp2.c_str();
  string temp3 = to_string(displayXMax);
  const char *two = temp3.c_str();
  string temp4 = to_string(displayYMin);
  const char *three = temp4.c_str();
  string temp5 = to_string(displayYMax);
  const char *four = temp5.c_str();
  printCenter(infoWindow, infoCols, 4, one);
  printCenter(infoWindow, infoCols, 5, two);
  printCenter(infoWindow, infoCols, 6, three);
  printCenter(infoWindow, infoCols, 7, four);
  */

    if (binoculars == true)
      map.clearfog_rad(playerx, playery, 2); 
    else 
      map.clearfog_rad(playerx, playery, 1); 
    fog = map.get_fog1();    
    for (int col = displayXMin; col <= displayXMax; col++) {
      for (int line = displayYMin; line <= displayYMax; line++) {
        if (fog[col][line] == 0) {
          mvwaddch(gameWindow, line, col, ' ');
        } else {
          showGrov(gameWindow, col, line, map.getAt(col, line));
        }
      }
    }
  wattron(gameWindow, COLOR_PAIR(HERO_PAIR));
  mvwaddch(gameWindow, playery, playerx, '@');
  wattroff(gameWindow, COLOR_PAIR(HERO_PAIR));
	refresh();
  wrefresh(gameWindow);
  wrefresh(infoWindow);
  move(cy, cx);

  }

  delwin(gameWindow);
  delwin(infoWindow);
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
  if (cols % 2 == 1) {
    xMax = herox + cols/2;
    xMin = herox - cols/2;
  } else {
    if (herox >= cols/2) {
      xMax = herox + cols/2 - 1;
      xMin = herox - cols/2;
    } else {
      xMax = herox + cols/2;
      xMin = herox - cols/2 +1;
    }
  } 

  if (lines % 2 == 1) {
    yMax = heroy + lines/2;
    yMin = heroy - lines/2;
  } else {
    if (heroy >= lines/2) {
      yMax = heroy + lines/2 - 1;
      yMin = heroy - lines/2;
    } else {
      yMax = heroy + lines/2;
      yMin = heroy - lines/2 +1;
    }
  } 

  if (xMin < 0) {
    int flip = xMin * -1;
    xMin = xMin + flip;
    xMax = xMax + flip;
  }
  if (xMax >= 128) {
    int flip = xMax - 127;
    xMax = xMax - flip;
    xMin = xMin - flip;
  }
  if (yMin < 0) {
    int flip = yMin * -1;
    yMin = yMin + flip;
    yMax = yMax + flip;
  }
  if (yMax >= 128) {
    int flip = yMax - 127;
    yMax = yMax - flip;
    yMin = xMin - flip;
  }
  return;
}

void printCenter(WINDOW *window, int cols, int line, const char *toPrint) {
  int length = strlen(toPrint);
  int printCol = ((cols - length) / 2) - 1;
  mvwprintw(window, line, printCol, toPrint);
}

void showGrov(WINDOW * window, int x, int y, grovnik* show) {
  char atpoint = ' ';
  if (show->poi) {
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
  wattron(window, COLOR_PAIR(show->terrain));
  mvwaddch(window, x, y, atpoint);
  wattroff(window, COLOR_PAIR(show->terrain));
}

