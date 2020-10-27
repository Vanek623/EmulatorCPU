#pragma once

#include <QDebug>
#include <QScrollBar>
#include <QPlainTextEdit>

#include "highlighter.h"

class CodeArea : public QPlainTextEdit
{
    Q_OBJECT
private:
    HighLighter *highlighter;

public:
    CodeArea(QWidget *parent = nullptr);

signals:
    void lineCountChanged(int lineCount);
    void viewPointChanged(int);

private slots:
    void highlightCurrentLine();

private:
    void setStyles();
};
