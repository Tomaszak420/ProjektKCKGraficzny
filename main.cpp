#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
using namespace std;

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
//Wyłączenie klawiatury i włączenie strzałek
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
//Usawienie naszej planszy na środku
    int height, width;
    getmaxyx(stdscr, height, width);
    int start_y = (height - 4) / 2;
    int start_x = (width - 8) / 2;
    WINDOW* win = newwin(6, 22, start_y - 1, start_x - 1);
    refresh();
    box(win, 0, 0);
    wrefresh(win);

    //Wybrane litery max długość to 16 no bo taka plansza
    const char* selected_letters[16];
    int selected_count = 0;

    // Wypisywanie liter w środku okna
    const int ROWS = 4, COLS = 4;
    string letters[ROWS][COLS];
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int randomIndex = rand() % 6;
            letters[i][j] = dice[i * COLS + j][randomIndex];  // Przechowywanie liter w tablicy dzięki czemu po wciśnięciu wiadomo jaka to litera
            mvwprintw(win, i + 1, j * 5 + 1, "| %s |", dice[i * COLS + j][randomIndex]); //Wyświetla wartości na oknie (win)
        }
    }
    wrefresh(win);

    // Pozycja kursora
    int cursor_y = 1,cursor_x = 1;

    while (true) {
        // Podświetlenie aktualnej pozycji kursora
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (i + 1 == cursor_y && j * 5 + 1 == cursor_x) {
                    wattron(win, A_REVERSE);  // Włącz podświetlenie jeśli kursor jest na tej pozycji
                }
                mvwprintw(win, i + 1, j * 5 + 1, "| %s |", letters[i][j].c_str());
                wattroff(win, A_REVERSE);  // Brak podświelenia i zwykłe litery jeśli kursor jest gdzie indziej
            }
        }
        wrefresh(win);

        int ch = getch();
        //Dodać jakoś żeby sprawdzało czy te litery sa obok//
        if (ch == KEY_UP && cursor_y > 1) {
            cursor_y--; //odejmuje od y
        } else if (ch == KEY_DOWN && cursor_y < ROWS) {
            cursor_y++; //dodaje do y
        } else if (ch == KEY_LEFT && cursor_x > 1) {  // Poruszanie w lewo
            cursor_x -= 5;
        } else if (ch == KEY_RIGHT && cursor_x < 1 + (COLS - 1) * 5) {  // Poruszanie w prawo
            cursor_x += 5;
        } else if (ch == 10) {  //Wybranie litery //Dodać blokade na tą samą litere
            if (selected_count < 16) {
                int letter_x = (cursor_x - 1) / 5;
                int letter_y = cursor_y - 1;
                selected_letters[selected_count++] = letters[letter_y][letter_x].c_str();  // Dodanie wybranej litery do wypisania/sprawdzenia
                move(height - 1, 0);  // Przesunięcie kursora na dół ekranu na chwile żeby wpisało litere

                for (int i = 0; i < selected_count; ++i) {
                    printw("%s ", selected_letters[i]);  // Wyświetlanie wybranych liter
                }
                refresh();
            }
        } else if (ch == 'x') {  // Dodać tu spradzenie słowa w słowniku po wciścięciu x
            break;
        }
    }

    endwin();
    return 0;
}
