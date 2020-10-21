#ifndef RAM_H
#define RAM_H

#include <QList>
#include <QDebug>

class RAM
{
public:
    RAM();
    RAM(quint16 size);
    ~RAM();

    void clear();

    bool write(const quint16 address,const quint32 num);
    quint32 read(const quint16 address) const;
    quint16 getMemSize() const;
    QList<quint32> *getMem() const;
    QList<QString> toStr() const;

private:
    QList<quint32> *mem;
    quint16 memSize;
};

#endif // RAM_H
