#pragma once

#include <QTextBlock>
#include <QPainter>
#include <QPaintEvent>
#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
public:
    CodeEditor(QWidget *parent = nullptr);

    void lineNumbersPaintEvent(QPaintEvent *event);
    int lineNumbersWidth();
    void resizeEvent(QResizeEvent *e);

private slots:
    void updateLineNumbersWidth(int blockCount);
    void highlightCurrentLine();
    void updateLineNumbers(const QRect &, int);

private:
    QWidget *lineNumbers;
};
