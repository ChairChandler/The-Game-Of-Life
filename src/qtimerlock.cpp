#include "qtimerlock.h"

QTimerLock::QTimerLock(QTimer *timer): m_timer(timer)
{
    m_timerActive = m_timer->isActive();

    if(m_timerActive)
        m_timer->stop();
}

void QTimerLock::disable()
{
    m_timerActive = false;
}

void QTimerLock::enable()
{
    m_timerActive = true;
}

QTimerLock::~QTimerLock()
{
    if(m_timerActive)
        m_timer->start();
}
