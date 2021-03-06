#include <ncurses.h>
#include <vector>
#include <fstream>

//#include "object.h"
//#include "world.h"
#include "split.h"

//color definitions
#define MEADOW_PAIR 1
#define SWAMP_PAIR 2
#define WATER_PAIR 3
#define WALL_PAIR 4
#define DIAMOND_PAIR 5
#define HERO_PAIR 6

void print_lose();
void print_win();
void movecheck();

using namespace std;

void showGrov(int y, int x, grovnik * show) {
	if (x < 0 || y < 0 || x > 127 || y > 127) return;
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
			case 4: //clues
				atpoint = '?';
				break;
			case 5: //ship
				atpoint = 'S';
				break;
			case 6: //binoculars
				atpoint = 'B';
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
	mvaddch(y, x, atpoint);
	attroff(COLOR_PAIR(show -> terrain));
}

// Move player to y1/x1 depending on terrain and use POI @ y1/x1
// Sorry you have to pass all that by reference but it's out of scope
void move_player(int* playery, int* playerx, int y1, int x1, World* map, int* energy, int* whiffles, bool* binoculars, bool* boat, vector<tool*>* inventory, bool* diamond) {
	grovnik* check = map->getAt(y1, x1);
	switch (check->terrain) {
		case 1: //meadow
			*playery = y1;
			*playerx = x1;
			(*energy)--;
			break;
		case 2: //swamp
			*playery = y1;
			*playerx = x1;
			*energy -= 2;
			break;
		case 3: //water
			if (*boat) {
				*playery = y1;
				*playerx = x1;
				break;
			}
			if(*boat)
			  (*energy)--; //don't want energy to go down if cant move
			break;
		case 4: //wall
			//(*energy)--; //dont want energy to go down if cant move
			break;
		case 5: //diamond
			*playery = y1;
			*playerx = x1;
			*diamond = true;
			break;
	}
	if (!check->poi) {
		return;
	}
	int objType = check->poi->get_type();
	if (objType == 1) { //treasure
		*whiffles += check->poi->get_cost();
		map->clearPOI(y1, x1);
	} else if (objType == 2) { //food
		food* foundFood = check->poi->getFood();
		if (*whiffles >= foundFood->get_cost()) {
			*whiffles -= foundFood->get_cost();
			*energy += foundFood->get_value();
			map->clearPOI(y1, x1);
		}
	} else if (objType == 3) { //tools
		tool* foundTool = check->poi->getTool();
		if (*whiffles >= foundTool->get_cost()) {
			*whiffles -= foundTool->get_cost();
			map->clearPOI(y1, x1);
			inventory->push_back(foundTool);
		}
	} else if (objType == 4) { //clues
		char * hint;
		clue * get_clue = check->poi->getClue();
		mvprintw(15, 119, "                                       "); // clears text for next use
		mvprintw(15, 119, "You found a clue!");
		hint = new char[strlen(get_clue->getHint()) + 1];
		strcpy(hint, get_clue->getHint());

		// displaying the clue close to where the player is
		move(*playery + 5, *playerx + 5);
		printw("The clue is: %s", hint);
		refresh();
		//deleting text
		mvprintw(16, 119, "Press any key to continue!");
		getch();
		mvprintw(16, 119, "                          ");
		refresh();
		for(unsigned int x = 0; x < strlen("The clue is: ") + strlen(hint); x++) {
			if(map->getfog(*playery + 5, *playerx + 5 + x)) {
				showGrov(*playery + 5, *playerx + 5 + x, map->getAt(*playery + 5, *playerx + 5 + x));
			} else {
				mvaddch(*playery + 5, *playerx + 5 + x, ' ');
			}
		}
		delete [] hint;
		*energy += 1; // fixed where it would take an energy when you pressed button to continue
		map->clearPOI(y1, x1);

	} else if (objType == 5) { //ship
		char answer;
		mvprintw(15, 119, "                                       "); // clears text for next use
		mvprintw(15, 119, "You have found a boat!");
		mvprintw(16, 119, "Would you like to purchase it?");
		mvprintw(17, 119, "Cost: 200 Whiffles");
		mvprintw(18, 119, "Press y or n: ");
		refresh();
		answer = getchar();
		// clearing text
		mvprintw(15, 119, "                                   ");
		mvprintw(16, 119, "                                   ");
		mvprintw(17, 119, "                                   ");
		mvprintw(18, 119, "                                   ");
		if(answer == 'y' || answer == 'Y')
		{
			if (*whiffles >= check->poi->get_cost()) {
				mvprintw(15, 119, "You purchased the boat!");
				*whiffles -= check->poi->get_cost();
				map->clearPOI(y1, x1);
				*boat = true;
			}
			else
				mvprintw(15, 119, "Error! Could not purchase!");
		}
		else
			mvprintw(15, 119, "You did not purchase the boat!");
	} else if (objType == 6) { //binoculars
		char answer;
		mvprintw(15, 119, "                                       "); // clears text for next use
		mvprintw(15, 119, "You have found some binoculars!");
		mvprintw(16, 119, "Would you like to purchase them?");
		mvprintw(17, 119, "Cost: 50 Whiffles");
		mvprintw(18, 119, "Press y or n: ");
		refresh();
		answer = getchar();
		// clearing text
		mvprintw(15, 119, "                                   ");
		mvprintw(16, 119, "                                   ");
		mvprintw(17, 119, "                                   ");
		mvprintw(18, 119, "                                   ");
		if(answer == 'y' || answer == 'Y')
		{
			if (*whiffles >= check->poi->get_cost()) {
				mvprintw(15, 119, "You purchased the binoculars!");
				*whiffles -= check->poi->get_cost();
				map->clearPOI(y1, x1);
				*binoculars = true;
			}
			else
				mvprintw(15, 119, "Error! Could not purchase!");
		}
		else
			mvprintw(15, 119, "You did not purchase the binoculars!");


	} else { //obsticles

		// TODO

	}
}

