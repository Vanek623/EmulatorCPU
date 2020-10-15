#include "alu.h"

ALU::ALU()
{
    flags=0;//2 - Zero, 1 - Carry, 0 - Negative
}

ALU::~ALU(){

}

quint32 ALU::addOp(const quint32 a, const quint16 b, bool doubleSize){

    quint32 result = a + b;

    flags = result == 0;
    flags = flags << 1;
    flags |= result & 65536; //check 16th bit

    if(doubleSize)return result & 0xFFFF;
    else return result;
}

quint16 ALU::subOp(const quint16 a, const quint16 b){
    int result = a - b;

    flags = result == 0;
    flags = flags << 1;
    flags |= result > 0xFFFF; //check 16th bit
    flags = flags << 1;
    flags |= result < 0;

    return static_cast<quint16> (a - b);

}

quint32 ALU::muxOp(const quint16 a, const quint16 b)
{
    quint32 result = a * b;

    flags = result == 0;
    flags = flags << 1;
    flags |= result > 0xFFFF;

    return result;
}

quint16 ALU::andOp(const quint16 a, const quint16 b){
    flags = (a&b) == 0;

    return static_cast<quint16> (a&b);
}

quint16 ALU::orOp(const quint16 a, const quint16 b){
    flags = (a|b) == 0;

    return static_cast<quint16> (a|b);
}

quint16 ALU::readFlags() const{
    return flags;
}
