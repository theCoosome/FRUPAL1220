#include <ncurses.h>
#include <string>
#include <vector>

#include "object.h"
#include "world.h"

using namespace std;

void drawValues(int splitPos, int whiffles, int energy, bool binocs, bool boat);
void drawTerr(int splitPos, grovnik * grov);
void drawInven(int splitPos, vector<tool*> inventory);
