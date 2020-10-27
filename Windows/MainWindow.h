#pragma once

#include <QDebug>

#include <QFile>
#include <QLabel>
#include <QObject>
#include <QToolBar>
#include <QAction>
#include <QString>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPlainTextEdit>

#include "vmwidget.h"
//#include "codeeditor_old.h"
#include "codeeditor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    CodeEditor *codeEditor;
    VMWidget *cpuWidget;
    QHBoxLayout *mainLayout;
    QToolBar *tools;

public:
    explicit MainWindow();
    ~MainWindow();

private slots:
    void compile();
    void run();
    void next();
    void reset();
    void loadFile();
    void saveFile();

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

private:
    void setupUI();
    void setupControls();
    void setupTextArea();
    QLabel *createTitle(const QString &title);
};

