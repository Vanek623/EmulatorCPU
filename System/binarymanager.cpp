#include "binarymanager.h"

BinaryManager::BinaryManager()
{
    commandList = nullptr;
}

void BinaryManager::saveDefaultBinary(const QList<Command *> &programm)
{

}

void BinaryManager::saveBinary(const QString &path, const QList<Command *> &programm)
{

}

QList<Command> *BinaryManager::loadDefaultBinary()
{
    return nullptr;
}

QList<Command> *BinaryManager::loadBinary(const QString &path)
{
    return nullptr;
}
