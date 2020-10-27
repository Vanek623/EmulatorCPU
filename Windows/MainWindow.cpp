#include "MainWindow.h"

MainWindow::MainWindow()
{
    setupUI();
}

MainWindow::~MainWindow()
{}

void MainWindow::compile(){
    cpuWidget->compileProg(codeEditor->getProgrammText());
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

void MainWindow::loadFile()
{
    QString filePath = QFileDialog::getOpenFileName();

    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            codeEditor->setProgrammText(stream.readAll());
            file.close();
        }
    }
}

void MainWindow::saveFile()
{
    QString filePath = QFileDialog::getOpenFileName();

    if(!filePath.isEmpty())
    {
        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << codeEditor->getProgrammText();
            file.close();
        }
    }
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
    layoutH->addWidget(codeEditor);

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
    QAction *loadFileBtn = new QAction("Load");
    QAction *saveFileBtn = new QAction("Save");

    tools->addAction(compileBtn);
    tools->addAction(runBtn);
    tools->addAction(nextBtn);
    tools->addAction(resetBtn);
    tools->addAction(loadFileBtn);
    tools->addAction(saveFileBtn);

    connect(compileBtn, SIGNAL(triggered()), this, SLOT(compile()));
    connect(runBtn, SIGNAL(triggered()), this, SLOT(run()));
    connect(nextBtn, SIGNAL(triggered()), this, SLOT(next()));
    connect(resetBtn, SIGNAL(triggered()), this, SLOT(reset()));
    connect(loadFileBtn, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(saveFileBtn, SIGNAL(triggered()), this, SLOT(saveFile()));

    addToolBar(Qt::TopToolBarArea, tools);
}

void MainWindow::setupTextArea()
{
    codeEditor = new CodeEditor(this);
    //progTxt->setPlainText("MOV1 1 1\nMOV1 2 2\nADD1 1 2");
    codeEditor->setMaximumWidth(300);
}

QLabel *MainWindow::createTitle(const QString &title)
{
    QLabel *tmpLbl = new QLabel(title);
    tmpLbl->setAlignment(Qt::AlignHCenter);
    tmpLbl->setStyleSheet("color: blue");

    return tmpLbl;
}
