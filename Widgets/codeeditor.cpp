#include "codeeditor.h"

void CodeEditor::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    lineArea->update();
}

CodeEditor::CodeEditor(QWidget *parent) : QWidget(parent)
{
    codeArea = new CodeArea(this);
    lineArea = new LineNumbersArea(this);

    connect(codeArea, SIGNAL(lineCountChanged(int)), lineArea, SLOT(updateNumberCounts(int)));
    connect(codeArea, SIGNAL(viewPointChanged(int)), lineArea, SLOT(updateLineNumbers(int)));

    QHBoxLayout *layout = new QHBoxLayout(this);

    layout->setMargin(0);
    layout->setSpacing(2);

    layout->addWidget(lineArea);
    layout->addWidget(codeArea);

    this->setLayout(layout);
}

QString CodeEditor::getProgrammText() const
{
    return codeArea->toPlainText();
}

void CodeEditor::setProgrammText(const QString &text)
{
    codeArea->setPlainText(text);
}
