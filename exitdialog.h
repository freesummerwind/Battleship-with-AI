#pragma once

#include <QDialog>
#include <QPushButton>

class ExitDialog : public QDialog
{
    Q_OBJECT
public:
    ExitDialog(QWidget* parent = 0);

private slots:
    void onOKBtnClicked();
    void onCancelBtnClicked();

private:
    QPushButton* okbtn,
               * cancelbtn;
};
