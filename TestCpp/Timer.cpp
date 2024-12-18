#include "Timer.h"


CTimer::CTimer()
{
    m_hTimer = NULL;
    m_mutexCount = 0;
}

CTimer:: ~CTimer()
{
    Stop();
}

bool CTimer::Start(unsigned int interval, bool immediately, bool once)
{
    if (m_hTimer)
    {
        return false;
    }

    SetCount(0);

    BOOL success = CreateTimerQueueTimer(&m_hTimer,
        NULL,
        TimerProc,
        this,
        immediately ? 0 : interval,
        once ? 0 : interval,
        WT_EXECUTEINTIMERTHREAD);

    return(success != 0);
}

void CTimer::Stop()
{
    DeleteTimerQueueTimer(NULL, m_hTimer, NULL);
    m_hTimer = NULL;
}

void CTimer::OnTimedEvent()
{
    if (m_pTimedFunction)
    {
        m_pTimedFunction();
    }
}

void CTimer::SetCount(int value)
{
    InterlockedExchange(&m_mutexCount, value);
}

int CTimer::GetCount()
{
    return InterlockedExchangeAdd(&m_mutexCount, 0);
}

void CTimer::SetTimedEvent(TimedFunction pFunc)
{
    m_pTimedFunction = pFunc;
}


///////////////////////////////////////////////////////////////////////////////
//
// TimerProc
//
void CALLBACK TimerProc(void* param, BOOLEAN timerCalled)
{
    CTimer* timer = static_cast<CTimer*>(param);
    timer->SetCount(timer->GetCount() + 1);
    timer->OnTimedEvent();
};
