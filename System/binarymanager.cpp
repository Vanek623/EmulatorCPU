#include "binarymanager.h"

BinaryManager::BinaryManager()
{

}

void BinaryManager::saveBinary(QList<Command> *commands)
{
    QFile file(findPathToBin());

    if(file.open(QIODevice::WriteOnly))
    {
        QList<Command>::const_iterator it;
        for(it = commands->begin(); it != commands->end(); ++it) {
            Binary binary;
            binary.operation = static_cast<quint16>((*it).getName());
            binary.operand1 = (*it).getOp1();
            binary.operand2 = (*it).getOp2();
            file.write(reinterpret_cast<char*>(&binary), sizeof (Binary));
        }

        file.close();
    }
}

QList<quint32> BinaryManager::loadBinary()
{
    QFile file(findPathToBin());
    QList<quint32> prog;

    if(file.open(QIODevice::ReadOnly))
    {
        while(!file.atEnd())
        {
            Binary binary;
            file.read(reinterpret_cast<char*>(&binary), sizeof (Binary));

            quint32 command =   static_cast<quint32>(binary.operation) << 27
                            |   static_cast<quint32>(binary.operand1) << 16
                            |   binary.operand2;

            prog.append(command);
        }

        file.close();
    }

    return prog;
}

QString BinaryManager::toAnothSys(const int num, const int numSys, const int size)
{
    return QString("%1").arg(QString::number(num, numSys), size, QLatin1Char('0')).toUpper();
}

QString BinaryManager::findPathToBin()
{
    QDir currentDir = QDir::current();
    currentDir.cdUp();

    return currentDir.absolutePath() + QString::fromUtf8("/EmulatorCPU/Binary/prog.txt");
}
