#include <string>
#include <vector>
#include "Dictionary.h"

#define KOLUMNY 4
#define RZEDY 4

using namespace std;

class BoardAnalyzer {
    string board[RZEDY][KOLUMNY];
    Dictionary dictionary;
    vector<string> all_words;
    vector<string> visited;

    vector<vector<int>> neighbor_list;

public:
    BoardAnalyzer(string board[RZEDY][KOLUMNY], string dictionary_file_path);
    void fillNeighborList();
};