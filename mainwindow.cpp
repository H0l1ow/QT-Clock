#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    clock = new Clock(this);
    connect(clock, &Clock::timeChanged, this, &MainWindow::updateClock);

    alarm = new Alarm(this);
    connect(alarm, &Alarm::alarmRinging, this, &MainWindow::handleAlarm);

    timer = new Timer(this);
    connect(timer, &Timer::timerUpdated, this, &MainWindow::updateTimer);
    connect(timer, &Timer::timerFinished, this, &MainWindow::timerFinished);

    connect(ui->setAlarmButton, &QPushButton::clicked, this, &MainWindow::setAlarm);
    connect(ui->startTimerButton, &QPushButton::clicked, this, &MainWindow::startTimer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClock(const QString &time)
{
    ui->Digital_clock->setText(time);
}

void MainWindow::handleAlarm()
{
    ui->alarmStatusLabel->setText("Alarm ringing!");
    // Tutaj możesz dodać dodatkowe działania, np. odtwarzanie dźwięku
}

void MainWindow::updateTimer(const QString &time)
{
    ui->timerStatusLabel->setText(time);
}

void MainWindow::timerFinished()
{
    ui->timerStatusLabel->setText("Time's up!");
    // Tutaj możesz dodać dodatkowe działania, np. odtwarzanie dźwięku
}

void MainWindow::setAlarm()
{
    alarm->setAlarmTime(ui->alarmTimeEdit->time());
    ui->alarmStatusLabel->setText("Alarm set for " + alarm->getAlarmTime().toString("hh:mm:ss"));
}

void MainWindow::startTimer()
{
    int minutes = ui->timerMinutesSpinBox->value();
    int seconds = ui->timerSecondsSpinBox->value();
    timer->startTimer(minutes, seconds);
}
