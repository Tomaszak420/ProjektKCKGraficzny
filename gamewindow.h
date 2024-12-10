#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include "GameState.h"

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(GameState *gameState, QWidget *parent = nullptr);

private slots:
    void updateBoard();
    void handleCellClick();
    void checkWord();
    void updateFoundWords();
    void updateWordCounter();
    void restartGame();
    void onBackToMenuClicked();
    void updateTime();  // Nowa metoda do aktualizacji czasu
    void endGame();

private:



    GameState *state;

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
