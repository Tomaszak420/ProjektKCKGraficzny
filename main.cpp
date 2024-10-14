#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <fstream>
#include <cstring>
using namespace std;

bool SprawdzSlowo(const char* word) {
    ifstream file("../dictionary.txt");
    if (!file.is_open()) {
        cerr << "Błąd otwierania słownika" << endl;
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

    const int ROWS = 4, COLS = 4;
    string letters[ROWS][COLS];
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
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (i + 1 == cursor_y && j * 5 + 1 == cursor_x) {
                    wattron(win, A_REVERSE);
                }
                mvwprintw(win, i + 1, j * 5 + 1, "| %s |", letters[i][j].c_str());
                wattroff(win, A_REVERSE);
            }
        }
        wrefresh(win);

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
            if (selected_count < MAX_SELECTED) {
                int letter_x = (cursor_x - 1) / 5;
                int letter_y = cursor_y - 1;
                selected_letters[selected_count++] = letters[letter_y][letter_x].c_str();
                move(height - 1, 0);
                clrtoeol();
                for (int i = 0; i < selected_count; ++i) {
                    printw("%s ", selected_letters[i]);
                }
                refresh();
            }
            // Wykonanie sprawdzenia słowa
        } else if (ch == 'w') {
            if (selected_count > 0) {
                // Złączenie liter w jedno słowo
                char word[17] = "";
                for (int i = 0; i < selected_count; ++i) {
                    strcat(word, selected_letters[i]);
                }

                // Sprawdzenie, czy słowo istnieje w pliku
                if (SprawdzSlowo(word)) {
                    move(height - 2, 0);
                    clrtoeol();
                    printw("Słowo znalezione: %s", word);
                } else {
                    move(height - 2, 0);
                    clrtoeol();
                    printw("Słowo nie znalezione: %s", word);
                }

                refresh();

                // Wyczyszczenie tablicy wybranych liter
                selected_count = 0;
                for (int i = 0; i < MAX_SELECTED; ++i) {
                    selected_letters[i] = nullptr;
                }

                move(height - 1, 0);
                clrtoeol();
                refresh();
            }
        } else if (ch == 'x') {
            break;
        }
    }

    endwin();
    return 0;
}
