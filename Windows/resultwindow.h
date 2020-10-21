#pragma once
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class ResultWindow : public QDialog
{
    Q_OBJECT
private:
    QPushButton *closeBtn;
public:
    ResultWindow(QWidget *parent, const int strNum);
};
