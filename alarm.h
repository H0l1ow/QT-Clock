#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Alarm : public QObject
{
    Q_OBJECT

public:
    explicit Alarm(QObject *parent = nullptr);
    void setAlarmTime(const QTime &time);
    QTime getAlarmTime() const;

signals:
    void alarmRinging();

private slots:
    void checkAlarm();

private:
    QTimer *timer;
    QTime alarmTime;
};

#endif // ALARM_H
