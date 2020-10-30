#pragma once

#include <QFile>
#include <QList>

#include "command.h"

class BinaryManager
{
private:
    QList<Command*> *commandList;
public:
    BinaryManager();

    void saveDefaultBinary(const QList<Command*> &programm);
    void saveBinary(const QString &path, const QList<Command*> &programm);

    QList<Command> *loadDefaultBinary();
    QList<Command> *loadBinary(const QString &path);

};
