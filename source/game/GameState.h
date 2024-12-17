#include <string>
#include <vector>

#include "../board/BoardAnalyzer.h"
#include "../coordinates/Coordinates.h"

#define KOLUMNY 4
#define RZEDY 4
#define MAX_WYBRANYCH 16

#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;

class GameState {
    
        
    vector<string> all_words;
    vector<struct coordinates> selected_coordinates;
    vector<string> selected_letters;

    public:
    string board[RZEDY][KOLUMNY];
    vector<string> found_words;

    void startGame();
    bool isOnBoard(string word);
    void fillBoard();
    bool hasBeenSelected(struct coordinates cursor);
    bool isValidSelection(struct coordinates selected_letter);
    void tryAddLetter(struct coordinates cursor);
    bool tryAddSelectedWord();
    void restartGame();
    string getSelectedWord();
    int getSelectedLength();
    bool isFoundWord(string word);
    void clearSelection();
    vector<struct coordinates> getSelectedCoordinates();
    int calculateScore();

};

#endif