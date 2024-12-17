#ifndef LEADERBOARDUPDATEWINDOW_H
#define LEADERBOARDUPDATEWINDOW_H

#include <QDialog>
#include "../leaderboard/Leaderboard.h"
namespace Ui {
class LeaderboardUpdateWindow;
}

class LeaderboardUpdateWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LeaderboardUpdateWindow(Leaderboard *lb, QWidget *parent = nullptr);
    ~LeaderboardUpdateWindow();
    void goToLeaderboard();

private:
    Ui::LeaderboardUpdateWindow *ui;
    Leaderboard *leaderboard;
};

#endif // LEADERBOARDUPDATEWINDOW_H
