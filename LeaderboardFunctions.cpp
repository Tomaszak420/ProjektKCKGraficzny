#include "LeaderboardFunctions.h"
#include "LeaderboardItem.h"
#include <curses.h>
#include <vector>

void displayList(Leaderboard lb)
{
    std::vector<struct LeaderboardItem> items = lb.getItemsList();

    // Wypisywanie wynikow
    for (int i = 0; i < items.size(); i++)
    {
        mvprintw(i, 0, "%d. %s - wynik: %d", i + 1, items[i].name, items[i].score);
    }

    // Jesli czesc wpisow w leaderboardzie jest pusta
    if (items.size() < lb.getMaxLength())
    {
        for (int i = items.size(); i < lb.getMaxLength(); i++)
        {
            mvprintw(i, 0, "%d. PUSTY", i + 1);
        }
    }
}

ScreenChoice leaderboard(Leaderboard lb) 
{
    clear();
    refresh();

    displayList(lb);

    mvprintw(lb.getMaxLength() + 1, 0, "Aby wrocic do menu, nacisnij dowolny przycisk.");
    int ch = getch();

    return MENU;
}