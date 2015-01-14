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
    uint32 GetEventParticipants() const { return m_EventParticipants.size(); }

    typedef std::list<EventLocation> TempEventLocation;

    bool AddEventLocation(uint32 mapId, float x, float y, float z, float orientation);
    void DeleteEventLocation();

    void AddPlayerToEvent(Player* player);
    void DeletePlayerFromEvent(Player* player);

    uint32 GetPlayerLimit() { return m_PlayerLimit; }
    void SetPlayerLimit(uint32 playerLimit) { m_PlayerLimit = playerLimit; }
    bool HasPlayerLimit() { return m_PlayerLimit; }

    void TeleportPlayersToEvent();

    uint32 GetEventStatus() { return m_EventStatus; }
    void SetEventStatus(uint32 eventStatus) { m_EventStatus = eventStatus; }

private:

    EventParticipants m_EventParticipants;

    EventLocation eventLoc;
    
    uint32 m_EventStatus;
    uint32 m_PlayerLimit;
};

#define sTempEventMgr ACE_Singleton<TempEventMgr, ACE_NULL_MUTEX>::instance()

#endif
