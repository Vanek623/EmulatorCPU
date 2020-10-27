#pragma once
#include <QWidget>
#include <QHBoxLayout>

#include "linenumbersarea.h"
#include "codearea.h"

class CodeEditor : public QWidget
{
    Q_OBJECT
private:
    LineNumbersArea *lineArea;
    CodeArea *codeArea;

protected:
    void paintEvent(QPaintEvent *event);

public:
    explicit CodeEditor(QWidget *parent = nullptr);

    QString getProgrammText() const;
    void setProgrammText(const QString &text);
};
