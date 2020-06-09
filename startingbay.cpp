#include <QGridLayout>
#include <QLabel>
#include "startingbay.h"

StartingBay::StartingBay(QWidget *parent) : QWidget(parent)
{
    square = new bool*[10];

    QGridLayout* bay = new QGridLayout();
    bay->setSpacing(1);

    QLabel* row, * column;
    for(int i = 0; i < 10; ++i)
    {
        square[i] = new bool[10];
        row = new QLabel("", this);
        column = new QLabel("", this);
        row->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        column->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        row->setFont(QFont("Times New Roman", 10));
        column->setFont(QFont("Times New Roman", 10));
        row->setNum(i+1);
        column->setText(QString('A'+i));
        bay->addWidget(row, i+1, 0);
        bay->addWidget(column, 0, i+1);
        for(int j = 0; j < 10; ++j)
        {
            cells[i][j] = new Cell(i, j, this);
            cells[i][j]->setEnabled(0);
            cells[i][j]->setFont(QFont("Times New Roman", 16));

            bay->addWidget(cells[i][j], i+1, j+1);

            square[i][j] = 0;

            connect(cells[i][j], &Cell::buttonClicked,
                    this, &StartingBay::onButtonClicked);
        }
    }

    linkors = 1;
    cruisers = 2;
    destroyers = 3;
    boats = 4;

    ships = new QComboBox();
    ships->setFixedSize(350, 90);
    ships->setFont(QFont("Times New Roman", 16));
    ships->addItem("Linkor (4 cells)");
    ships->addItem("Cruiser (3 cells)");
    ships->addItem("Destroyer (2 cells)");
    ships->addItem("Boat (1 cell)");

    add = new QPushButton("Add ship", this);
    add->setFixedSize(150, 90);
    add->setFont(QFont("Times New Roman", 12));
    remove = new QPushButton("Remove ship", this);
    remove->setFixedSize(150, 90);
    remove->setFont(QFont("Times New Roman", 12));
    cancel = new QPushButton("Cancel", this);
    cancel->setFixedSize(150, 90);
    cancel->setFont(QFont("Times New Roman", 12));
    start = new QPushButton("Start battle", this);
    start->setFixedSize(150, 90);
    start->setFont(QFont("Times New Roman", 12));

    remove->setEnabled(0);
    cancel->setEnabled(0);
    start->setEnabled(0);

    connect(add, &QPushButton::clicked,
            this, &StartingBay::addShip);
    connect(remove, &QPushButton::clicked,
            this, &StartingBay::removeShip);
    connect(cancel, &QPushButton::clicked,
            this, &StartingBay::cancelAction);
    connect(start, &QPushButton::clicked,
            this, &StartingBay::startBattle);

    QGridLayout* grid = new QGridLayout(this);
    grid->setHorizontalSpacing(50);
    grid->addLayout(bay, 0, 0, 3, 1);
    grid->addWidget(ships, 0, 1, 1, 2);
    grid->addWidget(add, 1, 1, 1, 1);
    grid->addWidget(remove, 1, 2, 1, 1);
    grid->addWidget(cancel, 2, 1, 1, 1);
    grid->addWidget(start, 2, 2, 1, 1);

    setLayout(grid);
}

void StartingBay::setDefault()
{
    if(linkors != 0 || cruisers != 0 ||
            destroyers != 0 || boats != 0)
    {
        add->setEnabled(1);
        start->setEnabled(0);
    }
    else
    {
        start->setEnabled(1);
        add->setEnabled(0);
    }

    if(linkors != 1 || cruisers != 2 ||
            destroyers != 3 || boats != 4)
        remove->setEnabled(1);
    else remove->setEnabled(0);

    cancel->setEnabled(0);
    ships->setEnabled(1);

    inactive.clear();

    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
        {
            cells[i][j]->setEnabled(0);
            if(cells[i][j]->text() == "." ||
                    cells[i][j]->text() == " ")
                cells[i][j]->setText("");
            if(square[i][j])
            {
                inactive.insert({i-1, j-1});
                inactive.insert({i-1, j});
                inactive.insert({i-1, j+1});
                inactive.insert({i, j-1});
                inactive.insert({i, j});
                inactive.insert({i, j+1});
                inactive.insert({i+1, j-1});
                inactive.insert({i+1, j});
                inactive.insert({i+1, j+1});
            }
        }
}

