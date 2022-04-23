#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "../includes/defines.h"
#include "../includes/structures.h"
#include "../includes/prototypes.h"

int fenetrePlateau(GameState *gamestate){

	if(!gamestate){
		return -1;
	}

	int statusPlateau = 0;

	//Pour les logs
	char logText[LINE_LOG_MAX][CHAR_DESC_MAX];
	int pLog = 0;	//Position ligne log

 	
 	while (statusPlateau != 1 && statusPlateau != 2 && statusPlateau != 3) {		//0 RAS /1 COMBAT /2 SAVE /3 QUITTER
			    	
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
		hGame = 26;		//22 avant
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
		
		game = frameWindow(1);
		log = frameWindow(2);
		
		score = frameWindow(3);
		afficheScore(score,gamestate->highscore);
		
		menu = frameWindow(4);
		affichePersoWin(game,gamestate->team_player);
		afficheMonsterWin(game,gamestate->team_monster);
		
		wrefresh(log);
		wrefresh(game); 
		wrefresh(score);
		wrefresh(menu);

		statusPlateau = selectionMenu(menu,score, log, hMenu, wMenu, yMenu, xMenu, 1, 1, gamestate, &pLog, logText);
			
	}
	
	return statusPlateau;

}
void afficheScore(WINDOW* win,Score* score){

	if(!win || !score){
		return;
	}

	mvwprintw(win, 2,1,"ALT: %d",score->alt);
	mvwprintw(win, 3,1,"MONEY: %-9.2f",score->money);	
}

void afficheScoreRev(WINDOW* win,Score* score){

	if(!win || !score){
		return;
	}

	wattron(win,COLOR_PAIR(1));
	wattron(win,A_BOLD);
	wattron(win,A_REVERSE);

	mvwprintw(win, 3,1,"MONEY: %-9.2f",score->money);
	
	wattroff(win,COLOR_PAIR(1));
	wattroff(win,A_BOLD);
	wattroff(win,A_REVERSE);	
}

void affichePersoWin(WINDOW* win,Node* perso){

	if(!win || !perso){
		return;
	}

	int espace = 15; //espace entre perso
	Node* current;
	int n = 0;
	
	current = perso;


	while (current != NULL){

		mvwprintw(win, 14,espace*n+1,"%s",getEntity(current)->name);

		wattroff(win,A_BOLD);
		mvwprintw(win, 15,espace*n+1,"HP : %4.0lf",getEntity(current)->health);
		mvwprintw(win, 16,espace*n+1,"ATT: %4.0lf",getEntity(current)->attack);
		mvwprintw(win, 17,espace*n+1,"DEF: %4.0lf",getEntity(current)->defense);
		mvwprintw(win, 18,espace*n+1,"SPD: %4.0lf",getEntity(current)->speed);
		
		wattron(win,A_BOLD);
		
		current=current->next;
		n++;
		
	}
}

void affichePersoReverseWin(WINDOW* win,Node* perso){

	if(!win || !perso){
		return;
	}

	int espace = 15; //espace entre perso
	Node* current;
	int n = 0;
	
	current = perso;


	while (current != NULL){
	
		wattron(win,COLOR_PAIR(1));
		wattron(win,A_BOLD);
		wattron(win,A_REVERSE);

		mvwprintw(win, 15,espace*n+1,"HP : %4.0lf",getEntity(current)->health);
		mvwprintw(win, 16,espace*n+1,"ATT: %4.0lf",getEntity(current)->attack);
		mvwprintw(win, 17,espace*n+1,"DEF: %4.0lf",getEntity(current)->defense);
		mvwprintw(win, 18,espace*n+1,"SPD: %4.0lf",getEntity(current)->speed);
		
		wattroff(win,COLOR_PAIR(1));
		wattroff(win,A_BOLD);
		wattroff(win,A_REVERSE);
	
		current=current->next;
		n++;
		
	}
}

void afficheMonsterWin(WINDOW* win,Node* monster){

	if(!win || !monster){
		return;
	}

	int espace = 15; //space between entities
	Node* current;
	int n = 0;
	
	current = monster;

	while (current != NULL){
	
		mvwprintw(win, 2,espace*n+1,"%s",getEntity(current)->name);
		wattroff(win,A_BOLD);
		mvwprintw(win, 3,espace*n+1,"HP : %4.0lf",getEntity(current)->health);
		mvwprintw(win, 4,espace*n+1,"ATT: %4.0lf",getEntity(current)->attack);
		mvwprintw(win, 5,espace*n+1,"DEF: %4.0lf",getEntity(current)->defense);
		mvwprintw(win, 6,espace*n+1,"SPD: %4.0lf",getEntity(current)->speed);
		
		wattron(win,A_BOLD);
		
		current=current->next;
		n++;
		
	}
}

