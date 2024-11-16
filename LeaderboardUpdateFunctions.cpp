#include "LeaderboardUpdateFunctions.h"
#include <curses.h>
using namespace std;

string getName()
{
    string name = "";

    nocbreak();
    echo();

    int ch = getch();

    while ( ch != 10 )
    {
        name.push_back(ch);
        ch = getch();
    }

    cbreak();
    noecho();

    return name;
}

ScreenChoice leaderboardUpdate(Leaderboard *lb)
{
    clear();
    refresh();

    int score = lb->getScoreBuffer();

    mvprintw(0, 0, "Gratulacje! Uzyskales jeden z najlepszych wynikow.");
    mvprintw(1, 0, "Twoj wynik: %d", score);
    mvprintw(2, 0, "Podaj swoje imie, aby dodac wynik do leaderboardu (Enter zatwierdza):");

    move(3, 0);

    string name = getName();

    lb->insertScore(name, score);

    return LEADERBOARD;
}
