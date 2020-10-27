#include "highlighter.h"

HighLighter::HighLighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    setupPatterns();
}

void HighLighter::highlightBlock(const QString &text)
{
    QString word = "";
    QString breakSims = "/: ";

    int index = 0;
    bool isComment = false;

    for(int i=0; i<text.length(); i++)
    {
        QChar sim = text.at(i);
        if(breakSims.contains(sim))
        {
            bool isBreakerFound = false;
            for(int j=0; j<breakSims; j++)
            {
                isBreakerFound = sim == breakSims.at(j);
                if(isBreakerFound)
                {
                    switch (j) {
                    case 0:
                        findAndSetFormat(index, word);
                        index += word.length();
                        setFormat(index, text.length() - word.length(), rules.first().format);
                        isComment = true;
                        break;
                    case 1:
                        word.append(sim);
                        findAndSetFormat(index, word);
                        index += word.length();
                        word = "";
                        isBreakerFound = true;
                        break;
                    case 2:
                        if(!word.isEmpty())
                        {
                            findAndSetFormat(index, word);
                            index += word.length() + 1;
                            word = "";
                        }
                        else
                        {
                            index++;
                        }
                        isBreakerFound = true;
                        break;
                    default:
                        break;
                    }

                    break;  //break if isBreakerFound
                }
            }
        }
        else word.append(sim);

        if(i == text.length() - 1) findAndSetFormat(index, word);
        if(isComment) break;
    }

    setCurrentBlockState(0);
}

void HighLighter::setupPatterns()
{
    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::cyan);
    addRule("/.*", commentFormat);

    setupCommands();

    QTextCharFormat markFormat;
    markFormat.setForeground(Qt::yellow);
    markFormat.setFontItalic(true);
    addRule("\\b[G-Z]{1}[0-9]{1}:?", markFormat);

    QTextCharFormat operandDecFormat;
    operandDecFormat.setForeground(Qt::gray);
    addRule("\\b\\d+\\b", operandDecFormat);

    QTextCharFormat operandHexFormat;
    operandDecFormat.setForeground(Qt::gray);
    addRule("\\b0x[0-9A-Fa-f]+\\b", operandDecFormat);

    QTextCharFormat unknowFormat;
    unknowFormat.setForeground(Qt::red);
    addRule("\\b.*\\b", unknowFormat);
}

void HighLighter::setupCommands()
{
    QStringList commands;
    commands<<"NOP"<<"MOV1"<<"MOV2"<<"MOV3"<<"MOV4"<<"MOV5"<<"ADD1"<<"ADD2"
            <<"ADD3"<<"SUB1"<<"SUB2"<<"MUX"<<"AND1"<<"AND2"<<"OR1"<<"OR2"
            <<"JP"<<"JZ"<<"JN"<<"JMP";

    QTextCharFormat commandFormat;
    commandFormat.setForeground(Qt::green);
    commandFormat.setFontWeight(QFont::Bold);

    foreach(const QString &command, commands)
    {
        addRule(command+"\\b", commandFormat);
    }
}

void HighLighter::addRule(const QString &patternStr, const QTextCharFormat format)
{
    HighLighterRule rule;

    rule.format = format;
    rule.pattern = QRegExp(patternStr);

    rules.append(rule);
}

void HighLighter::findAndSetFormat(const int begin, const QString &word)
{
    bool isFound = false;
    foreach(const HighLighterRule &rule, rules)
    {
        if(rule.pattern.exactMatch(word))
        {
            setFormat(begin, word.length(), rule.format);
            isFound = true;
            break;
        }
    }

    if(!isFound) setFormat(begin, word.length(), rules.last().format);
}
