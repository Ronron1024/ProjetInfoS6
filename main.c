#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "includes/defines.h"
#include "includes/prototypes.h"

int main (){
	// Init random generation
	srand(time(NULL));

	#pragma region Declaration
	char log[CHAR_LOG_MAX] = {0};

	Node* team_player = NULL;
	Node* team_monster = NULL;

	Item nothing = {
		"Nothing",
		"Nothing",
		EQUIPMENT,
		0.0, 0, 0, 0, 0
	};

	Item sword = {
		"Sword",
		"Wooden sword",
		EQUIPMENT,
		10.0, 0, 3, 0, 0
	};
	Item plate = {
		"Plate",
		"Wooden plate",
		EQUIPMENT,
		15.0, 0, 0, 2, 0
	};

	Entity player1 = {
		"Gerem1",
		sword,
		plate,
		5, 1, 0, 0
	};

	Entity player2 = {
		"Gerem2",
		sword,
		nothing,
		5, 1, 0, 0
	};

	Entity player3 = {
		"Gerem3",
		nothing,
		nothing,
		5, 1, 0, 0
	};

	Entity monster1 = {
		"Monster1",
		nothing,
		nothing,
		10, 1, 1, 0
	};

	Entity monster2 = {
		"Monster2",
		nothing,
		plate,
		10, 1, 1, 0
	};

	push(&team_player, &player1, sizeof(Entity));
	push(&team_player, &player2, sizeof(Entity));
	push(&team_player, &player3, sizeof(Entity));
	
	push(&team_monster, &monster1, sizeof(Entity));
	push(&team_monster, &monster2, sizeof(Entity));
	#pragma endregion

	while (fight(&team_player, &team_monster, log))
	{
		printf("%s\n", log);
		//getchar();
	} printf("%s\n", log); // fight outcome

	return 0;
}

