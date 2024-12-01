#include <gtest/gtest.h>
#include "../BoardAnalyzer.h"
#include "../BoardAnalyzer.cpp"
#include "../GameFunctions.h"
#include "../GameFunctions.cpp"
#include "../GameState.h"
#include "../GameState.cpp"
#include "../InstructionsFunctions.h"
#include "../InstructionsFunctions.cpp"
#include "../Leaderboard.h"
#include "../Leaderboard.cpp"
#include "../LeaderboardItem.h"
#include "../LeaderboardFunctions.h"
#include "../LeaderboardFunctions.cpp"
#include "../LeaderboardUpdateFunctions.h"
#include "../LeaderboardUpdateFunctions.cpp"
#include "../Coordinates.h"

#include "../Dictionary.h"
#include "../Dictionary.cpp"

// Test sprawdzający, czy plansza jest poprawnie wypełniana literami
TEST(GameStateTests, FillBoard) {
    GameState gs;
    gs.fillBoard();
    for (int i = 0; i < RZEDY; ++i) {
        for (int j = 0; j < KOLUMNY; ++j) {
            ASSERT_FALSE(gs.board[i][j].empty());
        }
    }
}

// Test sprawdzający, czy wybranie tej samej komórki nie jest dozwolone

TEST(GameStateTests, IsValidSelection_SameCell) {
    GameState gs;
    gs.fillBoard();
    coordinates c = {3, 3};
    gs.tryAddLetter(c);
    EXPECT_FALSE(gs.isValidSelection(c));

}

// Test sprawdzający poprawność wyboru sąsiadujących komórek
//nwm czemu nie działa
TEST(GameStateTests, IsValidSelection_AdjacentCell) {
    GameState gs;
    gs.fillBoard();
    coordinates c1 = {2, 2};
    coordinates c2 = {2, 1};
    gs.tryAddLetter(c1);

    EXPECT_TRUE(gs.isValidSelection(c2));

}

// Test dodawania słów do znalezionych
TEST(GameStateTests, TryAddSelectedWord) {
    GameState gs;
    gs.fillBoard();
    gs.selected_letters = {"T", "E", "S", "T"};
    EXPECT_TRUE(gs.tryAddSelectedWord());
    EXPECT_FALSE(gs.tryAddSelectedWord()); // Nie powinno dodać ponownie tego samego słowa
}

// Test sprawdzający poprawność obliczeń punktów
TEST(GameStateTests, CalculateScore) {
    GameState gs;
    gs.found_words = {"test", "hello", "example"};
    EXPECT_EQ(gs.calculateScore(), 1 + 2 + 5); // test (4), hello (5), example (7)
}

// Test sprawdzający czyszczenie zaznaczenia
TEST(GameStateTests, ClearSelection) {
    GameState gs;
    gs.selected_coordinates = {{0, 0}, {1, 1}};
    gs.clearSelection();
    EXPECT_EQ(gs.selected_coordinates.size(), 0);
}

// Test sprawdzający restart gry
TEST(GameStateTests, RestartGame) {
    GameState gs;
    gs.found_words = {"test"};
    gs.restartGame();
    EXPECT_TRUE(gs.found_words.empty());
    EXPECT_FALSE(gs.board[0][0].empty());
}

// Test sprawdzający, czy słowo znajduje się na planszy
TEST(GameStateTests, IsOnBoard) {
    GameState gs;
    gs.all_words = {"test", "word"};
    EXPECT_TRUE(gs.isOnBoard("test"));
    EXPECT_FALSE(gs.isOnBoard("missing"));
}

// Główna funkcja testowa Google Test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
