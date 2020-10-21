#include "resultwindow.h"

ResultWindow::ResultWindow(QWidget *parent, const int strNum) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
    this->setModal(true);
    this->setMinimumWidth(100);
    this->setMinimumHeight(100);
    this->setWindowTitle("Compiltator brief");

    QVBoxLayout *layout = new QVBoxLayout();

    if(strNum == -1)
    {
        QLabel *title = new QLabel("Компиляция прошла успешно!");
        title->setAlignment(Qt::AlignHCenter);
        title->setStyleSheet("color: green;");

        layout->addWidget(title);
    }
    else
    {
        QLabel *title = new QLabel("Компиляция прошла неудачно!");
        title->setAlignment(Qt::AlignHCenter);
        title->setStyleSheet("color: red;");

        QLabel *text = new QLabel("Ошибка в " + QString::number(strNum + 1) + " строке...");

        layout->addWidget(title);
        layout->addWidget(text);

    }

    closeBtn = new QPushButton("OK");
    connect(closeBtn, SIGNAL(clicked()), SLOT(accept()));

    layout->addWidget(closeBtn);

    setLayout(layout);
}
