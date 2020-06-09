#include "computerbay.h"

ComputerBay::ComputerBay(QWidget* parent) : QWidget(parent)
{
    grid = new QGridLayout(this);
    grid->setSpacing(1);

    linkors = 1;
    cruisers = 2;
    destroyers = 3;
    boats = 4;

    placeShips();

    QLabel* row, * column;
    for(int i = 0; i < 10; ++i)
    {
        row = new QLabel("", this);
        column = new QLabel("", this);
        row->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        column->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        row->setFont(QFont("Times New Roman", 10));
        column->setFont(QFont("Times New Roman", 10));
        row->setNum(i+1);
        column->setText(QString('A'+i));
        grid->addWidget(row, i+1, 0);
        grid->addWidget(column, 0, i+1);
        for(int j = 0; j < 10; ++j)
        {
            cells[i][j] = new Cell(i, j, this);

            grid->addWidget(cells[i][j], i+1, j+1);

            connect(cells[i][j], &Cell::buttonClicked,
                    this, &ComputerBay::onButtonClicked);
        }
    }

    QLabel* lbl1 = new QLabel("Left:", this);
    lbl1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    lbl1->setFont(QFont("Times New Roman", 16));

    QLabel* sh1 = new QLabel("Linkors - ", this);
    sh1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sh1->setFont(QFont("Times New Roman", 16));

    QLabel* sh2 = new QLabel("Cruisers - ", this);
    sh2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sh2->setFont(QFont("Times New Roman", 16));

    QLabel* sh3 = new QLabel("Destroyers - ", this);
    sh3->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sh3->setFont(QFont("Times New Roman", 16));

    QLabel* sh4 = new QLabel("Boats - ", this);
    sh4->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    sh4->setFont(QFont("Times New Roman", 16));

    lin = new QLabel(QString::number(linkors), this);
    lin->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    lin->setFont(QFont("Times New Roman", 16));

    cr = new QLabel(QString::number(cruisers), this);
    cr->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    cr->setFont(QFont("Times New Roman", 16));

    des = new QLabel(QString::number(destroyers), this);
    des->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    des->setFont(QFont("Times New Roman", 16));

    boa = new QLabel(QString::number(boats), this);
    boa->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    boa->setFont(QFont("Times New Roman", 16));

    grid->addWidget(lbl1, 1, 11, 2, 2);
    grid->addWidget(sh1, 3, 11, 2, 1);
    grid->addWidget(sh2, 5, 11, 2, 1);
    grid->addWidget(sh3, 7, 11, 2, 1);
    grid->addWidget(sh4, 9, 11, 2, 1);
    grid->addWidget(lin, 3, 12, 2, 1);
    grid->addWidget(cr, 5, 12, 2, 1);
    grid->addWidget(des, 7, 12, 2, 1);
    grid->addWidget(boa, 9, 12, 2, 1);

    setLayout(grid);
}

