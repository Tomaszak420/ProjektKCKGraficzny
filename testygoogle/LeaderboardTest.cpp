#include <gtest/gtest.h>
#include "../Leaderboard.h"
#include "../Leaderboard.cpp"
#include "../LeaderboardItem.h"


// Test inicjalizacji Leaderboard
TEST(LeaderboardTest, Initialization) {
    Leaderboard lb(5); // Maksymalna długość leaderboardu to 5

    EXPECT_EQ(lb.getMaxLength(), 5);
    EXPECT_TRUE(lb.getItemsList().empty());
}

// Test dodawania elementów do Leaderboard
TEST(LeaderboardTest, insertScore) {
    Leaderboard lb(3);

    lb.insertScore("Player1", 100);
    lb.insertScore("Player2", 150);

    std::vector<LeaderboardItem> items = lb.getItemsList();
    EXPECT_EQ(items.size(), 3);
    EXPECT_EQ(items[0].name, "Player2");
    EXPECT_EQ(items[1].score, 100);
}

// Test uzyskania pustych miejsc
TEST(LeaderboardTest, EmptySlots) {
    Leaderboard lb(5);

    lb.insertScore("Player1", 100);

    EXPECT_EQ(lb.getItemsList().size(), 1);
    EXPECT_EQ(lb.getMaxLength(), 5);
}
