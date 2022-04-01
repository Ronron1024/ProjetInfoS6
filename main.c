#include <stdio.h>
#include <stdlib.h>
#include "fenetre.h"
#include <ncurses.h>

int main (){


//Pour avoir des datas ...
	PERSO perso1={"HERCULE",12,NULL};
	PERSO perso2={"FLAMBI",13,NULL};
	
	OBJET objet1={"EPEE", "Epée de décoration qui peut couper de la purée",23.7,NULL,NULL};
	OBJET objet2={"FOURCHETTE", "Pour manger et piquer les monstres acessoireement",212.9,NULL,NULL};
	
	OBJET objet3={"DOUDOUNE", "Vetement de demi saison, procure une defense plutot faible",4.7,NULL,NULL};
	OBJET objet4={"POTION TABASCO", "Un remontant qui ne laisse pas indifferent",29.9,NULL,NULL};
	OBJET objet5={"TABAC", "Un peu fumeux pour une arme",20.5,NULL,NULL};
	
	SCORE score={100,200.0};
	
	OBJET *inventaire;
	OBJET *boutique;
	
	perso1.suivant = &perso2;
	
	objet1.suivant =&objet2;
	objet2.precedent=&objet1;
	
	objet3.suivant =&objet4;
	objet4.suivant=&objet5;
	objet4.precedent=&objet3;
	objet5.precedent=&objet4;
	
	inventaire = &objet1;
	boutique = &objet3;
	
	GAMESTATE GameState={&perso1,boutique,inventaire,&score};

//
	//Init ncurses
	initscr();
	cbreak();
	noecho();
	start_color();
	//
	
	fenetreIntro();
	fenetrePlateau(&GameState);
	
	//End ncurses
	endwin();
	//

	printf("BYE PADAWANN!!!!!!!!\n");	
	
	return 0;
}

