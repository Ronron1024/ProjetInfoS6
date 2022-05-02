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



#pragma region Displaying
//Affichage...

void printwCentered(const char* str);
void printwXCentered(int y, const char* str);
void printwYCentered(int x, const char* str);

void splashscreen();
GameMode homeMenu();

// Continue menu, chose save
char* menuContinue();

// Ncurses input text
void input(WINDOW* win, char* buffer, int buffer_size);

//Retourne les fenetres qui composent l' ecran de jeu principal
WINDOW* fenetreGame(int hGame,int wGame,int yGame,int xGame);
WINDOW* fenetreLog(int hLog,int wLog,int yLog,int xLog);
WINDOW* fenetreScore(int hScore, int wScore,int yScore,int xScore);
WINDOW* fenetreMenu(int hMenu, int wMenu,int yMenu,int xMenu);

// Logging
WINDOW* printLogs();
WINDOW* logMessage(char* message);

// Game over screen
void gameOverScreen();

//Retourne la fenetre qui compose le menu boutique
WINDOW* boutiqueMenu(int hMenu, int wMenu,int yMenu,int xMenu);

//Retourne la fenetre qui compose le menu inventaire
WINDOW* inventaireMenu(int hMenu, int wMenu,int yMenu,int xMenu);
//...

// Return save window
WINDOW* saveMenu(int hMenu, int wMenu, int yMenu, int xMenu);

//Fct menu inventaire
void menuInventaire(WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);

// save menu
void menuSave(GameState *gamestate);

//Fontion qui retourne le choix utilisateur 0=>Boutique / 1=>Inventaire / 2=>Combat / 3=>Save / 4=>Quitter et qui transmet les log et le gamestate aux fonctions descendantes 
int selectionMenu(int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);

// describe function !!!!
void affichePersoWin(WINDOW* win,Node* perso);
void affichePersoReverseWin(WINDOW* win,Node* perso);
void afficheMonsterWin(WINDOW* win,Node* monster);

//Affiche les objets item dans la fenetre win par page
void afficheAllObjetWin(WINDOW* win,Node* objet, int page);

//void afficheObjetWin(WINDOW* win,Node* objet, int n);
void afficheObjetWinReverse(WINDOW* win,Node* objet, int n);

int compterObjet(Node* objet);
void menuBoutique(WINDOW* win, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState *gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);

//Affiche la partie score avec une police classique
void afficheScore(WINDOW* win,Score* highScore);
//Affiche le champ money de la partie score avec une police reverse
void afficheScoreRev(WINDOW* win,Score* score);

int achatBoutique(Score* highScore, Node* objet);

//Retourne 0 si la vente de l' objet est faite
int venteInventaire(Score* highscore, Node** headInventory, Node* objet);

//Retourne la position de objet dans la liste
int sameItem(Node** inventory, Node* objet);
//Retourne le nombre d' objet dans la liste
int multiSameItem(Node** inventory, Node* objet);

