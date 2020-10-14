#pragma once

#include <QLabel>
#include <QString>
#include <QWidget>
#include <QStringList>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "RamType.h"

class RamWidget : public QWidget
{
    Q_OBJECT
private:
    QTableWidget *table;
    QLabel *name;
    QVBoxLayout *mainLayout;
    RamTypes type;

public:
    RamWidget(const int colCnt, const int rowCnt,
              const QString &tableName, const RamTypes ramType);
    ~RamWidget();
    void updateContent(const QList<quint32> *content);
    void resizeTable();

private:
    void setupUI(const int colCnt, const int rowCnt,
                 const QString &tableName, const RamTypes ramType);
    void setupTable(const int colCnt, const int rowCnt,
                    const QStringList &headers);
    void setupTableName(const QString &tableName);
    void fillRow(const quint32 value, const int row);
    QString toAnothSys(const int num, const int numSys, const int size);
    QTableWidgetItem *createCell(const quint16 value, const quint16 mask,
                                 const quint16 numSys, const quint16 width);
};
