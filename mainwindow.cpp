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
    connect(alarm, &Alarm::alarmsUpdated, this, &MainWindow::updateAlarmList);
    connect(alarm, &Alarm::alarmStopped, this, &MainWindow::highlightActiveAlarm);

    timer = new Timer(this);
    connect(timer, &Timer::timerUpdated, this, &MainWindow::updateTimer);
    connect(timer, &Timer::timerFinished, this, &MainWindow::timerFinished);

    connect(ui->addAlarmButton, &QPushButton::clicked, this, &MainWindow::addAlarm);
    connect(ui->removeAlarmButton, &QPushButton::clicked, this, &MainWindow::removeAlarm);
    connect(ui->resetAlarmButton, &QPushButton::clicked, this, &MainWindow::resetAlarm);
    connect(ui->startTimerButton, &QPushButton::clicked, this, &MainWindow::startTimer);

    updateAlarmList();
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
    ui->alarmStatusLabel->setText("Time's up!!!!!");
    playSound("qrc:/sounds/kierwa.mp3");
}

void MainWindow::updateTimer(const QString &time)
{
    ui->timerStatusLabel->setText(time);
}

void MainWindow::timerFinished()
{
    ui->timerStatusLabel->setText("Time's up!!!!!");
    playSound("qrc:/sounds/ohh_bro.mp3");
}

void MainWindow::addAlarm()
{
    alarm->addAlarm(ui->alarmTimeEdit->time());
}

void MainWindow::removeAlarm()
{
    int currentIndex = ui->alarmListWidget->currentRow();
    if (currentIndex != -1) {
        alarm->removeAlarm(currentIndex);
    }
}

void MainWindow::resetAlarm()
{
    ui->alarmStatusLabel->setText("Alarm");
    alarm->resetAlarm();
}

void MainWindow::updateAlarmList()
{
    ui->alarmListWidget->clear();
    QList<QDateTime> alarms = alarm->getAlarms();
    for (const QDateTime &alarmTime : alarms) {
        ui->alarmListWidget->addItem(alarmTime.toString("hh:mm:ss (dd-MM-yyyy)"));
    }
}

void MainWindow::highlightActiveAlarm()  // podswietlanie wykonanych alarmow, do dokonczenia
{
    for (int i = 0; i < ui->alarmListWidget->count(); ++i) {
        QListWidgetItem *item = ui->alarmListWidget->item(i);
        item->setBackground(Qt::green);
    }
}

void MainWindow::startTimer()
{
    int minutes = ui->timerMinutesSpinBox->value();
    int seconds = ui->timerSecondsSpinBox->value();
    timer->startTimer(minutes, seconds);
}

void MainWindow::playSound(const QString path) // tu jest problem nakladajacych sie dzwiekow, play sound twozy caly czas nowe obiekty
{
    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl(path));
    audioOutput->setVolume(50);
    player->play();
}
