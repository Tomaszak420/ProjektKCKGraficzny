#include <gtest/gtest.h>
#include "../Dictionary.h"
#include <fstream>

// Funkcja pomocnicza do tworzenia pliku tymczasowego
void createTempFile(const std::string& file_name) {
    std::ofstream temp_file(file_name);
    temp_file << "apple\nbanana\ncherry\n";
    temp_file.close();
}

// Test funkcji loadWordList z plikiem tymczasowym
TEST(DictionaryTest, LoadWordList) {
    createTempFile("test_dictionary.txt");

    // Tworzymy obiekt Dictionary i ładujemy słowa
    Dictionary dict("test_dictionary.txt");
    EXPECT_TRUE(dict.loadWordList("test_dictionary.txt"));

    // Usuwamy plik tymczasowy po teście
    std::remove("test_dictionary.txt");
}

// Test funkcji findWord
TEST(DictionaryTest, FindWord) {
    // Tworzymy plik tymczasowy
    createTempFile("test_dictionary.txt");

    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");

    EXPECT_NE(dict.findWord("apple"), -1); // "apple" powinno być znalezione
    EXPECT_EQ(dict.findWord("not_in_dictionary"), -1); // Słowo nieobecne

    // Usuwamy plik tymczasowy po teście
    std::remove("test_dictionary.txt");
}

// Test funkcji findWordThatStartsWith
TEST(DictionaryTest, FindWordThatStartsWith) {
    // Tworzymy plik tymczasowy
    createTempFile("test_dictionary.txt");

    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");

    int index = dict.findWordThatStartsWith("app");
    EXPECT_NE(index, -1); // Powinien znaleźć prefiks "app"
    EXPECT_TRUE(dict.getWord(index).find("app") == 0); // Słowo zaczyna się od "app"

    // Usuwamy plik tymczasowy po teście
    std::remove("test_dictionary.txt");
}

// Test funkcji getWord
TEST(DictionaryTest, GetWord) {
    // Tworzymy plik tymczasowy
    createTempFile("test_dictionary.txt");

    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");

    EXPECT_NE(dict.getWord(0), ""); // Pierwsze słowo powinno być niepuste
    EXPECT_EQ(dict.getWord(-1), ""); // Indeks ujemny powinien zwrócić pusty string
    EXPECT_EQ(dict.getWord(dict.word_list.size()), ""); // Indeks poza zakresem powinien zwrócić pusty string

    // Usuwamy plik tymczasowy po teście
    std::remove("test_dictionary.txt");
}

// Test funkcji hasWord
TEST(DictionaryTest, HasWord) {
    // Tworzymy plik tymczasowy
    createTempFile("test_dictionary.txt");

    Dictionary dict("test_dictionary.txt");
    dict.loadWordList("test_dictionary.txt");

    EXPECT_TRUE(dict.hasWord("apple")); // "apple" powinno być obecne
    EXPECT_FALSE(dict.hasWord("not_in_dictionary")); // Słowo nieobecne

    // Usuwamy plik tymczasowy po teście
    std::remove("test_dictionary.txt");
}
