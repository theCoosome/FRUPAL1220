#include <ncurses.h>
using namespace std;


int main() {
    initscr();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    clear();

    //initialize variables

    bool running = true; // program running conditional

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
          case 113: // q
            //press q to quit
            running = false;
            break;
        }

        refresh();

    }

    return endwin();
}







