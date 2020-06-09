#pragma once

#include <QWidget>
#include <QLabel>
#include <set>
#include "cell.h"

enum class shotType {
    GUESS,
    DIRECTION,
    KILL,
};

class UserBay : public QWidget
{
    Q_OBJECT
public:
    explicit UserBay(bool** sq, QWidget *parent = nullptr);

signals:
    void computersTurn();
    void usersTurn();
    void computerWin(QString);

public slots:
    void shot();

private:
    shotType type = shotType::GUESS;
    std::set<std::pair<int, int>> ship;
    bool up;
    bool down;
    bool square[10][10];
    std::set<std::pair<int, int>> active;
    Cell* cells[10][10];
    int linkors, cruisers, destroyers, boats;
    QLabel* lin, * cr, * des, * boa;
};
