#include "vmwidget.h"

VMWidget::VMWidget()
{
    cpu = nullptr;
    resultWindow = nullptr;

    setupUI();
}

VMWidget::~VMWidget()
{
    delete cpu;
}

void VMWidget::resizeTables(){
    dataRam->resizeTable();
    progRam->resizeTable();
}

void VMWidget::compileProg(const QString &progTxt){
    Builder builder;
    int compileResult = builder.compile(progTxt);
    if(compileResult == -1){
        if(cpu != nullptr)
        {
            delete cpu;
            cpu = nullptr;
        }

        cpu = new ControlUnit(builder.getProgrammList());

        progRam->updateContent(cpu->getProg());
        //qDebug() << "OK";
    }

    if(resultWindow != nullptr)
    {
        delete resultWindow;
        resultWindow = nullptr;
    }

    resultWindow = new ResultWindow(this, compileResult);
    resultWindow->show();
}

void VMWidget::runProg(){
    while(cpu->Work());

    dataRam->updateContent(cpu->getData());
    regs->updateValues(cpu->getRegs());
}

void VMWidget::nextCom(){
    cpu->Work();
    dataRam->updateContent(cpu->getData());
    regs->updateValues(cpu->getRegs());
}

void VMWidget::resetData(){
    cpu->Reset();

    dataRam->updateContent(cpu->getData());
    regs->updateValues(cpu->getRegs());
}

void VMWidget::setupUI(){
    mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);

    setupRegs();
    setupRams();

    setLayout(mainLayout);
}

void VMWidget::setupRegs()
{
    QStringList regNames;
    regNames << "PC" << "Flags" << "H0" << "L1" << "R2" << "R3"  << "R4" << "I5" << "S6" << "B7";
    regs = new RegsWidget("Регистры общего назначения", regNames, 0);

    mainLayout->addWidget(regs);
}

void VMWidget::setupRams(){
    progRam = new RamWidget(3, PROG_SIZE, "Память команд", PROG);
    mainLayout->addWidget(progRam);

    dataRam = new RamWidget(1, DATA_SIZE, "Память данных", DATA);
    mainLayout->addWidget(dataRam);
}
