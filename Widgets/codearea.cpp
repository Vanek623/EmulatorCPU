#include "codearea.h"

CodeArea::CodeArea(QWidget *parent) : QPlainTextEdit (parent)
{
    connect(this, SIGNAL(blockCountChanged(int)), this, SIGNAL(lineCountChanged(int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SIGNAL(viewPointChanged(int)));

    //highlightCurrentLine();

    highlighter = new HighLighter(this->document());

    setStyles();

    this->setMaximumBlockCount(998);
    this->setPalette(QPalette(QColor(Qt::black)));
}

void CodeArea::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if(!isReadOnly())
    {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::gray).lighter(50);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);

    emit viewPointChanged(this->verticalScrollBar()->value());
}

void CodeArea::setStyles()
{
    QFont font;
    font.setFamily("Courier");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);

    this->setFont(font);
}
