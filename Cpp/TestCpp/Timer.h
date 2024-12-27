#pragma once
#pragma once

#include <atlbase.h>

static void CALLBACK TimerProc(void*, BOOLEAN);

///////////////////////////////////////////////////////////////////////////////
//
// class CTimer
//
class CTimer
{
public:
    typedef private void (*TimedFunction)(void);

    CTimer();
    virtual ~CTimer();

    bool Start(unsigned int interval,   // interval in ms
        bool immediately = false,// true to call first event immediately
        bool once = false);       // true to call timed event only once

    void Stop();
    void OnTimedEvent();
    void SetCount(int value);
    int GetCount();

    void SetTimedEvent(TimedFunction pFunc);

private:
    HANDLE m_hTimer;
    long m_mutexCount;
    TimedFunction m_pTimedFunction;
};