int main() {
	initscr();
	keypad(stdscr, true);
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
	char ** obstypes = map.fileRead(heroy, herox);

	bool running = true; // program running conditional

	// player variables
	int energy = 100;
	int whiffles = 1000;
	bool binoculars = false;
	bool boat = false;
	vector<tool*> inventory;
	bool diamond = false;

	// cursor position
	int cx = 0;
	int cy = 0;
	int playerx = *herox;
	int playery = *heroy;
	delete herox;
	delete heroy;


	// set values, due to possibility of changing viewport
	int Cols = COLS;
	int Rows = LINES;
	int splitPos = min(128, Cols * 3 / 4);


	map.clearfog_rad(playery, playerx, 1);
	// Clear map for debugging file reader
	//map.clearfog_rad(0, 0, 128);

	// Initial world draw
	for (int y = 0; y < 128; y++) {
		for (int x = 0; x < Cols * 3/4; x++) {
			if(map.getfog(y, x)) {
				showGrov(y, x, map.getAt(y, x));
			} else {
				mvaddch(y, x, ' ');
			}
		}
	}

	// Initial hero display
	attron(COLOR_PAIR(6));
	mvaddch(playery, playerx, '@');
	attroff(COLOR_PAIR(6));

	//Draw the splitscreen split
	mvvline(0, splitPos, '|', Rows);
	drawValues(splitPos, whiffles, energy, binoculars, boat);
	if (map.getfog(cy, cx)) {
		drawTerr(splitPos, map.getAt(cy, cx), obstypes);
	} else {
		drawTerr(splitPos, NULL, obstypes);
	}

	//drawsplit(whiffles, energy, binoculars, boat, map.getAt(cy, cx), inventory);

	while (running) {

		int ch = getch();

		// User input
		switch(ch) {

			case 'q': //press q to quit
				running = false;
				break;

			//Player movement
			case 'w': //move player up
				if (playery) {
					move_player(&playery, &playerx, playery - 1, playerx, &map, &energy, &whiffles, &binoculars, &boat, &inventory, &diamond);
				}
				break;
			case 's': //move player down
				if (playery < 128) {
					move_player(&playery, &playerx, playery + 1, playerx, &map, &energy, &whiffles, &binoculars, &boat, &inventory, &diamond);
				}
				break;
			case 'a': //move player left
				if (playerx) {
					move_player(&playery, &playerx, playery, playerx - 1, &map, &energy, &whiffles, &binoculars, &boat, &inventory, &diamond);
				}
				break;
			case 'd': //move player right
				if (playerx < 128) {
					move_player(&playery, &playerx, playery, playerx + 1, &map, &energy, &whiffles, &binoculars, &boat, &inventory, &diamond);
				}
				break;

			case 'c':
				map.clearfog_rad(64, 64, 65);
				for (int y = 0; y < 128; y++) {
					for (int x = 0; x < Cols * 3/4; x++) {
						showGrov(y, x, map.getAt(y, x));
					}
				}
				break;

			// Cursor movement
			case KEY_UP: //move up
				if(cy) {
					--cy;
				}
				break;
			case KEY_DOWN: //move down
				if(cy < Rows - 1) {
					++cy;
				}
				break;
			case KEY_LEFT: //move left
				if(cx) {
					--cx;
				}
				break;
			case KEY_RIGHT: //move right
				if(cx < Cols - 1) {
					++cx;
				}
				break;
			default:
				break;
		}

		//Player movement post-draw
		if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd') {
			showGrov(playery, playerx, map.getAt(playery, playerx));

			int radius;
			if(binoculars) {
				map.clearfog_rad(playery, playerx, 2);
				radius = 2;
			} else {
				map.clearfog_rad(playery, playerx, 1);
				radius = 1;
			}
			for(int y = playery - radius; y <= playery + radius; y++) {
				for(int x = playerx - radius; x <= playerx + radius; x++) {
					showGrov(y, x, map.getAt(y, x));
				}
			}

			// hero display post-move
			attron(COLOR_PAIR(6));
			mvaddch(playery, playerx, '@');
			attroff(COLOR_PAIR(6));
		}

		// If the user types something, draw over it
		if (ch != -1) {
			if (cx < splitPos){ // Redraw map info
				if(map.getfog(cy, cx)) {
					showGrov(cy, cx, map.getAt(cy, cx));
				} else {
					mvaddch(cy, cx, ' ');
				}
				// hero display. In case you typed over it
				attron(COLOR_PAIR(6));
				mvaddch(playery, playerx, '@');
				attroff(COLOR_PAIR(6));
			}
			if (cx == splitPos) { //Redraw the screen split
				mvaddch(cy, splitPos, '|');
			}
			if (cx > splitPos){ // Redraw splitscreen blank background
				mvaddch(cy, cx, ' ');
			}
		}


		drawValues(splitPos, whiffles, energy, binoculars, boat);
		if (map.getfog(cy, cx)) {
			drawTerr(splitPos, map.getAt(cy, cx), obstypes);
		} else {
			drawTerr(splitPos, NULL, obstypes);
		}
		//After the mvaddch, because they move the cursor as well
		move(cy, cx);

		if(energy <= 0)
			running = false;
		if(diamond)
			running = false;

		refresh();
	}

	if(energy <= 0)
		print_lose();
	if(diamond)
		print_win();

	// obstypes de-allocation
	for (int i=0; i < 10; ++i) {
		delete[] obstypes[i];
	}
	delete[] obstypes;

	return endwin();
}

void print_lose()
{
	beep();
	flash();
	wrefresh(stdscr);
	initscr();
	noecho();
	mvprintw((LINES/2), (COLS/2)-8, "YOU LOSE");
	move(0,0);
	refresh();
	getch();
	endwin();
	refresh();
}

void print_win()
{
	beep();
	flash();
	wrefresh(stdscr);
	initscr();
	noecho();
	mvprintw((LINES/2), (COLS/2)-8, "YOU WIN");
	move(0,0);
	refresh();
	getch();
	endwin();
	refresh();
}

