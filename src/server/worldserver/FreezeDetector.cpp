#include "FreezeDetector.h"

FreezeDetectorRunnable::FreezeDetectorRunnable()
{
    m_loops      = 0;
    w_loops      = 0;
    m_lastchange = 0;
    w_lastchange = 0;
    _delayTime   = 0;
}

void FreezeDetectorRunnable::run()
{
    if (!_delayTime)
        return;
    
    while (!World::IsStopped())
    {
        ACE_Based::Thread::Sleep(1000);
        uint32 curtime = getMSTime();
        // normal work
        if (w_loops != World::m_worldLoopCounter)
        {
            w_lastchange = curtime;
            w_loops = World::m_worldLoopCounter;
        }
        // possible freeze
        else if (getMSTimeDiff(w_lastchange, curtime) > _delayTime)
        {
            sLog->outError("FreezeDetector: Hanging! Kicking out server!");
            *((uint32 volatile*)NULL) = 0;          // bang crash
        }
    }
}