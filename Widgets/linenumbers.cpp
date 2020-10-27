#include "linenumbers.h"

LineNumbers::LineNumbers(CodeEditor* editor) : QWidget (editor)
{
    this->codeEditor = editor;
}

QSize LineNumbers::sizeHint() const
{
    return QSize(codeEditor->lineNumbersWidth(), 0);
}

void LineNumbers::paintEvent(QPaintEvent *event)
{
    codeEditor->lineNumbersPaintEvent(event);
}
