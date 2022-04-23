#ifndef INCLUDED_STRUCTURE_H
#define INCLUDED_STRUCTURE_H

#include "defines.h"

typedef struct Node
{
	void* data;
	struct Node* next;
	struct Node* prev;
} Node;

typedef struct
{
	char name[CHAR_NAME_MAX];
	char description[CHAR_DESC_MAX];
	Type type; // EQUIPEMENT // PIEGE // ITEM
	float price;
	double health;
	double attack;
	double defense;
	double speed;
} Item;

typedef struct
{
	char name[CHAR_NAME_MAX];
	Item weapon;
	Item armor;
	double health;
	double attack;
	double defense;
	double speed;
} Entity;

typedef struct
{
	int alt;
	float money;
} Score;

typedef struct
{
	int id;		//Lvl
	Node* monsters;
	Item treasure;		//hypothetic item function of search or not after fight
	int remain_searches; 	// ???
} Plateau;

typedef struct
{
	Node* team_player;
	Node* team_monster;
	Node* inventory;
	Node* shop;
	Score* highscore;
	Item treasure;		//hypothetic item function of search or not after fight
} GameState;

#endif
