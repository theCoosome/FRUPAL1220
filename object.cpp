//Author of file  Leah Moser
//This is the implementation file for the object class
//This class is where the heirarchical relationship is and it will be

#include "object.h"

object::object(): type(0), cost(0) {}

object::object(const object  &to_copy) {
	type = to_copy.type;
	cost = to_copy.cost;
}

object::object(int add_type, int add_cost) {
	type = add_type;
	cost = add_cost;
}

object::~object() {}

int object::get_type() {
	return type;
}

int object::get_cost() {
	return cost;
}

food * object::getFood() {
	if (type == 2)
		return dynamic_cast<food*>(this);
	return NULL;
}

tool * object::getTool() {
	if (type == 3)
		return dynamic_cast<tool*>(this);
	return NULL;
}

clue * object::getClue() {
	if (type == 4)
		return dynamic_cast<clue*>(this);
	return NULL;
}

obstacle * object::getObst() {
	if (type == 7)
		return dynamic_cast<obstacle*>(this);
	return NULL;
}

clue::clue():object(4, 0), hint(NULL) {}

clue::clue(char * data):object(4, 0) {
	hint = new char[strlen(data)+1];
	strcpy(hint, data);
}

clue::~clue() {
	if (hint) {
		delete [] hint;
	}
}

char * clue::getHint() {
	return hint;
}


food::food():object(0, 2), name(NULL), value(0) {}


food::food(int add_cost, char *add_name, int add_value):object(2, add_cost) {
	name  = new char[strlen(add_name)+1];
	strcpy(name, add_name);
	value = add_value;
}

food::food(const food &to_copy):object(to_copy) {
	name = new char[strlen(to_copy.name)+1];
	strcpy(name, to_copy.name);
	value = to_copy.value;
}

char* food::get_name() {
	return name;
}

int food::get_value() {
	return value;
}

food::~food() {
	if (name) {
		delete [] name;
	}
}


tool::tool():object(0, 3), name(NULL), power(0), obs_type(0) {}

tool::tool(int add_cost, char *add_name, int add_power, int add_obstype):object(3, add_cost) {
	name = new char[strlen(add_name)+1];
	power = add_power;
	obs_type = add_obstype;
}

tool::tool(const tool &to_copy):object(to_copy) {
	name = new char[strlen(to_copy.name)+1];
	strcpy(name, to_copy.name);
	obs_type = to_copy.obs_type;
	power = to_copy.power;
}

char* tool::get_t_name() {
	return name;
}

int tool::get_power() {
	return power;
}

int tool::get_obstype() {
	return obs_type;
}

tool::~tool() {
	if (name) {
		delete [] name;
	}
}

treasure::treasure():object(0, 1), is_empty(0) {}

treasure::treasure(int add_cost, bool add_isempty):object(1, add_cost) {
	is_empty = add_isempty;
}

bool treasure::get_empty() {
	return is_empty;
}

treasure::~treasure() {}

obstacle::obstacle():obs_type(0) {}

obstacle::obstacle(int add_cost, int add_obstype):object(7, add_cost) {
	obs_type = add_obstype;
}

obstacle::obstacle(const obstacle &to_copy):object(to_copy) {
	obs_type = to_copy.obs_type;
}


int obstacle::get_obstacle() {
	return obs_type;
}

obstacle::~obstacle() {}