void afficheAllObjetWin(WINDOW* win,Node* objet){

	int espace = 16; //espace entre perso
	Node* current;
	int n = 0;
	
	current = objet;

	while (current != NULL){

		wattron(win,A_BOLD);
		mvwprintw(win, 1,espace*n,"%-16s",getItem(current)->name);
		wattroff(win,A_BOLD);
		
		mvwprintw(win, 2,espace*n,"Price: %-9.2f",getItem(current)->price);

		mvwprintw(win, 3,espace*n,"HP : %4.0lf",getItem(current)->health);
		mvwprintw(win, 4,espace*n,"ATT: %4.0lf",getItem(current)->attack);
		mvwprintw(win, 5,espace*n,"DEF: %4.0lf",getItem(current)->defense);
		mvwprintw(win, 6,espace*n,"SPD: %4.0lf",getItem(current)->speed);
		
		current=current->next;
		n++;		
	}
}

void afficheObjetWin(WINDOW* win,Node* objet, int n){

	int espace = 16; //espace entre objet

	wattron(win,A_BOLD);
	mvwprintw(win, 1,espace*n,"%-16s",getItem(objet)->name);	
	wattroff(win,A_BOLD);
	
	mvwprintw(win, 2,espace*n,"Price: %-9.2f",getItem(objet)->price);	
	
	mvwprintw(win, 3,espace*n,"HP : %4.0lf",getItem(objet)->health);
	mvwprintw(win, 4,espace*n,"ATT: %4.0lf",getItem(objet)->attack);
	mvwprintw(win, 5,espace*n,"DEF: %4.0lf",getItem(objet)->defense);
	mvwprintw(win, 6,espace*n,"SPD: %4.0lf",getItem(objet)->speed);
}

void afficheObjetWinReverse(WINDOW* win,Node* objet, int n){

	int espace = 16; //espace entre objet

	wattron(win,COLOR_PAIR(1));
	wattron(win,A_BOLD);
	wattron(win,A_REVERSE);

	mvwprintw(win, 1,espace*n,"%-16s",getItem(objet)->name);
	mvwprintw(win, 2,espace*n,"Price: %-9.2f",getItem(objet)->price);
	
	//mvwprintw(win, 3,espace*n,"HP : %4.0lf",getItem(objet)->health);
	//mvwprintw(win, 4,espace*n,"ATT: %4.0lf",getItem(objet)->attack);
	//mvwprintw(win, 5,espace*n,"DEF: %4.0lf",getItem(objet)->defense);
	//mvwprintw(win, 6,espace*n,"SPD: %4.0lf",getItem(objet)->speed);
	
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
		mvwprintw(score, 1,1,"Score");		   	
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
	mvwprintw(menu, 2,31,"FIGHT");
	mvwprintw(menu, 2,46,"SAVE");
	mvwprintw(menu, 2,61,"QUITTER");

	return menu;
}

WINDOW* boutiqueMenu(WINDOW* boutique, int hMenu, int wMenu,int yMenu,int xMenu){

	boutique = newwin(hMenu-4,wMenu-2,yMenu+3,xMenu+1);
	
	//Pour ecrire dans la fenetre
	/*wattron(boutique,COLOR_PAIR(1));
	wattron(boutique,A_BOLD);
	mvwprintw(boutique, 2,1,"BOUTIQUE");
	wattroff(boutique,COLOR_PAIR(1));
	wattroff(boutique,A_BOLD);
	*/
	
	mvwprintw(boutique, hMenu-5,wMenu-15,"QUIT: press q");
		
	return boutique;

}

WINDOW* fouilleMenu(WINDOW* fouille, int hMenu, int wMenu,int yMenu,int xMenu){

	fouille = newwin(hMenu-4,wMenu-2,yMenu+3,xMenu+1);
	

char menuT[5][CHAR_DESC_MAX]={"CADAVRES","POCHES","RECOINS","COFFRE","STATUETTE"};


	mvwprintw(fouille, 2,0,"CADAVRES");	
	mvwprintw(fouille, 3,0,"POCHES");	
	mvwprintw(fouille, 4,0,"RECOINS");
	mvwprintw(fouille, 5,0,"COFFRE");	
	mvwprintw(fouille, 6,0,"STATUETTE");	

	keypad(fouille,TRUE);

	mvwprintw(fouille, hMenu-5,wMenu-15,"QUIT: press q");
		
	return fouille;

}

void boutiqueFct(WINDOW* boutique) {
	
	while (wgetch(boutique) != 'q'){
	
	}
}


