#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include "ramWidget.h"
#include "regsWidget.h"
#include "resultwindow.h"

#include "controlunit.h"
#include "builder.h"

#include "cpuconsts.h"


class VMWidget : public QWidget
{
private:
    RegsWidget *regs;
    RamWidget *progRam;
    RamWidget *dataRam;
    QVBoxLayout *mainLayout;

    ControlUnit *cpu;
    ResultWindow *resultWindow;

public:
    VMWidget();
    ~VMWidget();

    void resizeTables();

    void compileProg(const QString &progTxt);
    void runProg();
    void nextCom();
    void resetData();

private:
    void setupUI();
    void setupRegs();
    void setupRams();
};
