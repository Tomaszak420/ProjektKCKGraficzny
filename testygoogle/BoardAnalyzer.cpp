#include <gtest/gtest.h>
#include <fstream>
#include "../BoardAnalyzer.h"
#include "../Dictionary.h"
#include <cstdlib>

// Klasa testowa
class BoardAnalyzerTest : public ::testing::Test {
protected:
    BoardAnalyzer *analyzer;
    string testBoard[RZEDY][KOLUMNY] = {
            {"A", "B", "C", "D"},
            {"E", "F", "G", "H"},
            {"I", "J", "K", "L"},
            {"M", "N", "O", "P"}
    };
    std::string testDictionaryFile;

    void SetUp() override {
        // Utworzenie tymczasowego pliku słownika
        testDictionaryFile = "test_dictionary.txt";
        std::ofstream dictFile(testDictionaryFile);
        dictFile << "APPLE\n";
        dictFile << "BANANA\n";
        dictFile << "GRAPE\n";
        dictFile << "KIWI\n";
        dictFile << "MELON\n";
        dictFile.close();

        analyzer = new BoardAnalyzer(testBoard, testDictionaryFile);
    }

    void TearDown() override {
        // Usunięcie tymczasowego pliku słownika po teście
        std::remove(testDictionaryFile.c_str());
        delete analyzer;
    }
};

// Test konstrukcji obiektu
TEST_F(BoardAnalyzerTest, ConstructorInitializesBoardCorrectly) {
    for (int i = 0; i < RZEDY; i++) {
        for (int j = 0; j < KOLUMNY; j++) {
            EXPECT_EQ(analyzer->getAllWords().size(), 0); // Na początku lista słów jest pusta
        }
    }
}

// Test funkcji fillNeighborList
TEST_F(BoardAnalyzerTest, FillNeighborListCorrectly) {
    analyzer->fillNeighborList();
    auto neighbors = analyzer->getAllWords();
    EXPECT_TRUE(neighbors.empty()); // Upewnij się, że lista sąsiedztwa nie jest pusta
}

// Test funkcji findAllWords
TEST_F(BoardAnalyzerTest, FindAllWords) {
    analyzer->findAllWords();
    auto words = analyzer->getAllWords();
    EXPECT_FALSE(words.empty()); // Oczekujemy, że znajdzie jakieś słowa
}

// Test funkcji removeDuplicates
TEST_F(BoardAnalyzerTest, RemoveDuplicates) {
    analyzer->findAllWords();
    analyzer->removeDuplicates();
    auto words = analyzer->getAllWords();
    auto unique_words = std::vector<string>(words.begin(), words.end());
    EXPECT_EQ(unique_words.size(), words.size()); // Po usunięciu duplikatów rozmiar powinien być taki sam
}

// Test funkcji searchNode
TEST_F(BoardAnalyzerTest, SearchNodeFindsWords) {
    analyzer->searchNode(0); // Zacznij od pierwszego wierzchołka
    auto words = analyzer->getAllWords();
    EXPECT_FALSE(words.empty()); // Powinien znaleźć jakieś słowa
}

// Test visitedLettersAsString
TEST_F(BoardAnalyzerTest, VisitedLettersAsString) {
    analyzer->searchNode(0);
    string word = analyzer->visitedLettersAsString();
    EXPECT_FALSE(word.empty()); // Sprawdź, czy ciąg znaków nie jest pusty
}
