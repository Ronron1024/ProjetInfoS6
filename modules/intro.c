#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "../includes/structures.h"

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

    int menu_item_count = 2;
    char menu_items[2][CHAR_NAME_MAX] = {
        "New game",
        "Continue"
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