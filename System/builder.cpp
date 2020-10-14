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

    tmpInfo.num = 0;
    tmpInfo.opCnt = 0;
    commandList->insert("NOP", tmpInfo);

    tmpInfo.num = 1;
    tmpInfo.opCnt = 2;
    commandList->insert("MOV1", tmpInfo);

    tmpInfo.num = 2;
    tmpInfo.opCnt = 2;
    commandList->insert("MOV2", tmpInfo);

    tmpInfo.num = 3;
    tmpInfo.opCnt = 2;
    commandList->insert("MOV3", tmpInfo);

    tmpInfo.num = 4;
    tmpInfo.opCnt = 2;
    commandList->insert("MOV4", tmpInfo);

    tmpInfo.num = 5;
    tmpInfo.opCnt = 2;
    commandList->insert("MOV5", tmpInfo);

    tmpInfo.num = 6;
    tmpInfo.opCnt = 2;
    commandList->insert("ADD1", tmpInfo);

    tmpInfo.num = 7;
    tmpInfo.opCnt = 2;
    commandList->insert("ADD2", tmpInfo);

    tmpInfo.num = 8;
    tmpInfo.opCnt = 2;
    commandList->insert("SUB1", tmpInfo);

    tmpInfo.num = 9;
    tmpInfo.opCnt = 2;
    commandList->insert("SUB2", tmpInfo);

    tmpInfo.num = 10;
    tmpInfo.opCnt = 2;
    commandList->insert("AND1", tmpInfo);

    tmpInfo.num = 11;
    tmpInfo.opCnt = 2;
    commandList->insert("AND2", tmpInfo);

    tmpInfo.num = 12;
    tmpInfo.opCnt = 2;
    commandList->insert("OR1", tmpInfo);

    tmpInfo.num = 13;
    tmpInfo.opCnt = 2;
    commandList->insert("OR2", tmpInfo);

    tmpInfo.num = 14;
    tmpInfo.opCnt = 1;
    commandList->insert("JP", tmpInfo);

    tmpInfo.num = 15;
    tmpInfo.opCnt = 1;
    commandList->insert("JZ", tmpInfo);

    tmpInfo.num = 16;
    tmpInfo.opCnt = 1;
    commandList->insert("JN", tmpInfo);

    tmpInfo.num = 17;
    tmpInfo.opCnt = 1;
    commandList->insert("JMP", tmpInfo);
}

int Builder::parse(const QStringList &words)
{
    program = new QList<Command*>();
    QStringList::const_iterator it;
    int line = 0;

    quint16 op1, op2;
    ComNames name;

    for(it = words.begin(); it != words.end(); ++it){
        if(commandList->contains(*it))
        {
            COMINFO curInfo = commandList->value(*it);

            name = static_cast<ComNames>(curInfo.num);

            if(curInfo.opCnt >= 1)
            {
                bool isOk;
                quint16 tmpOp;
                if(it + 1 != words.end())
                {
                    //Обработка операнда связанного с меткой
                    if(name >= JP && name <= JMP)
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

            program->append(new Command(name,op1,op2));
        }
        else return line;

        line++;
    }

    return -1;
}
