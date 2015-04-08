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
SDName: Eastern_Plaguelands
SD%Complete: 100
SDComment: Quest support: 5211, 5742. Special vendor Augustus the Touched
SDCategory: Eastern Plaguelands
EndScriptData */

/* ContentData
mobs_ghoul_flayer
npc_augustus_the_touched
npc_darrowshire_spirit
npc_tirion_fordring
npc_eris_havenfire
EndContentData */

#include "ScriptPCH.h"

//id8530 - cannibal ghoul
//id8531 - gibbering ghoul
//id8532 - diseased flayer

struct mobs_ghoul_flayerAI : public ScriptedAI
{
    mobs_ghoul_flayerAI(Creature *c) : ScriptedAI(c) {}

    void Reset() {}

    void EnterCombat(Unit* /*who*/) {}

    void JustDied(Unit* Killer)
    {
        if (Killer->GetTypeId() == TYPEID_PLAYER)
            me->SummonCreature(11064, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000);
    }
};

CreatureAI* GetAI_mobs_ghoul_flayer(Creature* creature)
{
    return new mobs_ghoul_flayerAI (creature);
}

/*######
## npc_augustus_the_touched
######*/

bool GossipHello_npc_augustus_the_touched(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if (creature->isVendor() && player->GetQuestRewardStatus(6164))
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
    return true;
}

bool GossipSelect_npc_augustus_the_touched(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        player->SEND_VENDORLIST(creature->GetGUID());
    return true;
}

/*######
## npc_darrowshire_spirit
######*/

#define SPELL_SPIRIT_SPAWNIN    17321

