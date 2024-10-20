#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <fstream>
#include <cstring>

using namespace std;

// Definicja struktury przechowującej współrzędne
struct coordinates {
    int x;
    int y;
};

// Funkcja losująca litery na planszy
void losujKosci(string litery[4][4], WINDOW* okno) {
    const char* kostka[16][6] = {
            {"R", "I", "F", "O", "B", "X"}, {"I", "F", "E", "H", "E", "Y"},
            {"D", "E", "N", "O", "W", "S"}, {"U", "T", "O", "K", "N", "D"},
            {"H", "M", "S", "R", "A", "O"}, {"L", "U", "P", "E", "T", "S"},
            {"A", "C", "I", "T", "O", "A"}, {"Y", "L", "G", "K", "U", "E"},
            {"Qu", "B", "M", "J", "O", "A"}, {"E", "H", "I", "S", "P", "N"},
            {"V", "E", "T", "I", "G", "N"}, {"B", "A", "L", "I", "Y", "T"},
            {"E", "Z", "A", "V", "N", "D"}, {"R", "A", "L", "E", "S", "C"},
            {"U", "W", "I", "L", "R", "G"}, {"P", "A", "C", "E", "M", "D"}
    };

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int randomIndex = rand() % 6;
            litery[i][j] = kostka[i * 4 + j][randomIndex];
            mvwprintw(okno, i + 1, j * 5 + 1, "| %s |", litery[i][j].c_str());
        }
    }
    wrefresh(okno);
}

// Sprawdzenie, czy wybrane współrzędne były już zaznaczone
bool hasBeenSelected(struct coordinates* coords_so_far, int selected_count, int cursor_y, int cursor_x) {
    for (int i = 0; i < selected_count; ++i) {
        if (coords_so_far[i].y == cursor_y && coords_so_far[i].x == cursor_x) {
            return true;
        }
    }
    return false;
}

// Sprawdzenie, czy wybór jest sąsiadem ostatniej litery
bool isValidSelection(struct coordinates* coords_so_far, int selected_count, int cursor_y, int cursor_x) {
    if (selected_count == 0) {
        return true; // Pierwszy wybór jest zawsze prawidłowy
    }

    int last_x = coords_so_far[selected_count - 1].x;
    int last_y = coords_so_far[selected_count - 1].y;

    return abs(last_x - cursor_x) <= 1 && abs(last_y - cursor_y) <= 1;
}

// Funkcja sprawdzająca, czy słowo znajduje się w słowniku
bool sprawdzSlowoWSlowniku(const char* slowo) {
    ifstream plik("../dictionary.txt");
    if (!plik.is_open()) {
        cerr << "Błąd otwierania pliku" << endl;
        return false;
    }

    string linia;
    while (getline(plik, linia)) {
        if (linia == slowo) {
            return true;
        }
    }
    return false;
}

// Wyświetlanie interfejsu użytkownika
void wyswietlUI(int liczba_znalezionych_slow) {
    mvprintw(0, 0, "Kontrolki: ");
    mvprintw(1, 0, "Strzalki - Poruszanie sie");
    mvprintw(2, 0, "Enter - zeby wybrac");
    mvprintw(3, 0, "W - sprawdź slowo");
    mvprintw(4, 0, "R - Restart gry");
    mvprintw(5, 0, "X - zeby zakonczyc");

    mvprintw(0, COLS / 2, "Boggle");
    mvprintw(0, COLS - 20, "Slowa znalezione: %d", liczba_znalezionych_slow);
    refresh();
}

// Wyświetlanie listy znalezionych słów
void wyswietlListeZnalezionychSlow(WINDOW* lista_okno, char znalezione_slowa[][20], int liczba_znalezionych) {
    werase(lista_okno);  // Czyszczenie okna
    box(lista_okno, 0, 0);  // Rysowanie ramki

    mvwprintw(lista_okno, 0, 1, "Znalezione slowa");
    for (int i = 0; i < liczba_znalezionych; ++i) {
        mvwprintw(lista_okno, i + 1, 1, "%s", znalezione_slowa[i]);
    }
    wrefresh(lista_okno);
}

