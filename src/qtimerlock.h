#ifndef QTIMERLOCK_H
#define QTIMERLOCK_H

#include <QTimer>

//Class for locking the QTimer at the beginning and unlocking at the end of the scope
class QTimerLock
{
public:
    explicit QTimerLock(QTimer *timer);
    void disable();
    void enable();
    ~QTimerLock();
private:
    bool m_timerActive;
    QTimer *m_timer;
};

#endif // QTIMERLOCK_H
