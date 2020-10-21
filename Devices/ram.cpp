#include "ram.h"

RAM::RAM(quint16 size)
{
    memSize = size;
    mem = new QList<quint32>();

    for(int i=0; i< memSize;i++){
        mem->append(0);
    }
}

RAM::RAM(){

}

RAM::~RAM(){
    delete mem;
    //qDebug() << __PRETTY_FUNCTION__;
}

void RAM::clear(){
    for(int i=0;i<memSize;i++)
    {
        mem->insert(i,0);
    }
}

bool RAM::write(const quint16 address, const quint32 num){
    if(address < memSize){
        mem->insert(address, num);
        return false;
    }

    return true;
}

QList<QString> RAM::toStr() const
{
    QList<QString> tmp;
    QList<quint32>::const_iterator it = mem->begin();
    for(;it != mem->end();++it){
        tmp.append( QString::number(*it) );
    }
    return tmp;
}

quint32 RAM::read(const quint16 address) const{
    if(address < memSize){
        return mem->at(address);
    }

    return 0;
}

quint16 RAM::getMemSize() const{
    return memSize;
}

QList<quint32> *RAM::getMem() const{
    return mem;
}
