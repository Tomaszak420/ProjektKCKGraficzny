#include <string>
#include <vector>
#include <algorithm>
#include "Dictionary.h"

#define KOLUMNY 4
#define RZEDY 4

using namespace std;

#ifndef BOARDANALYZER_H
#define BOARDANALYZER_H

class BoardAnalyzer 
{
    string board[RZEDY][KOLUMNY];
    Dictionary dictionary;
    vector<string> all_words;
    vector<int> visited;
    vector<vector<int>> neighbor_list;

    void fillNeighborList();
    void findAllWords();
    void searchNode(int node_number);
    string visitedLettersAsString();
    void removeDuplicates();

public:
    BoardAnalyzer(string board[RZEDY][KOLUMNY], string dictionary_file_path);
    vector<string> getAllWords();
};

#endif