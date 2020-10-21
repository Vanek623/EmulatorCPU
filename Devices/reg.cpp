#include "reg.h"

Reg::Reg()
{
    val=0;
}

Reg::~Reg(){

}

void Reg::write(const quint16 a){
    val = a;
}

quint16 Reg::read() const{
    return val;
}

QString Reg::toStr() const{
    return QString::number(val,16).toUpper();
}
