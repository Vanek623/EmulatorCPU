#include "linenumbersarea.h"

LineNumbersArea::LineNumbersArea(QWidget *parent) : QWidget (parent)
{
    lineCount = 1;
    startLine = 0;
    maxWidth = lineNumbersWidth(9999);

    setStyles();
}

QSize LineNumbersArea::sizeHint() const
{
    return QSize(maxWidth, 0);
}

void LineNumbersArea::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::lightGray);
    painter.setPen(Qt::black);

    //updateWidth(lineCount);

    for(int i=0; i<lineCount; i++)
    {
        QString number = QString::number(i + 1 + startLine);
        painter.drawText(0, 3 + i*fontMetrics().height(), this->width(), fontMetrics().height(), Qt::AlignRight, number);
    }
}

void LineNumbersArea::updateNumberCounts(int lineCount)
{
    this->lineCount = lineCount;
    this->update();
}

void LineNumbersArea::updateLineNumbers(int scrollValue)
{
    startLine = scrollValue;
    this->update();
}

int LineNumbersArea::lineNumbersWidth(int lineCount) const
{
    int digits = 1;
    int max = qMax(1, lineCount);

    while (max >= 10)
    {
        max /= 10;
        digits++;
    }

    int space = 3 + fontMetrics().averageCharWidth() * digits;

    return space;
}

void LineNumbersArea::setStyles()
{
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);

    this->setFont(font);

    this->setStyleSheet("font-size: 14px;");
    this->setMinimumWidth(10);
}
