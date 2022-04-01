#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "fenetre.h"

//void fenetrePlateau(PERSO* perso, OBJET* objetBoutique, OBJET* objetInventaire, SCORE* highScore){
void fenetrePlateau(GAMESTATE *GameState){

	int finPlateau = 1; //tant que le combat est pas fini
 
 	while(finPlateau){
			    	
		//get screen size
		int yMax,xMax;
		getmaxyx(stdscr,yMax,xMax);
		
		//definition couleur
		init_pair(2, COLOR_RED,COLOR_CYAN);
		init_pair(1, COLOR_YELLOW,COLOR_BLUE);
		
		//Variables fenetres	
		WINDOW* game;
		WINDOW* menu; 
		WINDOW* score;
		WINDOW* log;
		   
		int xGame, yGame, hGame, wGame;
		int xMenu, yMenu, hMenu, wMenu;
		int xScore, yScore, hScore, wScore;
		int xLog, yLog, hLog ,wLog;	
		
		//fenetre game	   	
		xGame = yGame = 0; 
		hGame = 22;
		wGame = xMax;
		
		//fenetre input/log	   	
		hLog = 7;
		wLog = xMax;
		yLog = yMax-hLog;
		xLog = 0;
		
		//fenetre highscore&Or  	
		yScore = hGame;
		hScore = yMax-hLog-hGame;
		wScore = 20;
		xScore = xMax-wScore;
		
		//fenetre menu
		xMenu = 0; 
		yMenu = hGame; 
		//hMenu = 10;
		hMenu = yMax-hLog-hGame;
		wMenu = xMax-wScore;
		
		
		game = fenetreGame(game,hGame,wGame,yGame,xGame);
		log = fenetreLog(log, hLog, wLog, yLog, xLog);	
		score = fenetreScore(score, hScore, wScore,yScore,xScore);
		afficheScore(score,GameState->highScore);
		menu = fenetreMenu(menu,hMenu,wMenu,yMenu,xMenu);
		
		affichePersoWin(game,GameState->perso);
		
		wrefresh(log);
		wrefresh(game); 
		wrefresh(score);
		wrefresh(menu);

		finPlateau = selectionMenu(menu,score, hMenu, wMenu, yMenu, xMenu, 1, 1, GameState->objetBoutique, GameState->objetInventaire, GameState->highScore);
	}

}
void afficheScore(WINDOW* win,SCORE* score){

	mvwprintw(win, 2,1,"ALT: %d",score->alt);
	mvwprintw(win, 3,1,"MONEY: %-9.2f",score->money);	
}

void afficheScoreRev(WINDOW* win,SCORE* score){

	wattron(win,COLOR_PAIR(1));
	wattron(win,A_BOLD);
	wattron(win,A_REVERSE);

	mvwprintw(win, 3,1,"MONEY: %-9.2f",score->money);
	
	wattroff(win,COLOR_PAIR(1));
	wattroff(win,A_BOLD);
	wattroff(win,A_REVERSE);	
}

void affichePersoWin(WINDOW* win,PERSO* perso){

	int espace = 15; //espace entre perso
	PERSO* current;
	int n = 0;
	
	current = perso;


	while (current != NULL){

		mvwprintw(win, 2,espace*n+1,"%s",current->name);
		mvwprintw(win, 3,espace*n+1,"PV: %d",current->id);
		
		current=current->suivant;
		n++;
		
	}
}

void afficheAllObjetWin(WINDOW* win,OBJET* objet){


	int espace = 16; //espace entre perso
	OBJET* current;
	int n = 0;
	
	current = objet;

	while (current != NULL){

		mvwprintw(win, 2,espace*n+1,"%-16s",current->name);
		mvwprintw(win, 3,espace*n+1,"Price: %-9.2f",current->price);
		
		current=current->suivant;
		n++;		
	}
}


void afficheObjetWin(WINDOW* win,OBJET* objet, int n){

	int espace = 16; //espace entre objet

	mvwprintw(win, 2,espace*n+1,"%-16s",objet->name);
	mvwprintw(win, 3,espace*n+1,"Price: %-9.2f",objet->price);	
}


void afficheObjetWinReverse(WINDOW* win,OBJET* objet, int n){

	int espace = 16; //espace entre objet

	wattron(win,COLOR_PAIR(1));
	wattron(win,A_BOLD);
	wattron(win,A_REVERSE);

	mvwprintw(win, 2,espace*n+1,"%-16s",objet->name);
	mvwprintw(win, 3,espace*n+1,"Price: %-9.2f",objet->price);
	
	wattroff(win,COLOR_PAIR(1));
	wattroff(win,A_BOLD);
	wattroff(win,A_REVERSE);
}

