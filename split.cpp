//Author of this file: Leah Moser
// This is the file that will be in charge of
//The split screen with stats





#include <ncurses.h>
#include <string>


using namespace std;

int drawsplit(int whiffles, int energy, bool binocs, bool boat)
{
	initscr();
	//the begining of arugument declarations 
	int y_beg, x_beg;
	int x_max, y_max;
	int height, width;
	height = LINES;
	y_beg = 0;
	width = COLS/4;
	x_beg = COLS - width;
	getmaxyx(stdscr, y_max, x_max);
	int left, right, top, bottom, tl, tr, bl, br;
	left = right = 0;
	top = bottom = 32;
	tl = tr = 42;
	bl = br = 42;
	const char *bino = "off";
	const char *bote = "off";
	//conversion from integers to chars for window print
	string tmp = to_string(whiffles);
    	char const *to_add = tmp.c_str();
	string temp = to_string(energy);
    	char const *to_add2 = tmp.c_str();
	if(binocs == true)
	{
		bino = "on";
	}
	if(boat == true)
	{
		bote = "on";
	}

	WINDOW *win = newwin(height, width, y_beg, x_beg);

	refresh();

	//split display print

	wborder(win, left, right, top, bottom, tl, tr, bl, br);
	mvprintw(2, (COLS-width/2)-7, "Bag Contents");
        mvprintw(LINES-13, (COLS-width/2)-7, "Whiffles: ");
	mvprintw(LINES-12, (COLS-width/2)-7, to_add);
	mvprintw(LINES-10, (COLS-width/2)-7, "Energy: ");
	mvprintw(LINES-9, (COLS-width/2)-7, to_add2);
	mvprintw(LINES-7, (COLS-width/2)-7, "Binoculars: ");
	mvprintw(LINES-6, (COLS-width/2)-7, bino);
	mvprintw(LINES-4, (COLS-width/2)-7, "Boat: ");
	mvprintw(LINES-3, (COLS-width/2)-7, bote);

	wrefresh(win);

//	endwin();
	

	return 0;
}


