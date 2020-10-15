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
    //Parse the text to lines and then
    //parse the lines to words and put it to collection
    marks = new QMap<QString,quint16>();

    QString editProgTxt;
    editProgTxt.append(rawProgTxt);

    const QRegExp commentRegExp(QString::fromUtf8("\\/\\/[a-zA-Z0-9а-яА-Я ]*"));
    const QRegExp errSimbols(QString::fromUtf8("\t"));

    editProgTxt.remove(commentRegExp);
    editProgTxt.remove(errSimbols);
    //qDebug() << editProgTxt;

    //init marks list
    int lineCnt = 0;
    foreach (QString line, editProgTxt.split('\n'))
    {
        const QRegExp markRegExp("[a-zA-Z]+[0-9]*:[a-zA-Z]+");

        if(line.contains(markRegExp) > 0)
        {
            marks->insert(line.split(':').at(0),lineCnt);
        }

        lineCnt++;
    }

    const QRegExp markExp("[a-zA-Z]+[0-9]*:");
    editProgTxt.remove(markExp);

    //parse to words(tokens)
    QStringList words;
    foreach (QString line, editProgTxt.split('\n'))
    {
        foreach (QString word, line.split(' '))
        {
            if(!word.isEmpty())
            {
                words.append(word);
                //qDebug() << word;
            }
        }
    }

    setupCommandList();

    return parse(words);
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

        if(tmpInfo.name>=JP && tmpInfo.name<=JMP || tmpInfo.name == ADD3 ) tmpInfo.opCnt = 1;
        else if(i!=0) tmpInfo.opCnt = 2;
        else tmpInfo.opCnt = 0;

        commandList->insert(list.at(i), tmpInfo);
    }
}

int Builder::parse(const QStringList &words)
{
    program = new QList<Command*>();
    QStringList::const_iterator it;
    int line = 0;

    for(it = words.begin(); it != words.end(); ++it){
        quint16 op1, op2;

        if(commandList->contains(*it))
        {
            COMINFO curInfo = commandList->value(*it);

            if(curInfo.opCnt >= 1)
            {
                bool isOk;
                quint16 tmpOp;
                if(it + 1 != words.end())
                {
                    //Обработка операнда связанного с меткой
                    if(curInfo.name >= JP && curInfo.name <= JMP)
                    {
                        if(marks->contains(*(++it))) op1 = marks->value(*it);
                        else return line;
                    }
                    //Обычная обработка операнда
                    else
                    {
                        tmpOp = (*(++it)).toShort(&isOk);
                        if(isOk) op1 = tmpOp;
                        else return line;
                    }

                }
                else return line;

                if(curInfo.opCnt == 2)
                {
                    if(it + 1 != words.end())
                    {
                        tmpOp = (*(++it)).toShort(&isOk);
                        if(isOk) op2 = tmpOp;
                        else return line;
                    }
                    else
                    {
                        return line;
                    }
                }
                else op2 = 0;
            }
            else op1 = op2 = 0;

            program->append(new Command(curInfo.name,op1,op2));
        }
        else return line;

        line++;
    }

    return -1;
}
