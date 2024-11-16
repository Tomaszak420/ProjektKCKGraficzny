#include <vector>
#include "LeaderboardItem.h"

#ifndef LEADERBOARD_H
#define LEADERBOARD_H
class Leaderboard {
    std::vector<struct LeaderboardItem> items;
    int max_length;

public:
    Leaderboard(int max_length);
    bool doesChangeLeaderboard(int new_score);
    void insertScore(std::string name, int new_score);
    std::vector<struct LeaderboardItem> getItemsList();
    int getMaxLength();
};
#endif