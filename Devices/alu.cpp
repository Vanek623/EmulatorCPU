#include "alu.h"

ALU::ALU()
{
    flags=0;//2 - Zero, 1 - Carry, 0 - Negative
}

ALU::~ALU(){

}

quint16 ALU::addOp(const quint16 a, const quint16 b){

    int result = a + b;

    flags = result == 0;
    flags = flags << 1;
    flags |= result & 65536; //check 16th bit

    return (quint16) (a + b);
}

quint16 ALU::subOp(const quint16 a, const quint16 b){
    int result = a - b;

    flags = result == 0;
    flags = flags << 1;
    flags |= result & 65536; //check 16th bit
    flags = flags << 1;
    flags |= result < 0;

    return static_cast<quint16> (a - b);

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
