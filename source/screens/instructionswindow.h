#ifndef INSTRUCTIONSWINDOW_H
#define INSTRUCTIONSWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QAbstractAnimation>
#include <QVBoxLayout>

namespace Ui {
class InstructionsWindow;
}

class InstructionsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InstructionsWindow(QWidget *parent = nullptr);
    ~InstructionsWindow();
    void goBackToMainWindow();

private:
    Ui::InstructionsWindow *ui;
    void setupUI();
};

#endif // INSTRUCTIONSWINDOW_H
