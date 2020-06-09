#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QFrame>
#include "userbay.h"
#include "computerbay.h"
#include "startingbay.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void startGame();
    void placeShips();
    void game();
    void reset(QString info);
    void rules();

private:
    QGridLayout* grid;
    QFrame* frame;
    QLabel* lbl1;
    QLabel* lbl2;
    StartingBay* user_start;
    ComputerBay* computer;
    UserBay* user_game;
};
