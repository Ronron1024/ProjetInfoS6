#ifndef INCLUDED_DEFINE_H
#define INCLUDED_DEFINE_H

// Aliases & Types
typedef int Team;
#define TEAM1 0
#define TEAM2 1

typedef int Type;
typedef int TypeEquipment;
#define NULL_ITEM 0
#define ITEM 1
#define ARMOR 0
#define WEAPON 1
#define TRAP 3
#define EQUIPMENT 2

typedef int GameStatus;
#define PLAYING 0
#define SAVE 1
#define QUIT 2
#define RAS 3
#define GAMEOVER 4

typedef int GameMode;
#define GAMEMODE_PLAY 0
#define GAMEMODE_CONTINUE 1
#define GAMEMODE_DEBUG 2

// Strings size
#define CHAR_NAME_MAX 50
#define CHAR_DESC_MAX 200
#define CHAR_LOG_MAX 128
#define CHAR_SAVE_MAX 16
#define LINE_SIZE   1000

// Settings
#define BASE_MONEY 200.0
#define REWARD_MONEY 10
#define COEFF_REWARD 1
#define COEFF_DIFFICULTY 1
#define COEFF_ITEM_UPGRADE 1.2
#define TRAP_PROBA 0.5
#define LINE_LOG_MAX 4
//#define COUT_HP_FOUILLE 2
#define COEFF_VENTE 0.9
#define SAVE_FOLDER "resources/saves/"
#define SPLASHSCREEN_PATH "resources/splashscreen.txt"

#define ALLIES_PATH "resources/allies.txt"
#define ARMORS_PATH "resources/armors.txt"
#define WEAPONS_PATH "resources/weapons.txt"
#define ITEMS_PATH "resources/items.txt"
#define TRAPS_PATH "resources/traps.txt"
#define MONSTERS_PATH "resources/monsters.txt"

#define LOGFILE "resources/logs.txt"
#define ASCII_ART_BUFFER_SIZE 2048
#define NB_LEVEL 10
#define MAX_OBJET_AFFICHAGE 11

// Ncurses
#define KEY_RETURN 10 // Not defined in curses.h ?
#define KEY_ERASE 8
#define PAIR_YELLOW_BLUE 1
#define PAIR_RED_CYAN 2
#define PAIR_RED_BLACK 3
#define PAIR_WHITE_RED 4

#endif
