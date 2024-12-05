#include "Leaderboard.h"
#include"LeaderboardItem.h"
Leaderboard::Leaderboard(int max_length)
{
    this->max_length = max_length;
    this->score_buffer = 0;
}

bool Leaderboard::doesChangeLeaderboard(int new_score)
{
    if (items.size() < max_length) return true;

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
    LeaderboardItem new_item = { name, new_score };

    for (it = items.begin(); it < items.end(); it++)
    {
        if (it->score < new_score)
        {
            items.insert(it, new_item);
        }
    }

    if (items.size() > max_length)
    {
        items.pop_back();
    }

    if (items.size() < max_length)
    {
        items.push_back(new_item);
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

void Leaderboard::setScoreBuffer(int new_score)
{
    score_buffer = new_score;
}

int Leaderboard::getScoreBuffer()
{
    return score_buffer;
}
