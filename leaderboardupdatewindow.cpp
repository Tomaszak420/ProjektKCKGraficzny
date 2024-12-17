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

    ui->scoreLabel->setText(QString("Masz jeden z najlepszych wynikow: %1").arg(leaderboard->getScoreBuffer()));

    connect(ui->pushButton, &QPushButton::clicked, this, &LeaderboardUpdateWindow::goToLeaderboard);
}

LeaderboardUpdateWindow::~LeaderboardUpdateWindow()
{
    delete ui;
}

void LeaderboardUpdateWindow::goToLeaderboard() {
    QString input = ui->lineEdit->text();
    string name = input.toStdString();
    
    int score = leaderboard->getScoreBuffer();
    leaderboard->insertScore(name, score);

    LeaderboardWindow *leaderboardWindow = new LeaderboardWindow(leaderboard, qobject_cast<MainWindow*>(parent()));
    if (leaderboardWindow) {
        leaderboardWindow->show();
        this->close();
    }
}