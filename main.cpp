#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <fstream>
#include <cstring>
using namespace std;

bool hasBeenSelected(struct coordinates* coords_so_far, int selected_count, int cursor_y, int cursor_x);
bool isValidSelection(struct coordinates* coords_so_far, int selected_count, int cursor_y, int cursor_x);

struct coordinates {
    int x;
    int y;
};

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

// Funkcja znajdująca wybraną literę w tablicy
int znajdzWybranaLitere(const char* wybrane_litery[], int liczba_wybranych, const char* litera) {
    for (int i = 0; i < liczba_wybranych; ++i) {
        if (strcmp(wybrane_litery[i], litera) == 0) {
            return i;  // Zwraca indeks litery w tablicy
        }
    }
    return -1;  // Nie znaleziono litery
}

// Funkcja wyświetlająca interfejs użytkownika
void wyswietlUI(int liczba_znalezionych_slow) {
    mvprintw(0, 0, "Kontrolki: ");
    mvprintw(1, 0, "Strzalki - Poruszanie sie");
    mvprintw(2, 0, "Enter - zeby wybrac");
    mvprintw(3, 0, "W - sprawdź slowo");
    mvprintw(4, 0, "R - Restart gry |Dodac|");
    mvprintw(5, 0, "L - sprawdź leaderboard |Dodac|");
    mvprintw(6, 0, "X - zeby zakonczyc");

    mvprintw(0, COLS / 2, "Boggle");
    mvprintw(0, COLS - 20, "Slowa znalezione: %d", liczba_znalezionych_slow);
    refresh();
}