WINDOW* inventaireMenu(WINDOW* inventaire, int hMenu, int wMenu,int yMenu,int xMenu){

	inventaire = newwin(hMenu-4,wMenu-2,yMenu+3,xMenu+1);
	mvwprintw(inventaire, hMenu-5,wMenu-15,"QUIT: press q");
	
	return inventaire;

}

int selectionMenu(WINDOW* win, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]) {

	int selection;
	int choix = 1;
	
	char menuT[5][CHAR_NAME_MAX]={"BOUTIQUE","INVENTAIRE","FIGHT","SAVE","QUITTER"};
	
	keypad(win,TRUE);
	
	selection = 0;

	while( choix ){
	
		wattron(win,COLOR_PAIR(1));
		wattron(win,A_BOLD);
		wattron(win,A_REVERSE);
		mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);
		wrefresh(win);

		afficheAllLog( frameWindow(6), pLog, logText);
		wrefresh(log);
		
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
							
				wattron(win,COLOR_PAIR(1));
				wattron(win,A_BOLD);
				wattron(win,A_REVERSE);
				wattron(win,A_ITALIC);
				mvwprintw(win, 2,1+selection*15,"%s",&menuT[selection][0]);
				wrefresh(win);
			
			
				

				if ( selection == 0 ){ //BOUTIQUE
	
					menuBoutique(win,scr, log, hMenu, wMenu, yMenu, xMenu, gamestate, pLog, logText);
					choix = 0 ;
					
					
				wattroff(win,COLOR_PAIR(1));
				wattroff(win,A_BOLD);
				wattroff(win,A_REVERSE);
				wattroff(win,A_ITALIC);
					
					
					
					return 0;
				}
				
				if ( selection == 1 ){ //INVENTAIRE
					
					menuInventaire(win,scr, log, hMenu, wMenu, yMenu, xMenu, gamestate, pLog, logText);
					choix = 0 ;
					
					return 0;
				}
				
	
				if ( selection == 2 ){ //FIGHT
					//menuFouille(win,scr, log, hMenu, wMenu, yMenu, xMenu, gamestate, pLog, logText);
					//choix = 0 ;
					
					return 1;
				}			
	
				if ( selection == 3 ){ //SAVE
					//choix = 0;
					
					return 2;
				}
				
				if ( selection == 4 ){ //QUITTER
					//choix = 0;
					
					return 3;
				}
				
				
				break;

			default:		
				break;
				
	
		}
	
	}
	
	return 1;
}

// Replace by countList(Node*);
int compterObjet(Node* objet){

	Node* current;
	int n = 0;
	
	current = objet;

	while (current != NULL){

		current=current->next;
		n++;	
	}
	
	return n;
}

