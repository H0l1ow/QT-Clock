#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include "clock.h"
#include "alarm.h"
#include "timer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateClock(const QString &time);
    void handleAlarm();
    void updateTimer(const QString &time);
    void timerFinished();
    void addAlarm();
    void removeAlarm();
    void resetAlarm();
    void updateAlarmList();
    void highlightActiveAlarm();
    void startTimer();
    void playSound(const QString path);

private:
    Ui::MainWindow *ui;
    Clock *clock;
    Alarm *alarm;
    Timer *timer;
    QMediaPlayer* player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
};

#endif // MAINWINDOW_H
