#include <QApplication>
#include <QCloseEvent>
#include "mainwindow.h"
#include "resetwindow.h"
#include "ruleswindow.h"
#include "exitdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    frame = new QFrame(this);
    setCentralWidget(frame);

    startGame();
}

void MainWindow::startGame()
{
    delete frame;

    frame = new QFrame(this);
    setCentralWidget(frame);

    QPushButton* start = new QPushButton("Start Game", frame),
               * rules = new QPushButton("Rules", frame),
               * quit = new QPushButton("Quit", frame);

    start->setFixedSize(300, 100);
    rules->setFixedSize(300, 100);
    quit->setFixedSize(300, 100);
    start->setFont(QFont("Times New Roman", 16));
    rules->setFont(QFont("Times New Roman", 16));
    quit->setFont(QFont("Times New Roman", 16));

    grid = new QGridLayout(frame);
    grid->setVerticalSpacing(10);

    grid->addWidget(start, 0, 0);
    grid->addWidget(rules, 1, 0);
    grid->addWidget(quit, 2, 0);

    connect(start, &QPushButton::clicked,
            this, &MainWindow::placeShips);
    connect(rules, &QPushButton::clicked,
            this, &MainWindow::rules);
    connect(quit, &QPushButton::clicked,
            qApp, &QApplication::quit);
}

void MainWindow::placeShips()
{
    delete frame;

    frame = new QFrame(this);
    setCentralWidget(frame);

    user_start = new StartingBay(frame);

    lbl1 = new QLabel("Arrange your ships", frame);
    lbl1->setFont(QFont("Times New Roman", 16));
    lbl1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    grid = new QGridLayout(frame);
    grid->setHorizontalSpacing(50);
    grid->setVerticalSpacing(10);

    grid->addWidget(lbl1, 0, 0, 1, 1);
    grid->addWidget(user_start, 1, 0, 1, 1);

    connect(user_start, &StartingBay::ready, this, &MainWindow::game);
}

void MainWindow::game()
{
    user_game = new UserBay(user_start->getSquare(), frame);
    computer = new ComputerBay(frame);

    delete lbl1;
    delete user_start;

    lbl1 = new QLabel("Your bay", frame);
    lbl1->setFont(QFont("Times New Roman", 16));
    lbl1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    lbl2 = new QLabel("Opponent's bay", frame);
    lbl2->setFont(QFont("Times New Roman", 16));
    lbl2->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    grid->addWidget(lbl1, 0, 0, 1, 1);
    grid->addWidget(lbl2, 0, 1, 1, 1);
    grid->addWidget(user_game, 1, 0, 1, 1);
    grid->addWidget(computer, 1, 1, 1, 1);

    connect(computer, &ComputerBay::computersTurn,
            user_game, &UserBay::shot);
    connect(user_game, &UserBay::computersTurn,
            user_game, &UserBay::shot);
    connect(computer, &ComputerBay::usersTurn,
            computer, &ComputerBay::setEnable);
    connect(user_game, &UserBay::usersTurn,
            computer, &ComputerBay::setEnable);
    connect(computer, &ComputerBay::userWin,
            this, &MainWindow::reset);
    connect(user_game, &UserBay::computerWin,
            this, &MainWindow::reset);
}

void MainWindow::reset(QString info)
{
    info += " Do you want to play again?";
    ResetWindow* wind = new ResetWindow(info);
    int flag = wind->exec();

    if(flag == QDialog::Accepted)
    {
        placeShips();
    }
    if(flag == QDialog::Rejected)
    {
        startGame();
    }
}

void MainWindow::rules()
{
    RulesWindow* rules = new RulesWindow();
    rules->exec();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    ExitDialog* d = new ExitDialog();
    int flag = d->exec();

    if(flag == QDialog::Accepted)
    {
        event->accept();
    }
    if(flag == QDialog::Rejected)
    {
        event->ignore();
    }
}
