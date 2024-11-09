#include "BoardAnalyzer.h"

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

// Tworzy graf w postaci listy sasiedztwa
void BoardAnalyzer::fillNeighborList()
{

    for (int i = 0; i < RZEDY * KOLUMNY; i++)
    {
        // W tej liście będziemy przechowywać sąsiadów danego wierzchołka.
        vector<int> i_neighbor_list;

        // Konwersja numeru wierzchołka na jego numer kolumny oraz numer wiersza
        int rows = i / RZEDY;
        int cols = i % KOLUMNY;

        // Wektory będą przechowywały numery wierszy i kolumn, które mogą posiadać sąsiedzi wierzchołka
        vector<int> possible_rows;
        vector<int> possible_cols;

        // Dodawanie możliwych wierszy
        possible_rows.push_back(rows);
        if (rows != 0)
            possible_rows.push_back(rows - 1);
        if (rows != (RZEDY - 1))
            possible_rows.push_back(rows + 1);

        // Dodawanie możliwych kolumn
        possible_cols.push_back(cols);
        if (cols != 0)
            possible_cols.push_back(cols - 1);
        if (cols != (KOLUMNY - 1))
            possible_cols.push_back(cols + 1);

        // Tworzymy wszystkie możliwe pary: numer wiersza - numer kolumny
        for (int j = 0; j < possible_rows.size(); j++)
        {
            for (int k = 0; k < possible_cols.size(); k++)
            {
                // Sprawdzamy, czy para współrzędnych to współrzędne wierzchołka, którego sąsiadów szukamy.
                // Jeśli nie, to dodajemy ją do listy sąsiadów.
                // (Zakładamy, że żaden wierzchołek nie jest swoim własnym sąsiadem.)
                if (!(possible_rows[j] == rows && possible_cols[k] == cols))
                {
                    i_neighbor_list.push_back(possible_rows[j] * RZEDY + possible_cols[k]);
                }
            }
        }

        // Listę sąsiadów wierzchołka dodajemy do listy, która będzie zwierała listy sąsiadów wszystkich wierzchołków.
        neighbor_list.push_back(i_neighbor_list);
    }
}

// Znajduje wszystkie slowa na planszy.
// Po zakonczeniu dzialania wszystkie slowa na planszy znajduja sie w wektorze all_words.
void BoardAnalyzer::findAllWords()
{
    for (int i = 0; i < RZEDY * KOLUMNY; i++)
    {
        searchNode(i);
    }

    removeDuplicates();
}

// Zwraca liste wszystkich slow wystepujacych na planszy
vector<string> BoardAnalyzer::getAllWords()
{
    if (all_words.empty())
    {
        fillNeighborList();
        findAllWords();
    }

    return all_words;
}

// Usuwa duplikaty z listy wszystkich slow na planszy
// (to samo slowo moglo pojawic sie kilka razy w roznych miejscach)
void BoardAnalyzer::removeDuplicates()
{
    sort(all_words.begin(), all_words.end());

    // Unique wyrzuca wszytkie duplikaty wystepujace w posortowanej liscie na jej koniec
    // i zwraca referencje do punktu, od ktorego w liscie znajduja sie juz same duplikaty.
    auto it = unique(all_words.begin(), all_words.end());

    // Usuwanie duplikatow zgormadzonych na koncu listy
    all_words.erase(it, all_words.end());
}

// Metoda do rekurencyjnego przeszukiwania grafu
void BoardAnalyzer::searchNode(int node_number)
{
    visited.push_back(node_number);

    string word = visitedLettersAsString();

    // Binarnie wyszukujemy pierwsze slowo w slowniku, ktore zaczyna sie na 'word'
    int word_index = dictionary.findWordThatStartsWith(word);

    // Rozpoczyna sie analiza slowa, na ktorym zatrzymalo sie wyszukiwanie binarne oraz slowa nastepnego.
    string found_word = dictionary.getWord(word_index);
    string found_word_next = dictionary.getWord(word_index + 1);

    // Sprawdza, czy slowo zostalo znalezione.
    bool word_found = (found_word == word);
    // Pokrywa przypadek, gdy slowo zostalo znalezione, ale w slowniku znajduja sie jeszcze inne wyrazy, dla ktorych slowo jest prefiksem
    bool prefix_found = (found_word_next.rfind(word, 0) == 0);
    // Pokrywa przypadek, gdy slowo nie zostalo znalezione, ale w slowniku sa wyrazy, dla ktorych jest ono prefiksem
    bool no_word_but_prefix_found = (!word_found && (found_word.rfind(word, 0) == 0));

    if (word_found)
    {
        all_words.push_back(word);
    }

    // Jesli w slowniku sa slowa, dla ktorych slowo jest prefiksem, przeszukiwanie trwa dalej.
    if (prefix_found || no_word_but_prefix_found)
    {
        for (int node : neighbor_list[node_number])
        {
            searchNode(node);
        }
    }

    visited.pop_back();
}

// Klasa przechowuje numery kolejno odwiedzanych wierzcholkow podczas przeszukiwania grafu.
// Ta metoda laczy odpowiadajace im litery w jeden string.
string BoardAnalyzer::visitedLettersAsString()
{
    string word = "";

    for (int node : visited)
    {
        word += board[node / RZEDY][node % KOLUMNY];
    }

    return word;
}
