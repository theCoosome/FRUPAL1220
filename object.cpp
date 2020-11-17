//Author of file  Leah Moser
//This is the implementation file for the object class
//This class is where the heirarchical relationship is and it will be 

#include "object.h"

object::object(): type(0), cost(0)
//default constructor sets all data members to their zero value
{


}


object::object(const object  &to_copy)
//copy constructor 
{
	
	type = to_copy.type;
	cost = to_copy.cost;
}



object::object(int add_type, int add_cost)
//constructor with arguments
{
	type = add_type;
	cost = add_cost;
}



void object::display()
//display function
{
	//this needs work
}


object::~object()
//destructor
{
}

food::food():name(NULL), value(0)
//default constructor
{

}


food::food(int add_type, int add_cost, char *add_name, int add_value):object(add_type, add_cost)
//constructor with arguments
{
	name  = new char[strlen(add_name)+1];
	strcpy(name, add_name);
	value = add_value;


}



food::food(const food &to_copy):object(to_copy)
//copy constructor
{
	name = new char[strlen(to_copy.name)+1];
	strcpy(name, to_copy.name);
	value = to_copy.value;
}


void food::display()
//display function
{
	object::display();
	//needs work
}


food::~food()
//destructor for the play area
{
	delete [] name;
	name = NULL;
}


tool::tool():name(NULL), power(0), obs_type(0)
//default constructor
{

}

tool::tool(int add_type, int add_cost, char *add_name, int add_power, int add_obstype):object(add_type, add_cost)
//constructor with args
{
	name = new char[strlen(add_name)+1];
	power = add_power;
	obs_type = add_obstype;
	
}

tool::tool(const tool &to_copy):object(to_copy)
//copy constructor
{
	name = new char[strlen(to_copy.name)+1];
	strcpy(name, to_copy.name);
	obs_type = to_copy.obs_type;
	power = to_copy.power;
}


void tool::display()
{
	object::display();
	//needs work 

}


tool::~tool()
{
	delete [] name;
	name = NULL;
}

treasure::treasure():is_empty(0)
//default constructor
{

}

treasure::treasure(int add_type, int add_cost, bool add_isempty):object(add_type, add_cost)
//constructor with arguments
{
	is_empty = add_isempty;
}

treasure::treasure(const treasure &to_copy):object(to_copy)
//copy constructor
{
	//this will probably be needed later when we add stuff to treasure
}


void treasure::display()
//display function
{
	object::display();
	//will need work
}

treasure::~treasure()
//destructor for the treasure
{
}

obstacle::obstacle():obs_type(0)
//default constructor
{

}


obstacle::obstacle(int add_obstype): object(add_type, add_cost)
//constructor with arguments
{
	obs_type = add_obstype;
}



obstacle::obstacle(const obstacle &to_copy):object(to_copy)
//copy constructor
{
	obs_type = to_copy.obs_type;
}


void obstacle::display()
//display function
{
	object::display();
	//will need work
}

obstacle::~obstacle()
//destructor for the obstacle
{
}

