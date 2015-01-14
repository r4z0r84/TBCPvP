#include "TempEventMgr.h"
#include "Player.h"
#include "MapManager.h"

TempEventMgr::TempEventMgr()
{
    m_EventParticipants.clear();
}

void TempEventMgr::ActiveEvent()
{
    // Clear participants list on initialize
    m_EventParticipants.clear();
}

void TempEventMgr::DisableEvent()
{
    // Clear participants list on delete
   m_EventParticipants.clear();
}

bool TempEventMgr::AddEventLocation(uint32 mapId, float x, float y, float z, float orientation)
{
    eventLoc.mapId          = mapId;
    eventLoc.x              = x;
    eventLoc.y              = y;
    eventLoc.z              = z;
    eventLoc.orientation    = orientation;

    if (!sMapMgr->IsValidMapCoord(eventLoc.mapId, eventLoc.x, eventLoc.y, eventLoc.z))
    {
        // Not valid map coords
        return false;
    }

    return true;
}

void TempEventMgr::DeleteEventLocation()
{
    eventLoc.mapId          = 0;
    eventLoc.x              = 0;
    eventLoc.y              = 0;
    eventLoc.z              = 0;
    eventLoc.orientation    = 0; 
}

void TempEventMgr::AddPlayerToEvent(Player* player)
{
    if (m_EventParticipants.find(player) == m_EventParticipants.end())
        m_EventParticipants.insert(player);
}

void TempEventMgr::DeletePlayerFromEvent(Player* player)
{
    EventParticipants::iterator iter = m_EventParticipants.find(player);
    if (iter == m_EventParticipants.end())
        return;

    m_EventParticipants.erase(iter);
}

void TempEventMgr::TeleportPlayersToEvent()
{
    for (EventParticipants::const_iterator itr = m_EventParticipants.begin(); itr != m_EventParticipants.end(); ++itr)
    {
        (*itr)->TeleportTo(eventLoc.mapId, eventLoc.x, eventLoc.y, eventLoc.z, eventLoc.orientation);
    }
}
