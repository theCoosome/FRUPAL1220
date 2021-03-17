//Author of this file: Leah Moser
// This is the file that will be in charge of
//The split screen with stats


#include "split.h"

void printInCenter(int startingColumns, int columns, int line, const char * phraseToPrint) {
  int lengthOfPhrase = strlen(phraseToPrint);
  int printColumnStart = ((columns - lengthOfPhrase) / 2) + startingColumns;
  mvprintw(line, printColumnStart, phraseToPrint);
}

void drawValues(int x_beg, int whiffles, int energy, bool binoculars, bool boat) {
	char *binocularString = (char*)"off";
	char *boatString = (char*)"off";

	if (binoculars == true)	{
		binocularString = (char*)"on ";
	}
  if (boat == true) {
		boatString = (char*)"on ";
	}

  printInCenter(x_beg, COLS/4, 2, "Hero of Frupal");
	mvprintw(LINES-13, x_beg+3, "Whiffles: ");
	mvprintw(LINES-12, x_beg+3, "%-4d", whiffles);
	mvprintw(LINES-10, x_beg+3, "Energy: ");
	mvprintw(LINES-9, x_beg+3, "%-3d", energy);
	mvprintw(LINES-7, x_beg+3, "Binoculars: ");
	mvprintw(LINES-6, x_beg+3, binocularString);
	mvprintw(LINES-4, x_beg+3, "Ship: ");
	mvprintw(LINES-3, x_beg+3, boatString);

}

void drawTerr(int x_beg, Grovnik * grovnik, char ** obstacleTypes) {


  //grovnik info under cursor
	char * terrainType;
	if(grovnik) {
	  switch (grovnik->terrain) {
	    case 1: 
	      terrainType = (char*)"Meadow";
	      break;
	    case 2: 
	      terrainType = (char*)"Swamp";
	      break;
	    case 3: 
	      terrainType = (char*)"Water";
	      break;
	    case 4: 
	      terrainType = (char*)"Wall";
	      break;
	    default:
	      terrainType = (char*)"Unknown";
	      break;
	  }
	} else {
		terrainType = (char*)"Unknown";
	}

	mvprintw(4, x_beg+3, "Terrain:");
	//predraw to clear for terrain
	clearPrint(5, x_beg+3);
	mvprintw(5, x_beg+3, terrainType);
	mvprintw(7, x_beg+3, "Grovnik Info:");
  clearPrint(8, x_beg+3);
	clearPrint(9, x_beg+3);
	clearPrint(10, x_beg+3);
	if (grovnik) {
		object * temp = grovnik -> pointOfInterest;
		if(temp) {
			switch (temp -> get_type()) {
			 case 1: { // Treasure. show "treasure"
				mvprintw(8, x_beg+3, "Treasure");
				break;
			 }
			 case 2: { // Food. Show name & cost
				clearPrint(8, x_beg+3);
				mvprintw(8, x_beg+3, "Food:");
				food *print_food = temp->getFood();
				mvprintw(8, x_beg+3, print_food->get_name());

				clearPrint(9, x_beg+3);
				mvprintw(9, x_beg+3, "Cost:");
				mvprintw(9, x_beg+10, "%-3d", temp->get_cost());
				break;
			 }
			 case 3: { // Tool. show name, cost, effectiveness
				tool *print_tool = temp->getTool();
				clearPrint(8, x_beg+3);
				mvprintw(8, x_beg+3, "Tool:  ");
				mvprintw(8, x_beg+10, print_tool -> get_t_name());

				clearPrint(9, x_beg+3);
				mvprintw(9, x_beg+3, "Effective on ");
				mvprintw(9, x_beg+16, obstacleTypes[print_tool -> get_obstype()]);

				clearPrint(10, x_beg+3);
				mvprintw(10, x_beg+3, "Cost:  ");
				mvprintw(10, x_beg+10, "%-3d", temp->get_cost());
				//mvprintw(9, x_beg+3, p_tool);
				break;
			 }
			 case 4: { // clue. Leave clues behind and show info whenever
				clearPrint(8, x_beg+3);
				mvprintw(8, x_beg+3, "Clue");
				//Print the clue?
				break;
			 }
			 case 5: { // ship. Display cost
				clearPrint(8, x_beg+3);
				mvprintw(8, x_beg+3, "Ship");

				clearPrint(9, x_beg+3);
				mvprintw(9, x_beg+3, "Cost:  ");
				mvprintw(9, x_beg+10, "%-3d", temp->get_cost());
				break;
			 }
			 case 6: { // binoculars. show cost
				clearPrint(8, x_beg+3);
				mvprintw(8, x_beg+3, "Binoculars");

				clearPrint(9, x_beg+3);
				mvprintw(9, x_beg+3, "Cost:  ");
				mvprintw(9, x_beg+10, "%-3d", temp->get_cost());
				break;
			 }
			 case 7: { // obstacle. Display type
			 	clearPrint(8, x_beg+3);
				mvprintw(8, x_beg+3, "Obstacle:");
				mvprintw(8, x_beg+13, obstacleTypes[temp->getObst()->get_obstacle()]);

				clearPrint(9, x_beg+3);
				mvprintw(9, x_beg+3, "Energy required: ");
				mvprintw(9, x_beg+22, "%-3d", temp -> get_cost());
				break;
			 }
			}
		}
	}

}

void clearPrint(int where, int spot)
{
	mvprintw(where, spot, "                                    ");
}