void menuBoutique(WINDOW* boutique,WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){

	//Node** teamPlayer = &(gamestate->team_player); 
	Node* shop = gamestate->shop;
	Node** inventory = &(gamestate->inventory);
	Score* highscore = gamestate->highscore;

	Node* current;
	
	char message[CHAR_DESC_MAX];
	int n = 0;
	int cmptObjet;
	int choix = 1;
	int achatConvulsif;
	int ch;
	
	boutique = frameWindow(5);	
	keypad(boutique,TRUE);
	
	current = shop;

	afficheAllObjetWin(boutique,shop);
			
	cmptObjet = compterObjet(shop);
				
	afficheObjetWinReverse(boutique,shop, n);
	
	//Ecrit dans la fentre boutique
	mvwaddstr(boutique, hMenu-5,0,getItem(current)->description);
	
	//ou ecrit dans le log
	//printfLog(log, getItem(current)->description, pLog, logText);
		
	char message2[]="=> BOUTIQUE";

	printfLog(log, message2, pLog, logText);
				
	wrefresh(boutique);
			
		while(choix){
	
			achatConvulsif =1;  // :)

			switch ( wgetch(boutique) ){
			
				case KEY_RIGHT:
								
					if(n!=cmptObjet-1){
						current=current->next;
						n++;
					}	
					
					//Trame de fond
					boutique = frameWindow(5);	
					keypad(boutique,TRUE);
					afficheAllObjetWin(boutique,shop);	
					
					//	
					afficheObjetWinReverse(boutique,current, n);
					afficheObjetWin(boutique,current->prev, n-1);								
					mvwaddstr(boutique, hMenu-5,0,getItem(current)->description);
							
					wrefresh(boutique);
					
					break;
								
				case KEY_LEFT:
						
					if(n!=0){
						current=current->prev;
						n--;
					}
					
					//Trame de fond
					boutique = frameWindow(5);
					keypad(boutique,TRUE);	
					afficheAllObjetWin(boutique,shop);
							
					afficheObjetWin(boutique,current->next, n+1);
					afficheObjetWinReverse(boutique,current, n);
					mvwaddstr(boutique, hMenu-5,0,getItem(current)->description);
					
					wrefresh(boutique);
					
					break;
						
				case 'q':
					choix = 0 ;
					break;
					
				//case 27:
					//choix = 0 ;
					//break;
					
										
				case 10:
				
					wattron(boutique,COLOR_PAIR(1));
					wattron(boutique,A_BOLD);
					wattron(boutique,A_REVERSE);
					
					//On ecrit dans le log					
					sprintf(message, "%-6.2f",getItem(current)->price);
					strcat(message, " ACHAT [Oo/Nn]");				
					printfLog (log, message, pLog, logText);
								
					wattroff(boutique,COLOR_PAIR(1));
					wattroff(boutique,A_BOLD);
					wattroff(boutique,A_REVERSE);

						while(achatConvulsif){
						
							ch = wgetch(boutique);			
						
							if( ch == 'O' || ch == 'o'){
								
								if( achatBoutique(highscore, current) == 0){
								
									//Update money & inventory
									afficheScoreRev(scr,highscore);
									push(inventory, getItem(current), sizeof(Item));
									
									//Log
									strcpy(message,"ACHAT: ");
									strcat(message, getItem(current)->name);
									strcat(message, " OK");
									printfLog (log, message, pLog, logText);

									wrefresh(scr);	
									
								}
								
								
								
								else{
									strcpy(message,"ACHAT: ");
									strcat(message, getItem(current)->name);
									strcat(message, " KO");
									
									printfLog (log, message, pLog, logText);
									
									achatConvulsif=0;
								}		
							}
							if( ch == 'N' || ch == 'n' ) {
								achatConvulsif=0;
								//afficheScore(scr,highscore);
								//wrefresh(scr);	
							}
							
							if( ch == 'q' ) {
								choix = 0;
								//afficheScore(scr,highscore);
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


int achatBoutique(Score* highscore, Node* objet){
	
	if( highscore->money - getItem(objet)->price < 0) {

		return 1; 	
	}
	
	else{ 			
		highscore->money = highscore->money - getItem(objet)->price;

		return 0; 	
	}
}
					
//FONCTION A FINIR: ON re vend et utilise depuis l' inventaire?
void menuInventaire(WINDOW* inventaire, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){

	Node** teamPlayer = &(gamestate->team_player); 
	Node** teamMonster = &(gamestate->team_monster);
	//Node* shop = gamestate->shop;
	Node** inventory = &(gamestate->inventory);
	Score* highscore = gamestate->highscore;

	char message[CHAR_DESC_MAX];

	Node* current;
	int n = 0;
	int useConvulsif;
	int cmptObjet;
	int choix = 1;
	int ch;
		
	inventaire = frameWindow(7);	
	keypad(inventaire,TRUE);
	
	current = *inventory;

	afficheAllObjetWin(inventaire,*inventory);	
					
	cmptObjet = compterObjet(*inventory);				
	afficheObjetWinReverse(inventaire,*inventory, n);
			
			
	//Ecrit dans la fentre inventaire
	mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
			
	char message2[]="=> INVENTAIRE";
	printfLog(log, message2, pLog, logText);
		
	while(choix){
						
		useConvulsif =1;  // :)
		cmptObjet = compterObjet(*inventory);
		
			switch ( wgetch(inventaire) ){
			
				case KEY_RIGHT:

					if(n!=cmptObjet-1){
						current=current->next;
						n++;
					}	
					
					
					//Trame de fond
					inventaire = frameWindow(7);	
					keypad(inventaire,TRUE);	
					afficheAllObjetWin(inventaire,*inventory);
							
					afficheObjetWinReverse(inventaire,current, n);													
					mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
					
					wrefresh(inventaire);

					break;
								
				case KEY_LEFT:
								
					if(n!=0){
						current=current->prev;
						n--;
					}
					//Trame de fond
					inventaire = frameWindow(7);	
					keypad(inventaire,TRUE);
					afficheAllObjetWin(inventaire,*inventory);

					afficheObjetWinReverse(inventaire,current, n);
					mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
					
					wrefresh(inventaire);
					
					break;
						
				case 'q':
					choix = 0 ;
					break;
										
				case 10:
						
					wattron(inventaire,COLOR_PAIR(1));
					wattron(inventaire,A_BOLD);
					wattron(inventaire,A_REVERSE);
					
					//On ecrit dans le log	
					strcpy(message,"Use, Merge or Sell [U/M/S]");								
					printfLog (log, message, pLog, logText);
																
					wattroff(inventaire,COLOR_PAIR(1));
					wattroff(inventaire,A_BOLD);
					wattroff(inventaire,A_REVERSE);

						while(useConvulsif){
						
							ch = wgetch(inventaire);			
						
							if( ch == 'U' || ch == 'u' ){
							
								//Choix du 1er de la liste
								Node* entity = *teamPlayer;
								
								if( useItem(inventory,  current, teamPlayer, entity) == 0 ){
								
									//Log
									strcpy(message, "USE: ");
									strcat(message, getItem(current)->name);
									strcat(message, " OK");
										
									printfLog(log, message, pLog, logText);
					
									//Suppression inventaire
									sup(inventory, current);
																		
									//Update affichage inventaire	
									inventaire = frameWindow(7);	
									keypad(inventaire,TRUE);
									afficheAllObjetWin(inventaire,*inventory);
								
									//On se recalle sur le meme item si i l existe
									if ( sameItem(inventory,  current) >= 0){
			
										afficheObjetWinReverse(inventaire,current, sameItem(inventory,  current ) );
										mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
									
									}
									
									else{
									
										n = 0;
	
										afficheObjetWinReverse(inventaire,*inventory, n); //On ré affiche le 1er item en yellow
										useConvulsif =0;
										
										//On se re positionne en début de liste
										current = *inventory;
										mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
										
									}
							
									//Update affichage perso/monster
									WINDOW* game = frameWindow(1);	
									afficheMonsterWin(game,*teamMonster);
									affichePersoWin(game,*teamPlayer);
									affichePersoReverseWin(game,entity);
									wrefresh(game);
									wrefresh(inventaire);										

								}
								
								
								
								else{
									//Log
									strcpy(message, "USE: ");
									strcat(message, getItem(current)->name);
									strcat(message, " KO");
										
									printfLog(log, message, pLog, logText);
									
									useConvulsif =0;
									
									//On se re positionne en début de liste
									current = *inventory;
								}

		
							}
							if( ch == 'M' || ch == 'm' ) {
							
								if ( mergeItem(current,inventory) == 0 ){
								
								//Au moins 2 Items du meme genre
					
								//Update affichage inventaire
								inventaire = frameWindow(7);	
								keypad(inventaire,TRUE);
								afficheAllObjetWin(inventaire,*inventory);
								wrefresh(inventaire);
								
								strcpy(message, "MERGE: ");
								strcat(message, getItem(current)->name);
								strcat(message, " OK");
									
								printfLog(log, message, pLog, logText);
								
								
								
																	//On se recalle sur le meme 
									if ( sameItem(inventory,  current) >= 0){
			
										afficheObjetWinReverse(inventaire,current, sameItem(inventory,  current ) );
										mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
									
									}
									
									else{
									
										n = 0;
										
										afficheObjetWinReverse(inventaire,*inventory, n); //On ré affiche le 1er item en yellow
										useConvulsif =0;
										
										//On se re positionne en début de liste
										current = *inventory;
										mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
										
									}
									
									wrefresh(inventaire);	
								}								
								
								else{
									strcpy(message, "MERGE: ");
									strcat(message, getItem(current)->name);
									strcat(message, " KO");
									
									printfLog(log, message, pLog, logText);
									
									useConvulsif =0;
									
									//On se re positionne en début de liste
									n=0;	
									current = *inventory;
								
								}
							
							}
							
							if( ch == 'S' || ch == 's' ) {
							
							
							
								if( venteInventaire(highscore, inventory, current) == 0){
								
									//Update "score"
									afficheScoreRev(scr,highscore);
									wrefresh(scr);
									
									//Suppression inventaire
									sup(inventory, current);
																		
									//Update affichage inventaire
									inventaire = frameWindow(7);	
									keypad(inventaire,TRUE);
									afficheAllObjetWin(inventaire,*inventory);
									wrefresh(inventaire);
									
									
									strcpy(message, "SOLD: ");
									strcat(message, getItem(current)->name);
									strcat(message, " OK");
										
									printfLog(log, message, pLog, logText);
									
									
									
									//On se recalle sur le meme 
									if ( sameItem(inventory,  current) >= 0){
			
										afficheObjetWinReverse(inventaire,current, sameItem(inventory,  current ) );
										mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
									
									}
									
									else{
									
										n = 0;
										
										afficheObjetWinReverse(inventaire,*inventory, n); //On ré affiche le 1er item en yellow
										useConvulsif =0;
										
										//On se re positionne en début de liste
										current = *inventory;
										mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
										
									}
									
									wrefresh(inventaire);	
								
								
								}
								
								else{
								
									strcpy(message, "SOLD: ");
									strcat(message, getItem(current)->name);
									strcat(message, " KO");
										
									printfLog(log, message, pLog, logText);
									
									useConvulsif=0;
									
									//On se re positionne en début de liste
									n=0;	
									current = *inventory;
				
								}

		
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

void printfLog (WINDOW* win, char* message, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX] ){

	WINDOW* log;

	int yMax,xMax;
	getmaxyx(stdscr,yMax,xMax);

	int hLog = 7;
	int wLog = xMax;
	int yLog = yMax-hLog;
	int xLog = 0;
	
	wclear(win);
	
	win = fenetreLog(win, hLog, wLog, yLog, xLog);
	
	log = newwin(hLog-3,wLog-2,yLog+2,xLog+1);
	
	scrollok(log,TRUE);
		
	wattron(log,COLOR_PAIR(1));
	wattron(log,A_BOLD);

	//Nb de ligne visible
	if ( (*pLog) <hLog-3)
	{	
		strcpy( logText[*pLog], message);
		mvwaddstr(log,*pLog,0,message);
		(*pLog)++;	
	}
	else{
		scroll(log);
		strcpy( logText[*pLog], message);
		shiftArraw(logText);
		mvwaddstr(log,3,0,message);

	}
	
	wattroff(log,COLOR_PAIR(1));
	wattroff(log,A_BOLD);
		
	afficheLog(log, pLog, logText);
		
	return;

}

void afficheLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){

	int reverse = (*pLog) - 2;

	while( (reverse) >= 0 ){
	
		mvwaddstr(log,reverse,0,logText[reverse]);
		
		reverse--;
	
	}
	
	wrefresh(log);
}


void afficheAllLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){

	int reverse = (*pLog) - 1;

	while( (reverse) >= 0 ){
	
		mvwaddstr(log,reverse,0,logText[reverse]);
		
		reverse--;
	
	}
	
	wrefresh(log);
}


void shiftArraw(char logText[LINE_LOG_MAX][CHAR_DESC_MAX] ){

	for (int n=0; n <LINE_LOG_MAX; n++){
	
		strcpy ( logText[n], logText[n+1] );

	}
}

WINDOW* frameWindow(int number){

	WINDOW* win = NULL;

	//get screen size
	int yMax,xMax;
	getmaxyx(stdscr,yMax,xMax);
	   
	int xGame, yGame, hGame, wGame;
	int xMenu, yMenu, hMenu, wMenu;
	int xScore, yScore, hScore, wScore;
	int xLog, yLog, hLog ,wLog;	
		
	//fenetre game	   	
	xGame = yGame = 0; 
	hGame = 26;		//22 avant
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
		
	
	switch(number){
	
		case 1:
			return fenetreGame(win,hGame,wGame,yGame,xGame);
			break;
			
			
		case 2:
			return fenetreLog(win, hLog, wLog, yLog, xLog);
			break;
			
			
		case 3:
			return fenetreScore(win, hScore, wScore,yScore,xScore);
			break;
					
		case 4:
			return fenetreMenu(win,hMenu,wMenu,yMenu,xMenu);
			break;
			
		case 5:
			return boutiqueMenu(win, hMenu, wMenu,yMenu,xMenu);
			break;	
			
		case 6:	
			return newwin(hLog-3,wLog-2,yLog+2,xLog+1);	
			break;
			
			
		case 7:	
			return inventaireMenu(win, hMenu, wMenu,yMenu,xMenu);	
			break;
				
		case 8:	
			return fouilleMenu(win, hMenu, wMenu,yMenu,xMenu);	
			break;			
			
		default:
			break;
	}
	
	return NULL;
}


int mergeItem(Node* objet,Node** inventory){

	Node* current;
	int n = 0;
	int supp = 0;
	
	double health;
	double attack; 
	double defense;
	double speed;

	//Controle si au moins 2 Items du meme genre
	current = *inventory;

	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
			n++;
		}
		
		current=current->next;	
		
	}
		
	//Au moins 2 Items du meme genre
	if (n>1){
		
		//1ere boucle on sup de l' inventaire
		current = *inventory;
			
		while (current != NULL && supp != 1){
	
			if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
				
				health = getItem(current)->health;
				attack = getItem(current)->attack;
				defense = getItem(current)->defense;
				speed = getItem(current)->speed;

				sup(inventory, current);
				supp = 1;
			}
				
		current=current->next;	
				
		}
		
		//2eme boucle on merge
		current = *inventory;
			
		while (current != NULL){
	
			if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
				
				getItem(current)->health += health; 		
				getItem(current)->attack += attack;
				getItem(current)->defense += defense;
				getItem(current)->speed += speed;
				
				return 0;
						
			}
				
		current=current->next;	
				
		}			
	}

	return 1;

}


void upgradeItem(Node* objet,Node** inventory){

	Node* current;

	current = *inventory;

	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
		
			getItem(objet)->health++;
			getItem(objet)->attack++;
			getItem(objet)->defense++;
			getItem(objet)->speed++;
			
			return;
			
		}		
		current=current->next;	
	}
}

int useItem(Node** headItem, Node* objet,Node** headEntity, Node* entity){

	Node* current = *headItem;

	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
	
			getEntity(entity)->health += getItem(objet)->attack;
			getEntity(entity)->attack += getItem(objet)->attack;
			getEntity(entity)->defense += getItem(objet)->defense;
			getEntity(entity)->speed += getItem(objet)->speed;
			return 0;
			
		}		
		current=current->next;	
	}
	
	return 1; //Pas trouvé item
}






