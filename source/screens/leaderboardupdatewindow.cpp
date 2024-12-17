#include "leaderboardupdatewindow.h"
#include "ui_leaderboardupdatewindow.h"
#include "leaderboardwindow.h"
#include "mainwindow.h"
#include <iostream>
#include <string>

LeaderboardUpdateWindow::LeaderboardUpdateWindow(Leaderboard *lb, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::LeaderboardUpdateWindow),
    leaderboard(lb)
{
    ui->setupUi(this);

    setWindowTitle(QString("Gratulacje!"));

    ui->scoreLabel->setText(QString("Masz jeden z najlepszych wynikow: %1").arg(leaderboard->getScoreBuffer()));

    connect(ui->pushButton, &QPushButton::clicked, this, &LeaderboardUpdateWindow::goToLeaderboard);
}

LeaderboardUpdateWindow::~LeaderboardUpdateWindow()
{
    delete ui;
}

void LeaderboardUpdateWindow::goToLeaderboard() 
{
    // Dodanie wyniku do leaderboardu
    QString input = ui->lineEdit->text();
    string name = input.toStdString();

    int score = leaderboard->getScoreBuffer();
    leaderboard->insertScore(name, score);

    // Przejscie do leaderboardu
    LeaderboardWindow *leaderboardWindow = new LeaderboardWindow(leaderboard, qobject_cast<MainWindow*>(parent()));
    if (leaderboardWindow) {
        leaderboardWindow->show();
        this->close();
    }
}