void printfLog (WINDOW* win, char* message, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX] );
void afficheLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void afficheAllLog(WINDOW* log, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void shiftArraw(char logText[LINE_LOG_MAX][CHAR_DESC_MAX] );

WINDOW* frameWindow(int number);

Node* mergeItem(Node* objet,Node** inventory);
void upgradeItem(Node* objet,Node** inventory);

//Ajoute les stats de l 'objet à l' entité, retourne si cela s' est bien passé
int useItem(Node** headItem, Node* objet,Node** headEntity, Node* entity);
//Retire les stats de l 'objet à l' entité
int notUseItem(Node** headItem, Node* objet,Node** headEntity, Node* entity);

//void menuFouille(WINDOW* fouille,WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, GameState* gamestate, int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);
void coutFouille(Node** teamPlayer, int cout);
#pragma endregion



#pragma region LinkedLists
// Linked Lists

void freeList(Node* head);

void push(Node** head, const void* data, const size_t data_size);

void delete(Node** list, Node* node);

int count(Node* list);

void printList(Node* head, void (*fptr)(const void*));

void debugList(Node* head);

void saveList(Node* head, FILE* save_file, void (*fptr)(const void*, FILE*));

Node* getRandomNode(Node* list);

//OB à revoir
void sup(Node** head, Node* objet);
#pragma endregion



#pragma region Structures
// Structures

void initGameState(GameState* gamestate);

void printEntity(const void* data);

Entity* getEntity(Node* liste);

Entity getEntityComputedStats(Entity entity);

void saveEntity(const void* data, FILE* save_file);

bool isDead(Entity entity);

void printItem(const void* data);

Item* getItem(Node* liste);

Item getNullItem();

Item* upItem(Item* item, int level);

void saveItem(const void* data, FILE* save_file);

Entity getNullEntity();

Item getRandomItem();
Item getRandomTrap();

Plateau* getPlateau(Node* liste);

void savePlateau(const void* data, FILE* save_file);
#pragma endregion



#pragma region Gameplay
// Gameplay

// Save the game
void saveGame(Node* run, GameState gamestate);

// Load a game
void loadGame(Node** run, GameState* gamestate);

// Reset logging when it's a new game
void resetLogs();

// Game over, delete save
void deleteSave(char* save_path);

// Init shop when it's a new game
void initShop(Node** shop);

// Upgrade shop according to settings
void upgradeShop(Node** shop, int level);

//Retourne un status en fonction du besoin: -1 ERREUR / 0 RAS / 1 FIGHT/ 2 SAVE / 3 QUITTER
int fenetrePlateau(GameState *gamestate);

bool fight(Node** team1, Node** team2, char* log);

void addStats(Entity* entity, Item item);

void fouille(WINDOW* game, GameState* gamestate);

double attack(Entity* attacker, Entity* defender);

bool canGetAlly();

// Reward the player at the end of a level
void rewardPlayer(Score* score, int level);

//Creation d' une liste chainée de plateau en fonction du nombre de level <=> une run // return 0 si OK
int generationRun(int nblevel,Node** headPlateau);

// Add next plateau (level)
int generateNextPlateau(Node** run);

//Maj de la liste monstre et treasure dans le gamestate // return 0 si OK
int updateGamestate(Node* plateau, GameState* gamestate);

//Copie un objet dans la structure Item (on utimsera entity->weapon or armor)
void copyItemToPerso(Node* objet, Item* item );

//Supprime un Item (on utimsera entity->weapon or armor)
void removeItemToPerso(Item* item );

//Affiche en reverse  l' item de type equiptement à la position n dans la fenetre win
void afficheEquipmentReverseWin(WINDOW* win,Item* item, TypeEquipment, int n);

//Rajoute au nom de l' équipement un status qui indique si il est porté ou non (*)
void ajoutStatusEquipment(Node* objet,TypeEquipment typeEquipment);
void supStatusEquipment(Node* objet);

//Fonction qui retourne 0 si l' objet est equipé
int testItemEquiped(Node* objet);

//Fonction qui retourne -1 si il n y a plus de place dispo sur le perso / 0 pour position ARMOR libre / 1 pour position WEAPON libre
int testEntityEquiped(Node* entity);

//Recherche de la position occupé par l' objet sur l' entité => retourne -1 si probleme / 0 pour position ARMOR  / 1 pour position WEAPON 
int searchEntityEquiped(Node* objet);

//Conditions pour utiliser un ITEM: 1 de type ITEM / 2 Ajout au stat c' est bien passé 3 objet non nul
int isUseItem(Node ** inventory, Node* current, Node** teamPlayer, Node* entity);

//Condition pour désequiper => /1 de type EQUIPEMENT /2 l' equipement est deja equipé /3 objet non null
int isEquipedItem(Node* current);

//Condition pour vendre un Item =>1/Equipement non équipé /2 La vente s' est bien déroulé /3 Objet non null
int isSellItem (Node** inventory, Node* current, Score* highscore);

//Condition pour equiper un equipement =>1/ de type equipement 2/Entity non equipé 3/equipemnt non equipé
int isEquipItem(Node* current, Node* entity);

//Retoune 0/Si il n' accepte pas /1 si il accepte la fouille 
int IsSearch(int* pLog, char logText[LINE_LOG_MAX][CHAR_DESC_MAX]);


//BDD
Item* recupererLigne(char*ligne);
Entity* recupererLigneEntity(char*ligne);
Node*chargerTxtItem(char*nomFichier);
Node* chargerTxtEntity(char*nomFichier);
//Item*insertionAlpha(Item*liste,Item*nouvelElement);
Item*saisirElementItem(void);
Item*saisirElementArme(void);
Item*saisirElementObjet(void);
void printMenu(void);
void printSousMenu(void);
void printAjoutListe(void);
void saveTxt(Node*liste,char*nomFichier);
void afficheListe(Node *liste);
void afficheElement(Item *elem);
void afficheListeRec(Node *liste);
Entity selectEntity(Node* head, int n);
Entity modified(Entity monster, int id);

//

#pragma endregion


#pragma region Misc
// Misc

int randInt(int min, int max);

int getPlateauId();

#pragma endregion


#endif
