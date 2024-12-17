#include "BoardAnalyzer.h"

/**
 * Tworzy obiekt klasy BoardAnalyzer z podaną planszą i ścieżką do pliku słownika.
 *
 * Inicjalizuje planszę podaną konfiguracją oraz inicjalizuje atrybut słownika
 * za pomocą ścieżki do pliku słownika.
 *
 * @param board Tablica 2D reprezentująca początkowy stan planszy gry.
 * @param dictionary_file_path Ścieżka do pliku słownika używanego do
 *                              walidacji słów na planszy.
 */
BoardAnalyzer::BoardAnalyzer(string board[RZEDY][KOLUMNY], string dictionary_file_path) : dictionary(dictionary_file_path)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

/**
 * @brief Wypełnia listę sąsiedztwa dla każdego wierzchołka w grafowej reprezentacji planszy.
 *
 * Funkcja uzupełnia `neighbor_list`, która jest listą sąsiadujących wierzchołków
 * dla każdego wierzchołka planszy, reprezentowanej jako graf. Plansza jest
 * traktowana jako 2D siatka z `RZEDY` wierszami i `KOLUMNY` kolumnami. Każdy
 * wierzchołek w siatce ma potencjalnych sąsiadów, którzy sąsiadują z nim w
 * wierszach i kolumnach, z wyjątkiem samego wierzchołka.
 *
 * Funkcja iteruje po każdym wierzchołku planszy, oblicza indeksy wiersza
 * i kolumny, określa możliwe sąsiednie wiersze i kolumny, a następnie
 * uzupełnia listę sąsiadów tego wierzchołka, wykluczając sam wierzchołek.
 */
void BoardAnalyzer::fillNeighborList()
{

    for (int i = 0; i < RZEDY * KOLUMNY; i++)
    {
        // Lista sąsiadów dla danego wierzchołka.
        vector<int> i_neighbor_list;

        // Konwersja numeru wierzchołka na numer wiersza oraz kolumny.
        int rows = i / RZEDY;
        int cols = i % KOLUMNY;

        // Wektory przechowujące możliwe wiersze i kolumny dla sąsiadów wierzchołka.
        vector<int> possible_rows;
        vector<int> possible_cols;

        // Dodawanie możliwych wierszy.
        possible_rows.push_back(rows);
        if (rows != 0)
            possible_rows.push_back(rows - 1);
        if (rows != (RZEDY - 1))
            possible_rows.push_back(rows + 1);

        // Dodawanie możliwych kolumn.
        possible_cols.push_back(cols);
        if (cols != 0)
            possible_cols.push_back(cols - 1);
        if (cols != (KOLUMNY - 1))
            possible_cols.push_back(cols + 1);

        // Tworzenie wszystkich możliwych par: numer wiersza - numer kolumny.
        for (int j = 0; j < possible_rows.size(); j++)
        {
            for (int k = 0; k < possible_cols.size(); k++)
            {
                // Sprawdzanie, czy para współrzędnych to współrzędne wierzchołka,
                // którego sąsiadów szukamy. Jeśli nie, dodajemy do listy sąsiadów.
                if (!(possible_rows[j] == rows && possible_cols[k] == cols))
                {
                    i_neighbor_list.push_back(possible_rows[j] * RZEDY + possible_cols[k]);
                }
            }
        }

        // Dodanie listy sąsiadów wierzchołka do głównej listy sąsiedztwa.
        neighbor_list.push_back(i_neighbor_list);
    }
}

/**
 * Znajduje wszystkie słowa na planszy.
 *
 * Po zakończeniu działania wszystkie znalezione słowa na planszy znajdują się w wektorze `all_words`.
 */
void BoardAnalyzer::findAllWords()
{
    for (int i = 0; i < RZEDY * KOLUMNY; i++)
    {
        searchNode(i);
    }

    removeDuplicates();
}

/**
 * Zwraca listę wszystkich słów znajdujących się na planszy.
 *
 * Jeśli lista słów nie została jeszcze obliczona, inicjalizuje
 * graf sąsiedztwa i odnajduje wszystkie słowa na planszy.
 *
 * @return Wektor zawierający wszystkie słowa znalezione na planszy.
 */
vector<string> BoardAnalyzer::getAllWords()
{
    if (all_words.empty())
    {
        fillNeighborList();
        findAllWords();
    }

    return all_words;
}

/**
 * @brief Usuwa duplikaty słów z listy wszystkich słów na planszy.
 *
 * Funkcja sortuje listę `all_words` i usuwa duplikaty, aby każde słowo
 * występowało tylko raz na liście końcowej.
 *
 * Proces obejmuje:
 * 1. Sortowanie wektora `all_words`.
 * 2. Użycie algorytmu `unique`, który przesuwa wszystkie duplikaty na koniec wektora.
 * 3. Wywołanie `erase` w celu usunięcia duplikatów z wektora.
 *
 * Dzięki temu wektor `all_words` zawiera wyłącznie unikalne słowa w porządku rosnącym.
 */
void BoardAnalyzer::removeDuplicates()
{
    sort(all_words.begin(), all_words.end());

    auto it = unique(all_words.begin(), all_words.end());

    all_words.erase(it, all_words.end());
}

/**
 * Metoda rekurencyjnego przeszukiwania grafu, służąca do znajdowania wszystkich możliwych
 * słów na planszy zgodnych ze słownikiem.
 *
 * @param node_number Numer wierzchołka (litery na planszy), od którego rozpoczyna się przeszukiwanie.
 *
 * Metoda:
 * 1. Dodaje numer wierzchołka do listy odwiedzonych.
 * 2. Tworzy string reprezentujący odwiedzone litery.
 * 3. Wykonuje wyszukiwanie binarne w słowniku w celu znalezienia słów
 *    zaczynających się od danego prefiksu.
 * 4. Jeśli znajdzie dopasowane słowo, dodaje je do listy `all_words`.
 * 5. Kontynuuje przeszukiwanie, jeśli prefiks pasuje do innych słów w słowniku.
 * 6. Po zakończeniu usuwa bieżący wierzchołek z listy odwiedzonych.
 */
void BoardAnalyzer::searchNode(int node_number)
{
    visited.push_back(node_number);

    string word = visitedLettersAsString();

    int word_index = dictionary.findWordThatStartsWith(word);

    string found_word = dictionary.getWord(word_index);
    string found_word_next = dictionary.getWord(word_index + 1);

    bool word_found = (found_word == word);
    bool prefix_found = (found_word_next.rfind(word, 0) == 0);
    bool no_word_but_prefix_found = (!word_found && (found_word.rfind(word, 0) == 0));

    if (word_found)
    {
        all_words.push_back(word);
    }

    if (prefix_found || no_word_but_prefix_found)
    {
        for (int node : neighbor_list[node_number])
        {
            searchNode(node);
        }
    }

    visited.pop_back();
}

/**
 * @brief Łączy litery odpowiadające odwiedzonym wierzchołkom w jeden ciąg znaków.
 *
 * Funkcja konwertuje listę odwiedzonych wierzchołków (ich indeksy) na string
 * składający się z odpowiadających im liter z planszy.
 *
 * @return Sklejony ciąg znaków odpowiadający odwiedzonym wierzchołkom.
 */
string BoardAnalyzer::visitedLettersAsString()
{
    string word = "";

    for (int node : visited)
    {
        word += board[node / RZEDY][node % KOLUMNY];
    }

    return word;
}