struct npc_darrowshire_spiritAI : public ScriptedAI
{
    npc_darrowshire_spiritAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    {
        DoCast(me, SPELL_SPIRIT_SPAWNIN);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void EnterCombat(Unit * /*who*/) {}
};
CreatureAI* GetAI_npc_darrowshire_spirit(Creature* creature)
{
    return new npc_darrowshire_spiritAI (creature);
}

bool GossipHello_npc_darrowshire_spirit(Player* player, Creature* creature)
{
    player->SEND_GOSSIP_MENU(3873, creature->GetGUID());
    player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    return true;
}

/*######
## npc_tirion_fordring
######*/

#define GOSSIP_HELLO    "I am ready to hear your tale, Tirion."
#define GOSSIP_SELECT1  "Thank you, Tirion.  What of your identity?"
#define GOSSIP_SELECT2  "That is terrible."
#define GOSSIP_SELECT3  "I will, Tirion."

bool GossipHello_npc_tirion_fordring(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if (player->GetQuestStatus(5742) == QUEST_STATUS_INCOMPLETE && player->getStandState() == UNIT_STAND_STATE_SIT)
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

    return true;
}

bool GossipSelect_npc_tirion_fordring(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(4493, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(4494, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->SEND_GOSSIP_MENU(4495, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            player->CLOSE_GOSSIP_MENU();
            player->AreaExploredOrEventHappens(5742);
            break;
    }
    return true;
}

/*######
## npc_eris_havenfire
## This contains script for the quest "The Balance of Light and Shadow"
## Enemy NPCs: Scourge Footsoldier (14486), Scourge Archer (14489)
## Friendly NPCs: Injured Peasant (14484), Plagued Peasant (14485)
## Unknown: Priest Epic Event Caller (14493), Invisible Trigger One (14495)
## Spells: Death's Door (23127) - on Injured, Seething Plague (23072)
##
######*/

#define GOSSIP_SELECT1 "The Eye led me here, Eris."
#define GOSSIP_SELECT2 "And I was suited to see this?"
#define GOSSIP_SELECT3 "I really did not know what to expect, Eris. I will use my powers to assist you if that is what is asked of me."
#define GOSSIP_SELECT4 "Those days are over, Eris."
#define GOSSIP_SELECT5 "So what can I do to help?"

enum PriestEpicQuest
{
    NPC_SCOURGE_FOOTSOLDIER = 14486,
    NPC_SCOURGE_ARCHER = 14489,
    NPC_PRIEST_EPIC_EVENT_CALLER = 14493,
    NPC_ERIS_HAVENFIRE = 14494,
    NPC_INJURED_PEASANT = 14484,
    NPC_PLAGUED_PEASANT = 14485,

    INJURED_PEASANT_COUNT = 10,
    PLAGUED_PEASANT_COUNT = 2,
    SCOURGE_ARCHER_COUNT = 7,

    SPELL_DEATHS_DOOR = 23127,
    SPELL_SEETHING_PLAGUE = 23072,

    QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW = 7622,

    SAY_SAVED1 = -1510000,
    SAY_SAVED2 = -1510001,
    SAY_SAVED3 = -1510002,
    SAY_DIED1 = -1510003,
    SAY_DIED2 = -1510004,
    SAY_DIED3 = -1510005,
    SAY_DIED4 = -1510006,
    SAY_EMPOWER = -1510007,
    SAY_COMPLETE = -1510008,
    SAY_SPAWN1 = -1510009,
    SAY_SPAWN2 = -1510010,
    SAY_SPAWN3 = -1510011
};

uint32 eventCreatures[] = { 14486, 14489, 14484, 14485, 14493 };

static float ArcherPosition[7][4] =
{
    { 3347.865234f, -3070.707275f, 177.881882f, 1.645396f },
    { 3357.144287f, -3063.327637f, 172.499222f, 1.841747f },
    { 3371.682373f, -3067.965332f, 175.233582f, 2.144123f },
    { 3379.904053f, -3059.370117f, 181.981873f, 2.646778f },
    { 3334.646973f, -3053.084717f, 174.101074f, 0.400536f },
    { 3368.005371f, -3022.475830f, 171.617966f, 4.268625f },
    { 3327.000244f, -3021.307861f, 170.578796f, 5.584163f }
};

struct npc_priest_epic_quest_callerAI : public NullCreatureAI
{
    npc_priest_epic_quest_callerAI(Creature *c) : NullCreatureAI(c) {}

    Player* pInvoker;

    uint8 SavedCount;
    uint8 KilledCount;
    uint8 currentPhase;

    bool eventRunning;
    bool canSpawnSoldier;

    uint32 CheckTimer;
    uint32 SoldierTimer;
    uint32 waitTimer;

    void Reset()
    {
        pInvoker = 0;

        currentPhase = 0;
        SavedCount = 0;
        KilledCount = 0;

        eventRunning = false;
        canSpawnSoldier = true;

        CheckTimer = 3000;
        SoldierTimer = urand(5000, 15000);
        waitTimer = 5000;
    }

    void StartEvent(Player* invoker)
    {
        pInvoker = invoker;
        eventRunning = true;
        waitTimer = 5000;

        for (uint8 i = 0; i < SCOURGE_ARCHER_COUNT; ++i)
        {
            if (Creature* pSummon = me->SummonCreature(NPC_SCOURGE_ARCHER, ArcherPosition[i][0], ArcherPosition[i][1], ArcherPosition[i][2], ArcherPosition[i][3]))
            {
                pSummon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE);
                pSummon->SetReactState(REACT_AGGRESSIVE);
            }
        }
            
    }

    void FinishEvent(bool success)
    {
        for (uint8 i = 0; i < 3; ++i)
            DespawnSummons(eventCreatures[i]);

        // Restore questgiver flag
        if (Creature* pTrigger = me->FindNearestCreature(NPC_PRIEST_EPIC_EVENT_CALLER, 100.0f))
        {
            pTrigger->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            pTrigger->Yell(SAY_COMPLETE, LANG_UNIVERSAL, 0);
        }
           
        if (success)
            pInvoker->CompleteQuest(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW);
        else
        {
            if (Creature* pTrigger = me->FindNearestCreature(NPC_ERIS_HAVENFIRE, 100.0f))
                pTrigger->DisappearAndDie();

            pInvoker->FailQuest(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW);
        }

        me->RemoveFromWorld();
    }

    void NextWave()
    {
        for (uint8 i = 0; i < INJURED_PEASANT_COUNT; ++i)
            DoSummon(NPC_INJURED_PEASANT, me, 10.5f, 5000, TEMPSUMMON_CORPSE_TIMED_DESPAWN);

        for (uint8 i = 0; i < PLAGUED_PEASANT_COUNT; ++i)
            DoSummon(NPC_PLAGUED_PEASANT, me, 10.5f, 5000, TEMPSUMMON_CORPSE_TIMED_DESPAWN);

        currentPhase++;
        canSpawnSoldier = true;
        SoldierTimer = urand(5000, 15000);
    }

    void SpawnSoldiers()
    {
        if (!pInvoker)
            return;

        Position pos;
        pInvoker->GetPosition(&pos);

        float randFac = float(urand(-5, 5));
        uint8 amount = currentPhase * 2;
        for (uint8 i = 0; i < (amount > 6 ? 6 : amount); ++i)
            if (Creature* soilder = pInvoker->SummonCreature(NPC_SCOURGE_FOOTSOLDIER, pos.GetPositionX() + randFac, pos.GetPositionY() + randFac, pos.GetPositionZ() + 1.0f, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                soilder->Attack(pInvoker, true);

        canSpawnSoldier = false;
    }

    void DespawnSummons(uint32 entry)
    {
        std::list<Creature*> tempList;
        float x, y, z;
        me->GetPosition(x, y, z);

        CellPair pair(Trinity::ComputeCellPair(x, y));
        Cell cell(pair);
        cell.data.Part.reserved = ALL_DISTRICT;
        cell.SetNoCreate();

        Trinity::AllCreaturesOfEntryInRange check(me, entry, 100);
        Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange> searcher(tempList, check);
        TypeContainerVisitor<Trinity::CreatureListSearcher<Trinity::AllCreaturesOfEntryInRange>, GridTypeMapContainer> cSearcher(searcher);
        cell.Visit(pair, cSearcher, *(me->GetMap()));

        for (std::list<Creature*>::const_iterator i = tempList.begin(); i != tempList.end(); ++i)
            (*i)->RemoveFromWorld();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!eventRunning)
            return;

        if (waitTimer)
        {
            if (waitTimer <= diff)
            {
                NextWave();
                waitTimer = 0;
            }
            else
            {
                waitTimer -= diff;
                return;
            }
        }

        if (canSpawnSoldier)
        {
            if (SoldierTimer < diff)
            {
                SpawnSoldiers();
                SoldierTimer = 0;
            }
            else
                SoldierTimer -= diff;
        }

        if (CheckTimer < diff)
        {
            if (SavedCount >= 50)
                FinishEvent(true);

            if (KilledCount >= 15)
                FinishEvent(false);

            if ((KilledCount + SavedCount) >= 12 * currentPhase)
                NextWave();

            CheckTimer = 3000;
        }
        else
            CheckTimer -= diff;
    }
};

CreatureAI* GetAI_npc_priest_epic_quest_caller(Creature* creature)
{
    return new npc_priest_epic_quest_callerAI(creature);
}

static float EscapePositions[4][3] =
{
    // Escape movement points for Peasants
    { 3345.032227f, -3023.691162f, 161.178528f },
    { 3340.042480f, -3004.720215f, 161.248352f },
    { 3334.029053f, -2992.794189f, 161.143433f },
    { 3331.889893f, -2975.391357f, 160.549240f }
};

struct npc_priest_quest_peasantAI : public ScriptedAI
{
    npc_priest_quest_peasantAI(Creature *c) : ScriptedAI(c) {}

    bool isMoving;
    uint8 currentPhase;
    uint32 diseaseTimer;

    void Reset()
    {
        isMoving = false;
        currentPhase = 1;
        diseaseTimer = 4000 + urand(6000, 22000);

        me->AddUnitMovementFlag(MOVEFLAG_WALK_MODE);
    };

    void AddDisease()
    {
        me->RemoveAllAuras(); // Remove all auras (e.g. Shield and HOT spells)
        me->AddAura(RAND(SPELL_DEATHS_DOOR, SPELL_SEETHING_PLAGUE), me);
    }

    void UpdateAI(const uint32 diff)
    {
        // Only update disease timer when moving
        if (isMoving)
        {
            if (diseaseTimer)
            {
                if (diseaseTimer < diff)
                {
                    AddDisease();           // Only reapply diseases once
                    diseaseTimer = 0;
                }
                else
                    diseaseTimer -= diff;
            }

            return;
        }

        if (currentPhase)
        {
            float randomFac = float(irand(-4, 4));
            switch (currentPhase)
            {
                case 1:
                {
                    if (roll_chance_i(40))
                        AddDisease();

                    if (roll_chance_i(5))
                        me->Yell(RAND(SAY_SPAWN1, SAY_SPAWN2, SAY_SPAWN3), LANG_UNIVERSAL, 0);

                    MovePoint(0, EscapePositions[0][0] + randomFac, EscapePositions[0][1] + randomFac, EscapePositions[0][2]);
                    break;
                }
                case 2:
                {
                    MovePoint(1, EscapePositions[1][0] + randomFac, EscapePositions[1][1] + randomFac, EscapePositions[1][2]);
                    break;
                }
                case 3:
                {
                    MovePoint(2, EscapePositions[2][0] + randomFac, EscapePositions[2][1] + randomFac, EscapePositions[2][2]);
                    break;
                }
                case 4:
                {
                    MovePoint(3, EscapePositions[3][0] + randomFac, EscapePositions[3][1] + randomFac, EscapePositions[3][2]);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void MovePoint(uint32 id, float x, float y, float z)
    {
        isMoving = true;
        me->GetMotionMaster()->MovePoint(id, x, y, z);
    }

    void JustDied(Unit* /*killer*/)
    {
        if (Creature* pTrigger = me->FindNearestCreature(NPC_PRIEST_EPIC_EVENT_CALLER, 100.0f))
            CAST_AI(npc_priest_epic_quest_callerAI, pTrigger->AI())->KilledCount++;

        if (roll_chance_i(25))
            me->Yell(RAND(SAY_DIED1, SAY_DIED2, SAY_DIED3), LANG_UNIVERSAL, 0);
    }

    void MovementInform(uint32 uiType, uint32 uiId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiId == 3)
        {
            if (Creature* pTrigger = me->FindNearestCreature(NPC_PRIEST_EPIC_EVENT_CALLER, 100.0f))
                CAST_AI(npc_priest_epic_quest_callerAI, pTrigger->AI())->SavedCount++;

            if (roll_chance_i(15))
                me->Yell(RAND(SAY_SAVED1, SAY_SAVED2, SAY_SAVED3), LANG_UNIVERSAL, 0);

            me->DisappearAndDie();
        }

        if (EscapePositions[uiId][3] > 0.0f)
            me->SetFacingToOrientation(EscapePositions[uiId][3]);

        ++currentPhase;
        isMoving = false;
    }
};

CreatureAI* GetAI_npc_priest_quest_peasant(Creature* creature)
{
    return new npc_priest_quest_peasantAI(creature);
}

bool GossipHello_npc_eris_havenfire(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    player->SEND_GOSSIP_MENU(7100, creature->GetGUID());

    return true;
}

bool GossipSelect_npc_eris_havenfire(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
{
    switch (uiAction)
    {
    case GOSSIP_ACTION_INFO_DEF + 1:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        player->SEND_GOSSIP_MENU(7101, creature->GetGUID());
        break;
    case GOSSIP_ACTION_INFO_DEF + 2:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        player->SEND_GOSSIP_MENU(7102, creature->GetGUID());
        break;
    case GOSSIP_ACTION_INFO_DEF + 3:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
        player->SEND_GOSSIP_MENU(7103, creature->GetGUID());
        break;
    case GOSSIP_ACTION_INFO_DEF + 4:
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SELECT5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        player->SEND_GOSSIP_MENU(7104, creature->GetGUID());
        break;
    case GOSSIP_ACTION_INFO_DEF + 5:
        player->SEND_GOSSIP_MENU(7105, creature->GetGUID());
        break;
    }
    return true;
}

bool QuestAccept_npc_eris_havenfire(Player* player, Creature* creature, Quest const *quest)
{
    if (quest->GetQuestId() == QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW)
    {
        // Only allow one active event
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

        if (Creature* pTrigger = creature->SummonCreature(NPC_PRIEST_EPIC_EVENT_CALLER, 3360.2f, -3050.24f, 165.25f, 1.90f))
            CAST_AI(npc_priest_epic_quest_callerAI, pTrigger->AI())->StartEvent(player);
    }

    return true;
}

void AddSC_eastern_plaguelands()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mobs_ghoul_flayer";
    newscript->GetAI = &GetAI_mobs_ghoul_flayer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_augustus_the_touched";
    newscript->pGossipHello = &GossipHello_npc_augustus_the_touched;
    newscript->pGossipSelect = &GossipSelect_npc_augustus_the_touched;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_darrowshire_spirit";
    newscript->GetAI = &GetAI_npc_darrowshire_spirit;
    newscript->pGossipHello = &GossipHello_npc_darrowshire_spirit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tirion_fordring";
    newscript->pGossipHello =  &GossipHello_npc_tirion_fordring;
    newscript->pGossipSelect = &GossipSelect_npc_tirion_fordring;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_eris_havenfire";
    newscript->pGossipHello = &GossipHello_npc_eris_havenfire;
    newscript->pGossipSelect = &GossipSelect_npc_eris_havenfire;
    newscript->pQuestAccept = &QuestAccept_npc_eris_havenfire;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_priest_epic_quest_caller";
    newscript->GetAI = &GetAI_npc_priest_epic_quest_caller;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_priest_quest_peasant";
    newscript->GetAI = &GetAI_npc_priest_quest_peasant;
    newscript->RegisterSelf();
}

