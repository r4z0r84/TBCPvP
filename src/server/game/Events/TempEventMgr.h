#ifndef TRINITY_DEF_TEMPEVENTMGR_H
#define TRINITY_DEF_TEMPEVENTMGR_H

#include "Player.h"

struct EventLocation
{
    uint32 eventEntry;
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

    TempEventMgr() {};
    ~TempEventMgr() {};

    void AddEvent(uint32 eventEntry);
    void DeleteEvent(uint32 eventEntry);

    typedef std::set<uint16> ActiveTempEvents;
    ActiveTempEvents const& GetActiveTempEventList() const { return m_ActiveTempEvents; }

    typedef std::map<uint32, EventLocation> TempEventLocation;
    TempEventLocation const& GetTempEventLocationMap() const { return m_TempEventLocation; }

    bool AddEventLocation(uint32 eventEntry, uint32 mapId, float x, float y, float z, float orientation);
    void DeleteEventLocation(uint32 eventEntry);

    void AddPlayerToEvent(uint32 eventEntry, Player* player);
    void DeletePlayerFromEvent(uint32 eventEntry, Player* player);

    uint32 GetEventStatus() const            { return m_EventStatus; }
    void SetEventStatus(uint32 eventStatus) { m_EventStatus = eventStatus; }

private:

    ActiveTempEvents m_ActiveTempEvents;
    TempEventLocation m_TempEventLocation;

    uint32 m_EventStatus;

};

#define sTempEventMgr ACE_Singleton<TempEventMgr, ACE_NULL_MUTEX>::instance()

#endif
