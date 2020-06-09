#pragma once

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <set>
#include "cell.h"

class ComputerBay : public QWidget
{
    Q_OBJECT

public:
    explicit ComputerBay(QWidget* parent = 0);

public slots:
    void setUnenable();
    void setEnable();

signals:
    void computersTurn();
    void usersTurn();
    void userWin(QString);

private slots:
    void onButtonClicked(int x, int y);

private:
    QGridLayout* grid;
    bool square[10][10];
    std::set<std::pair<int, int>> guessed;
    Cell* cells[10][10];
    int linkors, cruisers, destroyers, boats;
    QLabel* lin, * cr, * des, * boa;
    void placeShips();
};
