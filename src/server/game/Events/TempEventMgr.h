#ifndef TRINITY_DEF_TEMPEVENTMGR_H
#define TRINITY_DEF_TEMPEVENTMGR_H

#include "Player.h"

struct EventLocation
{
    uint32 mapId;
    float x;
    float y;
    float z;
    float orientation;
};

enum EventStatus
{
    EVENT_STATUS_INACTIVE         = 0,
    EVENT_STATUS_ACTIVE           = 1
};

class TempEventMgr
{
public:

    TempEventMgr();
    ~TempEventMgr() {};

    void ActiveEvent();
    void DisableEvent();

    typedef std::set<Player*> EventParticipants;
    //EventParticipants const& GetEventParticipantsForEvent(

    typedef std::list<EventLocation> TempEventLocation;

    bool AddEventLocation(uint32 mapId, float x, float y, float z, float orientation);
    void DeleteEventLocation();

    void AddPlayerToEvent(Player* player);
    void DeletePlayerFromEvent(Player* player);

    void TeleportPlayersToEvent();

    uint32 GetEventStatus() const            { return m_EventStatus; }
    void SetEventStatus(uint32 eventStatus) { m_EventStatus = eventStatus; }

private:

    EventParticipants m_EventParticipants;

    EventLocation eventLoc;
    
    uint32 m_EventStatus;
};

#define sTempEventMgr ACE_Singleton<TempEventMgr, ACE_NULL_MUTEX>::instance()

#endif
