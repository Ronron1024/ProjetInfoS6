#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

#include <ncurses.h>
#include "defines.h"
#include "structures.h"

// C'est un peu le bordel là ...

int randInt(int min, int max);
bool fight(Node** team1, Node** team2, char* log);
double attack(Entity* attacker, Entity* defender);


void fenetrePlateau(GameState *gamestate);

WINDOW* fenetreGame(WINDOW* game, int hGame,int wGame,int yGame,int xGame);
WINDOW* fenetreLog(WINDOW* log, int hLog,int wLog,int yLog,int xLog);
WINDOW* fenetreScore(WINDOW* score, int hScore, int wScore,int yScore,int xScore);
WINDOW* fenetreMenu(WINDOW* menu, int hMenu, int wMenu,int yMenu,int xMenu);

WINDOW* boutiqueMenu(WINDOW* boutique, int hMenu, int wMenu,int yMenu,int xMenu);
void boutiqueFct(WINDOW* boutique);

int selectionMenu(WINDOW* win, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);


// describe function !!!!
void affichePersoWin(WINDOW* win,Node* perso);
void affichePersoReverseWin(WINDOW* win,Node* perso);
void afficheMonsterWin(WINDOW* win,Node* monster);


void afficheAllObjetWin(WINDOW* win,Node* objet);
void afficheObjetWin(WINDOW* win,Node* objet, int n);
void afficheObjetWinReverse(WINDOW* win,Node* objet, int n);


int compterObjet(Node* objet);
//void menuBoutique(WINDOW* boutique, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, Node* objetBoutique, Node** inventaire, Score* highScore, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void menuBoutique(WINDOW* boutique, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);

void afficheScore(WINDOW* win,Score* highScore);
void afficheScoreRev(WINDOW* win,Score* score);
int achatBoutique(Score* highScore, Node* objet);



WINDOW* inventaireMenu(WINDOW* inventaire, int hMenu, int wMenu,int yMenu,int xMenu);
//void menuInventaire(WINDOW* inventaire, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, Node** teamPlayer, Node* objetBoutique, Node** objetInventaire, Score* highScore, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void menuInventaire(WINDOW* inventaire, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
int venteInventaire(Score* highscore, Node** headInventory, Node* objet);
int sameItem(Node** inventory, Node* objet);


void printfLog (WINDOW* win, char* message, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX] );
void afficheLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void afficheAllLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void shiftArraw(char logText[LINE_LOG_MAX][CHAR_DESC_MAX] );

// To be removed
//void fenetreIntro(void);

WINDOW* frameWindow(int number);

int mergeItem(Node* objet,Node** inventory);
void upgradeItem(Node* objet,Node** inventory);
int useItem(Node** headItem, Node* objet,Node** headEntity, Node* entity);

void menuFouille(WINDOW* fouille,WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void coutFouille(Node** teamPlayer, int cout);


void push(Node** head, const void* data, const size_t data_size);
void delete(Node** list, Node* node);

void printList(Node* head, void (*fptr)(const void*));
void debugList(Node* head);
int count(Node* list);
Node* getRandomNode(Node* list);

void printEntity(const void* data);
void printItem(const void* data);
Entity* getEntity(Node* liste);
Entity getEntityComputedStats(Entity entity);
bool isDead(Entity entity);
Item* getItem(Node* liste);

//OB
void sup(Node** head, Node* objet);


void printwCentered(const char* str);
void printwXCentered(int y, const char* str);
void printwYCentered(int x, const char* str);

void splashscreen();
GameMode homeMenu();

#endif