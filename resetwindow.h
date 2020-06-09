#pragma once

#include <QDialog>
#include <QPushButton>

class ResetWindow : public QDialog
{
    Q_OBJECT
public:
    ResetWindow(const QString& info, QWidget* parent = 0);

private slots:
    void onResetBtnClicked();
    void onEndBtnClicked();

private:
    QPushButton* resetbtn,
               * endbtn;
};
