#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Alarm::checkAlarm);
    timer->start(1000);
}

void Alarm::setAlarmTime(const QTime &time)
{
    alarmTime = time;
}

QTime Alarm::getAlarmTime() const
{
    return alarmTime;
}

void Alarm::checkAlarm()
{
    if (QTime::currentTime() >= alarmTime && alarmTime.isValid()) {
        emit alarmRinging();
    }
}
