 /*
  * Copyright (C) 2010-2012 Project SkyFire <http://www.projectskyfire.org/>
  * Copyright (C) 2010-2012 Oregon <http://www.oregoncore.com/>
  * Copyright (C) 2006-2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
  * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
SDName: Instance_Blood_Furnace
SD%Complete: 90
SDComment: Need to fix resetting the DoNextBroggokEvent
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */

#include "ScriptPCH.h"
#include "blood_furnace.h"

#define SAY_BROGGOK_INTRO            -1542015
#define MAX_ORC_WAVES                4
#define MAX_BROGGOK_WAVES            5
#define NASCENT_FEL_ORC              17398

#define MAX_ENCOUNTERS               3

struct instance_blood_furnace : public ScriptedInstance
{
    instance_blood_furnace(Map *map) : ScriptedInstance(map) {}

    uint64 The_MakerGUID;
    uint64 BroggokGUID;
    uint64 Kelidan_The_BreakerGUID;

    uint64 Door1GUID;
    uint64 Door2GUID;
    uint64 Door3GUID;
    uint64 Door4GUID;
    uint64 Door5GUID;
    uint64 Door6GUID;

    /* ---- Broggok Event Info ---- */
    struct BroggokEventInfo
    {
        BroggokEventInfo() : IsCellOpened(false), KilledOrcCount(0) {}

        uint64 CellGuid;
        bool IsCellOpened;
        uint8 KilledOrcCount;
        std::set<uint64> SortedOrcGuids;
    };

    // Broggok event data
    BroggokEventInfo BroggokEvent[MAX_ORC_WAVES];
    std::vector<uint64> NascentOrcGuids;

    uint32 BroggokEventTimer;
    uint32 BroggokEventPhase;
    uint32 BroggokDoorTimer;
    uint64 BroggokLeverGUID;
    /* ---- Broggok Event End ---- */


    uint32 Encounter[MAX_ENCOUNTERS];
    std::string str_data;

    void Initialize()
    {
        The_MakerGUID = 0;
        BroggokGUID = 0;
        Kelidan_The_BreakerGUID = 0;

        Door1GUID = 0;
        Door2GUID = 0;
        Door3GUID = 0;
        Door4GUID = 0;
        Door5GUID = 0;
        Door6GUID = 0;
        BroggokEvent[0].CellGuid = 0;
        BroggokEvent[1].CellGuid = 0;
        BroggokEvent[2].CellGuid = 0;
        BroggokEvent[3].CellGuid = 0;

        BroggokEventTimer = 0;
        BroggokEventPhase = 0;
        BroggokDoorTimer  = 0;
        BroggokLeverGUID  = 0;

        for (uint8 i = 0; i < MAX_ENCOUNTERS; i++)
            Encounter[i] = NOT_STARTED;
    }

    bool IsEncounterInProgress() const
    {
        for (uint8 i = 0; i < MAX_ENCOUNTERS; i++)
            if (Encounter[i] == IN_PROGRESS)
                return true;

        return false;
    }

    void OnCreatureCreate(Creature* creature)
    {
        switch (creature->GetEntry())
        {
            case 17381:
                The_MakerGUID = creature->GetGUID();
                break;
            case 17380:
                BroggokGUID = creature->GetGUID();
                break;
            case 17377:
                Kelidan_The_BreakerGUID = creature->GetGUID();
                break;
            case NASCENT_FEL_ORC:
                NascentOrcGuids.push_back(creature->GetGUID());
                break;
        }
    }

    void OnGameObjectCreate(GameObject* go, bool add)
    {
        switch (go->GetEntry())
        {
            case 181766: Door1GUID = go->GetGUID(); break;                  // Final exit door
            case 181811: Door2GUID = go->GetGUID(); break;                  // The Maker Front door
            case 181812: Door3GUID = go->GetGUID(); break;                  // The Maker Rear door
            case 181822: Door4GUID = go->GetGUID(); break;                  // Broggok Front door
            case 181819: Door5GUID = go->GetGUID(); break;                  // Broggok Rear door
            case 181823: Door6GUID = go->GetGUID(); break;                  // Kelidan exit door
            case 181982: BroggokLeverGUID = go->GetGUID(); break;           // Broggok lever
            case 181817: BroggokEvent[0].CellGuid = go->GetGUID(); break;   // Broggok Prison Cell 1
            case 181818: BroggokEvent[1].CellGuid = go->GetGUID(); break;   // 2
            case 181820: BroggokEvent[2].CellGuid = go->GetGUID(); break;   // 3
            case 181821: BroggokEvent[3].CellGuid = go->GetGUID(); break;   // 4
        }
    }

