#include "leaderboardwindow.h"
#include "ui_leaderboardwindow.h"
#include "mainwindow.h"

LeaderboardWindow::LeaderboardWindow(Leaderboard *lb, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeaderboardWindow),
    leaderboard(lb)
{
    ui->setupUi(this);

    // Wypełnij tabelę wynikami
    populateLeaderboard();

    // Połącz przycisk powrotu do menu z odpowiednią funkcją
    connect(ui->backToMenuButton, &QPushButton::clicked, this, &LeaderboardWindow::onBackToMenuClicked);
}

LeaderboardWindow::~LeaderboardWindow()
{
    delete ui;
}

void LeaderboardWindow::populateLeaderboard()
{
    std::vector<LeaderboardItem> items = leaderboard->getItemsList();
    int maxLength = leaderboard->getMaxLength();

    ui->tableWidget->setRowCount(maxLength);
    ui->tableWidget->setColumnCount(2); // Kolumny: Nazwa, Wynik
    ui->tableWidget->setHorizontalHeaderLabels({"Nazwa", "Wynik"});

    for (int i = 0; i < maxLength; i++) {
        QTableWidgetItem *nameItem;
        QTableWidgetItem *scoreItem;

        if (i < items.size()) {
            nameItem = new QTableWidgetItem(QString::fromStdString(items[i].name));
            scoreItem = new QTableWidgetItem(QString::number(items[i].score));
        } else {
            nameItem = new QTableWidgetItem("PUSTY");
            scoreItem = new QTableWidgetItem("");
        }

        // Blokowanie edycji komórek
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        scoreItem->setFlags(scoreItem->flags() & ~Qt::ItemIsEditable);

        // Ustawienie komórek w tabeli
        ui->tableWidget->setItem(i, 0, nameItem);
        ui->tableWidget->setItem(i, 1, scoreItem);
    }

    ui->tableWidget->resizeColumnsToContents();
}


void LeaderboardWindow::onBackToMenuClicked()
{
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {
        mainWindow->setupUI();
        mainWindow->show();
        this->close();
    }
}
