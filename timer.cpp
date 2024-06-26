#include "timer.h"

Timer::Timer(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Timer::updateTimer);
}

void Timer::startTimer(int minutes, int seconds)
{
    remainingTime = QTime(0, minutes, seconds);
    timer->start(1000);
    emit timerUpdated(remainingTime.toString("mm:ss"));
}

void Timer::stopTimer()
{
    timer->stop();
}

void Timer::updateTimer()
{
    if (remainingTime == QTime(0, 0, 0)) {
        timer->stop();
        emit timerFinished();
    } else {
        remainingTime = remainingTime.addSecs(-1);
        emit timerUpdated(remainingTime.toString("mm:ss"));
    }
}
