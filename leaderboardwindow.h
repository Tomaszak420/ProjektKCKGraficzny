#ifndef LEADERBOARDWINDOW_H
#define LEADERBOARDWINDOW_H

#include <QWidget>
#include "Leaderboard.h"

namespace Ui {
class LeaderboardWindow;
}

class LeaderboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LeaderboardWindow(Leaderboard *lb, QWidget *parent = nullptr);
    ~LeaderboardWindow();

private slots:
    void onBackToMenuClicked();

private:
    Ui::LeaderboardWindow *ui;
    Leaderboard *leaderboard;
    void populateLeaderboard();
};

#endif 
