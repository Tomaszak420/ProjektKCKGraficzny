#include <ncurses.h>
#include <string.h>
#include "ScreenChoice.h"

#define BUTTON_HEIGHT LINES / 4
#define BUTTON_WIDTH COLS / 2

// Przechowuje logo graficzne
const char* ascii_logo[] = {
"oooooooooo                                      o888            ",
" 888    888   ooooooo     oooooooo8   oooooooo8  888  ooooooooo8",
" 888oooo88  888     888 888    88o  888    88o   888 888oooooo8 ",
" 888    888 888     888  888oo888o   888oo888o   888 888        ",
"o888ooo888    88ooo88   888     888 888     888 o888o  88oooo888",
"                         888ooo888   888ooo888                  "
};

// Znajduje szerokosc logo
int getLogoWidth() {

    int logo_array_length = sizeof(ascii_logo) / sizeof(char *); 
    int width = 0;

    for (int i = 0; i < logo_array_length; i++) {

        int current_line_length = strlen(ascii_logo[i]);

        if (current_line_length > width) {
            width = current_line_length;
        }
    }

    return width;
}

// Wpisuje logo w docelowe okno
void printASCIILogo(WINDOW* window) {

    int start_x = (COLS - getLogoWidth()) / 2;
    int start_y = LINES / 4 - 4;

    int logo_array_length = sizeof(ascii_logo) / sizeof(char *); 

    for (int i = 0; i < logo_array_length; i++) 
    {
        mvwprintw(window, start_y + i, start_x, ascii_logo[i]);
    }

}

// Tworzy okno zawierajace logo
WINDOW* makeLogo() {

    WINDOW* logo = newwin(BUTTON_HEIGHT * 2 - 2, COLS - 2, 0, 0);
    box(logo, 0, 0);
    printASCIILogo(logo);

    return logo;
}

// Tworzy pojedynczy przycisk
void buttonInit(WINDOW** button, int y, int x, const char* text) {
    *button = newwin(BUTTON_HEIGHT - 2, BUTTON_WIDTH - 2, y, x);

    mvwprintw(*button, (BUTTON_HEIGHT - 2) / 2, (BUTTON_WIDTH - 2 - strlen(text))/ 2, text);
    box(*button, 0, 0);
}

// Tworzy przyciski i umieszcza je w tablicy
void makeButtons(WINDOW* buttons[2][2]) {
    buttonInit(&buttons[0][0], LINES / 2, 0, "GRAJ");
    buttonInit(&buttons[0][1], LINES / 2, COLS / 2, "LEADERBOARD");
    buttonInit(&buttons[1][0], (LINES / 2 + BUTTON_HEIGHT - 2), 0, "INSTRUKCJA GRY");
    buttonInit(&buttons[1][1], LINES / 2 + BUTTON_HEIGHT - 2, COLS / 2, "WYJSCIE");
}

// Wyświetla przyciski
void displayButtons(WINDOW* buttons[2][2]) {
    wrefresh(buttons[0][0]);
    wrefresh(buttons[0][1]);
    wrefresh(buttons[1][0]);
    wrefresh(buttons[1][1]);
}

// Glowna petla menu
int enterInteractionLoop(WINDOW* buttons[2][2]) {

    int cursor_x = 0, cursor_y = 0;

    while (true) {

        wbkgd(buttons[cursor_y][cursor_x], COLOR_PAIR(3));
        wrefresh(buttons[cursor_y][cursor_x]);

        int input = getch();

        wbkgd(buttons[cursor_y][cursor_x], COLOR_PAIR(4));
        wrefresh(buttons[cursor_y][cursor_x]);

        switch(input) {
            case KEY_UP:
                cursor_y = 0;
                break;
            case KEY_DOWN:
                cursor_y = 1;
                break;
            case KEY_LEFT:
                cursor_x = 0;
                break;
            case KEY_RIGHT:
                cursor_x = 1;
                break;
            case 10:
                return (cursor_x + 1) + 2 * cursor_y;

        }

    }

}

ScreenChoice convertUserChoice(int userChoice) {

    ScreenChoice choice;

    switch (userChoice)
    {
    case 1:
        choice = GAME;
        break;
    case 2:
        choice = LEADERBOARD;
        break;
    case 3:
        choice = INSTRUCTIONS;
        break;
    case 4:
        choice = EXIT;
        break;
    }
    return choice;

}

ScreenChoice menu() {
    
    // Czysci ekran, jesli wczesniej cos na nim bylo
    clear();
    refresh();

    // Tworzy i wyswietla logo
    WINDOW* logo = makeLogo();
    wrefresh(logo);

    // Tworzy i wyswietla przyciski
    WINDOW *buttons[2][2];
    makeButtons(buttons);
    displayButtons(buttons);
    
    int userChoice = enterInteractionLoop(buttons);
    
    // Zwalnia pamiec zaalokowana na wyswietlane elementy
    delwin(logo);
    delwin(buttons[0][0]);
    delwin(buttons[0][1]);
    delwin(buttons[1][0]);
    delwin(buttons[1][1]);

    ScreenChoice choice = convertUserChoice(userChoice);

    return choice;
}