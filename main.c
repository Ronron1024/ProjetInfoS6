#include <stdio.h>
#include <stdlib.h>
#include "fenetre.h"
#include <ncurses.h>

void affichePerso(PERSO *perso);

int main (){

	PERSO perso1={"HERCULE",12,NULL};
	PERSO perso2={"FLAMBI",13,NULL};
	
	perso1.suivant = &perso2;
	
	affichePerso(&perso1);


	//Init ncurses
	initscr();
	cbreak();
	noecho();
	start_color();
	//


	fenetrePlateau(&perso1);
	
	//End ncurses
	endwin();
	//

	return 0;
}


void affichePerso(PERSO *perso){
	
	printf("|Name  :     %20s|\n",perso->name);
	printf("|Id:         %20d|\n",perso->id);
	
}
