#include <QLabel>
#include <QGridLayout>
#include "ruleswindow.h"

RulesWindow::RulesWindow(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Rules");

    QLabel* rule = new QLabel(this);
    rule->setFont(QFont("Times New Roman", 14));
    rule->setText("There can be your advertising");

    okbtn = new QPushButton("OK", this);
    okbtn->setFont(QFont("Times New Roman", 10));

    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(10);

    grid->addWidget(rule, 0, 0, 1, 2);
    grid->addWidget(okbtn, 1, 1, 1, 1);

    connect(okbtn, &QPushButton::clicked,
            this, &RulesWindow::onOKClicked);
}

void RulesWindow::onOKClicked()
{
    accept();
}