    uint64 GetData64(uint32 data)
    {
        switch (data)
        {
            case DATA_THE_MAKER:            return The_MakerGUID;
            case DATA_BROGGOK:              return BroggokGUID;
            case DATA_KELIDAN_THE_MAKER:    return Kelidan_The_BreakerGUID;
            case DATA_DOOR1:                return Door1GUID;
            case DATA_DOOR2:                return Door2GUID;
            case DATA_DOOR3:                return Door3GUID;
            case DATA_DOOR4:                return Door4GUID;
            case DATA_DOOR5:                return Door5GUID;
            case DATA_DOOR6:                return Door6GUID;
        }

        return 0;
    }

    void SetData(uint32 type, uint32 data)
    {
        switch (type)
        {
            case TYPE_THE_MAKER_EVENT:
                if (Encounter[0] != DONE)
                    Encounter[0] = data;
                break;
            case TYPE_BROGGOK_EVENT:
                if (data == IN_PROGRESS)
                {
                    if (Creature* pBroggok = instance->GetCreature(BroggokGUID))
                    {
                        DoScriptText(SAY_BROGGOK_INTRO, pBroggok);
                        pBroggok->SetInCombatWithZone();
                    }

                    HandleGameObject(Door4GUID, false);

                    if (BroggokEventPhase <= MAX_ORC_WAVES)
                    {
                        DoSortBroggokOrcs();
                        DoNextBroggokEventPhase();
                    }
                }
                else
                    HandleGameObject(Door4GUID, true);

                if (data == FAIL)
                {
                    if (BroggokEventPhase <= MAX_BROGGOK_WAVES)
                    {
                        for (uint8 i = 0; i < MAX_ORC_WAVES; ++i)
                        {
                            if (!BroggokEvent[i].IsCellOpened)
                                continue;

                            BroggokEvent[i].KilledOrcCount = 0;
                            for (std::set<uint64>::const_iterator itr = BroggokEvent[i].SortedOrcGuids.begin(); itr != BroggokEvent[i].SortedOrcGuids.end(); ++itr)
                            {
                                if (Creature* pOrc = instance->GetCreature(*itr))
                                {
                                    if (!pOrc->isAlive())
                                    {
                                        pOrc->Respawn();
                                        BroggokEventPhase = 0;
                                    }
                                }
                            }

                            DoUseDoorOrButton(BroggokEvent[i].CellGuid);
                            BroggokEvent[i].IsCellOpened = false;

                            if (GameObject *Lever = instance->GetGameObject(BroggokLeverGUID))
                                Lever->ResetDoorOrButton();
                        }
                    }
                }
                if (Encounter[1] != DONE)
                    Encounter[1] = data;
                break;
            case TYPE_KELIDAN_THE_BREAKER_EVENT:
                if (Encounter[2] != DONE)
                    Encounter[2] = data;
                break;
        }

        if (data == DONE)
        {
            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    uint32 GetData(uint32 data)
    {
        switch (data)
        {
            case TYPE_THE_MAKER_EVENT:              return Encounter[0];
            case TYPE_BROGGOK_EVENT:                return Encounter[1];
            case TYPE_KELIDAN_THE_BREAKER_EVENT:    return Encounter[2];
        }

        return 0;
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

        sLog->outDebug("TSCR: Instance Blood Furnace: GetPlayerInMap, but PlayerList is empty!");
        return NULL;
    }


    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;
        std::ostringstream saveStream;

        saveStream << Encounter[0] << " " << Encounter[1] << " " << Encounter[2];

        char* out = new char[saveStream.str().length() + 1];
        strcpy(out, saveStream.str().c_str());
        if (out)
        {
            OUT_SAVE_INST_DATA_COMPLETE;
            return out;
        }

        return str_data.c_str();
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        std::istringstream loadStream(in);
        loadStream >> Encounter[0] >> Encounter[1] >> Encounter[2];

        for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            if (Encounter[i] == IN_PROGRESS || Encounter[i] == FAIL)
                Encounter[i] = NOT_STARTED;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

    void DoNextBroggokEventPhase()
    {
        float dx, dy;
        GetMovementDistanceForIndex(BroggokEventPhase, dx, dy);

        if (BroggokEventPhase >= MAX_ORC_WAVES)
        {
            DoUseDoorOrButton(Door5GUID);

            if (Creature* pBroggok = instance->GetCreature(BroggokGUID))
            {
                pBroggok->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                pBroggok->GetMotionMaster()->MovePoint(0, dx, dy, pBroggok->GetPositionZ());
                BroggokDoorTimer = 5000;
            }
        }
        else
        {
            if (!BroggokEvent[BroggokEventPhase].IsCellOpened)
                DoUseDoorOrButton(BroggokEvent[BroggokEventPhase].CellGuid);

            BroggokEvent[BroggokEventPhase].IsCellOpened = true;

            for (std::set<uint64>::const_iterator itr = BroggokEvent[BroggokEventPhase].SortedOrcGuids.begin(); itr != BroggokEvent[BroggokEventPhase].SortedOrcGuids.end(); ++itr)
            {
                if (Creature* pOrc = instance->GetCreature(*itr))
                {
                    pOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pOrc->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    pOrc->GetMotionMaster()->MovePoint(0, pOrc->GetPositionX() + dx, pOrc->GetPositionY() + dy, pOrc->GetPositionZ());
                }
            }
        }
        BroggokEventTimer = 30000;
        ++BroggokEventPhase;
    }

    void Update(uint32 diff)
    {
        if (BroggokEventTimer && BroggokEventPhase < MAX_ORC_WAVES)
        {
            if (BroggokEventTimer <= diff)
                DoNextBroggokEventPhase();
            else BroggokEventTimer -= diff;
        }

        if (BroggokDoorTimer)
        {
            if (BroggokDoorTimer <= diff)
            {
                if (GameObject *Brog2 = instance->GetGameObject(Door5GUID))
                    Brog2->ResetDoorOrButton();
            }
            else BroggokDoorTimer -= diff;
        }
    }

    void OnCreatureDeath(Creature* creature)
    {
        if (creature->GetEntry() == NASCENT_FEL_ORC)
        {
            uint8 uiClearedCells = 0;
            for (uint8 i = 0; i < std::min<uint32>(BroggokEventPhase, MAX_ORC_WAVES); ++i)
            {
                if (BroggokEvent[i].SortedOrcGuids.size() == BroggokEvent[i].KilledOrcCount)
                {
                    ++uiClearedCells;
                    continue;
                }

               if (BroggokEvent[i].SortedOrcGuids.find(creature->GetGUID()) != BroggokEvent[i].SortedOrcGuids.end())
                   BroggokEvent[i].KilledOrcCount++;

               if (BroggokEvent[i].SortedOrcGuids.size() == BroggokEvent[i].KilledOrcCount)
                   ++uiClearedCells;
            }

            if (uiClearedCells == BroggokEventPhase)
                DoNextBroggokEventPhase();
        }
    }

    void DoSortBroggokOrcs()
    {
        for (std::vector<uint64>::const_iterator itr = NascentOrcGuids.begin(); itr != NascentOrcGuids.end(); ++itr)
        {
            if (Creature* pOrc = instance->GetCreature(*itr))
            {
                for (uint8 i = 0; i < MAX_ORC_WAVES; ++i)
                {
                    if (GameObject* pDoor = instance->GetGameObject(BroggokEvent[i].CellGuid))
                    {
                        if (pOrc->IsWithinDistInMap(pDoor, 8.0f))
                        {
                            BroggokEvent[i].SortedOrcGuids.insert(pOrc->GetGUID());
                            if (!pOrc->isAlive())
                            {
                                pOrc->ForcedDespawn();
                                pOrc->Respawn();
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    void GetMovementDistanceForIndex(uint32 uiIndex, float& dx, float& dy)
    {
        GameObject* pDoor[2];

        if (uiIndex < MAX_ORC_WAVES)
        {
            pDoor[0] = instance->GetGameObject(BroggokEvent[(uiIndex / 2) * 2].CellGuid);
            pDoor[1] = instance->GetGameObject(BroggokEvent[(uiIndex / 2) * 2 + 1].CellGuid);
        }
        else
        {
            pDoor[0] = instance->GetGameObject(BroggokEvent[0].CellGuid);
            pDoor[1] = instance->GetGameObject(BroggokEvent[3].CellGuid);
        }

        if (!pDoor[0] || !pDoor[1])
            return;

        if (uiIndex < MAX_ORC_WAVES)
        {
            dx = (pDoor[0]->GetPositionX() + pDoor[1]->GetPositionX()) / 2 - pDoor[uiIndex % 2]->GetPositionX();
            dy = (pDoor[0]->GetPositionY() + pDoor[1]->GetPositionY()) / 2 - pDoor[uiIndex % 2]->GetPositionY();
        }
        else
        {
            dx = (pDoor[0]->GetPositionX() + pDoor[1]->GetPositionX()) / 2;
            dy = (pDoor[0]->GetPositionY() + pDoor[1]->GetPositionY()) / 2;
        }
    }
};

InstanceScript* GetInstanceScript_instance_blood_furnace(Map* map)
{
    return new instance_blood_furnace(map);
}

bool GOHello_go_prison_cell_lever(Player* player, GameObject* pGo)
{
    ScriptedInstance* instance = (ScriptedInstance*)pGo->GetInstanceScript();

    if (!instance)
        return false;

    if (instance->GetData(TYPE_BROGGOK_EVENT) != DONE && instance->GetData(TYPE_BROGGOK_EVENT) != IN_PROGRESS)
        instance->SetData(TYPE_BROGGOK_EVENT, IN_PROGRESS);

    return false;
}

void AddSC_instance_blood_furnace()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_blood_furnace";
    newscript->GetInstanceScript = &GetInstanceScript_instance_blood_furnace;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_prison_cell_lever";
    newscript->pGOHello = &GOHello_go_prison_cell_lever;
    newscript->RegisterSelf();
}

