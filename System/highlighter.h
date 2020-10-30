#pragma once

#include <QRegExp>
#include <QList>
#include <QTextDocument>
#include <QSyntaxHighlighter>

struct HighLighterRule
{
    QRegExp pattern;
    QTextCharFormat format;
};

class HighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
private:
    // first - comment
    // last - unknown
    QVector<HighLighterRule> rules;

public:
    HighLighter(QTextDocument *parent = NULL);

protected:
    void highlightBlock(const QString &text);

private:
    void setupPatterns();
    void setupCommands();

    void addRule(const QString &patternStr, const QTextCharFormat format);
    void findAndSetFormat(const int begin, const QString &word);
};
