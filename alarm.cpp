#include "alarm.h"

Alarm::Alarm(QObject *parent) : QObject(parent), activeAlarmIndex(-1)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Alarm::checkAlarms);
    timer->start(1000);
}

void Alarm::addAlarm(const QTime &time)
{
    QDateTime now = QDateTime::currentDateTime();
    QDateTime alarmDateTime = QDateTime(now.date(), time);

    if (alarmDateTime <= now) {
        alarmDateTime = alarmDateTime.addDays(1);
    }

    alarmTimes.append(alarmDateTime);
    emit alarmsUpdated();
}

void Alarm::removeAlarm(int index)
{
    if (index >= 0 && index < alarmTimes.size()) {
        alarmTimes.removeAt(index);
        emit alarmsUpdated();
    }
}

void Alarm::resetAlarm()
{
    if (activeAlarmIndex != -1) {
        alarmTimes.removeAt(activeAlarmIndex);
        activeAlarmIndex = -1;
        emit alarmStopped();
        emit alarmsUpdated();
    }
}

QList<QDateTime> Alarm::getAlarms() const
{
    return alarmTimes;
}

void Alarm::checkAlarms()
{
    QDateTime now = QDateTime::currentDateTime();
    for (int i = 0; i < alarmTimes.size(); ++i) {
        if (now >= alarmTimes[i] && alarmTimes[i].isValid()) {
            activeAlarmIndex = i;
            emit alarmRinging();
            break;
        }
    }
}
