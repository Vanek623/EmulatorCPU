#ifndef ALU_H
#define ALU_H

#include "QtCore"


class ALU
{
public:
    ALU();
    ~ALU();

    quint16 addOp(const quint16 a, const quint16 b);
    quint16 subOp(const quint16 a, const quint16 b);
    quint16 andOp(const quint16 a, const quint16 b);
    quint16 orOp(const quint16 a, const quint16 b);

    quint16 readFlags() const;

private:
    quint16 flags;
};

#endif // ALU_H
