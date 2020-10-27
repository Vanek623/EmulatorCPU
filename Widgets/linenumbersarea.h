#pragma once

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QDebug>

class LineNumbersArea : public QWidget
{
    Q_OBJECT
private:
    int lineCount;
    int startLine;
    int maxWidth;

public:
    LineNumbersArea(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    void linesPaintEvent(QPaintEvent *event);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void updateNumberCounts(int lineCount);
    void updateLineNumbers(int scrollValue);

private:
    int lineNumbersWidth(int lineCount) const;
    void setStyles();
    void updateWidth(int digit);
};
