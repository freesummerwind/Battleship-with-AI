#include <QGridLayout>
#include <thread>
#include <chrono>
#include "userbay.h"

UserBay::UserBay(bool** sq, QWidget *parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout(this);
    grid->setSpacing(1);

    linkors = 1;
    cruisers = 2;
    destroyers = 3;
    boats = 4;

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
        grid->addWidget(row, i+1, 2);
        grid->addWidget(column, 0, i+3);
        for(int j = 0; j < 10; ++j)
        {
            square[i][j] = sq[i][j];

            cells[i][j] = new Cell(i, j, this);
            cells[i][j]->setFont(QFont("Times New Roman", 16));

            if(square[i][j])
            {
                //cells[i][j]->setText("X");
                cells[i][j]->setText("[  ]");
            }

            active.insert({i, j});

            grid->addWidget(cells[i][j], i+1, j+3);
        }
    }

    QLabel* lbl1 = new QLabel("Left:", this);
    lbl1->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    lbl1->setFont(QFont("Times New Roman", 16));

    QLabel* sh1 = new QLabel(" - Linkors", this);
    sh1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    sh1->setFont(QFont("Times New Roman", 16));

    QLabel* sh2 = new QLabel(" - Cruisers", this);
    sh2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    sh2->setFont(QFont("Times New Roman", 16));

    QLabel* sh3 = new QLabel(" - Destroyers", this);
    sh3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    sh3->setFont(QFont("Times New Roman", 16));

    QLabel* sh4 = new QLabel(" - Boats", this);
    sh4->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
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

    grid->addWidget(lbl1, 1, 0, 2, 2);
    grid->addWidget(sh1, 3, 1, 2, 1);
    grid->addWidget(sh2, 5, 1, 2, 1);
    grid->addWidget(sh3, 7, 1, 2, 1);
    grid->addWidget(sh4, 9, 1, 2, 1);
    grid->addWidget(lin, 3, 0, 2, 1);
    grid->addWidget(cr, 5, 0, 2, 1);
    grid->addWidget(des, 7, 0, 2, 1);
    grid->addWidget(boa, 9, 0, 2, 1);

    setLayout(grid);
}

