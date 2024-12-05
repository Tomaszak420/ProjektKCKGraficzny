#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "instructionswindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)  // Inicjalizacja obiektu ui
{
    ui->setupUi(this);  // Ustawienie widżetów z pliku .ui
    connect(ui->Graj, &QPushButton::clicked, this, [this]() { onButtonClick(1); });
    connect(ui->Leaderboard, &QPushButton::clicked, this, [this]() { onButtonClick(2); });
    connect(ui->InstrukcjaGry, &QPushButton::clicked, this, [this]() { onButtonClick(3); });
    connect(ui->Wyjscie, &QPushButton::clicked, this, [this]() { onButtonClick(4); });
}
void MainWindow::setupUI()
{
    // Usuwamy stare UI (jeśli istnieje)
    delete ui;
    ui = new Ui::MainWindow;
    ui->setupUi(this);  // Ustawienie widżetów z pliku .ui
    connect(ui->Graj, &QPushButton::clicked, this, [this]() { onButtonClick(1); });
    connect(ui->Leaderboard, &QPushButton::clicked, this, [this]() { onButtonClick(2); });
    connect(ui->InstrukcjaGry, &QPushButton::clicked, this, [this]() { onButtonClick(3); });
    connect(ui->Wyjscie, &QPushButton::clicked, this, [this]() { onButtonClick(4); });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onButtonClick(int buttonId)
{
    ScreenChoice choice = convertUserChoice(buttonId);
    switch (choice) {
    case GAME:
        QMessageBox::information(this, "Game", "Starting Game...");
        break;
    case LEADERBOARD:
        QMessageBox::information(this, "Leaderboard", "Showing Leaderboard...");
        break;
    case INSTRUCTIONS: {
        InstructionsWindow *instructionsWindow = new InstructionsWindow(this);
        // Ustawiamy okno instrukcji jako centralny widget
        setCentralWidget(instructionsWindow);
        break;
    }
    case EXIT:
        QApplication::quit();
        break;
    }
}


ScreenChoice MainWindow::convertUserChoice(int userChoice)
{
    switch (userChoice) {
    case 1: return GAME;
    case 2: return LEADERBOARD;
    case 3: return INSTRUCTIONS;
    case 4: return EXIT;
    }
    return EXIT; // Default to exit if invalid
}