void ComputerBay::onButtonClicked(int x, int y)
{
    if(square[x][y])  //ship
    {
        cells[x][y]->setText("X");
        cells[x][y]->setFont(QFont("Times New Roman", 16));
        cells[x][y]->setEnabled(0);
        guessed.insert({x, y});
        bool xflag = false, yflag = false;
        if(x != 0) xflag = xflag || square[x-1][y];
        if(x != 9) xflag = xflag || square[x+1][y];
        if(y != 0) yflag = yflag || square[x][y-1];
        if(y != 9) yflag = yflag || square[x][y+1];
        if(xflag)   //vertical
        {
            int len = 1, x1 = x, x2 = x;
            bool flag = true;
            while(square[x1-1][y] && x1 > 0)
            {
                ++len;
                --x1;
                if(guessed.count({x1, y}) == 0) flag = false;
            }
            while(square[x2+1][y] && x2 < 9)
            {
                ++len;
                ++x2;
                if(guessed.count({x2, y}) == 0) flag = false;
            }
            if(flag)
            {
                if(len == 2)
                {
                    --destroyers;
                    des->setNum(destroyers);
                }
                if(len == 3)
                {
                    --cruisers;
                    cr->setNum(cruisers);
                }
                if(len == 4)
                {
                    --linkors;
                    lin->setNum(linkors);
                }
                for(int i = -1; i < len+1; ++i)
                    for(int j = -1; j < 2; ++j)
                        if(j != 0 || i == -1 || i == len)
                        {
                            if(x1+i > -1 && x1+i < 10 && y+j > -1
                                    && y+j < 10)
                            {
                                cells[x1+i][y+j]->setText(".");
                                cells[x1+i][y+j]->setFont(QFont
                                     ("Times New Roman", 16));
                                cells[x1+i][y+j]->setEnabled(0);
                            }
                        }
            }
        }
        else if(yflag)   //horisontal
        {
            int len = 1, y1 = y, y2 = y;
            bool flag = true;
            while(square[x][y1-1] && y1 > 0)
            {
                ++len;
                --y1;
                if(guessed.count({x, y1}) == 0) flag = false;
            }
            while(square[x][y2+1] && y2 < 9)
            {
                ++len;
                ++y2;
                if(guessed.count({x, y2}) == 0) flag = false;
            }
            if(flag)
            {
                if(len == 2)
                {
                    --destroyers;
                    des->setNum(destroyers);
                }
                if(len == 3)
                {
                    --cruisers;
                    cr->setNum(cruisers);
                }
                if(len == 4)
                {
                    --linkors;
                    lin->setNum(linkors);
                }
                for(int i = -1; i < 2; ++i)
                    for(int j = -1; j < len+1; ++j)
                        if(i != 0 || j == -1 || j == len)
                        {
                            if(x+i > -1 && x+i < 10 && y1+j > -1
                                    && y1+j < 10)
                            {
                                cells[x+i][y1+j]->setText(".");
                                cells[x+i][y1+j]->setFont(QFont
                                     ("Times New Roman", 16));
                                cells[x+i][y1+j]->setEnabled(0);
                            }
                        }
            }
        }
        else   //boat
        {
            --boats;
            boa->setNum(boats);
            for(int i = -1; i < 2; ++i)
                for(int j = -1; j < 2; ++j)
                    if(i != 0 || j != 0)
                    {
                        if(x+i > -1 && x+i < 10 && y+j > -1 && y+j < 10)
                        {
                            cells[x+i][y+j]->setText(".");
                            cells[x+i][y+j]->setFont(QFont
                                 ("Times New Roman", 16));
                            cells[x+i][y+j]->setEnabled(0);
                        }
                    }
        }
        if(linkors == 0 && cruisers == 0 && destroyers == 0
                && boats == 0) userWin(QString("You win!!!"));
        else usersTurn();
    }
    else  //empty place
    {
        cells[x][y]->setText(".");
        cells[x][y]->setFont(QFont("Times New Roman", 16));
        cells[x][y]->setEnabled(0);
        setUnenable();
        computersTurn();
    }
}

void ComputerBay::setUnenable()
{
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            cells[i][j]->setEnabled(0);
}

void ComputerBay::setEnable()
{
    for(int i = 0; i < 10; ++i)
        for(int j = 0; j < 10; ++j)
            if(cells[i][j]->text() != "X"
                    && cells[i][j]->text() != ".")
                cells[i][j]->setEnabled(1);
}

void ComputerBay::placeShips()
{
    std::set<std::pair<int, int>> active;
    for(int i = 0; i < 10; ++i)
    {
        for(int j = 0; j < 10; ++j)
        {
            active.insert({i, j});
            square[i][j] = 0;
        }
    }
    srand(time(0));
    int l = 4, k = 0;
    while(l)
    {
        int z = rand()%active.size();
        auto p = active.begin();
        for(int i = 0; i < z; ++i) ++p;
        std::pair<int, int> start = *p;
        std::vector<std::string> directions;
        if(active.count({start.first - l + 1, start.second}))
            directions.push_back("up");
        if(active.count({start.first + l - 1, start.second}))
            directions.push_back("down");
        if(active.count({start.first, start.second - l + 1}))
            directions.push_back("left");
        if(active.count({start.first, start.second + l - 1}))
            directions.push_back("right");
        if(directions.size() != 0)
        {
            int d = rand()%directions.size();
            if(directions[d] == "up")
            {
                for(int i = -1; i < l + 1; ++i)
                    for(int j = -1; j < 2; ++j)
                    {
                        active.erase({start.first - i,
                                     start.second - j});
                        if(j == 0 && i > -1 && i < l)
                            square[start.first - i][start.second] = 1;
                    }
            }
            if(directions[d] == "down")
            {
                for(int i = -1; i < l + 1; ++i)
                    for(int j = -1; j < 2; ++j)
                    {
                        active.erase({start.first + i,
                                     start.second + j});
                        if(j == 0 && i > -1 && i < l)
                            square[start.first + i][start.second] = 1;
                    }
            }
            if(directions[d] == "left")
            {
                for(int i = -1; i < l + 1; ++i)
                    for(int j = -1; j < 2; ++j)
                    {
                        active.erase({start.first - j,
                                     start.second - i});
                        if(j == 0 && i > -1 && i < l)
                            square[start.first][start.second - i] = 1;
                    }
            }
            if(directions[d] == "right")
            {
                for(int i = -1; i < l + 1; ++i)
                    for(int j = -1; j < 2; ++j)
                    {
                        active.erase({start.first + j,
                                     start.second + i});
                        if(j == 0 && i > -1 && i < l)
                            square[start.first][start.second + i] = 1;
                    }
            }

            ++k;
            if(k == 10 || k == 6 || k == 3 || k == 1) --l;
        }
    }
}
