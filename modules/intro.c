#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <dirent.h>
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

void intro()
{
    FILE* intro_file = fopen(INTRO_PATH, "r");
    if (!intro_file)
    {
        printf("Error while opening intro\n");
        return;
    }
    char line[CHAR_STORY_LINE_MAX] = {0};

    clear();
    int y = 10;
    while (fgets(line, CHAR_STORY_LINE_MAX, intro_file))
    {
        printwXCentered(y, line);
        y++;
    }
    
    fclose(intro_file);
    refresh();
    getch();
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
    int y = 5;
    attron(A_BOLD);
    while (fgets(ascii_art_buffer, ASCII_ART_BUFFER_SIZE, splashscreen_file))
    {
        printwXCentered(y, ascii_art_buffer);
        y++;
    }
    attroff(A_BOLD);
    refresh();
    fclose(splashscreen_file);
}

void gameOverScreen()
{
	char ascii_art_buffer[ASCII_ART_BUFFER_SIZE] = {0};
    FILE* splashscreen_file = fopen(GAMEOVER_PATH, "r");

    // Display error message
    if (!splashscreen_file)
    {
        attron(COLOR_PAIR(PAIR_RED_BLACK));
        attron(A_BOLD);
        printw("Can't read gameover file : %s", GAMEOVER_PATH);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(PAIR_RED_BLACK));
        refresh();
        return;
    }

    // Display ASCII ART
    clear();
    int y = 5;
    mvprintw(y, 25, "Coucou, tu veux voir ma ..");
    attron(A_BOLD);
    while (fgets(ascii_art_buffer, ASCII_ART_BUFFER_SIZE, splashscreen_file))
    {
        printwXCentered(y, ascii_art_buffer);
        y++;
    }
    attroff(A_BOLD);
    refresh();
    getch();
    fclose(splashscreen_file);
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

char* menuContinue()
{
    DIR* save_dir = opendir(SAVE_FOLDER);

    if (!save_dir)
    {
        printf("Error while opening saves folder\n");
        return "";
    }

    struct dirent* current_entry;
    char (*menu_items)[CHAR_SAVE_MAX] = {NULL};
    int number_items = 0;

    // Count files
    while ((current_entry = readdir(save_dir)))
    {
        if (strcmp(current_entry->d_name, ".") != 0 && strcmp(current_entry->d_name, "..") != 0)
            number_items++;
    }
    seekdir(save_dir, 0);

    // No save
    if (!number_items)
        return "";

    // Allocate 2D array (correct ?)
    menu_items = malloc(sizeof(char) * number_items * CHAR_SAVE_MAX);

    // Fill array
    int i = 0;
    while ((current_entry = readdir(save_dir)))
    {
        if (strcmp(current_entry->d_name, ".") != 0 && strcmp(current_entry->d_name, "..") != 0)
        {
            strcpy(menu_items[i], current_entry->d_name);
            // Remove file extension
            menu_items[i][strlen(menu_items[i]) - 4] = '\0';
            i++;
        }
    }

    
    int key = 0;
    int selected_item = 0;

    int base_y = (LINES - number_items)  / 2;
    int base_x = COLS / 2 - 4;

    while (key != KEY_RETURN)
    {
        // Move selection
        if (key == KEY_UP && selected_item > 0)
            selected_item--;
        else if (key == KEY_DOWN && selected_item < number_items - 1)
            selected_item++;

        clear();
        for (int i = 0; i < number_items; i++)
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
    
    return menu_items[selected_item];
}

void story(int level)
{
    if (level % STORY_STEPPING != 0)
        return;

    level /= STORY_STEPPING;

    DIR* story_dir = opendir(STORY_FOLDER);
    struct dirent* entry = NULL;
    char story_file_path [CHAR_STORY_LINE_MAX] = {0};
    int i = 0;
    while ((entry = readdir(story_dir)))
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            i++;
        if (i == level)
        {
            strcpy(story_file_path, STORY_FOLDER);
            strcat(story_file_path, entry->d_name);
            break;
        }
    }

    if (i < level) // Story doesn't exist
        return;

    FILE* story_file = fopen(story_file_path, "r");
    if (!story_file)
        return;
    char story_line[CHAR_STORY_LINE_MAX] = {0};

    clear();
    int y = 10;
    while (fgets(story_line, CHAR_STORY_LINE_MAX, story_file))
    {
        printwXCentered(y, story_line);
        y++;
    }

    fclose(story_file);
    closedir(story_dir);

    refresh();
    getch();
}