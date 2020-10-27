#pragma once

#include "lexeme.h"
#include <QList>
#include <QDebug>
#include <QStringList>

const QRegExp markInitExp(QString::fromUtf8("[G-Z]{1}[0-9]{1}:"));
const QRegExp markUseExp(QString::fromUtf8("[G-Z]{1}[0-9]{1}"));
const QRegExp commandExp(QString::fromUtf8("[A-Z]{2,3}[0-9]?"));
const QRegExp operandDecRegExp(QString::fromUtf8("[0-9]+"));
const QRegExp operandHexRegExp(QString::fromUtf8("0x[0-9A-F]+"));

class lexer
{
private:
    QList<lexeme> lexemes;
    bool hasUnknown;

public:
    lexer();

    void toLexems(const QString &text);

    QList<lexeme> *getLexemes();
    void printLexemes() const;

private:
    void addLexem(const QString &word);
    QString convertNumber(const QString &number, const bool fromDec);
};
