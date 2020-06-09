#pragma once

#include <QPushButton>

class Cell : public QPushButton
{
    Q_OBJECT

public:
    Cell(int i, int j, QWidget* parent = 0);

signals:
    void buttonClicked(int, int);

private slots:
    void onButton();

private:
    int x, y;
};
