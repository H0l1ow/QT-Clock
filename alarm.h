#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QList>

class Alarm : public QObject
{
    Q_OBJECT

public:
    explicit Alarm(QObject *parent = nullptr);
    void addAlarm(const QTime &time);
    void removeAlarm(int index);
    void resetAlarm();
    QList<QDateTime> getAlarms() const;

signals:
    void alarmRinging();
    void alarmsUpdated();
    void alarmStopped();

private slots:
    void checkAlarms();

private:
    QTimer *timer;
    QList<QDateTime> alarmTimes;
    int activeAlarmIndex;
};

#endif // ALARM_H
