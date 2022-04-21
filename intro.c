#include <ncurses.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Not defined in curses.h ?
#define KEY_RETURN 10

#define CHAR_NAME_MAX 50

#define SPLASHSCREEN_PATH "splashscreen.txt"
#define ASCII_ART_BUFFER_SIZE 2048

typedef int GameMode;
#define GAMEMODE_PLAY 0
#define GAMEMODE_CONTINUE 1
#define GAMEMODE_DEBUG 2

#define PAIR_YELLOW_BLUE 1
#define PAIR_RED_CYAN 2
#define PAIR_RED_BLACK 3
#define PAIR_WHITE_RED 4

void printwCentered(const char* str)
{
    int length = strlen(str);

    int x = (COLS - length) / 2;
    int y = LINES / 2;

    mvprintw(y, x, "%s", str);
}

void printwXCentered(int y, const char* str)
{
    int length = strlen(str);

    int x = (COLS - length) / 2;

    mvprintw(y, x, "%s", str);
}

void printwYCentered(int x, const char* str)
{
    int y = LINES / 2;

    mvprintw(y, x, "%s", str);
}

void splashscreen()
{
    char ascii_art_buffer[ASCII_ART_BUFFER_SIZE] = {0};
    FILE* splashscreen_file = fopen(SPLASHSCREEN_PATH, "r");

    // Display error message
    if (!splashscreen_file)
    {
        attron(COLOR_PAIR(PAIR_RED_BLACK));
        attron(A_BOLD);
        printw("Can't read splashscreen file : %s", SPLASHSCREEN_PATH);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(PAIR_RED_BLACK));
        refresh();
        return;
    }

    // Display ASCII ART
    attron(A_BOLD);
    while (fgets(ascii_art_buffer, ASCII_ART_BUFFER_SIZE, splashscreen_file))
        printw("%s", ascii_art_buffer);
    attroff(A_BOLD);
    refresh();
}

GameMode homeMenu()
{
    int key = 0;

    int menu_item_count = 3;
    char menu_items[3][CHAR_NAME_MAX] = {
        "Play",
        "Continue",
        "Debug"
    };
    int selected_item = 0;

    int base_y = (LINES - menu_item_count)  / 2;
    int base_x = COLS / 2 - 4; // length(Continue) / 2 = 4

    while (key != KEY_RETURN)
    {
        // Move selection
        if (key == KEY_UP && selected_item > 0)
            selected_item--;
        else if (key == KEY_DOWN && selected_item < menu_item_count - 1)
            selected_item++;

        clear();
        for (int i = 0; i < menu_item_count; i++)
        {
            if (i == selected_item)
            {
                attron(A_BOLD);
                attron(COLOR_PAIR(PAIR_WHITE_RED));
                mvprintw(base_y + i, base_x - 1, ">");
            }

            mvprintw(base_y + i, base_x, "%s\n", menu_items[i]);

            if (i == selected_item)
            {
                attroff(COLOR_PAIR(PAIR_WHITE_RED));
                attroff(A_BOLD);
            }
        }

        refresh();
        key = getch();
    }

    clear();
    return selected_item;
}

int main (int argc, char** argv)
{
    GameMode gamemode;

    initscr();
    cbreak(); // Disable buffering when typing (useless on windows ?)
    keypad(stdscr, TRUE); // Enable FN Keys reading
    noecho();
    start_color();
    init_pair(PAIR_YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
    init_pair(PAIR_RED_CYAN, COLOR_RED, COLOR_CYAN);
    init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(PAIR_WHITE_RED, COLOR_WHITE, COLOR_RED);

    splashscreen();
    getch();
    gamemode = homeMenu();
    
    endwin();

    switch (gamemode)
    {
        case GAMEMODE_PLAY:
            printf("Play\n");
            break;
        case GAMEMODE_CONTINUE:
            printf("Continue\n");
            break;
        case GAMEMODE_DEBUG:
            printf("Debug\n");
            break;
    }

    return 0;
}