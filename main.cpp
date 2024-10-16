#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <fstream>
#include <cstring>  // Potrzebne do operacji na tablicach znakowych
using namespace std;

bool checkWordInDictionary(const char* word) {
    ifstream file("../dictionary.txt");
    if (!file.is_open()) {
        cerr << "Error opening dictionary file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line == word) {
            return true;
        }
    }
    return false;
}

int findSelectedLetter(const char* selected_letters[], int selected_count, const char* letter) {
    for (int i = 0; i < selected_count; ++i) {
        if (strcmp(selected_letters[i], letter) == 0) {
            return i;  // Zwraca indeks litery w tablicy
        }
    }
    return -1;  // Nie znaleziono litery
}

void displayUI(int found_words_count) {

    mvprintw(0, 0, "Kotrolnki: ");
    mvprintw(1,0,"Strzalki- Poruszanie sie");
    mvprintw(2,0,"Enter - zeby wybrac");
    mvprintw(3,0,"W - sprawdz slowo");
    mvprintw(4,0,"R - Restart gry |Dodać|");
    mvprintw(5,0,"L - sprawdz leaderboard |Dodać|");
    mvprintw(6,0,"X - zeby zakonczyc");

    mvprintw(0, COLS/2, "Boggle");


    mvprintw(0, COLS - 20, "Slowa znalezione: %d", found_words_count);
    refresh();
}

int main() {
    srand(time(0));

    const char* dice[16][6] = {
            {"R", "I", "F", "O", "B", "X"},
            {"I", "F", "E", "H", "E", "Y"},
            {"D", "E", "N", "O", "W", "S"},
            {"U", "T", "O", "K", "N", "D"},
            {"H", "M", "S", "R", "A", "O"},
            {"L", "U", "P", "E", "T", "S"},
            {"A", "C", "I", "T", "O", "A"},
            {"Y", "L", "G", "K", "U", "E"},
            {"Qu", "B", "M", "J", "O", "A"},
            {"E", "H", "I", "S", "P", "N"},
            {"V", "E", "T", "I", "G", "N"},
            {"B", "A", "L", "I", "Y", "T"},
            {"E", "Z", "A", "V", "N", "D"},
            {"R", "A", "L", "E", "S", "C"},
            {"U", "W", "I", "L", "R", "G"},
            {"P", "A", "C", "E", "M", "D"}
    };

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int height, width;
    getmaxyx(stdscr, height, width);

    int start_y = (height - 4) / 2;
    int start_x = (width - 8) / 2;
    WINDOW* win = newwin(6, 22, start_y - 1, start_x - 1);

    refresh();
    box(win, 0, 0);
    wrefresh(win);

    // Tablica na wybrane litery
    const int MAX_SELECTED = 16;
    const char* selected_letters[MAX_SELECTED];
    int selected_count = 0;

    // Liczba znalezionych słów
    int found_words_count = 0;

    const int ROWS = 4, COLS = 4;
    string letters[ROWS][COLS];
    bool highlighted[ROWS][COLS] = {false}; // Podświetlenie dla liter
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int randomIndex = rand() % 6;
            letters[i][j] = dice[i * COLS + j][randomIndex];
            mvwprintw(win, i + 1, j * 5 + 1, "| %s |", dice[i * COLS + j][randomIndex]);
        }
    }
    wrefresh(win);

    int cursor_y = 1, cursor_x = 1;

    while (true) {
        // Wyświetlanie liter z podświetleniem
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (i + 1 == cursor_y && j * 5 + 1 == cursor_x) {
                    wattron(win, A_REVERSE);  // Podświetlenie kursora
                } else if (highlighted[i][j]) {
                    wattron(win, A_REVERSE);  // Podświetlenie wybranej litery
                }
                mvwprintw(win, i + 1, j * 5 + 1, "| %s ", letters[i][j].c_str());
                wattroff(win, A_REVERSE);
                wattroff(win, A_REVERSE);
            }
        }
        wrefresh(win);

        // Wyświetl UI
        displayUI(found_words_count);

        int ch = getch();

        if (ch == KEY_UP && cursor_y > 1) {
            cursor_y--;
        } else if (ch == KEY_DOWN && cursor_y < ROWS) {
            cursor_y++;
        } else if (ch == KEY_LEFT && cursor_x > 1) {
            cursor_x -= 5;
        } else if (ch == KEY_RIGHT && cursor_x < 1 + (COLS - 1) * 5) {
            cursor_x += 5;
        } else if (ch == 10) {  // Enter
            int letter_x = (cursor_x - 1) / 5;
            int letter_y = cursor_y - 1;

            // Sprawdzenie, czy litera już została wybrana
            if (highlighted[letter_y][letter_x]) {
                // Cofnięcie wyboru litery
                int index = findSelectedLetter(selected_letters, selected_count, letters[letter_y][letter_x].c_str());
                if (index != -1) {
                    // Usunięcie litery z tablicy selected_letters
                    for (int i = index; i < selected_count - 1; ++i) {
                        selected_letters[i] = selected_letters[i + 1];
                    }
                    selected_count--;
                }
                highlighted[letter_y][letter_x] = false;  // Usuń podświetlenie
            } else {
                if (selected_count < MAX_SELECTED) {
                    selected_letters[selected_count++] = letters[letter_y][letter_x].c_str();
                    highlighted[letter_y][letter_x] = true;  // Zaznacz podświetlenie
                }
            }

            move(height - 1, 0);
            clrtoeol();
            for (int i = 0; i < selected_count; ++i) {
                printw("%s ", selected_letters[i]);
            }
            refresh();
        } else if (ch == 'w') {  // Wykonanie sprawdzenia słowa
            if (selected_count > 0) {
                // Złączenie liter w jedno słowo
                char word[64] = "";
                for (int i = 0; i < selected_count; ++i) {
                    strcat(word, selected_letters[i]);
                }

                // Sprawdzenie, czy słowo istnieje w pliku
                if (checkWordInDictionary(word)) {
                    move(height - 2, 0);
                    clrtoeol();
                    printw("Word found: %s", word);
                    found_words_count++;  // Zwiększenie liczby znalezionych słów
                } else {
                    move(height - 2, 0);
                    clrtoeol();
                    printw("Word not found: %s", word);
                }

                refresh();

                // Wyczyszczenie tablicy wybranych liter i reset podświetlenia
                selected_count = 0;
                for (int i = 0; i < MAX_SELECTED; ++i) {
                    selected_letters[i] = nullptr;
                }

                // Reset podświetlenia
                for (int i = 0; i < ROWS; ++i) {
                    for (int j = 0; j < COLS; ++j) {
                        highlighted[i][j] = false;
                    }
                }

                move(height - 1, 0);
                clrtoeol();
                refresh();
            }
        } else if (ch == 'x') {  // Zakończenie
            break;
        }
    }

    endwin();
    return 0;
}
