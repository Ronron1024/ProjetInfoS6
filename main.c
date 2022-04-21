#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "includes/defines.h"
#include "includes/prototypes.h"

int main (){

	GameMode gamemode = GAMEMODE_PLAY;

//Pour avoir des datas ...
	GameState gamestate;
	memset(&gamestate,0,sizeof(GameState));
	
	Entity perso1={"GEREM",10, 10, 10, 10};
	
	Entity monster1={"JCVD",999,999,999,999};
	Entity monster2={"FLAMBI",100, 10, 10, 10};
	Entity monster3={"HERCULE",100, 10, 10, 10};


	Item objet1={"EPEE", "Epée de décoration qui peut couper de la purée","EQUIPEMENT",23.7,1,1,1,1};
	Item objet2={"FOURCHETTE", "Pour manger et piquer les monstres acessoirement","EQUIPEMENT",212.9,1,1,1,1};
	Item objet6={"FOURCHETTE", "Pour manger et piquer les monstres acessoirement","EQUIPEMENT",212.9,1,1,1,1};
	Item objet7={"CROISSANT", "Pur beurre, muscle les poignets d' amours","ITEM",12.9,1,1,1,1};
	
	Item objet3={"DOUDOUNE", "Vetement de demi saison, procure une defense plutot faible","EQUIPEMENT",4.7,1,1,1,1};
	Item objet4={"POTION TABASCO", "Un remontant qui ne laisse pas indifferent","ITEM",29.9,1,1,1,1};
	Item objet5={"TABAC", "Un peu fumeux pour une arme","ITEM",20.5,1,1,1,1};
	Item objet8={"FOURCHETTE", "Pour manger et piquer les monstres acessoirement","EQUIPEMENT",212.9,1,1,1,1};
	
	Score score={100,200.0};
	gamestate.highscore = &score;
	
	// Entities
	
	push(&gamestate.team_player, &perso1, sizeof(Entity));
	
	push(&gamestate.team_monster, &monster1, sizeof(Entity));
	push(&gamestate.team_monster, &monster2, sizeof(Entity));	
	push(&gamestate.team_monster, &monster3, sizeof(Entity));

	// Items inventory
	push(&gamestate.inventory, &objet1, sizeof(Item));
	push(&gamestate.inventory, &objet2, sizeof(Item));
	push(&gamestate.inventory, &objet6, sizeof(Item));
	push(&gamestate.inventory, &objet7, sizeof(Item));
	
	// Items shop
	push(&gamestate.shop, &objet3, sizeof(Item));
	push(&gamestate.shop, &objet4, sizeof(Item));
	push(&gamestate.shop, &objet5, sizeof(Item));
	push(&gamestate.shop, &objet8, sizeof(Item));

	//Init ncurses
	initscr();
	cbreak();
	keypad(stdscr, TRUE); // Enable FN Keys reading
	noecho();

	start_color();
    init_pair(PAIR_YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
    init_pair(PAIR_RED_CYAN, COLOR_RED, COLOR_CYAN);
    init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_WHITE_RED, COLOR_WHITE, COLOR_RED);
	
	//fenetreIntro(); // To be removed

	splashscreen();
    getch();
    gamemode = homeMenu();

	switch (gamemode)
    {
        case GAMEMODE_PLAY:
			fenetrePlateau(&gamestate);
            break;
        case GAMEMODE_CONTINUE:
			// To be implemented
            break;
        case GAMEMODE_DEBUG:
			// To be implemented
            break;
    }
	
	//End ncurses
	endwin();
	

	printf("BYE PADAWANN!!!!!!!!\n");
	
	return 0;
}

