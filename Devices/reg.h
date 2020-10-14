#ifndef REG_H
#define REG_H
#include "QtCore"

class Reg
{
public:
    Reg();
    ~Reg();

    void write(const quint16 a);
    quint16 read() const;
    QString toStr() const;
private:
    quint16 val;
};

#endif // REG_H
