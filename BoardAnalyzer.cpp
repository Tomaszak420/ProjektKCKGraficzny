#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer(string board[RZEDY][KOLUMNY], string dictionary_file_path) : dictionary(dictionary_file_path)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

void BoardAnalyzer::fillNeighborList() {

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

void BoardAnalyzer::findAllWords() {
    for (int i = 0; i < RZEDY * KOLUMNY; i++) {
        searchNode(i);
             
    }
    //searchNode(0);

    removeDuplicates();
}

void BoardAnalyzer::removeDuplicates()
{
    sort(all_words.begin(), all_words.end());

    auto it = unique(all_words.begin(), all_words.end());

    all_words.erase(it, all_words.end());
}

vector<string> BoardAnalyzer::getAllWords() 
{
    if (all_words.empty()) {
        fillNeighborList();
        findAllWords();
    }

    return all_words;
}

string BoardAnalyzer::visitedLettersAsString() 
{
    string word = "";

    for (int node: visited) {
        word += board[node / RZEDY][node % KOLUMNY];
    }

    return word;
}

void BoardAnalyzer::searchNode(int node_number) 
{
    visited.push_back(node_number);

    string word = visitedLettersAsString();

    if (dictionary.hasWord(word)) {
        all_words.push_back(word);
    }

    if (dictionary.hasWordsThatStartWith(word))
    {
        for (int node : neighbor_list[node_number])
        {
            searchNode(node);
        }
    }

    visited.pop_back();
}