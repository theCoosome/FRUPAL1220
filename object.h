#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>

#ifndef OBJECT_H
#define OBJECT_H

using namespace std;

class food;
class tool;
class clue;
class obstacle;

class object {
	public:
	object(); //default constructor
	object(const object & to_copy); //copy constructor
	object(int add_type, int add_cost); //constructor with args
	virtual ~object();//destructor
	int get_type();
	int get_cost();

	//type 2
	food * getFood();

	//type 3
	tool * getTool();

	//type 4
	clue * getClue();

	//type 7
	obstacle * getObst();

	protected:
	int type;
	int cost; //How much this object costs

};


class food: public object {
	public:
	food(); //default constructor
	food(int add_cost, char *add_name, int value); //constuctor with args
	food(const food &to_copy); //copy constructor
	~food(); //destructor
	char*  get_name();
	int get_value();

	protected:
	char *name; //The name of the food
	int value; //How much energy is restored
};


class tool: public object {
	public:
    tool(); 
    tool(int add_cost, char *add_name, int add_power, int obs_type);
    tool(const tool &to_copy);
    ~tool(); 

    int get_obstype();
    int get_power();
    char* get_t_name();

	protected:
    char *name; 
    int power; 
    int obs_type;
};


class treasure: public object {
	public:
    treasure(); 
    treasure(int add_cost, bool isempty);
    treasure(const treasure &to_copy); 
    ~treasure(); 

    bool get_empty();

	protected:
    bool is_empty;
};


class obstacle: public object {
	public:
    obstacle();
    obstacle(int add_cost, int obs_type);
    obstacle(const obstacle &to_copy);
    ~obstacle(); 
    int get_obstacle();

	protected:
    //cost repurposed to durability
    int obs_type;
};


class clue: public object {
	public:
    clue();
    clue(char * data);
    ~clue();
    char * getHint();

	protected:
    char * hint;
};

#endif

