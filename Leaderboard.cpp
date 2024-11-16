#include "Leaderboard.h"

Leaderboard::Leaderboard(int max_length)
{
    this->max_length = max_length;
}

bool Leaderboard::doesChangeLeaderboard(int new_score)
{
    for (LeaderboardItem item : items)
    {
        if (item.score < new_score)
        {
            return true;
        }
    }
    return false;
}

void Leaderboard::insertScore(std::string name, int new_score) 
{
    std::vector<struct LeaderboardItem>::iterator it;

    for (it = items.begin(); it < items.end(); it++) 
    {
        if (it->score < new_score)
        {   
            LeaderboardItem new_item = { name, new_score };
            items.insert(it, new_item);
        }
    }

    if (items.size() > max_length) 
    {
        items.pop_back();
    }
}

std::vector<struct LeaderboardItem> Leaderboard::getItemsList() 
{
    return items;
}

int Leaderboard::getMaxLength() 
{
    return max_length;
}