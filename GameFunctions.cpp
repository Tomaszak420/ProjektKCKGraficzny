#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "MenuFunctions.h"
#include "ScreenChoice.h"
#include "Coordinates.h"
#include "GameState.h"
#include "BoardAnalyzer.h"

using namespace std;

#define KOLUMNY 4
#define RZEDY 4
#define MAX_WYBRANYCH 16

// UI: Funkcja wyswietlajaca plansze
void displayBoard(string board[4][4], WINDOW* okno) {

    for (int i = 0; i < RZEDY; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            mvwprintw(okno, i + 1, j * 5 + 1, "| %s |", board[i][j].c_str());
        }
    }
    wrefresh(okno);
}

// UI: Wyswietla liczbe znlezionych slow
void updateFoundWordsCounterDisplay(int liczba_znalezionych_slow) {
    mvprintw(0, COLS - 20, "Slowa znalezione: %d", liczba_znalezionych_slow);
    refresh();
}

// UI: Wyświetlanie listy znalezionych słów
void wyswietlListeZnalezionychSlow(WINDOW *lista_okno, vector<string> found_words)
{
    werase(lista_okno);    // Czyszczenie okna
    box(lista_okno, 0, 0); // Rysowanie ramki

    mvwprintw(lista_okno, 0, 1, "Znalezione slowa");

    for (int i = 0; i < found_words.size(); ++i)
    {
        mvwprintw(lista_okno, i + 1, 1, "%s", found_words[i].c_str());
    }
    wrefresh(lista_okno);
}

// UI: Wyswietla instrukcje gry
void gameScreenInit() {
    mvprintw(0, 0, "Kontrolki: ");
    mvprintw(1, 0, "Strzalki - Poruszanie sie");
    mvprintw(2, 0, "Enter - zeby wybrac");
    mvprintw(3, 0, "W - sprawdź slowo");
    mvprintw(4, 0, "R - Restart gry");
    mvprintw(5, 0, "X - zeby zakonczyc");

    mvprintw(0, COLS / 2, "Boggle");
    mvprintw(0, COLS - 20, "Slowa znalezione: 0");
}

// Wyswietla plansze/aktualizuje jej wyglad
void updateBoard(WINDOW *plansza_okno, GameState state, struct coordinates cursor)
{
    for (int i = 0; i < RZEDY; ++i)
    {
        for (int j = 0; j < KOLUMNY; ++j)
        {
            // Jesli kursor znajduje sie w tym miejscu
            if (i + 1 == cursor.y && j * 5 + 1 == cursor.x)
            {
                wattron(plansza_okno, A_REVERSE | COLOR_PAIR(1)); // Podświetlenie kursora
            }
            // Jesli ta litera zostala wybrana
            else if (state.hasBeenSelected( { i , j } ))
            {
                wattron(plansza_okno, A_REVERSE | COLOR_PAIR(2)); // Podświetlenie wybranej litery
            }

            mvwprintw(plansza_okno, i + 1, j * 5 + 1, "| %s |", state.board[i][j].c_str());
            wattroff(plansza_okno, A_REVERSE | COLOR_PAIR(1));
            wattroff(plansza_okno, A_REVERSE | COLOR_PAIR(2));
        }
    }
    wrefresh(plansza_okno);
}

// Uaktualnia ekran przy restarcie gry
void restartGameDisplay(GameState state, WINDOW *lista_okno, WINDOW *plansza_okno)
{
    displayBoard(state.board, plansza_okno);

    wyswietlListeZnalezionychSlow(lista_okno, state.found_words);

    move(LINES - 2, 0);
    clrtoeol();
}

void tryAddSelectedWord(GameState *state, WINDOW *lista_okno)
{
    // Obsługa sprawdzania słowa
    if (state->getSelectedLength() > 0)
    {
        string slowo = state->getSelectedWord();

        if (state->isOnBoard(slowo))
        {
            // Proba dodania slowa do listy
            bool success = state->tryAddSelectedWord();

            if (success)
            {
                mvprintw(LINES - 2, 0, "Slowo %s dodane do listy!", slowo.c_str());
                clrtoeol();
            }
            else
            {
                mvprintw(LINES - 2, 0, "Slowo juz znalezione!");
                clrtoeol();
            }
        }
        else
        {
            mvprintw(LINES - 2, 0, "Slowo nie znalezione w slowniku!");
            clrtoeol();
        }

        wyswietlListeZnalezionychSlow(lista_okno, state->found_words);

        state->clearSelection();
    }
}

// Funkcja główna z pętlą gry
void enterInteractionLoop(WINDOW *plansza_okno, WINDOW *lista_okno, GameState state)
{
    struct coordinates cursor = {1, 1};

    auto startTime = std::chrono::steady_clock::now();
    auto lastTime = startTime;
    bool timeoutTimerRunning = true;
    bool updateTimerRunning = true;

    while (true)
    {
        if (timeoutTimerRunning)
        {
            auto now = std::chrono::steady_clock::now();

            if (std::chrono::duration_cast<std::chrono::seconds>(now - startTime) >= std::chrono::minutes(1))
            {
                mvprintw(LINES - 4 , 0, "CZAS MINAL!!!");
                refresh();
                timeoutTimerRunning = false;
                updateTimerRunning = false;
                break;
            }

            if (std::chrono::duration_cast<std::chrono::seconds>(now - lastTime) >= std::chrono::seconds(1))
            {
                int minutes = std::chrono::duration_cast<std::chrono::minutes>(now - startTime).count();
                int seconds = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
                mvprintw(LINES - 3 , 0, "%d:%d", minutes, seconds);
                refresh();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        updateBoard(plansza_okno, state, cursor);

        updateFoundWordsCounterDisplay(state.found_words.size());


        int ch = getch();

        // Obsługa ruchu kursora
        if (ch == KEY_UP && cursor.y > 1)
        {
            cursor.y--;
        }
        else if (ch == KEY_DOWN && cursor.y < RZEDY)
        {
            cursor.y++;
        }
        else if (ch == KEY_LEFT && cursor.x > 1)
        {
            cursor.x -= 5;
        }
        else if (ch == KEY_RIGHT && cursor.x < 1 + (KOLUMNY - 1) * 5)
        {
            cursor.x += 5;
        }
        else if (ch == 10) // Enter
        {
            state.tryAddLetter(cursor);
        }
        else if (ch == 'w' || ch == 'W')
        {
            // TODO
            tryAddSelectedWord(&state, lista_okno);
        }
        else if (ch == 'r' || ch == 'R')
        {
            state.restartGame();
            restartGameDisplay(state, lista_okno, plansza_okno);
        }
        else if (ch == 'x' || ch == 'X')
        {
            break;
        }

        int a = 5;
    }
}

ScreenChoice game() {

    clear();
    refresh();

    GameState state;
    state.startGame();

    int start_y = (LINES - 4) / 2;
    int start_x = (COLS - 8) / 2;

    WINDOW* plansza_okno = newwin(6, 22, start_y - 1, start_x - 1);
    //refresh();
    box(plansza_okno, 0, 0);
    wrefresh(plansza_okno);

    WINDOW* lista_okno = newwin(20, 20, 1, COLS - 20);
    box(lista_okno, 0, 0);
    mvwprintw(lista_okno, 0, 1, "Znalezione slowa");
    wrefresh(lista_okno);

    displayBoard(state.board, plansza_okno);

    gameScreenInit();

    nodelay(stdscr, TRUE);
    enterInteractionLoop(plansza_okno, lista_okno, state);
    nodelay(stdscr, FALSE);
    return EXIT;
}
