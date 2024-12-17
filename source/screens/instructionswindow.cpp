#include "instructionswindow.h"
#include "ui_instructionswindow.h"
#include "mainwindow.h"


InstructionsWindow::InstructionsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InstructionsWindow)
{
    ui->setupUi(this);

    // Połącz przycisk "Back to Main Menu" z funkcją, która wróci do głównego okna
    connect(ui->backToMainMenuButton, &QPushButton::clicked, this, &InstructionsWindow::goBackToMainWindow);
}

InstructionsWindow::~InstructionsWindow()
{
    delete ui;
}

void InstructionsWindow::goBackToMainWindow()
{
    // Zwracamy się do MainWindow, aby przejść do głównego okna
    MainWindow *mainWindow = qobject_cast<MainWindow *>(parent());
    if (mainWindow) {

        mainWindow->setupUI();
        mainWindow->show(); // Pokazujemy główne okno
        this->close(); // Zamykamy okno z instrukcjami
    }
}
