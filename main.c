#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "linkedlist.h"
#include "fenetre.h"
#include <ncurses.h>

int main (){


//Pour avoir des datas ...
	GameState gamestate;
	memset(&gamestate,0,sizeof(GameState));
	
	Entity perso1={"HERCULE",100, 10, 10, 10};
	Entity perso2={"FLAMBI",100, 10, 10, 10};

	Item objet1={"EPEE", "Epée de décoration qui peut couper de la purée",23.7};
	Item objet2={"FOURCHETTE", "Pour manger et piquer les monstres acessoireement",212.9};
	
	Item objet3={"DOUDOUNE", "Vetement de demi saison, procure une defense plutot faible",4.7};
	Item objet4={"POTION TABASCO", "Un remontant qui ne laisse pas indifferent",29.9,};
	Item objet5={"TABAC", "Un peu fumeux pour une arme",20.5};
	
	Score score={100,200.0};
	gamestate.highscore = &score;
	
	// Entities
	
	push(&gamestate.team_player, &perso1, sizeof(Entity));
	push(&gamestate.team_player, &perso2, sizeof(Entity));
	
	// Items inventory
	push(&gamestate.inventory, &objet1, sizeof(Item));
	push(&gamestate.inventory, &objet2, sizeof(Item));
	
	// Items shop
	push(&gamestate.shop, &objet3, sizeof(Item));
	push(&gamestate.shop, &objet4, sizeof(Item));
	push(&gamestate.shop, &objet5, sizeof(Item));


	//Init ncurses
	initscr();
	cbreak();
	noecho();
	start_color();
	
	fenetreIntro();
	fenetrePlateau(&gamestate);
	
	//End ncurses
	endwin();
	

	printf("BYE PADAWANN!!!!!!!!\n");	
	
	return 0;
}

