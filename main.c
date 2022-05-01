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

	Entity player = {
		0,	//id
		"Gerem",
		getNullItem(), getNullItem(),
		10, 10, 10, 10
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
	// splashscreen();
    // getch();
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