int main() {
    srand(time(0));

    // Tablica kości z literami
    const char* kostka[16][6] = {
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

    // Inicjalizacja ncurses
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    //Inicjalizacja pod obsluge koloru
    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		return 1;
	}
	start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);


    int wysokosc, szerokosc;
    getmaxyx(stdscr, wysokosc, szerokosc);

    int start_y = (wysokosc - 4) / 2;
    int start_x = (szerokosc - 8) / 2;
    WINDOW* okno = newwin(6, 22, start_y - 1, start_x - 1);

    refresh();
    box(okno, 0, 0);
    wrefresh(okno);

    // Tablica na wybrane litery
    const int MAX_WYBRANYCH = 16;
    const char* wybrane_litery[MAX_WYBRANYCH];
    struct coordinates selected_coordinates[16];
    //int selected_count = 0;

    int liczba_wybranych = 0;
    int liczba_znalezionych_slow = 0;

    const int RZEDY = 4, KOLUMNY = 4;
    string litery[RZEDY][KOLUMNY];
    bool podswietlone[RZEDY][KOLUMNY] = { false }; // Podświetlenie dla liter

    // Losowanie liter z kości
    for (int i = 0; i < RZEDY; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            int randomIndex = rand() % 6;
            litery[i][j] = kostka[i * KOLUMNY + j][randomIndex];
            mvwprintw(okno, i + 1, j * 5 + 1, "| %s |", kostka[i * KOLUMNY + j][randomIndex]);
        }
    }
    wrefresh(okno);

    int kursor_y = 1, kursor_x = 1;

    while (true) {
        // Wyświetlanie liter z podświetleniem
        for (int i = 0; i < RZEDY; ++i) {
            for (int j = 0; j < KOLUMNY; ++j) {
                if (i + 1 == kursor_y && j * 5 + 1 == kursor_x)
                {
                    wattron(okno, A_REVERSE | COLOR_PAIR(1));  // Podświetlenie kursora
                //} else if (podswietlone[i][j]) {
                }
                else if  (hasBeenSelected(selected_coordinates, liczba_wybranych, i, j))
                {
                    wattron(okno, A_REVERSE | COLOR_PAIR(2));  // Podświetlenie wybranej litery
                }
                mvwprintw(okno, i + 1, j * 5 + 1, "| %s |", litery[i][j].c_str());
                wattroff(okno, A_REVERSE | COLOR_PAIR(1));
                //wattroff(okno, A_REVERSE | COLOR_PAIR(2));
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
            /*int liter_x = (kursor_x - 1) / 5; //Wybiera SAMĄ litere bez tych ramek
            int liter_y = kursor_y - 1;

            // Sprawdzenie, czy litera już została wybrana
            if (podswietlone[liter_y][liter_x]) {
                // Cofnięcie wyboru litery
                int index = znajdzWybranaLitere(wybrane_litery, liczba_wybranych, litery[liter_y][liter_x].c_str());
                if (index != -1) {
                    // Usunięcie litery z tablicy wybrane_litery
                    for (int i = index; i < liczba_wybranych - 1; ++i) {
                        wybrane_litery[i] = wybrane_litery[i + 1];
                    }
                    liczba_wybranych--;
                }
                podswietlone[liter_y][liter_x] = false;  // Usuń podświetlenie
            } else {
                if (liczba_wybranych < MAX_WYBRANYCH) {
                    wybrane_litery[liczba_wybranych++] = litery[liter_y][liter_x].c_str();
                    podswietlone[liter_y][liter_x] = true;  // Zaznacz podświetlenie
                }
            }*/

            int letter_x = (kursor_x - 1) / 5;
            int letter_y = kursor_y - 1;

            // Sprawdza, czy mozna dana litere dodac do ciagu
            if (isValidSelection(selected_coordinates, liczba_wybranych, letter_y, letter_x))
            {

                wybrane_litery[liczba_wybranych] = litery[letter_y][letter_x].c_str();  // Dodanie wybranej litery do wypisania/sprawdzenia

                selected_coordinates[liczba_wybranych].y = letter_y; // Zapisanie koordynatow nowej litery
                selected_coordinates[liczba_wybranych].x = letter_x;

                liczba_wybranych++;

                move(wysokosc - 1, 0);  // Przesunięcie kursora na dół ekranu na chwile żeby wpisało litere

                for (int i = 0; i < liczba_wybranych; ++i) {
                    printw("%s ", wybrane_litery[i]);  // Wyświetlanie wybranych liter
                }
                refresh();
            }

            move(wysokosc - 1, 0);
            clrtoeol();
            for (int i = 0; i < liczba_wybranych; ++i) {
                printw("%s ", wybrane_litery[i]);
            }
            refresh();
        } else if (ch == 'w') {  // Wykonanie sprawdzenia słowa
            if (liczba_wybranych > 0) {
                // Złączenie liter w jedno słowo
                char slowo[17] = "";
                for (int i = 0; i < liczba_wybranych; ++i) {
                    strcat(slowo, wybrane_litery[i]);
                }

                // Sprawdzenie, czy słowo istnieje w pliku
                if (sprawdzSlowoWSlowniku(slowo)) {
                    move(wysokosc - 2, 0);
                    clrtoeol();
                    printw("Znalezione slowo: %s", slowo);
                    liczba_znalezionych_slow++;  // Zwiększenie liczby znalezionych słów
                } else {
                    move(wysokosc - 2, 0);
                    clrtoeol();
                    printw("Nie znaleziono slowa: %s", slowo);
                }

                refresh();

                // Wyczyszczenie tablicy wybranych liter i reset podświetlenia
                liczba_wybranych = 0;
                for (int i = 0; i < MAX_WYBRANYCH; ++i) {
                    wybrane_litery[i] = nullptr;
                }

                // Reset podświetlenia
                for (int i = 0; i < RZEDY; ++i) {
                    for (int j = 0; j < KOLUMNY; ++j) {
                        podswietlone[i][j] = false;
                    }
                }

                move(wysokosc - 1, 0);
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


//Jesli wybrana litere mozna dodac do ciagu, zwraca true. W przeciwnym razie - false.
bool isValidSelection(struct coordinates* coords_so_far, int selected_count, int cursor_y, int cursor_x)
{

    //Jesli to pierwsza zaznaczona litera - zawsze mozna ja dodac
    if (selected_count == 0) return true;

    //Jesli zoatala juz zaznaczona, zwraca false
    if (hasBeenSelected(coords_so_far, selected_count, cursor_y, cursor_x))
    {
        return false;
    }

    //Obliczenie odleglosci miedzy ostatnia dodana litera, a zaznaczona teraz
    int head_y = coords_so_far[selected_count - 1].y;
    int head_x = coords_so_far[selected_count - 1].x;
    int distance_y = abs(cursor_y - head_y);
    int distance_x = abs(cursor_x - head_x);

    //Jesli litera nie znajduje sie w bezposrednim sasiedztwie ostatnio dodanej litery, nie mozna jej dodac.
    if (distance_y > 1 || distance_x > 1) return false;

    //Litera moze byc dodana.
    return true;
}

//Jesli litera zostala juz zaznaczona, zwraca true. W przeciwnym razie - false
bool hasBeenSelected(struct coordinates* coords_so_far, int selected_count, int cursor_y, int cursor_x)
{
    //Przechodzi przez wszystkie zaznaczone do tej pory pola
    for (int i = 0; i < selected_count; i++)
    {
        //Jesli litera zostala juz zaznaczona
        if (cursor_y == coords_so_far[i].y && cursor_x == coords_so_far[i].x)
        {
            return true;
        }
    }

    //Litera nie zostala jeszcze zaznaczona
    return false;
}
