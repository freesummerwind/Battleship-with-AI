#include "cell.h"

Cell::Cell(int i, int j, QWidget* parent)
    : QPushButton(parent), x(i), y(j)
{
    this->setFixedSize(40, 40);
    connect(this, &QPushButton::clicked, this, &Cell::onButton);
}

void Cell::onButton()
{
    emit buttonClicked(x, y);
}
