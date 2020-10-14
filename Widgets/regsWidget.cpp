#include "regsWidget.h"

RegsWidget::RegsWidget(const QString &mainTitle, const QStringList &titles, const quint16 defValue){
    setupUI(mainTitle ,titles, defValue);
}

RegsWidget::~RegsWidget()
{
    QList<QLabel*>::iterator it;
    for(it = values->begin(); it != values->end(); ++it)
    {
        delete (*it);
    }

    delete values;
}

void RegsWidget::updateValues(const QList<quint16> &regValues){
    QList<QLabel*>::iterator it;
    int i = 0;
    for(it = values->begin(); it != values->end(); ++it){
        (*it)->setText( toAnothSys(regValues.at(i), 16, 4) );
        i++;
    }
}

void RegsWidget::setupUI(const QString &mainTitle, const QStringList &titles, const quint16 defValue)
{
    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(createTitle(mainTitle));

    QHBoxLayout *hLayout = new QHBoxLayout();
    values = new QList<QLabel*>();
    for(int i =0; i < titles.size();i++)
    {
        QVBoxLayout *regLayout = new QVBoxLayout();
        QLabel *regTitleLbl = new QLabel(titles.at(i));
        regTitleLbl->setAlignment(Qt::AlignHCenter);
        regLayout->addWidget( regTitleLbl );

        QLabel *regLbl = new QLabel(toAnothSys(defValue,16,4));
        regLbl->setAlignment(Qt::AlignHCenter);
        regLbl->setStyleSheet("border: 1px solid #000;");
        regLayout->addWidget( regLbl );
        values->append(regLbl);

        hLayout->addItem(regLayout);
    }

    mainLayout->addItem(hLayout);

    setLayout(mainLayout);
}

QString RegsWidget::toAnothSys(const int num, const int numSys, const int size)
{
    return QString("%1").arg(QString::number(num, numSys), size, QLatin1Char('0')).toUpper();
}

QLabel *RegsWidget::createTitle(const QString &title)
{
    QLabel *tmpLbl = new QLabel(title);
    tmpLbl->setAlignment(Qt::AlignHCenter);
    tmpLbl->setStyleSheet("color: blue");

    return tmpLbl;
}
