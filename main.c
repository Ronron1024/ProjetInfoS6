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

	// Game variables initialization
	GameStatus game_status = RAS;
	GameMode gamemode = GAMEMODE_PLAY;
	Node* run = NULL;
	GameState gamestate;
	initGameState(&gamestate);	// Prevent segmentation faults

	Item sweat = {
		"Sweat",
		"Un sweat a capuche, style hacker sombre",
		ARMOR,
		0,
		10.0,
		0.0,
		0.0,
		0.0,
		0.0
	};

	Item vodka = {
		"Vodka",
		"Ma plus fidele amie",
		ITEM,
		0,
		0.0, 5.0, 0.0, -1, 0
	};

	push(&gamestate.inventory, &sweat, sizeof(Item));
	push(&gamestate.inventory, &vodka, sizeof(Item));

	Entity player = {
		1,	//id
		"Gerem",
		getNullItem(), getNullItem(),
		100,100,100,0
	};

	// Init ncurses
	initscr();
	cbreak();
	keypad(stdscr, TRUE); // Enable FN Keys reading
	noecho();

	start_color();
    init_pair(PAIR_YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
    init_pair(PAIR_RED_CYAN, COLOR_RED, COLOR_CYAN);
    init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_WHITE_RED, COLOR_WHITE, COLOR_RED);

	// Intro
	splashscreen();
    getch();
	HOMEMENU:
    gamemode = homeMenu();

	// Load or create game
	switch (gamemode)
    {
        case GAMEMODE_PLAY: // New game
			push(&gamestate.team_player, &player, sizeof(Entity));

			initShop(&gamestate.shop);

			Score score = { 0, BASE_MONEY };
			gamestate.highscore = &score;

			// Intro
			intro();

			// First level
			generateNextPlateau(&run);				
			updateGamestate(run, &gamestate);
            break;

        case GAMEMODE_CONTINUE:
			strcpy(gamestate.save_file, menuContinue());
			if (strcmp(gamestate.save_file, "") == 0)
				goto HOMEMENU; // Oups ...
			loadGame(&run, &gamestate);
            break;
        case GAMEMODE_DEBUG:
			// To be implemented
            break;
    }

	// Game manager
	resetLogs();
	//recup le status de fenetre plateau
	while (game_status != QUIT && game_status != GAMEOVER)
	{
		game_status = fenetrePlateau(&gamestate);
		switch ( game_status )
		{
			case RAS:	// Nothing to do here
				break;

			case PLAYING:	// Next level
				generateNextPlateau(&run);
				rewardPlayer(gamestate.highscore, getPlateau(run)->id);
				upgradeShop(&gamestate.shop, getPlateau(run)->id);
				story(getPlateau(run)->id);
				updateGamestate(run, &gamestate);
				break;

			case SAVE:
				saveGame(run, gamestate);
				break;

			case GAMEOVER:
				deleteSave(gamestate.save_file);
				gameOverScreen();
				break; // No break between GAMEOVER and QUIT
				
			case QUIT:
				// Free malloc
				break;	
						
			case -1:
				printf("Erreur fatale: Ecran bleu window\n");
				break;
			
		}
	}
	
	//End ncurses
	endwin();

	printf("BYE PADAWANN!!!!!!!!\n");
	
	return 0;
	
}
