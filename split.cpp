//Author of this file: Leah Moser
// This is the file that will be in charge of
//The split screen with stats






#include "split.h"
void printCenter(int startingCols, int cols, int line, const char *toPrint) {
  int length = strlen(toPrint);
  int printCol = ((cols - length) / 2) + startingCols;
  mvprintw(line, printCol, toPrint);
  return;
}

void drawValues(int x_beg, int whiffles, int energy, bool binocs, bool boat) {

	char *bino = (char*)"off";
	char *bote = (char*)"off";
	//conversion from integers to chars for window print
	if(binocs == true)
	{
		bino = (char*)"on ";
	}
	if(boat == true)
	{
		bote = (char*)"on ";
	}

	//mvprintw(2, x_beg+8, "Hero");
  printCenter(x_beg, COLS/4, 2, "Hero");
	mvprintw(LINES-13, x_beg+3, "Whiffles: ");
	mvprintw(LINES-12, x_beg+3, "%-4d", whiffles);
	mvprintw(LINES-10, x_beg+3, "Energy: ");
	mvprintw(LINES-9, x_beg+3, "%-3d", energy);
	mvprintw(LINES-7, x_beg+3, "Binoculars: ");
	mvprintw(LINES-6, x_beg+3, bino);
	mvprintw(LINES-4, x_beg+3, "Boat: ");
	mvprintw(LINES-3, x_beg+3, bote);

}

void drawTerr(int x_beg, grovnik * grov) {


  //grovnik info under cursor
	char * terrType;
	if(grov) {
	  switch (grov->terrain) {
	    case 1: //meadow
	      terrType = (char*)"Meadow";
	      break;
	    case 2: //swamp
	      terrType = (char*)"Swamp";
	      break;
	    case 3: //water
	      terrType = (char*)"Water";
	      break;
	    case 4: //wall
	      terrType = (char*)"Wall";
	      break;
	    default:
	      terrType = (char*)"Unknown";
	      break;
	  }
	} else {
		terrType = (char*)"Unknown";
	}

  mvprintw(4, x_beg+3, "Terrain:");
  //predraw to clear for terrain
  mvprintw(5, x_beg+3, "                  ");
  mvprintw(5, x_beg+3, terrType);
  

  mvprintw(7, x_beg+3, "Grovnik Info:");

}

void drawInven(int x_beg, vector<tool*> inventory)
{
	return;
}


