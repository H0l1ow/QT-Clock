#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer(QObject *parent = nullptr);
    void startTimer(int minutes, int seconds);
    void stopTimer();

signals:
    void timerUpdated(const QString &time);
    void timerFinished();

private slots:
    void updateTimer();

private:
    QTimer *timer;
    QTime remainingTime;
};

#endif // TIMER_H
