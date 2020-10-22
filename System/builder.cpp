#include "builder.h"

Builder::Builder()
{

}

Builder::~Builder()
{
    QList<Command*>::iterator it;
    for (it = program->begin(); it != program->end(); ++it)
    {
        delete (*it);
    }

    delete program;

    delete commandList;
    delete marks;
}

int Builder::compile(const QString &rawProgTxt){
    lexer lexerObj;

    lexerObj.toLexems(rawProgTxt);
    //lexerObj.printLexemes();

    marks = new QMap<QString,quint16>();

    QList<lexeme> *lexemes = lexerObj.getLexemes();
    QList<lexeme>::const_iterator it;

    quint16 lineCnt = 0;
    for(it = lexemes->begin(); it != lexemes->end(); ++it)
    {
        if( (*it).getType() == MARK_I)
            marks->insert((*it).getValue(), lineCnt);
        else if((*it).getType() == COMMAND)
            lineCnt++;
    }

    setupCommandList();

    return parse(lexemes);
}

QList<Command*> *Builder::getProgrammList() const
{
    return program;
}

void Builder::setupCommandList()
{
    commandList = new QMap<QString, COMINFO>();

    COMINFO tmpInfo;
    QStringList list;

    list<<"NOP"<<"MOV1"<<"MOV2"<<"MOV3"<<"MOV4"<<"MOV5"<<"ADD1"<<"ADD2"
        <<"ADD3"<<"SUB1"<<"SUB2"<<"MUX"<<"AND1"<<"AND2"<<"OR1"<<"OR2"
        <<"JP"<<"JZ"<<"JN"<<"JMP";

    QList<ComNames> opNames;

    opNames <<NOP<<MOV1<<MOV2<<MOV3<<MOV4<<MOV5<<ADD1<<ADD2<<ADD3
            <<SUB1<<SUB2<<MUX<<AND1<<AND2<<OR1<<OR2<<JP<<JZ<<JN<<JMP;

    for(int i=0; i<list.size(); i++)
    {
        tmpInfo.name = opNames.at(i);

        if( (tmpInfo.name>=JP && tmpInfo.name<=JMP ) ) tmpInfo.opCnt = 1;
        else if(i!=0) tmpInfo.opCnt = 2;
        else tmpInfo.opCnt = 0;

        commandList->insert(list.at(i), tmpInfo);
    }
}

int Builder::parse(const QList<lexeme> *lexemes)
{
    program = new QList<Command*>();
    QList<lexeme>::const_iterator it;
    int line = 0;

    for(it = lexemes->begin(); it != lexemes->end(); ++it){
        quint16 op1, op2;
        lexeme lex = *it;

        if( lex.getType() == MARK_I) continue;
        else if( lex.getType() == COMMAND && commandList->contains(lex.getValue()) )
        {
            COMINFO curInfo = commandList->value(lex.getValue());

            if(curInfo.opCnt == 1 && it + 1 != lexemes->end())
            {
                lexeme op = *(++it);
                if(op.getType() == OPERAND)
                {
                    op1 = op.getValue().toUShort(nullptr, 16);
                    op2 = 0;
                }
                else if(op.getType() == MARK_U && marks->contains(op.getValue()))
                {
                    op1 = marks->value(op.getValue());
                    op2 = 0;
                }
                else
                {
                    return line;
                }
            }
            else if(curInfo.opCnt == 2 && it+1 != lexemes->end() && it+2 != lexemes->end())
            {
                for(int i=0 ; i<2; i++)
                {
                    lexeme op = *(++it);
                    if(op.getType() == OPERAND)
                    {
                        quint16 tmp_op = op.getValue().toUShort(nullptr, 16);
                        if(i == 0) op1 = tmp_op;
                        else op2 = tmp_op;
                    }
                    else if(op.getType() == MARK_U && marks->contains(op.getValue()))
                    {
                        quint16 tmp_op = marks->value(op.getValue());
                        if(i == 0) op1 = tmp_op;
                        else op2 = tmp_op;
                    }
                    else
                    {
                        return line;
                    }
                }

            }
            else if(curInfo.opCnt == 0)
            {
                op1 = op2 = 0;
            }
            else
            {
                return line;
            }

            program->append(new Command(curInfo.name,op1,op2));
        }
        else return line;

        line++;
    }

    return -1;
}
