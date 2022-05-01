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

	//Pour les logs
	char logText[LINE_LOG_MAX][CHAR_DESC_MAX];
	int pLog = 0;	//Position ligne log
 	
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

	return selectionMenu(hMenu, wMenu, yMenu, xMenu, 1, 1, gamestate, &pLog, logText);

}
void afficheScore(WINDOW* win,Score* score){

	if(!score || !win){
		return;
	}

	mvwprintw(win, 2,1,"ALT: %d",score->alt);
	mvwprintw(win, 3,1,"MONEY: %-9.2f",score->money);	
}

void afficheScoreRev(WINDOW* win,Score* score){

	if(!score || !win){
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

	if(!perso || !win){
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
		mvwprintw(win, 20,espace*n+1,"EQUIPMENT");
		
		wattroff(win,A_BOLD);
		mvwprintw(win, 21,espace*n+1,"%s",getEntity(current)->armor.name);
		mvwprintw(win, 22,espace*n+1,"%s",getEntity(current)->weapon.name); 
		
		wattron(win,A_BOLD);
		
		current=current->next;
		n++;
		
	}
}

void affichePersoReverseWin(WINDOW* win,Node* perso){

	if(!perso || !win){
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

void afficheEquipmentReverseWin(WINDOW* win, Item* item, TypeEquipment typeEquipment, int n){

	if(!item || !win){
		return;
	}

	int espace = 15; //espace entre perso
	
	wattron(win,COLOR_PAIR(1));
	wattron(win,A_BOLD);
	wattron(win,A_REVERSE);

	if( typeEquipment == ARMOR)
		mvwprintw(win, 21,espace*n+1,"%s",item->name); 
	
	if( typeEquipment == WEAPON)
		mvwprintw(win, 22,espace*n+1,"%s",item->name);
		
	wattroff(win,COLOR_PAIR(1));
	wattroff(win,A_BOLD);
	wattroff(win,A_REVERSE);	
}

void ajoutStatusEquipment(Node* objet,TypeEquipment typeEquipment){

	if(!objet){
		return;
	}
	
	if( typeEquipment == WEAPON){
		strcat(getItem(objet)->name, " *W");
	}
		
	if( typeEquipment == ARMOR){
		strcat(getItem(objet)->name, " *A");
	}
}



void supStatusEquipment(Node* objet){

	if(!objet){
		return;
	}

	char text[CHAR_NAME_MAX];
	int i=0;
	
	while( getItem(objet)->name[i] != '*'){
		text[i] = getItem(objet)->name[i];
		i++;
	}
	
	text[i-1]='\0';
	
	strcpy(getItem(objet)->name, text);
}



void afficheMonsterWin(WINDOW* win,Node* monster){

	if(!monster || !win){
		return;
	}

	int espace = 15; //space between entities
	Node* current = NULL;
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

void afficheAllObjetWin(WINDOW* win,Node* objet, int page){

	if ( !objet || !win ){
		return;
	}

	int espace = 16; //espace entre perso
	Node* current;
	int n = 0;
		
	current = objet;
	
	//On avance le pointeur par rapport à la page ou on se situe
	for(int i=0; i< page*MAX_OBJET_AFFICHAGE;i++){	
		current=current->next;
	}

	while (current != NULL && n<MAX_OBJET_AFFICHAGE){

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

void afficheObjetWinReverse(WINDOW* win,Node* objet, int n){

	if ( !objet || !win ){
		return;
	}

	int espace = 16; //espace entre objet

	wattron(win,COLOR_PAIR(1));
	wattron(win,A_BOLD);
	wattron(win,A_REVERSE);

	mvwprintw(win, 1,espace*n,"%-16s",getItem(objet)->name);
	mvwprintw(win, 2,espace*n,"Price: %-9.2f",getItem(objet)->price);
	
	wattroff(win,COLOR_PAIR(1));
	wattroff(win,A_BOLD);
	wattroff(win,A_REVERSE);
}

WINDOW* fenetreGame(int hGame,int wGame,int yGame,int xGame){

	WINDOW* game;
		
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

WINDOW* fenetreLog(int hLog,int wLog,int yLog,int xLog){

	WINDOW* log;

	log = newwin(hLog,wLog,yLog,xLog);
				
	wattron(log,COLOR_PAIR(1));
	wattron(log,A_BOLD);
	box(log, 0,0);
	mvwprintw(log, 1,1,"LOG");
	wattroff(log,COLOR_PAIR(1));
	wattroff(log, A_BOLD);
		
	return log;

}

void printLogs()
{
	WINDOW* logs_win = frameWindow(6);
	FILE* logfile = fopen(LOGFILE, "r");
	char message[CHAR_LOG_MAX] = {0};
	int lines = 0;

	// Count lines
	while (fgets(message, CHAR_LOG_MAX, logfile))
		lines++;
	fseek(logfile, 0, SEEK_SET);

	// Place cursor
	for (int i = 0; i < lines - LINE_LOG_MAX; i++)
		fgets(message, CHAR_LOG_MAX, logfile);

	// Display LINE_LOG_MAX logs
	for (int i = 0; i < LINE_LOG_MAX && fgets(message, CHAR_LOG_MAX, logfile); i++)
	{
		if (i == LINE_LOG_MAX - 1 || i == lines - 1)
		{
			wattron(logs_win, COLOR_PAIR(PAIR_YELLOW_BLUE));
			wattron(logs_win, A_BOLD);
		}
		mvwprintw(logs_win, i, 0, message);
		if (i == LINE_LOG_MAX - 1 || i == lines - 1)
		{
			wattroff(logs_win, A_BOLD);
			wattroff(logs_win, COLOR_PAIR(PAIR_YELLOW_BLUE));
		}
	}

	wrefresh(logs_win);
}

void logMessage(char* raw_message)
{
	// Because raw_message is const
	char message[CHAR_LOG_MAX] = {0};
	strcpy(message, raw_message);

	FILE* logfile = fopen(LOGFILE, "a");
	if (!logfile) // must handle error
	{
		printf("Error while saving file\n");
		return;
	}

	strcat(message, "\n");
	fputs(message, logfile);

	fclose(logfile);

	printLogs();
}

void resetLogs()
{
	FILE* logfile = fopen(LOGFILE, "w");
	if (!logfile)
	{
		printf("Error while reseting logfile\n");
		return;
	}
	fclose(logfile);
}

WINDOW* fenetreScore(int hScore, int wScore,int yScore,int xScore){
	
	WINDOW* score;

	score = newwin(hScore,wScore,yScore,xScore);
	wattron(score,COLOR_PAIR(1));
	wattron(score,A_BOLD);
	box(score, 0,0);
	mvwprintw(score, 1,1,"Score");		   	
	wattroff(score,COLOR_PAIR(1));
	wattroff(score, A_BOLD);
		
	return score;

}

WINDOW* fenetreMenu(int hMenu, int wMenu,int yMenu,int xMenu){

	WINDOW* menu;

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

WINDOW* boutiqueMenu(int hMenu, int wMenu,int yMenu,int xMenu){

	WINDOW* boutique;

	boutique = newwin(hMenu-4,wMenu-2,yMenu+3,xMenu+1);
	mvwprintw(boutique, hMenu-5,wMenu-15,"QUIT: press q");
		
	return boutique;

}

WINDOW* inventaireMenu(int hMenu, int wMenu,int yMenu,int xMenu){

	WINDOW* inventaire;
	
	inventaire = newwin(hMenu-4,wMenu-2,yMenu+3,xMenu+1);
	mvwprintw(inventaire, hMenu-5,wMenu-15,"QUIT: press q");
	
	return inventaire;

}

WINDOW* saveMenu(int hMenu, int wMenu, int yMenu, int xMenu)
{
	WINDOW *saveWin = newwin(hMenu-4,wMenu-2,yMenu+3,xMenu+1);
	return saveWin;
}

int selectionMenu(int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]) {

	if(!gamestate)
		return -1;

	char message[CHAR_LOG_MAX] = {0};
			
	WINDOW* win; //menu
	WINDOW* game;
	WINDOW* scr;
	WINDOW* log;
	
	win = frameWindow(4);
	game = frameWindow(1);
	scr = frameWindow(3);
	log = frameWindow(6);

	afficheScore(scr, gamestate->highscore);
	printLogs();

	//afficheMonsterWin(game, gamestate->team_monster);
	//wrefresh(game);

	wrefresh(win);
	wrefresh(scr);
	// wrefresh(log);

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

		// afficheAllLog( frameWindow(6), pLog, logText);

		// wrefresh(log);

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
					
					
					
					return RAS;
				}
				
				if ( selection == 1 ){ //INVENTAIRE
					
					menuInventaire(scr, log, hMenu, wMenu, yMenu, xMenu, gamestate, pLog, logText);
					choix = 0 ;
					
					return RAS;
				}
				
	
				if ( selection == 2 ){ //FIGHT

					while (fight(&gamestate->team_player, &gamestate->team_monster, message))
					{
						logMessage(message);
						game = frameWindow(1);
						affichePersoWin(game, gamestate->team_player);
						afficheMonsterWin(game, gamestate->team_monster);
						wgetch(game); // delay
					}				
					
					if (gamestate->team_player)
						return PLAYING;
					else
						return GAMEOVER;
				}			
	
				if ( selection == 3 ){ //SAVE
					menuSave(gamestate);					
					choix = 0;
					return SAVE;
				}
				
				if ( selection == 4 ){ //QUITTER
					//choix = 0;
					
					return QUIT;
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

		n++;
		current=current->next;
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
	int page = 0;

	//log
	// printfLog(log, "=> BOUTIQUE", pLog, logText);
	logMessage("=> BOUTIQUE");
	
	//Fenetre
	boutique = frameWindow(5);	
	keypad(boutique,TRUE);
	
	//Init liste objet boutique
	current = shop;
	
	//Log									
	sprintf(message, "%-6.2f",getItem(current)->price);
	strcat(message, " ACHAT [Oo]");				
	// printfLog (log, message, pLog, logText);
	logMessage(message);
				
	while(choix){

		//Affichage divers objet
		boutique = frameWindow(5);	
		keypad(boutique,TRUE);
		afficheAllObjetWin(boutique,shop,page);		
		cmptObjet = compterObjet(shop);

					
		afficheObjetWinReverse(boutique,current, n%MAX_OBJET_AFFICHAGE);
		mvwaddstr(boutique, hMenu-5,0,getItem(current)->description);
		wrefresh(boutique);
							
		switch ( wgetch(boutique) ){
			
			case KEY_RIGHT:
								
				if(n!=cmptObjet-1){
				
					current=current->next;
					n++;
					page = n / MAX_OBJET_AFFICHAGE;
					
					//Log									
					sprintf(message, "%-6.2f",getItem(current)->price);
					strcat(message, " ACHAT [Oo]");				
					// printfLog (log, message, pLog, logText);
					logMessage(message);
				}
				break;
				
			case KEY_LEFT:
						
				if(n!=0){
					current=current->prev;
					n--;
					page = n / MAX_OBJET_AFFICHAGE;
					
					//Log									
					sprintf(message, "%-6.2f",getItem(current)->price);
					strcat(message, " ACHAT [Oo]");				
					// printfLog (log, message, pLog, logText);
					logMessage(message);					
				}
				break;		
			
			case 'O':
			case 'o':						
					
				if( achatBoutique(highscore, current) == 0){
								
					//Update money & inventory
					afficheScoreRev(scr,highscore);
					push(inventory, getItem(current), sizeof(Item));
					wrefresh(scr);
									
					//Log
					strcpy(message,"ACHAT: ");
					strcat(message, getItem(current)->name);
					strcat(message, " OK");
					// printfLog (log, message, pLog, logText);
					logMessage(message);		
				}
								
				else{
					//Log
					strcpy(message,"ACHAT: ");
					strcat(message, getItem(current)->name);
					strcat(message, " KO");					
					// printfLog (log, message, pLog, logText);
					logMessage(message);
				}		
						
				wrefresh(boutique);
				break;	
											
			case 'q':
			case 'Q':
				choix = 0 ;
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
					
void menuInventaire(WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){

	Node** teamPlayer = &(gamestate->team_player); 
	Node** teamMonster = &(gamestate->team_monster);
	//Node* shop = gamestate->shop;
	Node** inventory = &(gamestate->inventory);
	Score* highscore = gamestate->highscore;
	
	//Choix du 1er de la liste
	Node* entity = *teamPlayer;
	
	Node* current;

	WINDOW* game;
	game = frameWindow(1);
	
	WINDOW* inventaire;
	inventaire = frameWindow(7);	
	keypad(inventaire,TRUE);
		
	char message[CHAR_DESC_MAX];

	int n = 0;
	int cmptObjet;
	int choix = 1;
	int page=0;
	
	//Log
	// printfLog(log, "=> INVENTAIRE", pLog, logText);
	logMessage("=> INVENTAIRE");
	
	//Init liste inventaire
	current = *inventory;
	
	//Log
	if (current != NULL){
		strcpy(message,"Use, Merge or Sell [U/M/S]");									
		// printfLog (log, message, pLog, logText);
		logMessage(message);
	}
	
	while(choix){
	
		//On dessine les objets
		inventaire = frameWindow(7);	
		keypad(inventaire,TRUE);
	
		afficheAllObjetWin(inventaire,*inventory, page);
		afficheObjetWinReverse(inventaire,current, n%MAX_OBJET_AFFICHAGE);	
		
		if(current != NULL){
			mvwaddstr(inventaire, hMenu-5,0,getItem(current)->description);
		}
		else{
			mvwaddstr(inventaire, hMenu-5,0,"C' est vide papa!!");
		}
		
		cmptObjet = compterObjet(*inventory);

		wrefresh(inventaire);

			switch ( wgetch(inventaire) ){
			
				case KEY_RIGHT:

					if( n!=cmptObjet-1 &&  cmptObjet!= 0){
						current=current->next;
						n++;
						page = n / MAX_OBJET_AFFICHAGE;
						
						//Log
						strcpy(message,"Use, Merge or Sell [U/M/S]");									
						// printfLog (log, message, pLog, logText);
						logMessage(message);

					}	
					break;
								
				case KEY_LEFT:
								
					if ( n!=0 ) {
						current=current->prev;
						n--;
						page = n / MAX_OBJET_AFFICHAGE;
						
						//Log
						strcpy(message,"Use, Merge or Sell [U/M/S]");									
						// printfLog (log, message, pLog, logText);
						logMessage(message);

					}
					break;
						
				case 'q':
				case 'Q':
					choix = 0 ;
					break;
						
				case 'U':
				case 'u':

					if( isUseItem(inventory, current, teamPlayer, entity) == 1 ){
													
						//Log
						strcpy(message, "USE: ");
						strcat(message, getItem(current)->name);
						strcat(message, " OK");				
						// printfLog(log, message, pLog, logText);
						logMessage(message);

						//Suppression inventaire
						sup(inventory, current);
						
						//On se repositione sur le meme item si i l' existe
						if ( sameItem(inventory,  current) >= 0){
							
							n= sameItem(inventory,  current);
							page = n / MAX_OBJET_AFFICHAGE;
						}
						
						//Si le meme item n' exite pas, on se posiotionne au début la liste
						if ( sameItem(inventory,  current) < 0){
							current = *inventory;
							page =0;
							n = 0;
						}

						//Update affichage perso/monster	
						afficheMonsterWin(game,*teamMonster);
						affichePersoWin(game,*teamPlayer);
						affichePersoReverseWin(game,entity);
						wrefresh(game);
						
						
						
					}									

					///Test sur l objet et si l' equipement est equipé
					else if( isEquipedItem(current) == 1 ){
					
						//On desequipe
							switch (searchEntityEquiped(current)) {
							
								case ARMOR: 
						 	
									removeItemToPerso(&getEntity(entity)->armor );
								
									if (notUseItem(inventory,  current, teamPlayer, entity) !=0 ){
										return;
									}
								
									//Log
									strcpy(message, "ARMOR REMOVED: ");
									strcat(message, getItem(current)->name);
									strcat(message, " OK");
									// printfLog(log, message, pLog, logText);
									logMessage(message);
									
									//Affichage
									game = frameWindow(1);
									affichePersoWin(game,*teamPlayer);
									affichePersoReverseWin(game,entity);
									afficheMonsterWin(game,*teamMonster);
									afficheEquipmentReverseWin(game,&getEntity(entity)->weapon,ARMOR,0); //0 <=> au premier perso
									supStatusEquipment(current);
									wrefresh(game);
									break;						 	
						 		
						
								case WEAPON:
							
									removeItemToPerso(&getEntity(entity)->weapon );
								
									if (notUseItem(inventory,  current, teamPlayer, entity) !=0 ){
										return;
									}
								
									//Log
									strcpy(message, "WEAPON REMOVED: ");
									strcat(message, getItem(current)->name);
									strcat(message, " OK");
									// printfLog(log, message, pLog, logText);
									logMessage(message);
									
									//Affichage
									game = frameWindow(1);
									affichePersoWin(game,*teamPlayer);
									affichePersoReverseWin(game,entity);
									afficheMonsterWin(game,*teamMonster);
									afficheEquipmentReverseWin(game,&getEntity(entity)->weapon,WEAPON,0); //0 <=> au premier perso
									supStatusEquipment(current);
									wrefresh(game);
									break;								
						 	}
							
						//}				
					}

					else if ( isEquipItem(current, entity) == 1 ) {
						
						//On equipe  						
						switch ( testEntityEquiped(entity) ){
						
							case ARMOR:
							
								copyItemToPerso(current, &getEntity(entity)->armor);
								
								if (useItem(inventory,  current, teamPlayer, entity) !=0 ){
									return;
								}
								
								//Log
								strcpy(message, "ARMOR EQUIPED: ");
								strcat(message, getItem(current)->name);
								strcat(message, " OK");
								// printfLog(log, message, pLog, logText);
								logMessage(message);
								
								//Affichage
								game = frameWindow(1);
								affichePersoWin(game,*teamPlayer);
								affichePersoReverseWin(game,entity);
								afficheMonsterWin(game,*teamMonster);
								afficheEquipmentReverseWin(game,&getEntity(entity)->armor,ARMOR,0); //0 <=> au premier perso
								ajoutStatusEquipment(current,ARMOR);
								wrefresh(game);
								
								break;							
								
							case WEAPON:
							
								copyItemToPerso(current, &getEntity(entity)->weapon);
								
								if (useItem(inventory,  current, teamPlayer, entity) !=0 ){
									return;
								}
								
								//Log
								strcpy(message, "WEAPON EQUIPED: ");
								strcat(message, getItem(current)->name);
								strcat(message, " OK");
								// printfLog(log, message, pLog, logText);
								logMessage(message);
								
								//Affichage
								game = frameWindow(1);
								affichePersoWin(game,*teamPlayer);
								affichePersoReverseWin(game,entity);
								afficheMonsterWin(game,*teamMonster);
								afficheEquipmentReverseWin(game,&getEntity(entity)->weapon,WEAPON,0); //0 <=> au premier perso
								ajoutStatusEquipment(current,WEAPON);
								wrefresh(game);
								
								break;
						}
							
					}
					
					else{	
						//Log
						strcpy(message, "USE: ");
						
						if(current){
							strcat(message, getItem(current)->name);
						}
						
						strcat(message, " KO");			
						// printfLog(log, message, pLog, logText);
						logMessage(message);
					}
					break;
		
				case 'M':
				case 'm':
					//test moins 2 Items du meme genre
					if ( multiSameItem(inventory,  current) > 1){
						
						//On recupere l' objet merger
						current = mergeItem(current,inventory);		
							
						strcpy(message, "MERGE: ");
						strcat(message, getItem(current)->name);
						strcat(message, " OK");
									
						// printfLog(log, message, pLog, logText);
						logMessage(message);
								
						//On se repositione sur un objet identique
						n= sameItem(inventory,  current);
						page = n / MAX_OBJET_AFFICHAGE;

						//Update affichage inventaire
						inventaire = frameWindow(7);	
						keypad(inventaire,TRUE);
						afficheAllObjetWin(inventaire,*inventory,page);
						afficheObjetWinReverse(inventaire,current, n%MAX_OBJET_AFFICHAGE);
						wrefresh(inventaire);
					}			
					else{
						//Log
						strcpy(message, "MERGE: ");
						
						if(current){
							strcat(message, getItem(current)->name);
						}
						
						strcat(message, " KO");			
						// printfLog(log, message, pLog, logText);
						logMessage(message);		
					}
					break;
									
				case 'S':
				case 's':	
								
					if( isSellItem(inventory, current, highscore) == 1 ){
					
						//Suppression de l' objet vendu dans l'inventaire
						sup(inventory, current);
					
						//Log
						strcpy(message, "SOLD: ");
						strcat(message, getItem(current)->name);
						strcat(message, " OK");				
						// printfLog(log, message, pLog, logText);
						logMessage(message);
								
						//Update affichage "money"
						afficheScoreRev(scr,highscore);
						wrefresh(scr);
					
						//On se repositione sur le meme item si i l' existe
						if ( sameItem(inventory,  current) >= 0){
							
							n= sameItem(inventory,  current);
							page = n / MAX_OBJET_AFFICHAGE;
						}
						
						//Si le meme item n' exite pas, on se posiotionne au début la liste
						if ( sameItem(inventory,  current) < 0){
							current = *inventory;
							page =0;
							n = 0;
						}
					}
					else{
						//Log	
						strcpy(message, "SOLD: ");
						
						if(current){
							strcat(message, getItem(current)->name);
						}
							
						strcat(message, " KO");				
						// printfLog(log, message, pLog, logText);
						logMessage(message);		
					}
					
					break;						
				default:
					break;	
					
			}
		}
}

void menuSave(GameState *gamestate)
{
	WINDOW* save_win = frameWindow(8);
	char save_file[CHAR_SAVE_MAX] = {0};
	char message[CHAR_LOG_MAX] = {0};
	int key = -1;

	if (strcmp(gamestate->save_file, "") == 0)	// Save file not defined
	{
		mvwprintw(save_win, 2, 2, "Save in : ");
		input(save_win, save_file, CHAR_SAVE_MAX);
		strcpy(gamestate->save_file, save_file);
	}
	else
	{
		mvwprintw(save_win, 2, 2, "Save in %s ? (O/n)", gamestate->save_file);
		while (key != 0)
		{
			key = wgetch(save_win);
			switch(key)
			{
				case 'O':
				case 'o':
					key = 0;
					break;
				case 'N':
				case 'n':
					strcpy(gamestate->save_file, "");
					wclear(save_win);
					menuSave(gamestate);
					return;
					break;
				default:
					key = -1;
			}
		}
	}

	// Save the game
	sprintf(message, "Game saved in %s", gamestate->save_file);
	logMessage(message);
}

void input(WINDOW* win, char* buffer, int buffer_size)
{
	int key = 0;
	while ((key = wgetch(win)) != KEY_RETURN)
	{
		if (
			strlen(buffer) < buffer_size &&
				((key >= 'A' && key <= 'Z') ||
				(key >= 'a' && key <= 'z') ||
				(key >= '0' && key <= '9') ||
				key == '_' || key == '-' || key == '.')
		)
		{
			wprintw(win, "%c", key);
			strcat(buffer, (char*) &key);
		}
		else if (key == KEY_ERASE)
		{
			buffer[strlen(buffer)-1] = '\0';
			wclear(win);
			mvwprintw(win, 2, 2, "Save in : %s", buffer);
		}
	}
}


//A SUP
/*void printfLog (WINDOW* win, char* message, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX] ){

	if(!message || !pLog)
		return;

	WINDOW* log;

	int yMax,xMax;
	getmaxyx(stdscr,yMax,xMax);

	int hLog = 7;
	int wLog = xMax;
	int yLog = yMax-hLog;
	int xLog = 0;
	
	wclear(win);
	
	win = fenetreLog(hLog, wLog, yLog, xLog);
	
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

*/

WINDOW* frameWindow(int number){

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
			return fenetreGame(hGame,wGame,yGame,xGame);
			break;
			
			
		case 2:
			return fenetreLog(hLog, wLog, yLog, xLog);
			break;
			
			
		case 3:
			return fenetreScore(hScore, wScore,yScore,xScore);
			break;
					
		case 4:
			return fenetreMenu(hMenu,wMenu,yMenu,xMenu);
			break;
			
		case 5:
			return boutiqueMenu(hMenu, wMenu,yMenu,xMenu);
			break;	
			
		case 6:	
			return newwin(hLog-3,wLog-2,yLog+2,xLog+1);	
			break;
			
			
		case 7:	
			return inventaireMenu(hMenu, wMenu,yMenu,xMenu);	
			break;
				
		case 8:
			return saveMenu(hMenu, wMenu, yMenu, xMenu);
			break;			
			
		default:
			break;
	}
	
	return NULL;
}


Node* mergeItem(Node* objet,Node** inventory){

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
				
				return current;
						
			}
				
		current=current->next;	
				
		}			
	}

	return NULL;

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

	if( !headItem || !objet ||!headEntity || !entity){
		return 1;
	}

	Node* current = *headItem;

	while (current != NULL){ 							//On verifie que l' objet est bien dans l' inventaire
	
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


int notUseItem(Node** headItem, Node* objet,Node** headEntity, Node* entity){

	if( !headItem || !objet ||!headEntity || !entity){
		return 1;
	}

	Node* current = *headItem;

	while (current != NULL){ 							//On verifie que l' objet est bien dans l' inventaire
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){
	
			getEntity(entity)->health -= getItem(objet)->attack;
			getEntity(entity)->attack -= getItem(objet)->attack;
			getEntity(entity)->defense -= getItem(objet)->defense;
			getEntity(entity)->speed -= getItem(objet)->speed;
			return 0;
			
		}		
		current=current->next;	
	}
	
	return 1; //Pas trouvé item
}






void copyItemToPerso(Node* objet, Item* item ){

	if(!objet || !item){
		return;
	}
	
	strcpy( item->name, getItem(objet)->name );
	strcpy( item->description, getItem(objet)->description );
	item->type = getItem(objet)->type;
	item->price = getItem(objet)->price;
	item->health = getItem(objet)->health;
	item->attack = getItem(objet)->attack;
	item->defense = getItem(objet)->defense;
	item->speed = getItem(objet)->speed;
}


void removeItemToPerso(Item* item ){

//Item null_item = {"NULL", "NULL",NULL_ITEM,0,0,0,0,0};

	if(!item)
		return;
		
	strcpy( item->name, "NULL");	
	strcpy( item->description, "NULL");
	item->type = NULL_ITEM;
	item->price = 0;
	item->health = 0;
	item->attack = 0;
	item->defense = 0;
	item->speed = 0;			
}



//
//int removeItemWeapon(Node** headItem, Node* objet,Node** headEntity, Node* entity){ //equipent ->Invzntriere

//	if( !headItem || !objet ||headEntity || !entity){
//		return 1;
//	}






void coutFouille(Node** teamPlayer, int cout){

	Node* current;
	
	current = *teamPlayer;

	getEntity(current)->health -= cout;

}

//Retourne 0 si la vente de l' objet est faite
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



//Retourne la position de objet dans la liste
int sameItem(Node** inventory, Node* objet){

	if ( !inventory && !objet )
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

//Retourne le nombre d' objet dans la liste
int multiSameItem(Node** inventory, Node* objet){

	if ( !inventory && !objet )
		return -1;

	Node* current = *inventory;
	int n=0;
	
	while (current != NULL){
	
		if( strcmp(getItem(objet)->name, getItem(current)->name) ==0){		
			n++;	
		}		
		current=current->next;	
	}
	return n;
}
				
//Fonction qui retourne 0 si l' objet est equipé
int testItemEquiped(Node* objet){

	char text[CHAR_NAME_MAX];
	int i=0;

	strcpy( text, getItem(objet)->name);
	
	while( text[i] != '\0'){
	
		if( text[i] == '*'){
		
			return 0;	//equiped
		}
		
		i++;
	}
	
	return -1; 			//Not equiped

}

//Fonction qui retourne -1 si il n y a plus de place dispo sur le perso / 0 pour position ARMOR libre / 1 pour position WEAPON libre
int testEntityEquiped(Node* entity){

	if( getEntity(entity)->armor.type == NULL_ITEM )
		return 0;
	if( getEntity(entity)->weapon.type == NULL_ITEM )
		return 1;
	
	return -1;
}


//Recherche de la position occupé par l' objet sur l' entité => retourne -1 si probleme / 0 pour position ARMOR  / 1 pour position WEAPON 
int searchEntityEquiped(Node* objet){

	char text[CHAR_NAME_MAX];
	int i=0;
	
	strcpy( text, getItem(objet)->name);
	
	while( text[i] != '\0'){
		
		if( text[i] == '*'){
			
			i++;
			
			if( text[i] == 'A')
				return 0;	//ARMOR equiped
			if( text[i] == 'W')
				return 1;	//WEAPON equiped
		}
		
		i++;
	}
	
	return -1; 			//Not found??

}


//Conditions pour utiliser un ITEM: 1 de type ITEM / 2 Ajout au stat c' est bien passé 3 objet non nul
int isUseItem(Node ** inventory, Node* current, Node** teamPlayer, Node* entity){

	if(!inventory || !current || !teamPlayer || !entity)
		return -1;

	else 
		return ( getItem(current)->type == ITEM && useItem(inventory,  current, teamPlayer, entity) == 0 );
}




///Condition pour désequiper => /1 de type EQUIPEMENT /2 l' equipement est deja equipé /3 objet non null
int isEquipedItem(Node* current){

	if (!current)
		return -1;
	else
		return ( getItem(current)->type == EQUIPMENT && testItemEquiped(current) == 0 );
}
		
//Condition pour vendre un Item =>1/Equipement non équipé /2 La vente s' est bien déroulé /3 Objet non null
int isSellItem (Node** inventory, Node* current, Score* highscore){

	if( !inventory || !current || !highscore)
		return -1;
	else
		return ( testItemEquiped(current) !=0 && venteInventaire(highscore, inventory, current) == 0 );
}



//Condition pour equiper un equipement =>1/ de type equipement 2/Entity non equipé 3/equipemnt non equipé
int isEquipItem(Node* current, Node* entity){
	if(!current || !entity)
		return -1;

	else 
	return ( getItem(current)->type == EQUIPMENT && testEntityEquiped(entity) != -1 && testItemEquiped(current) != 0);
}

//FOUILLE
//Retoune 0/Si il n' accepte pas /1 si il accepte la fouille 
int IsSearch(int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]){

	WINDOW* win;
	WINDOW* log;
	char message[CHAR_NAME_MAX];
	int choix = 1;
	
	log = frameWindow(5);
	wrefresh(log);
	
	//Log									
	strcpy(message, "FOUILLE [O/N]");				
	// printfLog (log, message, pLog, logText);
	logMessage(message);

	while(choix){

		//Affichage divers
		win = frameWindow(5);
		mvwaddstr(win, 0,0,"On fouille ou pas?");	
		keypad(win,TRUE);
		wrefresh(win);
							
		switch ( wgetch(win) ){
			
		
			case 'O':
			case 'o':	
			
				strcpy(message, "FOUILLE OK");				
				// printfLog (log, message, pLog, logText);
				logMessage(message);			
					
				return 1;
				break;	
				
				
			case 'N':
			case 'n':	
			
				strcpy(message, "FOUILLE KO");				
				// printfLog (log, message, pLog, logText);
				logMessage(message);						
					
				return 0;
				break;		
											
			//case 'q':
			//case 'Q':
			//	choix = 0 ;
			//	break;
				
		}
	}
	return 0;
}

void gameOverScreen()
{
	clear();
	mvprintw(0,0,"Game over !");
	getch();
}
//...





/*Plateau* generationRun(int nblevel,FILE* bdd_monster, FILE* bdd_item){ //Attente fct Thomas
int generationRun(int nblevel, Node** headPlateau){

	if(!headPlateau)
		return 1; //ko

	Plateau current;

	for(int i = nblevel; i > 0; i--){
	
		current.id = i;
		current.monsters = NULL;
		current.treasure.price = 190;
		push(headPlateau, &current, sizeof(Plateau));
		
	}
	
	return 0; //OK
}
*/
   
   
      	
int updateGamestate(Node* plateau, GameState* gamestate){

	if(!gamestate || !plateau)
		return 1;
			
	gamestate->team_monster = getPlateau(plateau)->monsters;
	gamestate->treasure = getPlateau(plateau)->treasure;
	gamestate->highscore->alt = ( getPlateau(plateau)->id ) * 1000;
	
	return 0;

}

void deleteSave(char* save_path)
{
	// No save
	if (strcmp(save_path, "") == 0)
		return;

	int save_path_length = strlen(SAVE_FOLDER) + CHAR_SAVE_MAX + strlen(".bin");
	char* full_save_path = malloc(sizeof(char) * save_path_length);
	strcpy(full_save_path, SAVE_FOLDER);
	strcat(full_save_path, save_path);
	strcat(full_save_path, ".bin");

	remove(full_save_path);
	free(full_save_path);
}