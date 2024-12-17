#include "leaderboardupdatewindow.h"
#include "ui_leaderboardupdatewindow.h"
#include "leaderboardwindow.h"
#include "mainwindow.h"

LeaderboardUpdateWindow::LeaderboardUpdateWindow(Leaderboard *lb, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LeaderboardUpdateWindow),
    leaderboard(lb)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, &LeaderboardUpdateWindow::goToLeaderboard);
}

LeaderboardUpdateWindow::~LeaderboardUpdateWindow()
{
    delete ui;
}

void LeaderboardUpdateWindow::goToLeaderboard() {
    LeaderboardWindow *leaderboardWindow = new LeaderboardWindow(leaderboard, qobject_cast<MainWindow*>(parent()));
    //setCentralWidget(leaderboardWindow);
    if (leaderboardWindow) {
        leaderboardWindow->show();
        this->close();
    }
}