void StartingBay::onButtonClicked(int x, int y)
{
    if(cells[x][y]->text() == "X")
    {
        bool xflag = 0, yflag = 0;
        if(x != 0 && x != 9) xflag = cells[x-1][y]->text() == "X"
                || cells[x+1][y]->text() == "X";
        else if(x == 0) xflag = cells[x+1][y]->text() == "X";
        else if(x == 9) xflag = cells[x-1][y]->text() == "X";
        if(y != 0 && y != 9) yflag = cells[x][y-1]->text() == "X"
                || cells[x][y+1]->text() == "X";
        else if(y == 0) yflag = cells[x][y+1]->text() == "X";
        else if(y == 9) yflag = cells[x][y-1]->text() == "X";
        if(xflag)
        {
            int x1 = x, x2 = x, len = 1;
            if(x != 0) while(cells[x1-1][y]->text() == "X")
            {
                --x1;
                ++len;
                if(x1 == 0) break;
            }
            if (x != 9) while(cells[x2+1][y]->text() == "X")
            {
                ++x2;
                ++len;
                if(x2 == 9) break;
            }
            for(int i = 0; i < len; ++i)
            {
                cells[x1+i][y]->setText("");
                square[x1+i][y] = 0;
            }
            if(len == 2)
            {
                ++destroyers;
                if(destroyers == 1) ships->addItem("Destroyer (2 cells)");
            }
            else if(len == 3)
            {
                ++cruisers;
                if(cruisers == 1) ships->addItem("Cruiser (3 cells)");
            }
            else if(len == 4)
            {
                ++linkors;
                if(linkors == 1) ships->addItem("Linkor (4 cells)");
            }
        }
        else if(yflag)
        {
            int y1 = y, y2 = y, len = 1;
            if(y != 0) while(cells[x][y1-1]->text() == "X")
            {
                --y1;
                ++len;
                if(y1 == 0) break;
            }
            if(y != 9) while(cells[x][y2+1]->text() == "X")
            {
                ++y2;
                ++len;
                if(y2 == 9) break;
            }
            for(int j = 0; j < len; ++j)
            {
                cells[x][y1+j]->setText("");
                square[x][y1+j] = 0;
            }
            if(len == 2)
            {
                ++destroyers;
                if(destroyers == 1) ships->addItem("Destroyer (2 cells)");
            }
            else if(len == 3)
            {
                ++cruisers;
                if(cruisers == 1) ships->addItem("Cruiser (3 cells)");
            }
            else if(len == 4)
            {
                ++linkors;
                if(linkors == 1) ships->addItem("Linkor (4 cells)");
            }
        }
        else
        {
            cells[x][y]->setText("");
            square[x][y] = 0;
            ++boats;
            if(boats == 1) ships->addItem("Boat (1 cell)");
        }
        setDefault();
    }
    else if(cells[x][y]->text() == " ")
    {
        int x1, y1;
        for(int i = 0; i < 10; ++i)
        {
            bool flag = 0;
            for(int j = 0; j < 10; ++j)
            {
                if(cells[i][j]->text() == ".")
                {
                    x1 = i;
                    y1 = j;
                    flag = 1;
                    break;
                }
            }
            if(flag) break;
        }

        if(x != x1)
        {
            int x_min = std::min(x, x1), len = std::abs(x - x1) + 1;
            for(int i = 0; i < len; ++i)
            {
                cells[x_min + i][y]->setText("X");
                square[x_min + i][y] = 1;
            }

            if(len == 2)
            {
                --destroyers;
                if(destroyers == 0)
                    ships->removeItem(ships->findText
                                      ("Destroyer (2 cells)"));
            }
            else if(len == 3)
            {
                --cruisers;
                if(cruisers == 0)
                    ships->removeItem(ships->findText
                                      ("Cruiser (3 cells)"));
            }
            else if(len == 4)
            {
                --linkors;
                if(linkors == 0)
                    ships->removeItem(ships->findText
                                      ("Linkor (4 cells)"));
            }
        }
        else if(y != y1)
        {
            int y_min = std::min(y, y1), len = std::abs(y - y1) + 1;
            for(int j = 0; j < len; ++j)
            {
                cells[x][y_min + j]->setText("X");
                square[x][y_min + j] = 1;
            }

            if(len == 2)
            {
                --destroyers;
                if(destroyers == 0)
                    ships->removeItem(ships->findText
                                      ("Destroyer (2 cells)"));
            }
            else if(len == 3)
            {
                --cruisers;
                if(cruisers == 0)
                    ships->removeItem(ships->findText
                                      ("Cruiser (3 cells)"));
            }
            else if(len == 4)
            {
                --linkors;
                if(linkors == 0)
                    ships->removeItem(ships->findText
                                      ("Linkor (4 cells)"));
            }
        }

        setDefault();
    }
    else
    {
        if(ships->currentText() == "Boat (1 cell)")
        {
            cells[x][y]->setText("X");
            square[x][y] = 1;
            --boats;
            if(boats == 0)
                ships->removeItem(ships->findText("Boat (1 cell)"));

            setDefault();
        }
        else if(ships->currentText() == "Destroyer (2 cells)")
        {
            cells[x][y]->setText(".");
            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < 10; ++j)
                {
                    if((i == x-1 && j == y) || (i == x && j == y-1) ||
                            (i == x+1 && j == y) || (i == x && j == y+1))
                    {
                        if(cells[i][j]->isEnabled())
                            cells[i][j]->setText(" ");
                    }
                    else
                    {
                        cells[i][j]->setEnabled(0);
                    }
                }
            }
        }
        else if(ships->currentText() == "Cruiser (3 cells)")
        {
            cells[x][y]->setText(".");
            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < 10; ++j)
                {
                    if((i == x-2 && j == y) || (i == x && j == y-2) ||
                            (i == x+2 && j == y) || (i == x && j == y+2))
                    {
                        if(cells[i][j]->isEnabled())
                            cells[i][j]->setText(" ");
                    }
                    else
                    {
                        cells[i][j]->setEnabled(0);
                    }
                }
            }
        }
        else if(ships->currentText() == "Linkor (4 cells)")
        {
            cells[x][y]->setText(".");
            for(int i = 0; i < 10; ++i)
            {
                for(int j = 0; j < 10; ++j)
                {
                    if((i == x-3 && j == y) || (i == x && j == y-3) ||
                            (i == x+3 && j == y) || (i == x && j == y+3))
                    {
                        if(cells[i][j]->isEnabled())
                            cells[i][j]->setText(" ");
                    }
                    else
                    {
                        cells[i][j]->setEnabled(0);
                    }
                }
            }
        }
    }
}

void StartingBay::addShip()
{
    add->setEnabled(0);
    remove->setEnabled(0);
    cancel->setEnabled(1);
    ships->setEnabled(0);
    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            if(inactive.count({i, j}) == 0)
                cells[i][j]->setEnabled(1);
        }
    }
}

void StartingBay::removeShip()
{
    add->setEnabled(0);
    remove->setEnabled(0);
    cancel->setEnabled(1);
    ships->setEnabled(0);
    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            if(cells[i][j]->text() == "X")
                cells[i][j]->setEnabled(1);
        }
    }
}

void StartingBay::cancelAction()
{
    setDefault();
}

void StartingBay::startBattle()
{
    emit ready();
}

bool** StartingBay::getSquare() const
{
    return square;
}
