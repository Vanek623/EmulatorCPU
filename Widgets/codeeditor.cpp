#include "codeeditor.h"
#include "linenumbers.h"

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit (parent)
{
    lineNumbers = new LineNumbers(this);

    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumbersWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumbers);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumbersWidth(0);
    highlightCurrentLine();
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
  QPlainTextEdit::resizeEvent(e);

  QRect cr = contentsRect();
  lineNumbers->setGeometry(QRect(cr.left(), cr.top(), lineNumbersWidth(), cr.height()));
}

void CodeEditor::lineNumbersPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumbers);
    painter.fillRect(event->rect(), Qt::lightGray);

    QTextBlock block = firstVisibleBlock();
    int blockNum = block.blockNumber();
    int top = static_cast<int>(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if(block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNum + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumbers->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(block).height());
        ++blockNum;
    }
}

int CodeEditor::lineNumbersWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());

    while (max >= 10)
    {
        max /= 10;
        digits++;
    }

    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEditor::updateLineNumbersWidth(int blockCount)
{
    Q_UNUSED(blockCount);

    setViewportMargins(lineNumbersWidth(), 0, 0, 0);
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumbers(const QRect &rect, int dy)
{
    if(dy)
    {
        lineNumbers->scroll(0, dy);
    }
    else
    {
        lineNumbers->update(0, rect.y(), lineNumbers->width(), rect.height());
    }

    if(rect.contains(viewport()->rect()))
    {
        updateLineNumbersWidth(0);

    }
}
