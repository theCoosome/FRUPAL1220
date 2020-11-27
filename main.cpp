#include <ncurses.h>
#include <vector>
#include <fstream>

#include "object.h"
#include "world.h"

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

    bool running = true; // program running conditional

    // player variables
    int energy = 100;
    int whiffles = 1000;
    bool binoculars = false;
    bool boat = false;
    // vector<object> inventory;


    // test world
    World testWorld = World();
    for (int i = 0; i < 128; i++) {
      for (int j = 0; j < 128; j++) {
        testWorld.setGrovnik(i, j, 0, nullptr); 
        attron(COLOR_PAIR(MEADOW_PAIR));
        mvaddch(i, j, ' ');
        attroff(COLOR_PAIR(MEADOW_PAIR));
      }
    }
    
    refresh(); 
    // cursor position
    int cx = 2;
    int cy = 2;

    // set values, due to possibility of changing viewport
    int Cols = COLS;
    int Rows = LINES;


    while (running) {
        int ch = getch();

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
        }

        refresh();

    }

    return endwin();
}







