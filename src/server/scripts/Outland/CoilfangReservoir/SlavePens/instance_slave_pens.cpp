
#include "ScriptPCH.h"
#include "slave_pens.h"

#define MAX_ENCOUNTERS 4

struct instance_slave_pens : public ScriptedInstance
{
    instance_slave_pens(Map *map) : ScriptedInstance(map) { }

    uint32 Encounter[MAX_ENCOUNTERS];

    uint64 MennuGUID;
    uint64 RokmarGUID;
    uint64 QuagmirranGUID;
    uint64 CageGUID;

    void Initialize()
    {
        MennuGUID = 0;
        RokmarGUID = 0;
        QuagmirranGUID = 0;
        CageGUID = 0;

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

        sLog->outDebug("TSCR: Instance Slave Pens: GetPlayerInMap, but PlayerList is empty!");
        return NULL;
    }
    
    void OnCreatureCreate(Creature* creature)
    {
        switch (creature->GetEntry())
        {
            case 17941: MennuGUID = creature->GetGUID(); break;
            case 17991: RokmarGUID = creature->GetGUID(); break;
            case 17942: QuagmirranGUID = creature->GetGUID(); break;
        }
    }
    
    void OnGameObjectCreate(GameObject* go, bool add)
    {
        switch (go->GetEntry())
        {
            case 182094: CageGUID = go->GetGUID(); break;
        }
    }

    
    void SetData(uint32 type, uint32 data)
    {
        Player* player = GetPlayerInMap();

        if (!player)
        {
            sLog->outDebug("TSCR: Instance Slave Pens: SetData (Type: %u Data %u) cannot find any player.", type, data);
            return;
        }

        switch (type)
        {
            case TYPE_MENNU_THE_BETRAYER:
                Encounter[0] = data;
                break;
            case TYPE_ROKMAR_THE_CRACKLER:
                Encounter[1] = data;
                break;
            case TYPE_QUAGMIRRAN:
                Encounter[2] = data;
                break;
            case TYPE_NATURALIST_EVENT:
                Encounter[3] = data;
                break;
        }

        if (data == DONE)
            SaveToDB();
    }
    
    uint32 GetData(uint32 type)
    {
        switch (type)
        {
            case TYPE_MENNU_THE_BETRAYER:
                return Encounter[0];
            case TYPE_ROKMAR_THE_CRACKLER:
                return Encounter[1];
            case TYPE_QUAGMIRRAN:
                return Encounter[2];
            case TYPE_NATURALIST_EVENT:
                return Encounter[3];
        }
        return 0;
    }

    uint64 GetData64(uint32 data)
    {
        switch (data)
        {
            case DATA_MENNU:
                return MennuGUID;
            case DATA_ROKMAR:
                return RokmarGUID;
            case DATA_QUAGMIRRAN:
                return QuagmirranGUID;
            case DATA_CAGE:
                return CageGUID;
        }
        return 0;
    }

    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;
        std::ostringstream stream;
        stream << Encounter[0] << " " << Encounter[1] << " " << Encounter[2] << " " << Encounter[3];
        char* out = new char[stream.str().length() + 1];
        strcpy(out, stream.str().c_str());
        if (out)
        {
            OUT_SAVE_INST_DATA_COMPLETE;
            return out;
        }
        return NULL;
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
        stream >> Encounter[0] >> Encounter[1] >> Encounter[2] >> Encounter[3];

        for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            if (Encounter[i] == IN_PROGRESS)
                Encounter[i] = NOT_STARTED;
        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceScript* GetInstanceData_instance_slave_pens(Map* map)
{
    return new instance_slave_pens(map);
}

void AddSC_instance_slave_pens()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "instance_slave_pens";
    newscript->GetInstanceScript = &GetInstanceData_instance_slave_pens;
    newscript->RegisterSelf();
}
