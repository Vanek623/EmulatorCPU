#pragma once

#include <QDir>
#include <QList>
#include <QDebug>
#include <QRegExp>

#include "command.h"

#pragma pack(1)

struct Binary
{
    quint16 operation : 5;
    quint16 operand1 : 11;
    quint16 operand2 : 16;
};

#pragma pack(0)

class BinaryManager
{
public:
    BinaryManager();

    static void saveBinary(QList<Command> *commands);
    static QList<quint32> loadBinary();

private:
    static QString toAnothSys(const int num, const int numSys, const int size);
    static QString findPathToBin();

};
