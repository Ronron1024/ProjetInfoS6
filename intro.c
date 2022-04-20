#include <ncurses.h>
#include <string.h>

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

int main (int argc, char** argv)
{
    initscr();
    cbreak(); // Disable buffering when typing (useless on windows ?)
    //keypad(stdscr, TRUE); // Enable FN Keys reading
    noecho();

    printwCentered("Centered");
    printwXCentered(2, "X Centered, Y = 2");
    printwYCentered(0, "Y Centered, X = 0");

    refresh();

    getch();
    endwin();

    return 0;
}