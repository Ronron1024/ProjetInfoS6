#ifndef INCLUDED_STRUCTURE_H
#define INCLUDED_STRUCTURE_H

#include "defines.h"

typedef struct Node
{
	void* data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct Item
{
	char name[CHAR_NAME_MAX];
	char description[CHAR_DESC_MAX];
	Type type; 				// WEAPON // ARMOR // TRAP // ITEM
	int equipped;
	float price;
	double health;
	double attack;
	double defense;
	double speed;
} Item;

typedef struct Entity
{
	int id;				//Pour indentifier le membre dans une team
	char name[CHAR_NAME_MAX];
	Item weapon;
	Item armor;
	double health;
	double attack;
	double defense;
	double speed;
} Entity;

typedef struct Score
{
	int alt;
	float money;
} Score;

typedef struct Plateau
{
	int id;		//Lvl
	Node* monsters;
	Item treasure;		//hypothetic item function of search or not after fight
	int remain_searches; 	// ???
} Plateau;

typedef struct GameState
{
	Node* team_player;
	Node* team_monster;
	Node* inventory;
	Node* shop;
	Score* highscore;
	Item treasure;		//hypothetic item function of search or not after fight
	char save_file[CHAR_SAVE_MAX];
} GameState;

#endif