void menuFouille(WINDOW* fouille,WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){
	Node** teamPlayer = &(gamestate->team_player); 
	Node** teamMonster = &(gamestate->team_monster); 
	//Node** inventory = &(gamestate->inventory);
	Score* highscore = gamestate->highscore;
	
	char message[CHAR_DESC_MAX];

	//Pour test...
	Node* headTrap = NULL;
	Node* trap = NULL;
	
	//Item objet999={"TUILE", "Et oui ça arrive à tout le monde","PIEGE",23.7,-1,-1,-1,-1};
	Item objet999={"TUILE", "Et oui ça arrive à tout le monde",TRAP,23.7,-1,-1,-1,-1};
	push(&headTrap, &objet999, sizeof(Item));
	trap = headTrap;
	//...

	int fouilleConvulsif;
	int ch;
	
	//Trame de fond
	fouille = frameWindow(8);	
	keypad(fouille,TRUE);
	wrefresh(fouille);
	
	mvwaddstr(fouille, hMenu-5,0,"Le temps perdu à fouiller vous coutera un peu d' energie et le resultat non garantie (PIEGE / ITEM / EQUIPEMENT) - Cross finger mon poulet!!");
	
	//Log
	char message2[]="=> FOUILLER";
	printfLog(log, message2, pLog, logText);
	

	int selection=0;
	int choix = 1;

	//char menuT[5][CHAR_DESC_MAX]={"Un cadavre","Nos poches","Les coins","Un coffre","Procrastiner"};
	char menuT[5][CHAR_DESC_MAX]={"CADAVRES","POCHES","RECOINS","COFFRE","STATUETTE"};
	
	keypad(fouille,TRUE);
	
	while( choix ){
	
		fouilleConvulsif=1; //:)
		
		wattron(fouille,COLOR_PAIR(1));
		wattron(fouille,A_BOLD);
		wattron(fouille,A_REVERSE);
		mvwprintw(fouille, 2+selection, 0,"%s",&menuT[selection][0]);
		wrefresh(fouille);
			
		switch ( wgetch(fouille) ){
			
			case KEY_DOWN:
							
				wattroff(fouille,COLOR_PAIR(1));
				wattroff(fouille,A_BOLD);
				wattroff(fouille,A_REVERSE);
				mvwprintw(fouille, 2+selection,0,"%s",&menuT[selection][0]);

				if(selection!=4){
					selection++;
				}
					
				wattron(fouille,COLOR_PAIR(1));
				wattron(fouille,A_BOLD);
				wattron(fouille,A_REVERSE);
				mvwprintw(fouille, 2+selection, 0,"%s",&menuT[selection][0]);
					
				wrefresh(fouille);
					
				break;
								
			case KEY_UP:
				
				wattroff(fouille,COLOR_PAIR(1));
				wattroff(fouille,A_BOLD);
				wattroff(fouille,A_REVERSE);
				mvwprintw(fouille, 2+selection, 0,"%s",&menuT[selection][0]);
				
				if(selection!=0){
					selection--;
				}
					
				wattron(fouille,COLOR_PAIR(1));
				wattron(fouille,A_BOLD);
				wattron(fouille,A_REVERSE);
				mvwprintw(fouille,2+selection, 0,"%s",&menuT[selection][0]);
				wrefresh(fouille);
					
				break;
						
			case 'q':
				choix = 0 ;
				break;
		
			case 10:	//touche enter			
								
				wattron(fouille,COLOR_PAIR(1));
				wattron(fouille,A_BOLD);
				wattron(fouille,A_REVERSE);
				wattron(fouille,A_ITALIC);
				mvwprintw(fouille, 2+selection, 0,"%s",&menuT[selection][0]);
				wrefresh(fouille);
		
				//On ecrit dans le log	
				strcpy(message,"Search or Not [S/N]");								
				printfLog (log, message, pLog, logText);
																
				wattroff(fouille,COLOR_PAIR(1));
				wattroff(fouille,A_BOLD);
				wattroff(fouille,A_REVERSE);
				
				while(fouilleConvulsif){
				
					keypad(fouille,TRUE);		
					ch = wgetch(fouille);	
							
					if( ch == 'S' || ch == 's' ){
		
						//Cout de la fouile		
						coutFouille(teamPlayer, COUT_HP_FOUILLE);
		
						switch  (selection){
						
							case 0:	//Fouiller un cadavre
							case 1:	//Fouiller nos poches
							case 2:	//Fouiller les coins
							case 3:	//Fouiller un coffre
							case 4:	//Statuette
		
								//"Item random: cherche un objet dans un file .csv, retourne un objet"
									
								//if ( strcmp( getItem(trap)->type, "PIEGE") == 0 ){
								if ( getItem(trap)->type == TRAP ){	
									//Log
									strcpy(message,"SEARCH: ");
									strcat(message,&menuT[selection][0]);
									strcat(message," -> PIEGE: ");
									strcat(message, getItem(trap)->name);					
									printfLog (log, message, pLog, logText);

									//Use item
									
										//Choix du 1er player de la liste
										Node* entity = *teamPlayer;
								
									useItem(&headTrap, trap,teamPlayer, entity);
									
									//Update affichage perso/monster
									WINDOW* game = frameWindow(1);
									afficheMonsterWin(game,*teamMonster);
									affichePersoWin(game,*teamPlayer);
									affichePersoReverseWin(game,entity);
									wrefresh(game);
									
									strcpy(message,"Search or Not [S/N]");								
									printfLog (log, message, pLog, logText);	
											
								}
												
								if ( getItem(trap)->type ==  EQUIPMENT ){	
									//PUSH inventaire
									//push(inventory, getItem(current), sizeof(Item));	
								}
										
								if ( getItem(trap)->type == ITEM ){	
									//PUSH inventaire
									//push(inventory, getItem(current), sizeof(Item));	
								}
								
								break;					
						
							/*
							case 1:		//Fouiller nos poches
							
							//Log
							strcpy(message,&menuT[selection][0]);
							printfLog (log, message, pLog, logText);
									
							//choix = 0 ; //pour quitter
			
								//return 1;
								
								break;

							
							case 2:		//Fouiller les coins"
								
								//Log
								strcpy(message,&menuT[selection][0]);
								printfLog (log, message, pLog, logText);
				
									//return 1;
								break;	
								
								
										
				
							case 3:		//Fouiller un coffre

								//Log
								strcpy(message,&menuT[selection][0]);
								printfLog (log, message, pLog, logText);
								
								//return 0;
								break;

							
							case 4:		//Statuette
								//Log
								strcpy(message,&menuT[selection][0]);
								printfLog (log, message, pLog, logText);
							
								choix = 0 ;
								fouilleConvulsif = 0;
								break;
							*/
						
						}
												
						wattroff(fouille,COLOR_PAIR(1));
						wattroff(fouille,A_BOLD);
						wattroff(fouille,A_REVERSE);
						wattroff(fouille,A_ITALIC);
							
						wrefresh(fouille);
						
						
						
						
				}
				
				if( ch == 'N' || ch == 'n' ){
					
					//choix = 0;
					fouilleConvulsif = 0;
				}
			}
							
		}
	}
}


