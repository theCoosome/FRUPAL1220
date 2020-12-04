//Author of this file: Leah Moser
// This is the file that will be in charge of
//The split screen with stats






#include "split.h"

int drawsplit(int whiffles, int energy, bool binocs, bool boat)
{
	//initscr();
	//the begining of arugument declarations
	int x = COLS*3/4;
	int y = 0;
	while(y != LINES)
	{
		mvaddch(y,x, '|');
		++y;
	}
/*
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
*/
	char *bino = (char*)"off";
	char *bote = (char*)"off";
	//conversion from integers to chars for window print
	if(binocs == true)
	{
		bino = (char*)"on";
	}
	if(boat == true)
	{
		bote = (char*)"on";
	}

//	WINDOW *win = newwin(height, width, y_beg, x_beg);
//	refresh();

	//split display print

//	wborder(win, left, right, top, bottom, tl, tr, bl, br);
	int x_beg = x;
	mvprintw(2, x_beg+6, "Hero");
        mvprintw(LINES-13, x_beg+3, "Whiffles: ");
	mvprintw(LINES-12, x_beg+3, "%-4d", whiffles);
	mvprintw(LINES-10, x_beg+3, "Energy: ");
	mvprintw(LINES-9, x_beg+3, "%-3d", energy);
	mvprintw(LINES-7, x_beg+3, "Binoculars: ");
	mvprintw(LINES-6, x_beg+3, bino);
	mvprintw(LINES-4, x_beg+3, "Boat: ");
	mvprintw(LINES-3, x_beg+3, bote);
//COLS*3/4-7

//	wrefresh(win);

	//endwin();


	return 0;
}


