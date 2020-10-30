#include "command.h"

Command::~Command(){
    //delete commandList;
}

Command::Command()
{
    this->name = static_cast<ComNames>(0);
    this->op1 = 0;
    this->op2 = 0;
}

Command::Command(const ComNames com, const quint16 op1, const quint16 op2)
{
    this->op1 = op1;
    this->op2 = op2;

    name = com;

//    commandList = new QStringList();
//    commandList->append( "MOV1 @R, OP");
//    commandList->append( "MOV2 @M, OP");
//    commandList->append( "MOV3 @R, @M");
//    commandList->append( "MOV4 @M, @R");
//    commandList->append( "MOV5 @R, @R");

//    commandList->append( "ADD1 @R1, @R2");
//    commandList->append( "ADD2 @R1, OP");

//    commandList->append( "SUB1 @R1, @R2");
//    commandList->append( "SUB2 @R1, OP");

//    commandList->append( "AND1 @R1, @R2");
//    commandList->append( "AND2 @R1, OP");

//    commandList->append( "OR1 @R1, @R2");
//    commandList->append( "OR2 @R, OP");

//    commandList->append( "JP L, X");
//    commandList->append( "JZ L, X");
//    commandList->append( "JN L, X");
//    commandList->append( "JMP L, X");
//    commandList->append( "NOP X, X");
}

//QStringList *Command::getCommandList() const
//{
//    return commandList;
//}

ComNames Command::getName() const{
    return name;
}

quint16 Command::getOp1() const{
    return op1;
}

quint16 Command::getOp2() const{
    return op2;
}

Command *Command::getCommand()
{
    return this;
}
