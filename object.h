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
	object(char *add_type, int add_cost); //constructor with args
	virtual ~object();//destructor
	virtual void display(); //display for the base clas

	protected:
	char *type; //may want to be changed to an intiger, given only 4 types
	int cost;

};


class food: public object
{
	public:
	food(); //default constructor
	food(char *add_type, int add_cost, char *add_name, int value); //constuctor with args
	food(const food &to_copy); //copy constructor
	~food(); //destructor
	void display();

	protected:
	char *name;
	int value;

};


class tool: public object
{
	public:
	tool(); //default constructor
	//constructor with args
	tool(char *add_type, int add_cost, char *add_name, int add_power); 
	tool(const tool &to_copy);
	void display(); //display function
	~tool(); //destrucor

	protected:
	char *name;
	int power;//how much power it has?

};


class treasure: public object
{
	public:
	treasure(); //default constructor
	//constructor with args
	treasure(char *add_type, int add_cost, char *add_name, bool is_empty); 
	treasure(const treasure &to_copy); //copy constructor
	~treasure(); // destructor
	void display();

	protected:
	bool is_empty; //will it dissapear when empty?
	int value; // Treasure chests appear to be defined to only contain whiffles.

};


class obstacle: public object
{
	public:
	obstacle(); //default constructor
	//constructor with args
	obstacle(char *add_type, int add_cost, char *add_name, int add_b_amount);
	obstacle(const obstacle &to_copy); //copy constructor
	~obstacle(); // destructor
	void display();

	protected:
	int b_amount; //how much to break it?

};

#endif



