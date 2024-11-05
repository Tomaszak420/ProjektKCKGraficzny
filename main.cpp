#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <fstream>
#include <cstring>
#include "MenuFunctions.h"
#include "GameFunctions.h"
#include "ScreenChoice.h"

using namespace std;

// Inicjalizacja ncurses
void ncursesInit() {

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
}

int main() {
    srand(time(0));

    ncursesInit();

    ScreenChoice choice = MENU;

    do {

        switch(choice){
            case MENU:
                choice = menu();
                break;
            case GAME:
                choice = game();
                break;
            case LEADERBOARD:
                break;
            case INSTRUCTIONS:
                break;
        }

    } while(choice != EXIT);

    endwin();
    return 0;
}

