#pragma once

#include <QWidget>
#include "codeeditor.h"

class LineNumbers : public QWidget
{
public:
    LineNumbers(CodeEditor *editor);

    QSize sizeHint() const override;
    void paintEvent(QPaintEvent *event) override;

private:
    CodeEditor *codeEditor;
};