// Funkcja główna z pętlą gry
void gra(WINDOW* okno, WINDOW* lista_okno) {
    const int MAX_WYBRANYCH = 16;
    const int RZEDY = 4, KOLUMNY = 4;

    string litery[RZEDY][KOLUMNY];
    const char* wybrane_litery[MAX_WYBRANYCH];
    struct coordinates selected_coordinates[MAX_WYBRANYCH];

    char znalezione_slowa[20][20];  // Tablica na znalezione słowa
    int liczba_wybranych = 0, liczba_znalezionych_slow = 0;

    losujKosci(litery, okno);

    int kursor_y = 1, kursor_x = 1;

    while (true) {
        // Wyświetlanie liter z podświetleniem
        for (int i = 0; i < RZEDY; ++i) {
            for (int j = 0; j < KOLUMNY; ++j) {
                if (i + 1 == kursor_y && j * 5 + 1 == kursor_x) {
                    wattron(okno, A_REVERSE | COLOR_PAIR(1));  // Podświetlenie kursora
                } else if (hasBeenSelected(selected_coordinates, liczba_wybranych, i, j)) {
                    wattron(okno, A_REVERSE | COLOR_PAIR(2));  // Podświetlenie wybranej litery
                }
                mvwprintw(okno, i + 1, j * 5 + 1, "| %s |", litery[i][j].c_str());
                wattroff(okno, A_REVERSE | COLOR_PAIR(1));
                wattroff(okno, A_REVERSE | COLOR_PAIR(2));
            }
        }
        wrefresh(okno);

        // Wyświetl UI
        wyswietlUI(liczba_znalezionych_slow);

        int ch = getch();

        // Obsługa ruchu kursora
        if (ch == KEY_UP && kursor_y > 1) {
            kursor_y--;
        } else if (ch == KEY_DOWN && kursor_y < RZEDY) {
            kursor_y++;
        } else if (ch == KEY_LEFT && kursor_x > 1) {
            kursor_x -= 5;
        } else if (ch == KEY_RIGHT && kursor_x < 1 + (KOLUMNY - 1) * 5) {
            kursor_x += 5;
        } else if (ch == 10) {  // Enter
            int letter_x = (kursor_x - 1) / 5;
            int letter_y = kursor_y - 1;

            if (isValidSelection(selected_coordinates, liczba_wybranych, letter_y, letter_x)) {
                selected_coordinates[liczba_wybranych] = { letter_x, letter_y };
                wybrane_litery[liczba_wybranych] = litery[letter_y][letter_x].c_str();
                liczba_wybranych++;
            }
        } else if (ch == 'w' || ch == 'W') {
            // Obsługa sprawdzania słowa
            if (liczba_wybranych > 0) {
                string slowo = "";
                for (int i = 0; i < liczba_wybranych; ++i) {
                    slowo += wybrane_litery[i];
                }

                if (sprawdzSlowoWSlowniku(slowo.c_str())) {
                    bool found = false;
                    for (int i = 0; i < liczba_znalezionych_slow; ++i) {
                        if (strcmp(znalezione_slowa[i], slowo.c_str()) == 0) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        strcpy(znalezione_slowa[liczba_znalezionych_slow], slowo.c_str());
                        liczba_znalezionych_slow++;
                        mvprintw(LINES-2, 0, "Slowo %s dodane do listy!",slowo.c_str());
                        clrtoeol();
                    } else {
                        mvprintw(LINES-2, 0, "Slowo juz znalezione!");
                        clrtoeol();
                    }
                } else {
                    mvprintw(LINES-2, 0, "Slowo nie znalezione w slowniku!");
                    clrtoeol();
                }

                wyswietlListeZnalezionychSlow(lista_okno, znalezione_slowa, liczba_znalezionych_slow);
                liczba_wybranych = 0;
                memset(selected_coordinates, 0, sizeof(selected_coordinates));
            }
        } else if (ch == 'r' || ch == 'R') {
            // Restart gry
            liczba_wybranych = 0;
            liczba_znalezionych_slow = 0;
            memset(selected_coordinates, 0, sizeof(selected_coordinates));
            memset(znalezione_slowa, 0, sizeof(znalezione_slowa));
            losujKosci(litery, okno);
            wyswietlListeZnalezionychSlow(lista_okno, znalezione_slowa, liczba_znalezionych_slow);
            move(LINES - 2, 0);
            clrtoeol();
        }
        else if (ch == 'x' || ch == 'X') {
            break;
        }
    }
}

int main() {
    srand(time(0));

    // Inicjalizacja ncurses
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);

    // Utworzenie okien do gry
    int wysokosc, szerokosc;
    getmaxyx(stdscr, wysokosc, szerokosc);

    int start_y = (wysokosc - 4) / 2;
    int start_x = (szerokosc - 8) / 2;
    WINDOW* okno = newwin(6, 22, start_y - 1, start_x - 1);
    refresh();
    box(okno, 0, 0);
    wrefresh(okno);

    WINDOW* lista_okno = newwin(20, 20, 1, szerokosc - 20);
    box(lista_okno, 0, 0);
    mvwprintw(lista_okno, 0, 1, "Znalezione slowa");
    wrefresh(lista_okno);

    gra(okno, lista_okno);

    endwin();
    return 0;
}
