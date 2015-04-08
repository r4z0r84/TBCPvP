#ifndef TRINITY_DEF_ANTICHEATMGR_H
#define TRINITY_DEF_ANTICHEATMGR_H

#include "Common.h"
#include "SharedDefines.h"
#include "AnticheatData.h"
#include "Chat.h"

class AnticheatData;

enum DetectionTypes
{
	SPEED_HACK_DETECTION = 1
};

// GUIDLow is the key
typedef std::map<uint32, AnticheatData> AnticheatPlayersDataMap;

class AnticheatMgr
{
public:
    AnticheatMgr() {};
    ~AnticheatMgr();

    void HandlePlayerLogin(Player* player);
    void HandlePlayerLogout(Player* player);

    void StartHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode);
    void SpeedHackDetection(Player* player, MovementInfo movementInfo);

private:
    AnticheatPlayersDataMap m_Players;

};

#define sAnticheatMgr ACE_Singleton<AnticheatMgr, ACE_Null_Mutex>::instance()

#endif
