#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "fenetre.h"

void fenetrePlateau(PERSO* perso){

	int ch;
	int finPlateau = 1; //tant que le combat est pas fini
	int menuActive = 1; //
 
 	while(finPlateau){
			    	
		//get screen size
		int yMax,xMax;
		getmaxyx(stdscr,yMax,xMax);
		
		//Variables fenetres	
		WINDOW* game;
		WINDOW* menu; 
		WINDOW* score;
		WINDOW* inputwin;
		   
		int xGame,yGame,hGame,wGame;
		int xMenu,yMenu,hMenu,wMenu;
		int xScore,yScore,hScore,wScore;
		int xInput,yInput,hInput,wInput;	
		
		//fenetre game	   	
		xGame = yGame = 0; 
		hGame = 25;
		wGame = xMax;

		game = newwin(hGame,wGame,yGame,xGame);   //newwin(height, width, start y, start x)
		wattron(game,A_BOLD);
		init_pair(1, COLOR_RED,COLOR_CYAN);
		wattron(game,COLOR_PAIR(1));	
		mvwprintw(game, 1,1,"GAME");		   	   	
		box(game, 0,0);			   	
		wattroff(game,COLOR_PAIR(1));
		
		affichePersoWin(game,perso);

		//fenetre input/log	   	
		hInput = 7;
		wInput = xMax;
		yInput = yMax-hInput;
		xInput = 0;

		inputwin = newwin(hInput,wInput,yInput,xInput);
		wattron(inputwin,COLOR_PAIR(1));
		wattron(inputwin,A_BOLD);	
		box(inputwin, 0,0);
		mvwprintw(inputwin, 1,1,"LOG");
		wattroff(inputwin,COLOR_PAIR(1));
		
		
		//fenetre highscore&Or  	
		yScore = hGame;
		hScore = yMax-hInput-hGame;
		wScore = 20;
		xScore = xMax-wScore;

		score = newwin(hScore,wScore,yScore,xScore);
		wattron(score,COLOR_PAIR(1));
		wattron(score,A_BOLD);
		box(score, 0,0);
		mvwprintw(score, 1,1,"SCORE");		   	
		wattroff(score,COLOR_PAIR(1));		
		
				   		
		//fenetre menu
		xMenu = 0; 
		yMenu = hGame; 
		//hMenu = 10;
		hMenu = yMax-hInput-hGame;
		wMenu = xMax-wScore;
		
		menu = newwin(hMenu,wMenu,yMenu,xMenu);
		afficheMenu(menu);
		
		wrefresh(inputwin);
		wrefresh(game); 
		wrefresh(score);
		wrefresh(menu);
		
		
		
		ch = wgetch(game) ;
		
		choixMenu(menu,ch);	
					
		if(ch == 410)  {
		
			wrefresh(inputwin);
			wrefresh(score);
			wrefresh(menu);
			wrefresh(game); 		
		}

	
	}

}

void affichePersoWin(WINDOW* win,PERSO* perso){

	PERSO* current;
	int n = 0;
	
	current = perso;


	while (current != NULL){

		mvwprintw(win, 2,15*n+1,"%s",current->name);
		mvwprintw(win, 3,15*n+1,"PV: %d",current->id);
		
		current=current->suivant;
		n++;
		
	}

}



void choixMenu(WINDOW* menu, int ch){


	switch(ch){
		
		case '1':
			mvwprintw(menu, 3,1," 1 pressed");
			wrefresh(menu);
			sleep(2);
			break;
				
		case '2':
			mvwprintw(menu, 3,1," 2 pressed");
			wrefresh(menu);
			sleep(2);
			break;	
			
		case '3':
			mvwprintw(menu, 3,1," 3 pressed");
			wrefresh(menu);
			sleep(2);
			break;	
			
			
			
				
			
		default:
			break;
	}
}



void afficheMenu(WINDOW* menu){


	wattron(menu,COLOR_PAIR(1));
	wattron(menu,A_BOLD);
	
	box(menu, 0,0);
	mvwprintw(menu, 1,1,"MENU");
	
	wattroff(menu,COLOR_PAIR(1));
	wattroff(menu,A_BOLD);

	mvwprintw(menu, 2,1," 1.BOUTIQUE");
	mvwprintw(menu, 2,15," 2.INVENTAIRE");
	mvwprintw(menu, 2,30," 3.FIGHT");

}










