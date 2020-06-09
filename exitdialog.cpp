#include <QLabel>
#include <QGridLayout>
#include "exitdialog.h"

ExitDialog::ExitDialog(QWidget* parent) : QDialog(parent)
{
    okbtn = new QPushButton("OK", this);
    cancelbtn = new QPushButton("Cancel", this);
    okbtn->setFont(QFont("Times New Roman", 10));
    cancelbtn->setFont(QFont("Times New Roman", 10));

    QLabel* label = new QLabel("Do you want to close battleship?", this);
    label->setFont(QFont("Times New Roman", 12));

    QGridLayout* grid = new QGridLayout();
    grid->addWidget(label, 0, 0, 1, 2);
    grid->addWidget(okbtn, 1, 0, 1, 1);
    grid->addWidget(cancelbtn, 1, 1, 1, 1);

    setWindowTitle("End");

    setLayout(grid);

    connect(okbtn, &QPushButton::clicked, this,
            &ExitDialog::onOKBtnClicked);
    connect(cancelbtn, &QPushButton::clicked, this,
            &ExitDialog::onCancelBtnClicked);
}


void ExitDialog::onOKBtnClicked()
{
    accept();
}

void ExitDialog::onCancelBtnClicked()
{
    reject();
}
