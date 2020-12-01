//Author of this file: Leah Moser
// This is the file that will be in charge of
//The split screen with stats





#include <ncurses.h>




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
	

	WINDOW *win = newwin(height, width, y_beg, x_beg);

	refresh();

	wborder(win, left, right, top, bottom, tl, tr, bl, br);
	mvprintw(2, (COLS-width/2)-7, "Bag Contents");
        mvprintw(LINES-10, (COLS-width/2)-7, "Whiffles: ");
	mvwaddch(win,LINES-10, (COLS-width/2)+20, char(whiffles));
	mvprintw(LINES-12, (COLS-width/2)-7, "Energy: ");
	mvwaddch(win,LINES-10, (COLS-width/2)+20, char(energy));



	wrefresh(win);

	move(y_max-1,x_max-1);
	refresh();
	getch();
	getch();
	endwin();

	return 0;
}


