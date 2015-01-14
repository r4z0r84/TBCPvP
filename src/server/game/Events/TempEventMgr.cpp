#include "TempEventMgr.h"
#include "MapManager.h"

void TempEventMgr::AddEvent(uint32 eventEntry)
{
    // Adding Event to database
}

void TempEventMgr::DeleteEvent(uint32 eventEntry)
{
    // Delete Event from database
}

bool TempEventMgr::AddEventLocation(uint32 eventEntry, uint32 mapId, float x, float y, float z, float orientation)
{
    for (TempEventLocation::const_iterator itr = GetTempEventLocationMap().begin(); itr != GetTempEventLocationMap().end(); ++itr)
    {
        if (itr->first == eventEntry)
            return false;
    }

    EventLocation eventLoc;
    eventLoc.eventEntry     = eventEntry;
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

    m_TempEventLocation[eventEntry] = eventLoc;
    return true;
}

void TempEventMgr::DeleteEventLocation(uint32 eventEntry)
{
    // Delete teleport location from event
}

void TempEventMgr::AddPlayerToEvent(uint32 eventEntry, Player* player)
{
    // ques the player for the event
}

void TempEventMgr::DeletePlayerFromEvent(uint32 eventEntry, Player* player)
{
    // deletes the player from the event
}