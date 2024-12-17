#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../leaderboard/Leaderboard.h"
#include "../game/GameState.h"

enum ScreenChoice {
    GAME,
    LEADERBOARD,
    INSTRUCTIONS,
    EXIT
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupUI();

private:
    Leaderboard *lb;
    void createLogo();
    GameState gameState;
    ScreenChoice convertUserChoice(int userChoice);
    void onButtonClick(int buttonId);

private:
    Ui::MainWindow *ui; // Wszechstronny obiekt do interakcji z .ui
};

#endif // MAINWINDOW_H
