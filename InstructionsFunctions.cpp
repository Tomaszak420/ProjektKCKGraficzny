#include "InstructionsFunctions.h"
#include <curses.h>

ScreenChoice instructions()
{
    clear();
    refresh();

    mvprintw(0, 0, "INSTRUKCJA");
    mvprintw(1, 0, "W grze Boggle szukasz slow na planszy 4x4. Mozesz zaznaczac slowa");
    mvprintw(2, 0, "wybierajac skladajace sie na nie kolejne litery. Kazda kolejna");
    mvprintw(3, 0, "litera musi sasiadowac z poprzednia (moze sasiadowac po skosie).");
    mvprintw(4, 0, "Litera na danym polu nie moze byc wybrana dwa razy do jednego slowa.");

    mvprintw(5, 0, "Aby wrocic do menu, nacisnij dowolny przycisk.");
    int ch = getch();

    return MENU;
}
