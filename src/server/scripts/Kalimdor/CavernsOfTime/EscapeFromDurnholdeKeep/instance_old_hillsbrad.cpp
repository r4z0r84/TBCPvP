 /*
  * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
  * Copyright (C) 2010-2012 Oregon <http://www.oregoncore.com/>
  * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
  * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
  * Copyright (C) 2012 Hufsa <isak.mortzell@gmail.com>
  *
  * This program is free software; you can redistribute it and/or modify it
  * under the terms of the GNU General Public License as published by the
  * Free Software Foundation; either version 2 of the License, or (at your
  * option) any later version.
  *
  * This program is distributed in the hope that it will be useful, but WITHOUT
  * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
  * more details.
  *
  * You should have received a copy of the GNU General Public License along
  * with this program. If not, see <http://www.gnu.org/licenses/>.
  */

/* ScriptData
SDName: Instance_Old_Hillsbrad
SD%Complete: 75
SDComment: If thrall escort fail, all parts will reset. In future, save sub-parts and continue from last known.
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

#include "ScriptPCH.h"
#include "old_hillsbrad.h"

#define THRALL_ENTRY        17876
#define TARETHA_ENTRY       18887
#define EPOCH_ENTRY         18096
#define DRAKE_ENTRY         17848
#define SKARLOC_ENTRY       17862
#define GO_ROARING_FLAME    182592
#define GO_THRALL_DOOR      184393

#define MAX_ENCOUNTERS      8

struct FireLoc
{
    float x;
    float y;
    float z;
    float orientation;
    float rotation2;
    float rotation3;
};

static FireLoc RoaringFlame[]=
{
    { 2157.28, 234.934, 53.8488,  1.72788, 0.760406,  0.649448 },
    { 2178.79, 254.287, 53.5769, -1.90241, 0.814116, -0.580703 },
    { 2150.41, 249.103, 53.8624, -0.76794, 0.374607, -0.927184 },
    { 2211.3,  246.804, 55.4124, -2.21657, 0.894934, -0.446198 },
    { 2119.77, 42.0842, 53.7686,  2.67035, 0.97237,   0.233445 },
    { 2081,    64.6541, 53.9115,  2.04204, 0.85264,   0.522499 },
    { 2064.9,  69.6156, 53.6659,  1.53589, 0.694658,  0.71934  },
    { 2070.08, 93.2598, 54.0862, -1.55334, 0.700909, -0.71325  },
    { 2073.39, 142.325, 54.4632, -2.98451, 0.996917, -0.078459 },
    { 2055.37, 111.925, 54.602,   2.42601, 0.936672,  0.350207 },
    { 2069.83, 106.7,   54.6518,  0.95993, 0.461749,  0.887011 },
    { 2086.59, 52.8431, 53.5683, -1.58825, 0.71325,  -0.700909 },
    { 2100.1,  42.5693, 53.575,   0.17453, 0.087156,  0.996195 },
    { 2228.1,  251.4,   55.5517, -0.54105, 0.267238, -0.96363  },
    { 2199.6,  271.738, 53.9931,  1.309,   0.608761,  0.793353 },
    { 2171.96, 262.641, 63.3226, -0.87266, 0.422618, -0.90630  },
    { 2176.22, 247.951, 53.9294,  0.59341, 0.292372,  0.956305 },
    { 2070.19, 80.9965, 64.3421,  1.09956, 0.522499,  0.85264  },
    { 2079.69, 74.5419, 53.7058, -0.15708, 0.078459, -0.996917 },
    { 2069.07, 124.392, 54.444,  -0.06981, 0.034899, -0.999391 },
    { 2118.76, 51.5617, 53.8408,  1.43117, 0.656059,  0.75471  },
    { 2100.35, 59.5064, 53.4081, -0.20944, 0.104528, -0.994522 },
    { 2202.69, 256.725, 62.7723, -1.88496, 0.809017, -0.587785 },
    { 2195.58, 257.778, 54.0599, -2.25148, 0.902585, -0.430511 }
};

struct instance_old_hillsbrad : public ScriptedInstance
{
    instance_old_hillsbrad(Map *map) : ScriptedInstance(map) { Initialize(); }

    uint32 Encounter[MAX_ENCOUNTERS];
    uint32 mBarrelCount;
    uint32 mThrallEventCount;

    uint64 ThrallGUID;
    uint64 ThrallDoorGUID;
    uint64 TarethaGUID;
    uint64 EpochGUID;

    void Initialize()
    {
        mBarrelCount        = 0;
        mThrallEventCount   = 0;
        ThrallGUID          = 0;
        ThrallDoorGUID      = 0;
        TarethaGUID         = 0;
        EpochGUID           = 0;

        for (uint8 i = 0; i < MAX_ENCOUNTERS; i++)
            Encounter[i] = NOT_STARTED;
    }

    Player* GetPlayerInMap()
    {
        Map::PlayerList const& players = instance->GetPlayers();

        if (!players.isEmpty())
        {
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                if (Player* plr = itr->getSource())
                    return plr;
            }
        }

        sLog->outDebug("TSCR: Instance Old Hillsbrad: GetPlayerInMap, but PlayerList is empty!");
        return NULL;
    }

    void OnCreatureCreate(Creature* creature)
    {
        switch (creature->GetEntry())
        {
            case THRALL_ENTRY:
                ThrallGUID = creature->GetGUID();
                break;
            case TARETHA_ENTRY:
                TarethaGUID = creature->GetGUID();
                break;
            case EPOCH_ENTRY:
                EpochGUID = creature->GetGUID();
                break;
        }
    }

    void OnGameObjectCreate(GameObject* go, bool add)
    {
        if (go->GetEntry() == GO_THRALL_DOOR)
            ThrallDoorGUID = go->GetGUID();
    }

    void SetData(uint32 type, uint32 data)
    {
        switch (type)
        {
            case TYPE_BARREL_DIVERSION:
            {
                if (data == IN_PROGRESS)
                {
                    if (mBarrelCount >= 5)
                        return;

                    ++mBarrelCount;
                    DoUpdateWorldState(WORLD_STATE_OH, mBarrelCount);

                    sLog->outDebug("Instance Old Hillsbrad: go_barrel_old_hillsbrad count %u", mBarrelCount);

                    Encounter[0] = IN_PROGRESS;

                    if (mBarrelCount == 5)
                    {
                        UpdateLodgeQuestCredit();
                        SetBuildingsOnFire();

                        if (Player* pPlayer = GetPlayerInMap())
                        {
                            Creature* drake = pPlayer->SummonCreature(DRAKE_ENTRY, 2128.43f, 71.01f, 64.42f, 1.74f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 1800000);
                            if (drake)
                            {
                                drake->Yell("You there, fetch water quickly! Get these flames out before the spread to the rest of the keep! Hurry, damn you!", 0, 0);
                                /*drake->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY,*/
                            }
                        }
                        else
                            sLog->outDebug("Instance Old Hillsbrad: SetData (Type: %u Data %u) cannot find any pPlayer.", type, data);
                        Encounter[0] = DONE;
                    }
                }
                break;
            }
            case TYPE_THRALL_EVENT:
            {
                if (data == FAIL)
                {
                    if (mThrallEventCount <= 20)
                    {
                        mThrallEventCount++;
                        Encounter[1] = NOT_STARTED;
                        sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall event failed %u times. Resetting all sub-events.",mThrallEventCount);
                        Encounter[2] = NOT_STARTED;
                        Encounter[3] = NOT_STARTED;
                        Encounter[4] = NOT_STARTED;
                        Encounter[5] = NOT_STARTED;
                    }
                    else if (mThrallEventCount > 20)
                    {
                        Encounter[1] = data;
                        Encounter[2] = data;
                        Encounter[3] = data;
                        Encounter[4] = data;
                        Encounter[5] = data;
                        sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall event failed %u times. Resetting all sub-events.",mThrallEventCount);
                    }
                }
                else
                    Encounter[1] = data;
                sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall escort event adjusted to data %u.", data);
                break;
            }
            case TYPE_THRALL_PART1:
                Encounter[2] = data;
                sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall event part I adjusted to data %u.", data);
                break;
            case TYPE_THRALL_PART2:
                Encounter[3] = data;
                sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall event part II adjusted to data %u.", data);
                break;
            case TYPE_THRALL_PART3:
                Encounter[4] = data;
                sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall event part III adjusted to data %u.", data);
                break;
            case TYPE_THRALL_PART4:
                Encounter[5] = data;
                sLog->outDebug("TSCR: Instance Old Hillsbrad: Thrall event part IV adjusted to data %u.", data);
                break;
            case TYPE_DRAKE_EVENT:
                if (Encounter[6] != DONE)
                    Encounter[6] = data;
                break;
            case TYPE_SKARLOC_EVENT:
                if (Encounter[7] != DONE)
                    Encounter[7] = data;
                break;
        }

        if (data == DONE)
            SaveToDB();
    }

    uint32 GetData(uint32 data)
    {
        switch (data)
        {
            case TYPE_BARREL_DIVERSION:
                return Encounter[0];
            case TYPE_THRALL_EVENT:
                return Encounter[1];
            case TYPE_THRALL_PART1:
                return Encounter[2];
            case TYPE_THRALL_PART2:
                return Encounter[3];
            case TYPE_THRALL_PART3:
                return Encounter[4];
            case TYPE_THRALL_PART4:
                return Encounter[5];
            case TYPE_DRAKE_EVENT:
                return Encounter[6];
            case TYPE_SKARLOC_EVENT:
                return Encounter[7];
        }
        return 0;
    }

    uint64 GetData64(uint32 data)
    {
        switch (data)
        {
            case DATA_THRALL:
                return ThrallGUID;
            case DATA_TARETHA:
                return TarethaGUID;
            case DATA_EPOCH:
                return EpochGUID;
            case DATA_THRALL_DOOR:
                return ThrallDoorGUID;
        }
        return 0;
    }

    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream stream;
        stream << Encounter[0] << " ";
        stream << Encounter[1] << " ";
        stream << Encounter[2] << " ";
        stream << Encounter[3] << " ";
        stream << Encounter[4] << " ";
        stream << Encounter[5] << " ";
        stream << Encounter[6] << " ";
        stream << Encounter[7];

        OUT_SAVE_INST_DATA_COMPLETE;

        return stream.str();
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        std::istringstream stream(in);

        stream  >> Encounter[0] >> Encounter[1] >> Encounter[2]
                >> Encounter[3] >> Encounter[4] >> Encounter[5]
                >> Encounter[6] >> Encounter[7];

        for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            if (Encounter[i] == IN_PROGRESS)
                Encounter[i] = NOT_STARTED;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

    void UpdateLodgeQuestCredit()
    {
        Map::PlayerList const& players = instance->GetPlayers();

        if (!players.isEmpty())
        {
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                if (Player* pPlayer = itr->getSource())
                    pPlayer->KilledMonsterCredit(LODGE_QUEST_TRIGGER, 0);
            }
        }
    }

    // temp
    void SetBuildingsOnFire()
    {
        if (Player* pPlayer = GetPlayerInMap())
        {
            for (uint8 i = 0; i < 23; ++i)
                pPlayer->SummonGameObject(GO_ROARING_FLAME, RoaringFlame[i].x, RoaringFlame[i].y, RoaringFlame[i].z, RoaringFlame[i].orientation, 0, 0, RoaringFlame[i].rotation2, RoaringFlame[i].rotation3, 180);
        }
        else
            sLog->outError("No player could spawn fires.");
    }

};

InstanceScript* GetInstanceData_instance_old_hillsbrad(Map* map)
{
    return new instance_old_hillsbrad(map);
}

void AddSC_instance_old_hillsbrad()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_old_hillsbrad";
    newscript->GetInstanceScript = &GetInstanceData_instance_old_hillsbrad;
    newscript->RegisterSelf();
}

