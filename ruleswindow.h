#pragma once

#include <QDialog>
#include <QPushButton>

class RulesWindow : public QDialog
{
    Q_OBJECT
public:
    RulesWindow(QWidget* parent = 0);

private slots:
    void onOKClicked();

private:
    QPushButton* okbtn;
};
