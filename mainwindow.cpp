#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpression>

#include <QWidget> //mouse

double memoryVal = 0.0;
double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool isNewCalculation = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i= 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearButtonPressed()));
    connect(ui->MemAdd, SIGNAL(released()), this,
            SLOT(MemAddButtonPressed()));
    connect(ui->MemClear, SIGNAL(released()), this,
            SLOT(MemClearButtonPressed()));
    connect(ui->MemGet, SIGNAL(released()), this,
            SLOT(MemGetButtonPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if (isNewCalculation) {
        ui->Display->setText(butVal);
        isNewCalculation = false;
    } else {
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(butVal);
        } else {
            QString newVal = displayVal + butVal;
            ui->Display->setText(QString::number(newVal.toDouble(), 'g', 16));
        }
    }
}

void MainWindow::MathButtonPressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else     if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else     if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else     {
        subTrigger = true;
    }
    ui->Display->setText("");
}

void MainWindow::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if (addTrigger || subTrigger || multTrigger || divTrigger) {
        if (addTrigger) {
            solution = calcVal + dblDisplayVal;
        } else if (subTrigger) {
            solution = calcVal - dblDisplayVal;
        } else if (multTrigger) {
            solution = calcVal * dblDisplayVal;
        } else {
            solution = calcVal / dblDisplayVal;
        }
    }

    ui->Display->setText(QString::number(solution));
    isNewCalculation = true;
}

void MainWindow::ChangeNumberSign() {

    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);

    if(match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }

}

void MainWindow::MemAddButtonPressed() {
    memoryVal += ui->Display->text().toDouble();
    isNewCalculation = true;
}

void MainWindow::MemClearButtonPressed() {
    memoryVal = 0.0;
}

void MainWindow::MemGetButtonPressed() {
    ui->Display->setText(QString::number(memoryVal, 'g', 16));
    isNewCalculation = true;
}

void MainWindow::ClearButtonPressed()
{
    ui->Display->setText("");
}


void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}
