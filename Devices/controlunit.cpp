#include "controlunit.h"

/*
 *Команды:
 * 32 бита
 * 31-27: код операции
 * 26-16: первый адрес
 * 15-0: второй адрес/операнд
 *
 * Система команд
 * 1. MOV1 @R, OP
 * 2. MOV2 @M, OP
 * 3. MOV3 @R, @M
 * 4. MOV4 @M, @R
 *
 * 5. ADD1 @R1, @R2 // R1 = @R1 + @R2
 * 6. ADD2 @R1, OP  // R1 = @R1 + OP
 *
 * 7. SUB1 @R1, @R2
 * 8. SUB2 @R1, OP
 *
 * 9.  AND1 @R1, @R2
 * 10. AND2 @R1, OP
 *
 * 11.  OR1 @R1, @R2
 * 12.  OR2 @R, OP
 *
 * 13. INC @R, X
 * 14. DEC @R, X
 *
 * 15. JP X, N
 * 16. JZ X, N
 * 17. JN X, N
 *
 * 18. NOP, X, X
 */

ControlUnit::ControlUnit(const QList<Command*> *inputProg){
    prog = new RAM(PROG_SIZE);
    data = new RAM(DATA_SIZE);

    curCom = nullptr;

    for(int i=0;i<8;i++)
        regs << Reg();

    quint16 memaddr = 0;
    QList<Command*>::const_iterator it;
    for(it = inputProg->begin(); it != inputProg->end(); ++it) {
        quint32 word = static_cast<quint32>((*it)->getName()) << 27;
        word += static_cast<quint32>((*it)->getOp1()) << 16;
        word += static_cast<quint32>((*it)->getOp2());

        prog->write(memaddr++,word);
    }

    pc = 0;
}

ControlUnit::~ControlUnit(){
    delete prog;
    delete data;

    if (curCom != nullptr)
        delete curCom;
}

bool ControlUnit::Work(){
    if(pc < prog->getMemSize()){
        quint32 word = prog->read(pc);
        quint16 op2 = word & 0xFFFF;
        quint16 op1 = (word >> 16) & 0x7FF;
        ComNames name = static_cast<ComNames> (word >> 27);

        if (curCom != nullptr)
        {
            delete curCom;
            curCom = nullptr;
        }

        curCom = new Command(name,op1,op2);

        switch (curCom->getName()) {
        case MOV1:
        case MOV2:
        case MOV3:
        case MOV4:
        case MOV5:
            movOp();
            break;
        case ADD1:
        case ADD2:
        case ADD3:
            addOp();
            break;
        case SUB1:
        case SUB2:
            subOp();
            break;
        case MUX:
            muxOp();
            break;
        case AND1:
        case AND2:
            andOp();
            break;
        case OR1:
        case OR2:
            orOp();
            break;
        case JP:
        case JZ:
        case JN:
        case JMP:
            jmpOp();
            break;
        default:
            nopOp();
            break;
        }

        flags = alu.readFlags();

        pc++;

        return true;
    }

    return false;
}

void ControlUnit::Reset()
{
    data->clear();

    for(int i=0; i<regs.length();i++)
    {
        regs[i].write(0);
    }

    flags = 0;
    pc = 0;
}

void ControlUnit::movOp(){
    switch (curCom->getName()) {
    case MOV1:
        regs[curCom->getOp1()].write(curCom->getOp2());
        break;
    case MOV2:
        data->write(curCom->getOp1(),curCom->getOp2());
        break;
    case MOV3:
        regs[curCom->getOp1()].write(data->read( regs.at(curCom->getOp2()).read() ));
        break;
    case MOV4:
        data->write( regs.at(curCom->getOp1()).read(),regs.at(curCom->getOp2()).read() );
        break;
    case MOV5:
        regs[curCom->getOp1()].write(regs.at(curCom->getOp2()).read());
        break;
    default:
        break;
    }
}

void ControlUnit::addOp(){
    quint32 a, b, result;
    switch (curCom->getName()) {
    case ADD1:
        regs[0].write(alu.addOp(regs.at(curCom->getOp1()).read(), regs.at(curCom->getOp2()).read(), false));
        break;
    case ADD2:
        regs[0].write( alu.addOp(regs.at(curCom->getOp1()).read(), curCom->getOp2(), false) );
        break;
    case ADD3:
        a = (regs.at(0).read() << 16) | regs.at(1).read();
        b = (regs.at(curCom->getOp1()).read() << 16) | regs.at(curCom->getOp2()).read();
        result = alu.addOp( a, b, true);
        qDebug() << QString::number(a, 16).toUpper() << QString::number(result, 16).toUpper();
        regs[0].write(result >> 16);
        regs[1].write(result & 0xFFFF);
        break;
    default:
        break;
    }
}

void ControlUnit::subOp(){
    switch (curCom->getName()) {
    case SUB1:
        regs[0].write(alu.subOp(regs.at(curCom->getOp1()).read(), regs.at(curCom->getOp2()).read()));
        break;
    case SUB2:
        regs[0].write( alu.subOp(regs.at(curCom->getOp1()).read(), curCom->getOp2()) );
        break;
    default:
        break;
    }
}

void ControlUnit::muxOp()
{
    quint32 result = alu.muxOp(regs.at(curCom->getOp1()).read(), regs.at(curCom->getOp2()).read());
    regs[0].write(result >> 16);
    regs[1].write(result & 0xFFFF);
}

void ControlUnit::andOp(){
    switch (curCom->getName()) {
    case AND1:
        regs[0].write( alu.andOp(regs.at(curCom->getOp1()).read(), regs.at(curCom->getOp2()).read()) );
        break;
    case AND2:
        regs[0].write( alu.andOp(regs.at(curCom->getOp1()).read(), curCom->getOp2()) );
        break;
    default:
        break;
    }
}

void ControlUnit::orOp(){
    switch (curCom->getName()) {
    case OR1:

        regs[curCom->getOp1()].write(alu.orOp(regs.at(0).read(),regs.at(curCom->getOp2()).read()));
        break;
    case OR2:
        regs[curCom->getOp1()].write(alu.orOp(regs.at(0).read(),curCom->getOp2()));
        break;
    default:
        break;
    }
}

void ControlUnit::jmpOp(){
    switch (curCom->getName()) {
    case JZ:
        if(flags & 4)
            pc = curCom->getOp1() - 1;
        break;
    case JN:
        if(flags & 1)
            pc = curCom->getOp1() - 1;
        break;
    case JP:
        if((flags & 5) == 0)
            pc = curCom->getOp1() - 1;
        break;
    case JMP:
        pc = curCom->getOp1() - 1;
        break;
    default:
        break;
    }
}

void ControlUnit::nopOp(){

}

QList<quint32> *ControlUnit::getData() const{
    return data->getMem();
}

QList<quint32> *ControlUnit::getProg() const{
    return prog->getMem();
}

QList<quint16> ControlUnit::getRegs() const{
    QList<quint16> tmp;
    tmp.append(pc);
    tmp.append(flags);

    QList<Reg>::const_iterator it = regs.begin();
    for(;it != regs.end();++it)
        tmp.append( (*it).read() );

    return tmp;
}

