#include <ncurses.h>

#define CHAR_NAME_MAX (50)

typedef struct perso{

	char name[CHAR_NAME_MAX];
	int id;
	struct perso *suivant;
} PERSO;




void fenetrePlateau(PERSO* perso);
void affichePersoWin(WINDOW* win,PERSO* perso);
void choixMenu(WINDOW* menu, int ch);
void afficheMenu(WINDOW* menu);



