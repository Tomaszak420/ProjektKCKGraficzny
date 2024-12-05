#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

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

    void createLogo();
    ScreenChoice convertUserChoice(int userChoice);
    void onButtonClick(int buttonId);

private:
    Ui::MainWindow *ui; // Wszechstronny obiekt do interakcji z .ui
};

#endif // MAINWINDOW_H
