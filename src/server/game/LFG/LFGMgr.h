#ifndef __LFGMGR_H
#define __LFGMGR_H

class LFGMgr
{
public:
    LFGMgr();
    ~LFGMgr();

    void Update(uint32 diff);

private:
    // General variables
    uint32 m_QueueTimer;                               ///< used to check interval of update
};

#define sLFGMgr ACE_Singleton<LFGMgr, ACE_Null_Mutex>::instance()
#endif