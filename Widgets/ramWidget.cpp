#include "ramWidget.h"

RamWidget::RamWidget(const int colCnt, const int rowCnt,
                     const QString &tableName, const RamTypes ramType){
    setupUI(colCnt, rowCnt, tableName, ramType);
}

RamWidget::~RamWidget()
{}

void RamWidget::updateContent(const QList<quint32> *content)
{

    for(int i=0;i<table->rowCount() && i<content->size();i++){
        fillRow(content->at(i),i);
    }
}

void RamWidget::setupUI(const int colCnt, const int rowCnt,
                        const QString &tableName, const RamTypes ramType){

    mainLayout = new QVBoxLayout();
    setupTableName(tableName);
    mainLayout->addWidget(name);

    type = ramType;
    QStringList headers;
    if(ramType == PROG)
    {
        headers << "Com" << "Op1" << "Op2";
    }
    else if(ramType == DATA)
    {
        headers << "Value";
    }
    setupTable(colCnt, rowCnt, headers);
    mainLayout->addWidget(table);

    setLayout(mainLayout);
}

void RamWidget::setupTable(const int colCnt, const int rowCnt,
                           const QStringList &headers)
{
    table = new QTableWidget();

    QStringList rowHeaders;
    table->setColumnCount(colCnt);
    table->setRowCount(rowCnt);

    for(int i=0; i<table->rowCount(); i++)
        rowHeaders << QString::number(i);

    table->setVerticalHeaderLabels(rowHeaders);
    table->setHorizontalHeaderLabels(headers);

    table->horizontalHeader()->setStretchLastSection(false);
    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setShowGrid(true);

    for(int i=0; i<table->rowCount(); i++)
    {
        fillRow(0,i);
    }
}

void RamWidget::setupTableName(const QString &tableName)
{
    name = new QLabel(tableName);
    name->setStyleSheet("QLabel {color: blue; font-size: 12px;}");
    name->setAlignment(Qt::AlignHCenter);
}

void RamWidget::fillRow(const quint32 value, const int row)
{
    quint32 line = value;
    if(type == PROG)
    {
        table->setItem(row,2, createCell(line, 0xFFFF, 16, 4));
        line = line >> 16;
        table->setItem(row,1, createCell(line, 0x7FF, 16, 3));
        line = line >> 11;
        table->setItem(row,0, createCell(line, 0x1F, 16, 2));
    }
    else if(type == DATA)
    {
        table->setItem(row,0, createCell(line,0xFFFF,16,4));
    }
}

void RamWidget::resizeTable(){
    for(int i=0;i<table->columnCount();i++)
    {
        table->setColumnWidth(i,table->width()/table->columnCount());
    }
}

QString RamWidget::toAnothSys(const int num, const int numSys, const int size)
{
    return QString("%1").arg(QString::number(num, numSys), size, QLatin1Char('0')).toUpper();
}

QTableWidgetItem *RamWidget::createCell(const quint16 value, const quint16 mask,
                                        const quint16 numSys, const quint16 width)
{
    QTableWidgetItem *tmp = new QTableWidgetItem(toAnothSys(value & mask, numSys, width));
    tmp->setTextAlignment(Qt::AlignHCenter);

    return tmp;
}
