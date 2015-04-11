#ifndef TRINITY_DEF_ANTICHEATMGR_H
#define TRINITY_DEF_ANTICHEATMGR_H

#include "Common.h"
#include "SharedDefines.h"
#include "AnticheatData.h"
#include "Chat.h"

class AnticheatData;

enum ReportTypes
{
    SPEED_HACK_REPORT = 0,
    FLY_HACK_REPORT,
    WALK_WATER_HACK_REPORT,
    TELEPORT_HACK_REPORT,
    JUMP_HACK_REPORT,
    TELEPORTPLANE_HACK_REPORT,
    CLIMB_HACK_REPORT,
    MAELSTROM_FLY_HACK_REPORT
};

enum DetectionTypes
{
    SPEED_HACK_DETECTION         = 1,
    FLY_HACK_DETECTION           = 2,
    WALK_WATER_HACK_DETECTION    = 3,
    TELEPORT_HACK_DETECTION      = 4,
    JUMP_HACK_DETECTION          = 5,
    TELEPORTPLANE_HACK_DETECTION = 6,
    CLIMB_HACK_DETECTION         = 7
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

private:
    void SpeedHackDetection(Player* player, MovementInfo movementInfo);
    void FlyHackDetection(Player* player, MovementInfo movementInfo);
    void WalkOnWaterHackDetection(Player* player, MovementInfo movementInfo);
    void TeleportHackDetection(Player* player, MovementInfo movementInfo);
    void JumpHackDetection(Player* player, MovementInfo movementInfo, uint32 opcode);
    void TeleportPlaneHackDetection(Player* player, MovementInfo movementInfo);
    void ClimbHackDetection(Player *player, MovementInfo movementInfo, uint32 opcode);

    void BuildReport(Player* player,uint8 reportType);

    AnticheatPlayersDataMap m_Players;
};

#define sAnticheatMgr ACE_Singleton<AnticheatMgr, ACE_Null_Mutex>::instance()

#endif
