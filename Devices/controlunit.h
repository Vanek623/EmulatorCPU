#pragma once

#include "reg.h"
#include "ram.h"
#include "alu.h"
#include "command.h"
#include "cpuconsts.h"

#include <QList>
#include <QString>

/*
 * Регистры:
 * R1 - Регистр АЛУ
 * R2, R3, R4 - РОН
 *
 * Флаги:
 * 0:ZF - флаг нуля
 * 1:CF - флаг переполнения
 * 2:NF - флаг отрицательности
 *
 * Команды:
 * 32 бита
 * 32-29: код операции
 * 28-16: первый адрес
 * 15-0: второй адрес/операнд
 *
 */

class ControlUnit
{
private:
    Command *curCom;
    RAM *prog;
    RAM *data;
    ALU alu;
    QList<Reg> regs;
    quint16 flags;
    quint16 pc;

    quint16 tickCounter;

public:
    ControlUnit();
    ~ControlUnit();

    bool Init(const QList<quint32> inputProg);
    bool Work();
    void Reset();

    QList<quint32> *getData() const;
    QList<quint32> *getProg() const;
    QList<quint16> getRegs() const;

    quint16 getPC() const;

private:
    void movOp();
    void addOp();
    void subOp();
    void muxOp();
    void andOp();
    void orOp();

    void jmpOp();
    void nopOp();
};
