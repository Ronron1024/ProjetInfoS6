#include <ncurses.h>
#include <string.h>
#include <stdio.h>

#define SPLASHSCREEN_PATH "splashscreen.txt"
#define ASCII_ART_BUFFER_SIZE 2048

#define PAIR_YELLOW_BLUE 1
#define PAIR_RED_CYAN 2
#define PAIR_RED_BLACK 3

void printwCentered(const char* str)
{
    int length = strlen(str);

    int x = (COLS - length) / 2;
    int y = LINES / 2;

    mvprintw(y, x, str);
}

void printwXCentered(int y, const char* str)
{
    int length = strlen(str);

    int x = (COLS - length) / 2;

    mvprintw(y, x, str);
}

void printwYCentered(int x, const char* str)
{
    int y = LINES / 2;

    mvprintw(y, x, str);
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
        printw(ascii_art_buffer);
    attroff(A_BOLD);
    refresh();
}

int main (int argc, char** argv)
{
    initscr();
    cbreak(); // Disable buffering when typing (useless on windows ?)
    //keypad(stdscr, TRUE); // Enable FN Keys reading
    noecho();
    start_color();
    init_pair(PAIR_YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
    init_pair(PAIR_RED_CYAN, COLOR_RED, COLOR_CYAN);
    init_pair(PAIR_RED_BLACK, COLOR_RED, COLOR_BLACK);

    splashscreen();

    getch();
    endwin();
    return 0;
}