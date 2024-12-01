#include <gtest/gtest.h>
#include <ncurses.h>
#include <cstring>
#include "../ScreenChoice.h"
#include "../MenuFunctions.cpp"

// Deklaracja zewnętrznego logo
extern const char* ascii_logo[];
int getLogoWidth();
ScreenChoice convertUserChoice(int userChoice);

// Test funkcji getLogoWidth
TEST(ScreenTests, GetLogoWidth) {
    int expected_width = 64; // Szerokość najdłuższej linii w logo.
    ASSERT_EQ(getLogoWidth(), expected_width);
    std::cout << "Test GetLogoWidth passed successfully.\n";
}

// Test funkcji convertUserChoice dla wszystkich opcji menu
TEST(ScreenTests, ConvertUserChoice_Game) {
    ASSERT_EQ(convertUserChoice(1), GAME);
    std::cout << "Test ConvertUserChoice_Game passed successfully.\n";
}

TEST(ScreenTests, ConvertUserChoice_Leaderboard) {
    ASSERT_EQ(convertUserChoice(2), LEADERBOARD);
    std::cout << "Test ConvertUserChoice_Leaderboard passed successfully.\n";
}

TEST(ScreenTests, ConvertUserChoice_Instructions) {
    ASSERT_EQ(convertUserChoice(3), INSTRUCTIONS);
    std::cout << "Test ConvertUserChoice_Instructions passed successfully.\n";
}

TEST(ScreenTests, ConvertUserChoice_Exit) {
    ASSERT_EQ(convertUserChoice(4), EXIT);
    std::cout << "Test ConvertUserChoice_Exit passed successfully.\n";
}


// Test funkcji makeLogo - sprawdza, czy okno zostało poprawnie utworzone
TEST(ScreenTests, MakeLogo) {
    initscr();
    WINDOW* logo = makeLogo();

    ASSERT_NE(logo, nullptr);
    std::cout << "Test MakeLogo passed successfully.\n";

    delwin(logo);
    endwin();
}
