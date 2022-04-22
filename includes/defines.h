#ifndef INCLUDED_DEFINE_H
#define INCLUDED_DEFINE_H

// ALIASES
// For data
typedef int Type;
#define NULL_ITEM 0
#define ITEM 1
#define EQUIPMENT 2
#define TRAP 3
// For homeMenu()
typedef int GameMode;
#define GAMEMODE_PLAY 0
#define GAMEMODE_CONTINUE 1
#define GAMEMODE_DEBUG 2

// Strings size
#define CHAR_NAME_MAX 50
#define CHAR_DESC_MAX 200

// Settings
#define LINE_LOG_MAX	10
#define COUT_HP_FOUILLE 2
#define COEFF_VENTE 0.9
#define SPLASHSCREEN_PATH "splashscreen.txt"
#define ASCII_ART_BUFFER_SIZE 2048

// Ncurses
#define KEY_RETURN 10 // Not defined in curses.h ?
#define PAIR_YELLOW_BLUE 1
#define PAIR_RED_CYAN 2
#define PAIR_RED_BLACK 3
#define PAIR_WHITE_RED 4

#endif
