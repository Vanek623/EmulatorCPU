#include "lexer.h"

lexer::lexer()
{
    hasUnknown = false;
}

void lexer::toLexems(const QString &text)
{
    const QString brakes = " \n:/";
    QString word = "";
    bool isComment = false;

    for(int i=0; i<text.length(); i++)
    {
        QChar sim = text.at(i);
        bool skip = false;

        if(isComment && sim != brakes.at(1)) continue;

        for(int j=0; j<brakes.length(); j++)
        {
            if(sim == brakes.at(j))
            {
                if(j == 2) word.append(sim);
                if(!word.isEmpty())
                    addLexem(word);
                //addLexem(word);
                if(j == 1 && word.isEmpty())
                    addLexem("EMPTY");

                skip = true;
                word = "";
                isComment = j == 3;
            }
        }
        if(!skip) word.append(sim);
        if(i == text.length() - 1 && !word.isEmpty()) addLexem(word);
    }
}

QList<lexeme> *lexer::getLexemes()
{
    return &lexemes;
}

void lexer::printLexemes() const
{
    int cnt = 1;
    for(int i=0; i < lexemes.size(); i++)
    {
        lexeme lex = lexemes.at(i);
        if(!(lex.getType() == OPERAND || lex.getType() == MARK_U))
        qDebug() << cnt++ << lex.getType() << lex.getValue();
    }
}

void lexer::addLexem(const QString &word)
{
    lexeme lex;
    lex.setValue(word);

    if(markInitExp.exactMatch(word))
    {
        lex.setType(MARK_I);
        QString tmp = word;
        tmp.chop(1);
        lex.setValue(tmp);
    }
    else if(markUseExp.exactMatch(word)) lex.setType(MARK_U);
    else if(commandExp.exactMatch(word)) lex.setType(COMMAND);
    else if(operandDecRegExp.exactMatch(word))
    {
        lex.setType(OPERAND);
        lex.setValue(convertNumber(word, true));
    }
    else if(operandHexRegExp.exactMatch(word))
    {
        lex.setType(OPERAND);
        lex.setValue(convertNumber(word, false));
    }
    else if(word.isEmpty()) lex.setType(EMPTY);
    else lex.setType(UNKWNOWN);

    hasUnknown = hasUnknown || lex.getType() == UNKWNOWN;

    lexemes.append(lex);
}

QString lexer::convertNumber(const QString &number, const bool fromDec)
{
    QString result;
    if(fromDec)
    {
        result = QString::number(number.toUShort(nullptr, 10), 16);
    }
    else
    {
        result = number;
        result.remove("0x");
    }

    return result;
}
