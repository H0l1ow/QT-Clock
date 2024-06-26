#include "clock.h"

Clock::Clock(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Clock::updateTime);
    timer->start(1000);
}

QString Clock::getCurrentTime() const
{
    return QTime::currentTime().toString("hh : mm : ss");
}

void Clock::updateTime()
{
    QString time_text = getCurrentTime();
    time_text[8] = (QTime::currentTime().second() % 2 == 0 ? ' ' : ':');
    emit timeChanged(time_text);
}
