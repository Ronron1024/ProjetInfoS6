#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <ncurses.h>
#include "defines.h"
#include "structures.h"

/*
For additionnals functions descriptions see :
    doc/functions.md
        or
    https://github.com/Ronron1024/ProjetInfoS6/blob/dev/doc/functions.md
*/



//Retourne un status en fonction du besoin: -1 ERREUR / 0 RAS / 1 FIGHT/ 2 SAVE / 3 QUITTER
int fenetrePlateau(GameState *gamestate);



//Affichage...

void printwCentered(const char* str);
void printwXCentered(int y, const char* str);
void printwYCentered(int x, const char* str);

void splashscreen();
GameMode homeMenu();

//Retourne les fenetres qui composent l' ecran de jeu principal
WINDOW* fenetreGame(WINDOW* game, int hGame,int wGame,int yGame,int xGame);
WINDOW* fenetreLog(WINDOW* log, int hLog,int wLog,int yLog,int xLog);
WINDOW* fenetreScore(WINDOW* score, int hScore, int wScore,int yScore,int xScore);
WINDOW* fenetreMenu(WINDOW* menu, int hMenu, int wMenu,int yMenu,int xMenu);

//Retourne la fenetre qui compose le menu boutique
WINDOW* boutiqueMenu(WINDOW* boutique, int hMenu, int wMenu,int yMenu,int xMenu);

//Retourne la fenetre qui compose le menu inventaire
WINDOW* inventaireMenu(WINDOW* inventaire, int hMenu, int wMenu,int yMenu,int xMenu);
//...



void boutiqueFct(WINDOW* boutique);

//Fontion qui retourne le choix utilisateur 0=>Boutique / 1=>Inventaire / 2=>Combat / 3=>Save / 4=>Quitter et qui transmet les log et le gamestate aux fonctions descendantes 
int selectionMenu(WINDOW* win, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);

// describe function !!!!
void affichePersoWin(WINDOW* win,Node* perso);
void affichePersoReverseWin(WINDOW* win,Node* perso);
void afficheMonsterWin(WINDOW* win,Node* monster);

void afficheAllObjetWin(WINDOW* win,Node* objet);
void afficheObjetWin(WINDOW* win,Node* objet, int n);
void afficheObjetWinReverse(WINDOW* win,Node* objet, int n);

int compterObjet(Node* objet);
void menuBoutique(WINDOW* boutique, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);

//Affiche la partie score avec une police classique
void afficheScore(WINDOW* win,Score* highScore);
//Affiche le champ money de la partie score avec une police reverse
void afficheScoreRev(WINDOW* win,Score* score);

int achatBoutique(Score* highScore, Node* objet);

void menuInventaire(WINDOW* inventaire, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
int venteInventaire(Score* highscore, Node** headInventory, Node* objet);
int sameItem(Node** inventory, Node* objet);

void printfLog (WINDOW* win, char* message, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX] );
void afficheLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void afficheAllLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void shiftArraw(char logText[LINE_LOG_MAX][CHAR_DESC_MAX] );

WINDOW* frameWindow(int number);

int mergeItem(Node* objet,Node** inventory);
void upgradeItem(Node* objet,Node** inventory);
int useItem(Node** headItem, Node* objet,Node** headEntity, Node* entity);

void menuFouille(WINDOW* fouille,WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void coutFouille(Node** teamPlayer, int cout);



// Linked Lists

void push(Node** head, const void* data, const size_t data_size);

void delete(Node** list, Node* node);

int count(Node* list);

void printList(Node* head, void (*fptr)(const void*));

void debugList(Node* head);

Node* getRandomNode(Node* list);

//OB à revoir
void sup(Node** head, Node* objet);



// Structures

void printEntity(const void* data);

Entity* getEntity(Node* liste);

Entity getEntityComputedStats(Entity entity);

bool isDead(Entity entity);

void printItem(const void* data);

Item* getItem(Node* liste);

Plateau* getPlateau(Node* liste);



// Gameplay

bool fight(Node** team1, Node** team2, char* log);

double attack(Entity* attacker, Entity* defender);

//Creation d' une liste chainée de plateau en fonction du nombre de level <=> une run // return 0 si OK
int generationRun(int nblevel,Node** headPlateau);

//Maj de la liste monstre et treasure dans le gamestate // return 0 si OK
int updateGamestate(Node* plateau, GameState* gamestate);



// Misc

int randInt(int min, int max);



#endif
