#include <ncurses.h>

#define CHAR_NAME_MAX (50)
#define CHAR_DESC_MAX (200)

typedef struct perso{

	char name[CHAR_NAME_MAX];
	int id;
	struct perso *suivant;
} PERSO;

typedef struct objet{

	char name[CHAR_NAME_MAX];
	char description[CHAR_DESC_MAX];
	float price;
	struct objet *suivant;
	struct objet *precedent;
} OBJET;


typedef struct score{

	int alt;
	float money;
} SCORE;


typedef struct GameState {
	PERSO *perso;
	OBJET *objetBoutique;
	OBJET *objetInventaire;
	SCORE *highScore;
} GAMESTATE;



void fenetrePlateau(GAMESTATE *GameState);

WINDOW* fenetreGame(WINDOW* game, int hGame,int wGame,int yGame,int xGame);
WINDOW* fenetreLog(WINDOW* log, int hLog,int wLog,int yLog,int xLog);
WINDOW* fenetreScore(WINDOW* score, int hScore, int wScore,int yScore,int xScore);
WINDOW* fenetreMenu(WINDOW* menu, int hMenu, int wMenu,int yMenu,int xMenu);

WINDOW* boutiqueMenu(WINDOW* boutique, int hMenu, int wMenu,int yMenu,int xMenu);
void boutiqueFct(WINDOW* boutique);
int selectionMenu(WINDOW* win, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, int largeur, int longueur, OBJET* objetBoutique, OBJET* objetInventaire, SCORE* highScore );

void affichePersoWin(WINDOW* win,PERSO* perso);


void afficheAllObjetWin(WINDOW* win,OBJET* objet);
void afficheObjetWin(WINDOW* win,OBJET* objet, int n);
void afficheObjetWinReverse(WINDOW* win,OBJET* objet, int n);


int compterObjet(OBJET* objet);
void menuBoutique(WINDOW* boutique, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, OBJET* objetBoutique, OBJET* inventaire, SCORE* highScore);


void afficheScore(WINDOW* win,SCORE* highScore);
void afficheScoreRev(WINDOW* win,SCORE* score);
int achatBoutique(SCORE* highScore, OBJET* objet);



WINDOW* inventaireMenu(WINDOW* inventaire, int hMenu, int wMenu,int yMenu,int xMenu);
void menuInventaire(WINDOW* inventaire, WINDOW* scr, WINDOW* log, int hMenu, int wMenu,int yMenu,int xMenu, OBJET* objetBoutique, OBJET* objetInventaire, SCORE* highScore);

void prinfLog (WINDOW* win, char* message );

void fenetreIntro(void);


