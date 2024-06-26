#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTime>
#include <QTimer>

class Clock : public QObject
{
    Q_OBJECT

public:
    explicit Clock(QObject *parent = nullptr);
    QString getCurrentTime() const;

signals:
    void timeChanged(const QString &time);

private slots:
    void updateTime();

private:
    QTimer *timer;
};

#endif // CLOCK_H
