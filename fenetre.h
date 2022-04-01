#ifndef INCLUDED_FENETRE_H
#define INCLUDED_FENETRE_H

#include <ncurses.h>

void fenetrePlateau(GameState *gamestate);

WINDOW* fenetreGame(WINDOW* game, int hGame,int wGame,int yGame,int xGame);
WINDOW* fenetreLog(WINDOW* log, int hLog,int wLog,int yLog,int xLog);
WINDOW* fenetreScore(WINDOW* score, int hScore, int wScore,int yScore,int xScore);
WINDOW* fenetreMenu(WINDOW* menu, int hMenu, int wMenu,int yMenu,int xMenu);

WINDOW* boutiqueMenu(WINDOW* boutique, int hMenu, int wMenu,int yMenu,int xMenu);
void boutiqueFct(WINDOW* boutique);
int selectionMenu(WINDOW* win, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, Node* objetBoutique, Node* objetInventaire, Score* highScore );

// describe function !!!!
void affichePersoWin(WINDOW* win,Node* perso);


void afficheAllObjetWin(WINDOW* win,Node* objet);
void afficheObjetWin(WINDOW* win,Node* objet, int n);
void afficheObjetWinReverse(WINDOW* win,Node* objet, int n);


int compterObjet(Node* objet);
void menuBoutique(WINDOW* boutique, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, Node* objetBoutique, Node* inventaire, Score* highScore);


void afficheScore(WINDOW* win,Score* highScore);
void afficheScoreRev(WINDOW* win,Score* score);
int achatBoutique(Score* highScore, Node* objet);



WINDOW* inventaireMenu(WINDOW* inventaire, int hMenu, int wMenu,int yMenu,int xMenu);
void menuInventaire(WINDOW* inventaire, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, Node* objetBoutique, Node* objetInventaire, Score* highScore);

void prinfLog (WINDOW* win, char* message );

void fenetreIntro(void);

#endif
