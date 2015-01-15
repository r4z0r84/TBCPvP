#ifndef TRINITY_DEF_TEMPEVENTMGR_H
#define TRINITY_DEF_TEMPEVENTMGR_H

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

    bool AddEventLocation(uint32 mapId, float x, float y, float z, float orientation);
    void DeleteEventLocation() { eventLoc.mapId = 0; eventLoc.x = 0;eventLoc.y = 0;eventLoc.z = 0; eventLoc.orientation = 0; }
    bool HasEventLocation() { return eventLoc.x != 0.0f && eventLoc.y != 0.0f && eventLoc.z != 0.0f; }

    void AddPlayerToEvent(Player* player);
    void RemovePlayerFromEvent(Player* player);

    uint32 GetPlayerLimit() { return m_PlayerLimit; }
    void SetPlayerLimit(uint32 playerLimit) { m_PlayerLimit = playerLimit; }
    bool HasPlayerLimit() { return m_PlayerLimit; }

    bool TeleportPlayersToEvent();

    uint32 GetEventStatus() { return m_EventStatus; }
    void SetEventStatus(uint32 eventStatus) { m_EventStatus = eventStatus; }

private:

    EventParticipants m_EventParticipants;

    EventLocation eventLoc;
    
    uint32 m_EventStatus;
    uint32 m_PlayerLimit;
};

#define sTempEventMgr ACE_Singleton<TempEventMgr, ACE_Null_Mutex>::instance()

#endif