WINDOW* fenetreGame(WINDOW* game, int hGame,int wGame,int yGame,int xGame){

		game = newwin(hGame,wGame,yGame,xGame);   //newwin(height, width, start y, start x)
		wattron(game,A_BOLD);
		wattron(game,COLOR_PAIR(1));	
		mvwprintw(game, 1,1,"GAME");		   	   	
		box(game, 0,0);
		
		wmove(game, hGame/2, 1);
		whline(game, xGame , wGame-2 ); 
					   	
		wattroff(game,COLOR_PAIR(1));
		
		return game;

}

WINDOW* fenetreLog(WINDOW* log, int hLog,int wLog,int yLog,int xLog){

		log = newwin(hLog,wLog,yLog,xLog);
		wattron(log,COLOR_PAIR(1));
		wattron(log,A_BOLD);	
		box(log, 0,0);
		mvwprintw(log, 1,1,"LOG");
		wattroff(log,COLOR_PAIR(1));
		
		return log;

}

WINDOW* fenetreScore(WINDOW* score, int hScore, int wScore,int yScore,int xScore){

		score = newwin(hScore,wScore,yScore,xScore);
		wattron(score,COLOR_PAIR(1));
		wattron(score,A_BOLD);
		box(score, 0,0);
		mvwprintw(score, 1,1,"SCORE");		   	
		wattroff(score,COLOR_PAIR(1));
		
		return score;

}

WINDOW* fenetreMenu(WINDOW* menu, int hMenu, int wMenu,int yMenu,int xMenu){

	menu = newwin(hMenu,wMenu,yMenu,xMenu);
	wattron(menu,COLOR_PAIR(1));
	wattron(menu,A_BOLD);
	box(menu, 0,0);
	mvwprintw(menu, 1,1,"MENU");
	wattroff(menu,COLOR_PAIR(1));
	
	wattroff(menu,A_BOLD);

	mvwprintw(menu, 2,1,"BOUTIQUE");
	mvwprintw(menu, 2,16,"INVENTAIRE");
	mvwprintw(menu, 2,31,"FOUILLE");
	mvwprintw(menu, 2,46,"FIGHT");
	mvwprintw(menu, 2,61,"QUITTER");

	return menu;
}

WINDOW* boutiqueMenu(WINDOW* boutique, int hMenu, int wMenu,int yMenu,int xMenu){

	
	

	boutique = newwin(hMenu-2,wMenu-1,yMenu+2,xMenu);
	wattron(boutique,COLOR_PAIR(2));
	wattron(boutique,A_BOLD);
	//wattron(boutique,A_BLINK);
	box(boutique, 0,0);
	mvwprintw(boutique, 1,1,"BOUTIQUE");
	wattroff(boutique,COLOR_PAIR(1));
	wattroff(boutique,A_BOLD);
	//wattroff(boutique,A_BLINK);
	
	
	return boutique;

}

void boutiqueFct(WINDOW* boutique) {

	
	while (wgetch(boutique) != 'q'){
	
	}

}

WINDOW* inventaireMenu(WINDOW* inventaire, int hMenu, int wMenu,int yMenu,int xMenu){

	inventaire = newwin(hMenu-2,wMenu-1,yMenu+2,xMenu);
	wattron(inventaire,COLOR_PAIR(2));
	wattron(inventaire,A_BOLD);
	box(inventaire, 0,0);
	mvwprintw(inventaire, 1,1,"INVENTAIRE");
	wattroff(inventaire,COLOR_PAIR(1));
	wattroff(inventaire,A_BOLD);
	
	return inventaire;

}

