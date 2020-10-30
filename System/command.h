#ifndef COMMAND_H
#define COMMAND_H

#include "QList"
#include "comnames.h"
/*
 *Команды:
 * 32 бита
 * 32-28: код операции
 * 27-16: первый адрес
 * 15-0: второй адрес/операнд
 *
 * Система команд
 * 0. MOV1 @R, OP
 * 1. MOV2 @M, OP
 * 2. MOV3 @R1, M[@R2]
 * 3. MOV4 M[@R1], @R2
 * 4. MOV5 @R, @R
 *
 * 5. ADD1 @R1, @R2 // R1 = @R1 + @R2
 * 6. ADD2 @R, OP  // R1 = @R1 + OP
 * 7. ADD3 @RH, @RL    //[R1:R2] = [R1:R2] + [@RH:@RL]
 *
 * 7. SUB1 @R1, @R2
 * 8. SUB2 @R, OP
 *
 * 9. AND1 @R1, @R2
 * 10. AND2 @R, OP
 *
 * 11.  OR1 @R1, @R2
 * 12.  OR2 @R, OP
 *
 * 13. JP N, X
 * 14. JZ N, X
 * 15. JN N, X
 * 16. JMP N, X
 *
 * 17. NOP
 */


class Command
{
public:
    Command();
    Command(const ComNames com,const quint16 op1,const quint16 op2);
    ~Command();

    ComNames getName() const;
    quint16 getOp1() const;
    quint16 getOp2() const;
    Command *getCommand();
    //QStringList *getCommandList() const;

private:
    ComNames name;
    quint16 op1, op2;
    //QStringList *commandList;
};

#endif // COMMAND_H
