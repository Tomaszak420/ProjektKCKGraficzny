#include "gamewindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "GameState.h"
#include "mainwindow.h"
#include "leaderboardwindow.h"
#include "leaderboardupdatewindow.h"
#include "Leaderboard.h"
#include "QTimer"
#include <iostream>
GameWindow::GameWindow(Leaderboard *leaderboard, GameState *gameState, QWidget *parent)
    : QWidget(parent), state(gameState),  lb(leaderboard)
{
    // Ustawienia głównego układu
    auto *mainLayout = new QVBoxLayout(this);

    // Plansza
    boardLayout = new QGridLayout();
    mainLayout->addLayout(boardLayout);

    // Lista znalezionych słów
    foundWordsList = new QListWidget();
    mainLayout->addWidget(foundWordsList);

    // Licznik słów
    wordCounterLabel = new QLabel("Znalezione słowa: 0");
    mainLayout->addWidget(wordCounterLabel);

    // Licznik czasu
    timeCounterLabel = new QLabel("Czas: 60"); // Na przykład 60 sekund
    mainLayout->addWidget(timeCounterLabel);

    // Przyciski sterujące
    auto *buttonLayout = new QHBoxLayout();
    restartButton = new QPushButton("Restart");
    endButton = new QPushButton("Zakończ");
    checkWordButton = new QPushButton("Sprawdz słowo");
    buttonLayout->addWidget(restartButton);
    buttonLayout->addWidget(checkWordButton);
    buttonLayout->addWidget(endButton);
    mainLayout->addLayout(buttonLayout);

    // Połączenia sygnałów i slotów
    connect(restartButton, &QPushButton::clicked, this, &GameWindow::restartGame);
    connect(endButton, &QPushButton::clicked, this, &GameWindow::onBackToMenuClicked);
    connect(checkWordButton, &QPushButton::clicked, this, &GameWindow::checkWord);
    state->fillBoard();

    // Timer
    timeLeft = 5;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTime);
    timer->start(1000);

    // Wypełnij planszę
    state->startGame();
    updateBoard();
}



void GameWindow::updateBoard()
{
    // Czyszczenie poprzedniej planszy
    QLayoutItem *child;
    while ((child = boardLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Tworzenie nowej planszy
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            auto *cellButton = new QPushButton(QString::fromStdString(state->board[i][j]));
            cellButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            connect(cellButton, &QPushButton::clicked, this, &GameWindow::handleCellClick);
            boardLayout->addWidget(cellButton, i, j);
        }
    }

    clearBoard();
}

void GameWindow::handleCellClick()
{
    auto *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    int row, col;
    // Znajdź pozycję przycisku w układzie
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (boardLayout->itemAtPosition(i, j)->widget() == clickedButton) {
                row = i;
                col = j;
                break;
            }
        }
    }

    
    if (state->isValidSelection({row, col})) 
    {
        // Zmieniamy kolor przycisku na zielony
        clickedButton->setStyleSheet("background-color: green;");

        // Dodaj literę do gry
        state->tryAddLetter({row, col});
    }

}


void GameWindow::checkWord()
{
    bool wordIsValid = state->tryAddSelectedWord();

    if (wordIsValid) 
    {
        //cerr << "Word is valid." << endl;
        updateFoundWords();
        updateWordCounter();
    }

    state->clearSelection();
    clearBoard();
}

void GameWindow::clearBoard() 
{
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            boardLayout->itemAtPosition(i, j)->widget()->setStyleSheet("background-color: darkslategrey;");
        }
    }
}

void GameWindow::updateFoundWords()
{
    string word = state->getSelectedWord();
    QString qword = QString::fromStdString(word);

    QListWidgetItem *item = new QListWidgetItem();
    item->setText(qword);

    foundWordsList->addItem(item);
}

void GameWindow::updateWordCounter()
{
    wordCounterLabel->setText(QString("Znalezione słowa: %1").arg(state->found_words.size()));
}

void GameWindow::clearFoundWords() 
{
    foundWordsList->clear();
}

void GameWindow::restartGame()
{

    state->restartGame();
    updateBoard();
    clearFoundWords();
    updateWordCounter();
}


void GameWindow::onBackToMenuClicked()
{
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        mainWindow->setupUI();
        mainWindow->show();
        this->close();
    }
}
void GameWindow::updateTime()
{
    if (timeLeft > 0) {
        timeLeft--;
        timeCounterLabel->setText(QString("Czas: %1").arg(timeLeft));
    } else {
        timer->stop(); // Zatrzymaj timer
        QMessageBox::information(this, "Czas minął", "Czas minął! Gra zakończona.");
        endGame();
    }
}
//TODO przejście do lb
void GameWindow::endGame()
{
    LeaderboardUpdateWindow *leaderboardUpdateWindow = new LeaderboardUpdateWindow(lb, qobject_cast<MainWindow *>(parent()));
    //LeaderboardWindow *leaderboardWindow = new LeaderboardWindow(lb, qobject_cast<MainWindow *>(parent()));

    if (leaderboardUpdateWindow) {
        leaderboardUpdateWindow->show();

        //leaderboardWindow->show();

        this->close();
    }
}