int selectionMenu(WINDOW* win, WINDOW* scr,int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, OBJET* objetBoutique, OBJET* objetInventaire, SCORE* highScore) {

	int selection;
	int choix = 1;
	
	char menuT[5][CHAR_NAME_MAX]={"BOUTIQUE","INVENTAIRE","FOUILLE","FIGHT","QUITTER"};
	
	keypad(win,TRUE);
	
	selection = 0;

	while( choix ){
	
		wattron(win,COLOR_PAIR(1));
		wattron(win,A_BOLD);
		wattron(win,A_REVERSE);
		mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);
		wrefresh(win);
	
	
		switch ( wgetch(win) ){
		
			case KEY_RIGHT:
						
				wattroff(win,COLOR_PAIR(1));
				wattroff(win,A_BOLD);
				wattroff(win,A_REVERSE);
				mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);

				if(selection!=4){
				selection++;
				}
				
				wattron(win,COLOR_PAIR(1));
				wattron(win,A_BOLD);
				wattron(win,A_REVERSE);
				mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);
				
				wrefresh(win);
				
				break;
							
			case KEY_LEFT:
			
				wattroff(win,COLOR_PAIR(1));
				wattroff(win,A_BOLD);
				wattroff(win,A_REVERSE);
				mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);
			
				if(selection!=0){
					selection--;
				}
				
				wattron(win,COLOR_PAIR(1));
				wattron(win,A_BOLD);
				wattron(win,A_REVERSE);
				mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);
				wrefresh(win);
				
				break;
				
			case 10:	//touche enter

				if ( selection == 0 ){
					menuBoutique(win,scr, hMenu, wMenu, yMenu, xMenu, objetBoutique, objetInventaire, highScore);
					choix = 0 ;
					
					return 1;
				}
				
				if ( selection == 1 ){
					menuInventaire(win,scr, hMenu, wMenu, yMenu, xMenu, objetBoutique, objetInventaire, highScore);
					choix = 0 ;
					
					return 1;
				}
				
				if ( selection == 4 ){
					//choix = 0;
					
					return 0;
				}
				
				
				break;

			default:		
				break;
				
	
		}
	
	}
	
	return 1;
}


int compterObjet(OBJET* objet){

	OBJET* current;
	int n = 0;
	
	current = objet;

	while (current != NULL){

		current=current->suivant;
		n++;	
	}
	
	return n;
}

void menuBoutique(WINDOW* boutique,WINDOW* scr, int hMenu, int wMenu,int yMenu,int xMenu,OBJET* objetBoutique, OBJET* objetInventaire, SCORE* highScore){

	OBJET* current;
	int n = 0;
	int cmptObjet;
	int choix = 1;
	int achatConvulsif;
	int ch;

	boutique = boutiqueMenu(boutique, hMenu, wMenu,yMenu,xMenu);	
	mvwprintw(boutique, hMenu-4,wMenu-17,"return: press q");
	
	keypad(boutique,TRUE);
	
	current = objetBoutique;

	afficheAllObjetWin(boutique,objetBoutique);
			
	cmptObjet = compterObjet(objetBoutique);
				
	afficheObjetWinReverse(boutique,objetBoutique, n);
	
	mvwprintw(boutique, hMenu-4,1,"%-100s",current->description);
				
	wrefresh(boutique);
			
		while(choix){
		
			achatConvulsif =1;  // :)

			switch ( wgetch(boutique) ){
			
				case KEY_RIGHT:
				
					mvwprintw(boutique, hMenu-5,1,"                          ");
					
					if(n!=cmptObjet-1){
						current=current->suivant;
						n++;
					}			
						
					afficheObjetWinReverse(boutique,current, n);
					afficheObjetWin(boutique,current->precedent, n-1);
					
					mvwprintw(boutique, hMenu-4,1,"%-100s",current->description);
							
					wrefresh(boutique);
					
					break;
								
				case KEY_LEFT:
	
					mvwprintw(boutique, hMenu-5,1,"                          ");
					
					if(n!=0){
						current=current->precedent;
						n--;
					}
					afficheObjetWin(boutique,current->suivant, n+1);
					afficheObjetWinReverse(boutique,current, n);
					
					mvwprintw(boutique, hMenu-4,1,"%-100s",current->description);
					
					wrefresh(boutique);
					
					break;
						
				case 'q':
					choix = 0 ;
					break;
										
				case 10:
					
					wattron(boutique,COLOR_PAIR(1));
					wattron(boutique,A_BOLD);
					wattron(boutique,A_REVERSE);
					
					mvwprintw(boutique, hMenu-5,10,"O/N?");
										
					wattroff(boutique,COLOR_PAIR(1));
					wattroff(boutique,A_BOLD);
					wattroff(boutique,A_REVERSE);
					
					mvwprintw(boutique, hMenu-5,1,"%-6.2f",current->price);
					
						while(achatConvulsif){
						
							ch = wgetch(boutique);			
						
							if( ch == 'O' ){
								achatBoutique(highScore, current);
								afficheScoreRev(scr,highScore);
								wrefresh(scr);			
							}
							if( ch == 'N' ) {
								achatConvulsif=0;
								mvwprintw(boutique, hMenu-5,1,"                          ");
								afficheScore(scr,highScore);
								wrefresh(scr);	
							}
							
							if( ch == 'q' ) {
								choix = 0;
								afficheScore(scr,highScore);
								achatConvulsif=0;
							}							
						}
												
					wrefresh(boutique);
					break;	
					
				default:
					break;	
					
			}
		}

}


