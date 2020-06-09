#include <QLabel>
#include <QGridLayout>
#include "resetwindow.h"

ResetWindow::ResetWindow(const QString& info, QWidget* parent)
    : QDialog(parent)
{
    resetbtn = new QPushButton("Reset the game", this);
    endbtn = new QPushButton("End the game", this);

    QLabel* label = new QLabel(info, this);

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(label, 0, 0, 1, 2);
    grid->addWidget(resetbtn, 1, 0, 1, 1);
    grid->addWidget(endbtn, 1, 1, 1, 1);

    setWindowTitle("Reset");

    setLayout(grid);

    connect(resetbtn, &QPushButton::clicked, this,
            &ResetWindow::onResetBtnClicked);
    connect(endbtn, &QPushButton::clicked, this,
            &ResetWindow::onEndBtnClicked);
}

void ResetWindow::onResetBtnClicked()
{
    accept();
}

void ResetWindow::onEndBtnClicked()
{
    reject();
}
