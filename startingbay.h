#pragma once

#include <QWidget>
#include <QComboBox>
#include <set>
#include "cell.h"

class StartingBay : public QWidget
{
    Q_OBJECT

public:
    explicit StartingBay(QWidget *parent = nullptr);
    bool** getSquare() const;

signals:
    void ready();

private slots:
    void onButtonClicked(int x, int y);
    void addShip();
    void removeShip();
    void cancelAction();
    void startBattle();

private:
    bool** square;
    std::set<std::pair<int, int>> inactive;
    Cell* cells[10][10];
    QComboBox* ships;
    int linkors, cruisers, destroyers, boats;
    QPushButton* add, * remove, * cancel, * start;

    void setDefault();
};
