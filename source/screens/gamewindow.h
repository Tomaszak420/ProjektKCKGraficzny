#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "../game/GameState.h"
#include "../leaderboard/Leaderboard.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(Leaderboard *leaderboard, GameState *gameState, QWidget *parent = nullptr);

private slots:
    void updateBoard();
    void clearBoard();
    void handleCellClick();
    void checkWord();
    void updateFoundWords();
    void clearFoundWords();
    void updateWordCounter();
    void restartGame();
    void onBackToMenuClicked();
    void updateTime();  // Nowa metoda do aktualizacji czasu
    void endGame();

private:



    GameState *state;
    Leaderboard *lb;

    QGridLayout *boardLayout;
    QListWidget *foundWordsList;
    QLabel *wordCounterLabel;
    QLabel *timeCounterLabel;  // Nowy QLabel dla licznika czasu
    QPushButton *restartButton;
    QPushButton *endButton;
    QPushButton *checkWordButton;
    QTimer *timer;  // Timer
    int timeLeft;
};

#endif // GAMEWINDOW_H
