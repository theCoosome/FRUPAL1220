//Author of this file: Leah Moser
// This is the file that will be in charge of
//The split screen with stats





#include <ncurses.h>
#include <string>


using namespace std;

int mainle(int whiffles, int energy)
{
	initscr();
	int y_beg, x_beg;
	int x_max, y_max;
	int height, width;
	height = LINES -1;
	y_beg = 0;
	width = COLS/4;
	x_beg = COLS - width;
	getmaxyx(stdscr, y_max, x_max);
	int left, right, top, bottom, tl, tr, bl, br;
	left = right = 0;
	top = bottom = tl = tr = bl = br = 95;
	string tmp = to_string(whiffles);
    	char const *to_add = tmp.c_str();
	string temp = to_string(energy);
    	char const *to_add2 = tmp.c_str();



	

	WINDOW *win = newwin(height, width, y_beg, x_beg);

	refresh();

	wborder(win, left, right, top, bottom, tl, tr, bl, br);
	mvprintw(2, (COLS-width/2)-7, "Bag Contents");
        mvprintw(LINES-13, (COLS-width/2)-7, "Whiffles: ");
	mvprintw(LINES-12, (COLS-width/2)-7, to_add);
	mvprintw(LINES-11, (COLS-width/2)-7, "Energy: ");
	mvprintw(LINES-10, (COLS-width/2)-7, to_add2);



	wrefresh(win);

	move(y_max-1,x_max-1);
	refresh();
	getch();
	getch();
	endwin();

	return 0;
}


