#ifndef TRINITY_DEF_TEMPEVENTMGR_H
#define TRINITY_DEF_TEMPEVENTMGR_H

struct EventLocation
{
    uint32 mapId;
    uint32 zoneId;
    float x;
    float y;
    float z;
    float orientation;
};

enum EventStatus
{
    EVENT_STATUS_INACTIVE         = 0,
    EVENT_STATUS_ACTIVE           = 1,
    EVENT_STATUS_IN_PROGRESS      = 2,
    EVENT_STATUS_FINISHED         = 3,
};

enum PlayerLimit
{
    PLAYER_LIMIT_NOT_SET          = -1,
    PLAYER_LIMIT_DEFAULT          = 0,
};

class TempEventMgr
{
public:

    TempEventMgr();
    ~TempEventMgr() {};

    void ResetEvent();

    typedef std::set<Player*> EventParticipants;
    uint32 GetEventParticipantCount() const { return m_EventParticipants.size(); }

    bool AddEventLocation(uint32 mapId, uint32 zoneId, float x, float y, float z, float orientation);
    void DeleteEventLocation() { eventLoc.mapId = 0; eventLoc.zoneId = 0; eventLoc.x = 0;eventLoc.y = 0;eventLoc.z = 0; eventLoc.orientation = 0; }
    bool HasEventLocation() { return eventLoc.x != 0.0f && eventLoc.y != 0.0f && eventLoc.z != 0.0f; }

    void AddPlayerToEvent(Player* player);
    void RemovePlayerFromEvent(Player* player, bool sendNotification);

    int32 GetPlayerLimit() { return m_PlayerLimit; }
    void SetPlayerLimit(int32 playerLimit) { m_PlayerLimit = playerLimit; }
    bool HasPlayerLimit() { return m_PlayerLimit > 0; }

    bool TeleportPlayersToEvent(Player* pInvoker);
    bool TeleportPlayersToEntryPoint(Player* pInvoker);

    uint32 GetEventStatus() { return m_EventStatus; }
    void SetEventStatus(Player* pInvoker, uint32 eventStatus);

    void SendEventInfoString(Player* pInvoker);

private:

    EventParticipants m_EventParticipants;

    EventLocation eventLoc;
    
    uint32 m_EventStatus;
    int32 m_PlayerLimit;

    std::string m_EventName;
};

#define sTempEventMgr ACE_Singleton<TempEventMgr, ACE_Null_Mutex>::instance()

#endif
