//Author of header: Leah Moser
//Program: Frupal Game 
//Date: 11/10/20
//This is the header file for the heirarchical relationship portion 
//of the program. This file holds all the prototypes for the funcitonality of the
//implementation file. 
//Note to the group: Please feel free to change anything you see might need 
//changing 



#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <stdio.h>
#include <stdlib.h>

#ifndef OBJECT_H
#define OBJECT_H 

using namespace std;


class object
{
	public:
	object(); //default constructor
	object(const object & to_copy); //copy constructor
	object(int add_type, int add_cost); //constructor with args
	virtual ~object();//destructor
	virtual void display(); //display for the base clas

	protected:
	int type;
	int cost; //How much this object costs

};


class food: public object
{
	public:
	food(); //default constructor
	food(int add_type, int add_cost, char *add_name, int value); //constuctor with args
	food(const food &to_copy); //copy constructor
	~food(); //destructor
	void display();

	protected:
	char *name; //The name of the food
	int value; //How much energy is restored

};


class tool: public object
{
	public:
	tool(); //default constructor
	//constructor with args
	tool(int add_type, int add_cost, char *add_name, int add_power, int obs_type); 
	tool(const tool &to_copy);
	void display(); //display function
	~tool(); //destrucor

	protected:
	char *name; //The name of the tool
	int power; //how much power it has?
	int obs_type; // What type(s?) of obsticles this is useful for

};


class treasure: public object
{
	public:
	treasure(); //default constructor
	//constructor with args
	treasure(int add_type, int add_cost, bool add_isempty); 
	treasure(const treasure &to_copy); //copy constructor
	~treasure(); // destructor
	void display();

	protected:
	bool is_empty; //will it dissapear when empty?
	//Treasure chests appear to be defined to only contain whiffles.
	//Cost is repurposed to how much money you gain when opened.

};


class obstacle: public object
{
	public:
	obstacle(); //default constructor
	//constructor with args
	obstacle(int add_type, int add_cost, int obs_type);
	obstacle(const obstacle &to_copy); //copy constructor
	~obstacle(); // destructor
	void display();

	protected:
	//Cost is repurposed into Durability, or Cost to destroy
	int obs_type; // The obsticle type

};

#endif



