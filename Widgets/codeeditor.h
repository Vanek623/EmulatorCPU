#pragma once

#include <QTextBlock>
#include <QPainter>
#include <QPaintEvent>
#include <QPlainTextEdit>
#include "highlighter.h"

class CodeEditor : public QPlainTextEdit
{
private:
    QWidget *lineNumbers;
    HighLighter *highlighter;
public:
    CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor();

    void lineNumbersPaintEvent(QPaintEvent *event);
    int lineNumbersWidth();
    void resizeEvent(QResizeEvent *e);

private slots:
    void updateLineNumbersWidth(int blockCount);
    void highlightCurrentLine();
    void updateLineNumbers(const QRect &, int);
};
