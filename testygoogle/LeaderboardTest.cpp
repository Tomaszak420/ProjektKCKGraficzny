#include <vector>
#include "../LeaderboardItem.h"
#include "../Leaderboard.h"
#include <cassert>
#include <iostream>



Leaderboard::Leaderboard(int max_length) {
    this->max_length = max_length;
    this->score_buffer = 0;
}

bool Leaderboard::doesChangeLeaderboard(int new_score) {
    if (items.size() < max_length) return true;

    for (LeaderboardItem item: items) {
        if (item.score < new_score) {
            return true;
        }
    }

    return false;
}

void Leaderboard::insertScore(std::string name, int new_score) {
    std::vector<struct LeaderboardItem>::iterator it;
    LeaderboardItem new_item = {name, new_score};

    for (it = items.begin(); it < items.end(); it++) {
        if (it->score < new_score) {
            items.insert(it, new_item);
            break;
        }
    }

    if (items.size() > max_length) {
        items.pop_back();
    }

    if (items.size() < max_length) {
        items.push_back(new_item);
    }
}

std::vector<struct LeaderboardItem> Leaderboard::getItemsList() {
    return items;
}

int Leaderboard::getMaxLength() {
    return max_length;
}

void Leaderboard::setScoreBuffer(int new_score) {
    score_buffer = new_score;
}

int Leaderboard::getScoreBuffer() {
    return score_buffer;
}

// Tests
void test_doesChangeLeaderboard() {
    Leaderboard lb(3);
    assert(lb.doesChangeLeaderboard(100) == true);
    lb.insertScore("Player1", 100);
    lb.insertScore("Player2", 200);
    lb.insertScore("Player3", 300);
    assert(lb.doesChangeLeaderboard(50) == false);
    assert(lb.doesChangeLeaderboard(150) == true);
}

void test_insertScore() {
    Leaderboard lb(3);
    lb.insertScore("Player1", 100);
    lb.insertScore("Player2", 200);
    lb.insertScore("Player3", 300);
    assert(lb.getItemsList().size() == 3);
    lb.insertScore("Player4", 50);
    assert(lb.getItemsList().size() == 3);
    lb.insertScore("Player5", 400);
    assert(lb.getItemsList().size() == 3);
    assert(lb.getItemsList()[0].name == "Player5");
    assert(lb.getItemsList()[0].score == 400);
}

void test_setGetScoreBuffer() {
    Leaderboard lb(3);
    lb.setScoreBuffer(500);
    assert(lb.getScoreBuffer() == 500);
}

int main() {
    test_doesChangeLeaderboard();
    test_insertScore();
    test_setGetScoreBuffer();
    std::cout << "Leaderboard passed!" << std::endl;
    return 0;
}