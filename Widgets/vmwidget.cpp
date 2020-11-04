#include "vmwidget.h"

VMWidget::VMWidget()
{
    cpu = new ControlUnit();

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
    if(!progTxt.isEmpty())
    {
        Builder builder;
        int compileResult = builder.compile(progTxt);
        if(compileResult == -1){
            if(!cpu->Init(BinaryManager::loadBinary()))
            {
                QString compileResultStr = "Размер программы слишком большой!";
                QMessageBox::warning(this, "Ошибка", compileResultStr);
                return;
            }
            else
            {
                QString compileResultStr = "Компиляция прошла успешно!";
                QMessageBox::information(this, "Результат компиляции", compileResultStr);
            }

            progRam->updateContent(cpu->getProg());
        }
        else
        {
            QString compileResultStr = "Компиляция прошла неудачно!\nОшибка в "
                                  + QString::number(compileResult + 1) + " строке...";

            QMessageBox::warning(this, "Результат компиляции", compileResultStr);
        }
    }
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
