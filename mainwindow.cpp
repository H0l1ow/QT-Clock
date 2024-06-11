#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");

    time_text[8] = (time.second() % 2 == 0 ? ' ' : ':');
    /*
    if ((time.second() % 2 == 0))
    {
        time_text[8] = ' ';
    }
    */
    ui->Digital_clock->setText(time_text);
}


// just for development commit
