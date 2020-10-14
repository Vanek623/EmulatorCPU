#include "MainWindow.h"

MainWindow::MainWindow()
{
    setupUI();
}

MainWindow::~MainWindow()
{}

void MainWindow::compile(){
    cpuWidget->compileProg(progTxt->toPlainText());
}

void MainWindow::run(){
    cpuWidget->runProg();
}

void MainWindow::next(){
    cpuWidget->nextCom();
}

void MainWindow::reset(){
    cpuWidget->resetData();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    cpuWidget->resizeTables();
}

void MainWindow::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    cpuWidget->resizeTables();
}

void MainWindow::setupUI(){
    setMinimumSize(800, 600);
    setWindowTitle("RISC emulator");

    this->setCentralWidget(new QWidget());
    QHBoxLayout *layoutH = new QHBoxLayout();

    setupTextArea();
    layoutH->addWidget(progTxt);

    cpuWidget = new VMWidget();
    layoutH->addWidget(cpuWidget);

    this->centralWidget()->setLayout(layoutH);

    setupControls();
}

void MainWindow::setupControls()
{
    tools = new QToolBar("Programm");

    QAction *compileBtn = new QAction("Compile");
    QAction *runBtn = new QAction("Run");
    QAction *nextBtn = new QAction("Next");
    QAction *resetBtn = new QAction("Reset");

    tools->addAction(compileBtn);
    tools->addAction(runBtn);
    tools->addAction(nextBtn);
    tools->addAction(resetBtn);

    connect(compileBtn, SIGNAL(triggered()), this, SLOT(compile()));
    connect(runBtn, SIGNAL(triggered()), this, SLOT(run()));
    connect(nextBtn, SIGNAL(triggered()), this, SLOT(next()));
    connect(resetBtn, SIGNAL(triggered()), this, SLOT(reset()));

    addToolBar(Qt::TopToolBarArea,tools);
}

void MainWindow::setupTextArea()
{
    progTxt = new QTextEdit();
    progTxt->setText("MOV1 1 1\nMOV1 2 2\nADD1 1 2");
    progTxt->setMaximumWidth(300);
}

QLabel *MainWindow::createTitle(const QString &title)
{
    QLabel *tmpLbl = new QLabel(title);
    tmpLbl->setAlignment(Qt::AlignHCenter);
    tmpLbl->setStyleSheet("color: blue");

    return tmpLbl;
}
