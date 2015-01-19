#ifndef TRINITY_DEF_FREEZEDETECTOR_H
#define TRINITY_DEF_FREEZEDETECTOR_H

#include "Common.h"

/// Start the server
class FreezeDetectorRunnable: public ACE_Based::Runnable
{
    public:
        FreezeDetectorRunnable();
        void run();
        void SetDelayTime(uint32 _newDelayTime) { _delayTime = _newDelayTime; }

    private:
        uint32 m_loops;
        uint32 m_lastchange;
        
        uint32 w_loops;
        uint32 w_lastchange;
        
        uint32 _delayTime;
};

#endif