int achatBoutique(SCORE* highScore, OBJET* objet){

	
	if( highScore->money-objet->price < 0) {
		return 1; 	
	}
	
	else{ 
		highScore->money=highScore->money-objet->price;
		return 0; 	
	}
}
					
//FONCTION A FINIR: ON re vend et utilise depuis l' inventaire?
void menuInventaire(WINDOW* inventaire, WINDOW* scr, int hMenu, int wMenu,int yMenu,int xMenu, OBJET* objetBoutique, OBJET* objetInventaire, SCORE* highScore){

	OBJET* current;
	int n = 0;
	int useConvulsif;
	int cmptObjet;
	int choix = 1;
	int ch;

	inventaire = inventaireMenu(inventaire, hMenu, wMenu,yMenu,xMenu);	
	mvwprintw(inventaire, hMenu-4,wMenu-17,"return: press q");
	
	keypad(inventaire,TRUE);
	
	current = objetInventaire;

	afficheAllObjetWin(inventaire,objetInventaire);
			
	cmptObjet = compterObjet(objetInventaire);
				
	afficheObjetWinReverse(inventaire,objetInventaire, n);
	
	mvwprintw(inventaire, hMenu-4,1,"%-100s",current->description);
			
	wrefresh(inventaire);
			
		while(choix){
					
			useConvulsif =1;  // :)

			switch ( wgetch(inventaire) ){
			
				case KEY_RIGHT:
				
					mvwprintw(inventaire, hMenu-5,1,"                          ");
					
					if(n!=cmptObjet-1){
						current=current->suivant;
						n++;
					}			
						
					afficheObjetWinReverse(inventaire,current, n);
					afficheObjetWin(inventaire,current->precedent, n-1);
					
					mvwprintw(inventaire, hMenu-4,1,"%-100s",current->description);
							
					wrefresh(inventaire);
					
					break;
								
				case KEY_LEFT:
	
					mvwprintw(inventaire, hMenu-5,1,"                          ");
					
					if(n!=0){
						current=current->precedent;
						n--;
					}
					afficheObjetWin(inventaire,current->suivant, n+1);
					afficheObjetWinReverse(inventaire,current, n);
					
					mvwprintw(inventaire, hMenu-4,1,"%-100s",current->description);
					
					wrefresh(inventaire);
					
					break;
						
				case 'q':
					choix = 0 ;
					break;
										
				case 10:
					
					wattron(inventaire,COLOR_PAIR(1));
					wattron(inventaire,A_BOLD);
					wattron(inventaire,A_REVERSE);
					
					mvwprintw(inventaire, hMenu-5,10,"O/N?");
										
					wattroff(inventaire,COLOR_PAIR(1));
					wattroff(inventaire,A_BOLD);
					wattroff(inventaire,A_REVERSE);
					
					mvwprintw(inventaire, hMenu-5,1,"%-6.2f",current->price);
					
						while(useConvulsif){
						
							ch = wgetch(inventaire);			
						
							if( ch == 'O' ){
								//USE ITEM FCT() ou vend?
								//achatBoutique(highScore, current);
								//afficheScoreRev(scr,highScore);
								//wrefresh(scr);			
							}
							if( ch == 'N' ) {
								useConvulsif=0;
								mvwprintw(inventaire, hMenu-5,1,"                          ");
								//afficheScore(scr,highScore);
								//wrefresh(scr);	
							}
							
							if( ch == 'q' ) {
								choix = 0;
								useConvulsif=0;
							}							
						}
												
					wrefresh(inventaire);
					break;	
					
				default:
					break;	
					
			}
		}
}



void fenetreIntro(void){

	WINDOW* intro;

	//get screen size
	int yMax,xMax;
	getmaxyx(stdscr,yMax,xMax);
	
	//definition couleur
	//init_pair(1, COLOR_RED,COLOR_CYAN);
	init_pair(1, COLOR_YELLOW,COLOR_BLUE);
		
	intro = newwin(yMax,xMax,0,0);
	
	wattron(intro,COLOR_PAIR(1));
	wattron(intro,A_BOLD);
	box(intro, 0,0);
	mvwprintw(intro, 1,1,"INTRO");	
	wattroff(intro,COLOR_PAIR(1));
	wattroff(intro,A_BOLD);
	 
	wrefresh(intro);
	
	while( wgetch(intro) != 10 ){ 

		wrefresh(intro);
		
	}
	
	clear();
	refresh();
	
	return;
	

}














