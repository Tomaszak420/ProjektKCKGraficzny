#include <string>
#include <vector>

#include "BoardAnalyzer.h"
#include "Coordinates.h"

#define KOLUMNY 4
#define RZEDY 4
#define MAX_WYBRANYCH 16

#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;

class GameState {
    public:
        string board[RZEDY][KOLUMNY];
        vector<string> all_words;
        vector<string> found_words;
        vector<struct coordinates> selected_coordinates;
        vector<string> selected_letters;
        int points;

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