#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal=0.0;
bool divTrigger=false;
bool multTrigger=false;
bool addTrigger=false;
bool subTrigger=false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton* numButtons[10];

    for(int i = 0 ; i < 10 ; ++i)
    {
        QString butName = "Button" + QString::number(i);
        numButtons[i]= MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()),this,
                SLOT(NumPressed()));
    }
    connect(ui->Add,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals,SIGNAL(released()),this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeSign,SIGNAL(released()),this,
            SLOT(ChangeNumberSign()));

    connect(ui->Clear,SIGNAL(released()),this,
            SLOT(ClearAll()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString butVal = button->text();
    QString displayVal = ui->Display->text();

    if (displayVal == "0" || calcVal != 0.0)
    {
        ui->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        ui->Display->setText(newVal);
    }
}
void MainWindow::MathButtonPressed()
{

    divTrigger=false;
    multTrigger=false;
    addTrigger=false;
    subTrigger=false;
    QString displayVal = ui->Display->text();
    calcVal=displayVal.toDouble();
    QPushButton *button=(QPushButton*) sender();
    QString butVal=button->text();
    if (QString::compare(butVal, QString("/"), Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if (QString::compare(butVal, QString("*"), Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }
    else if (QString::compare(butVal, QString("+"), Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else if (QString::compare(butVal, QString("-"), Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
}
void MainWindow::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if (addTrigger)
    {
        solution = calcVal + dblDisplayVal;
    }
    else if (subTrigger)
    {
        solution = calcVal - dblDisplayVal;
    }
    else if (multTrigger)
    {
        solution = calcVal * dblDisplayVal;
    }
    else if (divTrigger && dblDisplayVal != 0.0)
    {
        solution = calcVal / dblDisplayVal;
    }

    // Reset calcVal after calculation
    calcVal = 0.0;

    // Update the display with the result
    ui->Display->setText(QString::number(solution));
}
void MainWindow::ChangeNumberSign()
{
  QString displayVal = ui->Display->text();
  QRegExp reg("[-]?[0-9.]*");
  if(reg.exactMatch(displayVal))
  {
      double dblDisplayVal=displayVal.toDouble();
      double dblDisplayValSign=-1*dblDisplayVal;
      ui->Display->setText(QString::number(dblDisplayValSign));
  }
}

void MainWindow::ClearAll()
{
    ui->Display->setText("0"); // Reset the display to 0
    calcVal = 0.0; // Reset calculation value
    divTrigger = false; // Reset triggers
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
}