void UserBay::shot()
{
    srand(time(NULL));
    if(type == shotType::GUESS)
    {
        ship.clear();
        up = true;
        down = true;

        int k = rand()%active.size();
        auto iter = active.begin();
        for(int i = 0; i < k; ++i) ++iter;
        cells[iter->first][iter->second]->setEnabled(0);
        if(square[iter->first][iter->second])
        {
            type = shotType::DIRECTION;
            cells[iter->first][iter->second]->setText("X");
            ship.insert(*iter);
            active.erase(iter);
            computersTurn();
        }
        else
        {
            cells[iter->first][iter->second]->setText(".");
            active.erase(iter);
            usersTurn();
        }
    }
    else if(type == shotType::DIRECTION)
    {
        bool notABoat = false;
        std::pair<int, int> start = *ship.begin();
        if(start.first > 0)
            notABoat = notABoat || square[start.first-1][start.second];
        if(start.first < 9)
            notABoat = notABoat || square[start.first+1][start.second];
        if(start.second > 0)
            notABoat = notABoat || square[start.first][start.second-1];
        if(start.second < 9)
            notABoat = notABoat || square[start.first][start.second+1];
        if(!notABoat)
        {
            if(start.first > 0)
            {
                cells[start.first-1][start.second]->setEnabled(0);
                cells[start.first-1][start.second]->setText(".");
                active.erase({ start.first-1, start.second });
                if(start.second > 0)
                {
                    cells[start.first-1][start.second-1]->setEnabled(0);
                    cells[start.first-1][start.second-1]->setText(".");
                    active.erase({ start.first-1, start.second-1 });
                }
                if(start.second < 9)
                {
                    cells[start.first-1][start.second+1]->setEnabled(0);
                    cells[start.first-1][start.second+1]->setText(".");
                    active.erase({ start.first-1, start.second+1 });
                }
            }
            if(start.first < 9)
            {
                cells[start.first+1][start.second]->setEnabled(0);
                cells[start.first+1][start.second]->setText(".");
                active.erase({ start.first+1, start.second });
                if(start.second > 0)
                {
                    cells[start.first+1][start.second-1]->setEnabled(0);
                    cells[start.first+1][start.second-1]->setText(".");
                    active.erase({ start.first+1, start.second-1 });
                }
                if(start.second < 9)
                {
                    cells[start.first+1][start.second+1]->setEnabled(0);
                    cells[start.first+1][start.second+1]->setText(".");
                    active.erase({ start.first+1, start.second+1 });
                }
            }
            if(start.second > 0)
            {
                cells[start.first][start.second-1]->setEnabled(0);
                cells[start.first][start.second-1]->setText(".");
                active.erase({ start.first, start.second-1 });
            }
            if(start.second < 9)
            {
                cells[start.first][start.second+1]->setEnabled(0);
                cells[start.first][start.second+1]->setText(".");
                active.erase({ start.first, start.second+1 });
            }

            --boats;
            boa->setNum(boats);
            type = shotType::GUESS;
            if(linkors == 0 && cruisers == 0 && destroyers == 0
                    && boats == 0)
                computerWin(QString("Computer win!!!"));
            else computersTurn();
        }
        else
        {
            int n = 0;
            std::vector<std::string> s;
            if(start.first > 0)
                if(active.count({ start.first-1, start.second }))
                {
                    ++n;
                    s.push_back("up");
                }
            if(start.first < 9)
                if(active.count({ start.first+1, start.second }))
                {
                    ++n;
                    s.push_back("down");
                }
            if(start.second > 0)
                if(active.count({ start.first, start.second-1 }))
                {
                    ++n;
                    s.push_back("left");
                }
            if(start.second < 9)
                if(active.count({ start.first, start.second+1 }))
                {
                    ++n;
                    s.push_back("right");
                }
            int k = rand()%n;
            if(s[k] == "up")
            {
                cells[start.first-1][start.second]->setEnabled(0);
                active.erase({ start.first-1, start.second });
                if(square[start.first-1][start.second])
                {
                    type = shotType::KILL;
                    cells[start.first-1][start.second]->setText("X");
                    ship.insert({ start.first-1, start.second });
                    computersTurn();
                }
                else
                {
                    cells[start.first-1][start.second]->setText(".");
                    usersTurn();
                }
            }
            if(s[k] == "down")
            {
                cells[start.first+1][start.second]->setEnabled(0);
                active.erase({ start.first+1, start.second });
                if(square[start.first+1][start.second])
                {
                    type = shotType::KILL;
                    cells[start.first+1][start.second]->setText("X");
                    ship.insert({ start.first+1, start.second });
                    computersTurn();
                }
                else
                {
                    cells[start.first+1][start.second]->setText(".");
                    usersTurn();
                }
            }
            if(s[k] == "left")
            {
                cells[start.first][start.second-1]->setEnabled(0);
                active.erase({ start.first, start.second-1 });
                if(square[start.first][start.second-1])
                {
                    type = shotType::KILL;
                    cells[start.first][start.second-1]->setText("X");
                    ship.insert({ start.first, start.second-1 });
                    computersTurn();
                }
                else
                {
                    cells[start.first][start.second-1]->setText(".");
                    usersTurn();
                }
            }
            if(s[k] == "right")
            {
                cells[start.first][start.second+1]->setEnabled(0);
                active.erase({ start.first, start.second+1 });
                if(square[start.first][start.second+1])
                {
                    type = shotType::KILL;
                    cells[start.first][start.second+1]->setText("X");
                    ship.insert({ start.first, start.second+1 });
                    computersTurn();
                }
                else
                {
                    cells[start.first][start.second+1]->setText(".");
                    usersTurn();
                }
            }
        }
    }
    else
    {
        if(ship.begin()->first == (--ship.end())->first) // horisontal
        {
            if(!active.count({ship.begin()->first,
                            ship.begin()->second - 1})) up = false;
            if(!active.count({(--ship.end())->first,
                            (--ship.end())->second + 1})) down = false;
            if(up == false && down != false)
            {
                std::pair<int, int> r = *(--ship.end());
                r.second += 1;
                if(!square[r.first][r.second]) down = false;
            }
            if(up != false && down == false)
            {
                std::pair<int, int> r = *ship.begin();
                r.second -= 1;
                if(!square[r.first][r.second]) up = false;
            }
            if(up && down)
            {
                int k = rand()%2;
                if(k)
                {
                    cells[(--ship.end())->first]
                            [(--ship.end())->second+1]->setEnabled(0);
                    active.erase({ (--ship.end())->first,
                                   (--ship.end())->second+1 });
                    if(square[(--ship.end())->first]
                            [(--ship.end())->second+1])
                    {
                        cells[(--ship.end())->first]
                                [(--ship.end())->second+1]->setText("X");
                        ship.insert({ (--ship.end())->first,
                                      (--ship.end())->second+1 });
                        computersTurn();
                    }
                    else
                    {
                        cells[(--ship.end())->first]
                                [(--ship.end())->second+1]->setText(".");
                        down = false;
                        usersTurn();
                    }
                }
                else
                {
                    cells[ship.begin()->first]
                            [ship.begin()->second-1]->setEnabled(0);
                    active.erase({ ship.begin()->first,
                                   ship.begin()->second-1 });
                    if(square[ship.begin()->first]
                            [ship.begin()->second-1])
                    {
                        cells[ship.begin()->first]
                                [ship.begin()->second-1]->setText("X");
                        ship.insert({ ship.begin()->first,
                                      ship.begin()->second-1 });
                        computersTurn();
                    }
                    else
                    {
                        cells[ship.begin()->first]
                                [ship.begin()->second-1]->setText(".");
                        up = false;
                        usersTurn();
                    }
                }
            }
            else if(up)
            {
                cells[ship.begin()->first]
                        [ship.begin()->second-1]->setEnabled(0);
                active.erase({ ship.begin()->first,
                               ship.begin()->second-1 });
                if(square[ship.begin()->first]
                        [ship.begin()->second-1])
                {
                    cells[ship.begin()->first]
                            [ship.begin()->second-1]->setText("X");
                    ship.insert({ ship.begin()->first,
                                  ship.begin()->second-1 });
                    computersTurn();
                }
                else
                {
                    cells[ship.begin()->first]
                            [ship.begin()->second-1]->setText(".");
                    up = false;
                    usersTurn();
                }
            }
            else if(down)
            {
                cells[(--ship.end())->first]
                        [(--ship.end())->second+1]->setEnabled(0);
                active.erase({ (--ship.end())->first,
                               (--ship.end())->second+1 });
                if(square[(--ship.end())->first]
                        [(--ship.end())->second+1])
                {
                    cells[(--ship.end())->first]
                            [(--ship.end())->second+1]->setText("X");
                    ship.insert({ (--ship.end())->first,
                                  (--ship.end())->second+1 });
                    computersTurn();
                }
                else
                {
                    cells[(--ship.end())->first]
                            [(--ship.end())->second+1]->setText(".");
                    down = false;
                    usersTurn();
                }
            }
            else
            {
               int len = (--ship.end())->second
                       - ship.begin()->second + 1;
               int h = ship.begin()->first, v = ship.begin()->second;
               if(v > 0)
               {
                   if(h > 0)
                   {
                       cells[h - 1][v - 1]->setEnabled(0);
                       cells[h - 1][v - 1]->setText(".");
                       active.erase({ h - 1, v - 1 });
                   }
                   cells[h][v - 1]->setEnabled(0);
                   cells[h][v - 1]->setText(".");
                   active.erase({ h, v - 1 });
                   if(h < 9)
                   {
                       cells[h + 1][v - 1]->setEnabled(0);
                       cells[h + 1][v - 1]->setText(".");
                       active.erase({ h + 1, v - 1 });
                   }
               }
               if(v + len <= 9)
               {
                   if(h > 0)
                   {
                       cells[h - 1][v + len]->setEnabled(0);
                       cells[h - 1][v + len]->setText(".");
                       active.erase({ h - 1, v + len });
                   }
                   cells[h][v + len]->setEnabled(0);
                   cells[h][v + len]->setText(".");
                   active.erase({ h, v + len });
                   if(h < 9)
                   {
                       cells[h + 1][v + len]->setEnabled(0);
                       cells[h + 1][v + len]->setText(".");
                       active.erase({ h + 1, v + len });
                   }
               }
               for(int i = 0; i < len; ++i)
               {
                   if(h - 1 >= 0)
                   {
                       cells[h - 1][v + i]->setEnabled(0);
                       cells[h - 1][v + i]->setText(".");
                       active.erase({ h - 1, v + i });
                   }
                   cells[h][v + i]->setEnabled(0);
                   cells[h][v + i]->setText("X");
                   active.erase({ h, v + i });
                   if(h + 1 <= 9)
                   {
                       cells[h + 1][v + i]->setEnabled(0);
                       cells[h + 1][v + i]->setText(".");
                       active.erase({ h + 1, v + i });
                   }
               }

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
               type = shotType::GUESS;
               if(linkors == 0 && cruisers == 0 && destroyers == 0
                       && boats == 0)
                   computerWin(QString("Computer win!!!"));
               else computersTurn();
            }
        }
        else         //vertical
        {
            if(!active.count({ship.begin()->first - 1,
                            ship.begin()->second})) up = false;
            if(!active.count({(--ship.end())->first + 1,
                            (--ship.end())->second})) down = false;
            if(up == false && down != false)
            {
                std::pair<int, int> r = *(--ship.end());
                r.first += 1;
                if(!square[r.first][r.second]) down = false;
            }
            if(up != false && down == false)
            {
                std::pair<int, int> r = *ship.begin();
                r.first -= 1;
                if(!square[r.first][r.second]) up = false;
            }
            if(up && down)
            {
                int k = rand()%2;
                if(k)
                {
                    cells[(--ship.end())->first+1]
                            [(--ship.end())->second]->setEnabled(0);
                    active.erase({ (--ship.end())->first+1,
                                   (--ship.end())->second });
                    if(square[(--ship.end())->first+1]
                            [(--ship.end())->second])
                    {
                        cells[(--ship.end())->first+1]
                                [(--ship.end())->second]->setText("X");
                        ship.insert({ (--ship.end())->first+1,
                                      (--ship.end())->second });
                        computersTurn();
                    }
                    else
                    {
                        cells[(--ship.end())->first+1]
                                [(--ship.end())->second]->setText(".");
                        down = false;
                        usersTurn();
                    }
                }
                else
                {
                    cells[ship.begin()->first-1]
                            [ship.begin()->second]->setEnabled(0);
                    active.erase({ ship.begin()->first-1,
                                   ship.begin()->second });
                    if(square[ship.begin()->first-1]
                            [ship.begin()->second])
                    {
                        cells[ship.begin()->first-1]
                                [ship.begin()->second]->setText("X");
                        ship.insert({ ship.begin()->first-1,
                                      ship.begin()->second });
                        computersTurn();
                    }
                    else
                    {
                        cells[ship.begin()->first-1]
                                [ship.begin()->second]->setText(".");
                        up = false;
                        usersTurn();
                    }
                }
            }
            else if(up)
            {
                cells[ship.begin()->first-1]
                        [ship.begin()->second]->setEnabled(0);
                active.erase({ ship.begin()->first-1,
                               ship.begin()->second });
                if(square[ship.begin()->first-1]
                        [ship.begin()->second])
                {
                    cells[ship.begin()->first-1]
                            [ship.begin()->second]->setText("X");
                    ship.insert({ ship.begin()->first-1,
                                  ship.begin()->second });
                    computersTurn();
                }
                else
                {
                    cells[ship.begin()->first-1]
                            [ship.begin()->second]->setText(".");
                    up = false;
                    usersTurn();
                }
            }
            else if(down)
            {
                cells[(--ship.end())->first+1]
                        [(--ship.end())->second]->setEnabled(0);
                active.erase({ (--ship.end())->first+1,
                               (--ship.end())->second });
                if(square[(--ship.end())->first+1]
                        [(--ship.end())->second])
                {
                    cells[(--ship.end())->first+1]
                            [(--ship.end())->second]->setText("X");
                    ship.insert({ (--ship.end())->first+1,
                                  (--ship.end())->second });
                    computersTurn();
                }
                else
                {
                    cells[(--ship.end())->first+1]
                            [(--ship.end())->second]->setText(".");
                    down = false;
                    usersTurn();
                }
            }
            else
            {
                int len = (--ship.end())->first
                        - ship.begin()->first + 1;
                int h = ship.begin()->first, v = ship.begin()->second;
                if(h > 0)
                {
                    if(v > 0)
                    {
                        cells[h - 1][v - 1]->setEnabled(0);
                        cells[h - 1][v - 1]->setText(".");
                        active.erase({ h - 1, v - 1 });
                    }
                    cells[h - 1][v]->setEnabled(0);
                    cells[h - 1][v]->setText(".");
                    active.erase({ h - 1, v });
                    if(v < 9)
                    {
                        cells[h - 1][v + 1]->setEnabled(0);
                        cells[h - 1][v + 1]->setText(".");
                        active.erase({ h - 1, v + 1 });
                    }
                }
                if(h + len <= 9)
                {
                    if(v > 0)
                    {
                        cells[h + len][v - 1]->setEnabled(0);
                        cells[h + len][v - 1]->setText(".");
                        active.erase({ h + len, v - 1 });
                    }
                    cells[h + len][v]->setEnabled(0);
                    cells[h + len][v]->setText(".");
                    active.erase({ h + len, v });
                    if(v < 9)
                    {
                        cells[h + len][v + 1]->setEnabled(0);
                        cells[h + len][v + 1]->setText(".");
                        active.erase({ h + len, v + 1 });
                    }
                }
                for(int j = 0; j < len; ++j)
                {
                    if(v - 1 >= 0)
                    {
                        cells[h + j][v - 1]->setEnabled(0);
                        cells[h + j][v - 1]->setText(".");
                        active.erase({ h + j, v - 1 });
                    }
                    cells[h + j][v]->setEnabled(0);
                    cells[h + j][v]->setText("X");
                    active.erase({ h + j, v });
                    if(v + 1 <= 9)
                    {
                        cells[h + j][v + 1]->setEnabled(0);
                        cells[h + j][v + 1]->setText(".");
                        active.erase({ h + j, v + 1 });
                    }
                }

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
                type = shotType::GUESS;
                if(linkors == 0 && cruisers == 0 && destroyers == 0
                        && boats == 0) computerWin(QString("Computer win!!!"));
                else computersTurn();
            }
        }
    }
}