void coutFouille(Node** teamPlayer, int cout){

	Node* current;
	
	current = *teamPlayer;

	getEntity(current)->health -= cout;

}

int venteInventaire(Score* highscore, Node** headInventory, Node* objet){

	Node* current = *headInventory;

	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
		
			highscore->money +=  getItem(objet)->price * COEFF_VENTE;
			
			return 0;
			
		}		
		current=current->next;	
	}
	
	return 1; //Pas trouvé item
}




int sameItem(Node** inventory, Node* objet){

	if(!inventory && !objet)
		return -1;

	Node* current = *inventory;
	int n=0;
	
	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
				
			return n;			
		}		
		current=current->next;	
		n++;
	}

	return -1;
}

//Plateau* generationRun(int nblevel,FILE* bdd_monster, FILE* bdd_item){ //Attente fct Thomas
int generationRun(int nblevel, Node** headPlateau){

	if(!headPlateau)
		return 1; //ko

	Plateau current;

	for(int i = nblevel; i > 0; i--){
	
		current.id = i;
		current.monsters = NULL;
		//current->treasure = NULL
		push(headPlateau, &current, sizeof(Plateau));
		
	}
	
	return 0; //OK
}
      	
int uddateGamestate(Node* plateau, GameState* gamestate){

	if(!gamestate || !plateau)
		return 1;
			
	//current->team_monster = run->monsters;
	gamestate->team_monster = getPlateau(plateau)->monsters;
	gamestate->treasure = getPlateau(plateau)->treasure;
	gamestate->highscore->alt = ( getPlateau(plateau)->id ) * 1000;
	
	return 0;

}
