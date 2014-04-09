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
SDName: Old_Hillsbrad
SD%Complete: 70
SDComment: Quest support: 10283, 10284. All friendly NPC's. Thrall waypoints fairly complete, missing a few details, but possible to complete escort.
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

/* ContentData
npc_erozion
npc_thrall_old_hillsbrad
npc_taretha
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "old_hillsbrad.h"

#define QUEST_ENTRY_HILLSBRAD   10282
#define QUEST_ENTRY_DIVERSION   10283
#define QUEST_ENTRY_ESCAPE      10284
#define QUEST_ENTRY_RETURN      10285
#define ITEM_ENTRY_BOMBS        25853

/*######
## npc_erozion
######*/

bool GossipHello_npc_erozion(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    ScriptedInstance* pInstance = (creature->GetInstanceScript());
    if (pInstance && pInstance->GetData(TYPE_BARREL_DIVERSION) != DONE && !player->HasItemCount(ITEM_ENTRY_BOMBS, 1))
        player->ADD_GOSSIP_ITEM(0, "I need a pack of Incendiary Bombs.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    if (!player->GetQuestRewardStatus(QUEST_ENTRY_RETURN) && player->GetQuestStatus(QUEST_ENTRY_RETURN) == QUEST_STATUS_COMPLETE)
        player->ADD_GOSSIP_ITEM(0, "Teleport please, I'm tired.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    player->SEND_GOSSIP_MENU(9778, creature->GetGUID());

    return true;
}

bool GossipSelect_npc_erozion(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_ENTRY_BOMBS, 1);
        if (msg == EQUIP_ERR_OK)
            if (Item* item = player->StoreNewItem(dest, ITEM_ENTRY_BOMBS, true))
                player->SendNewItem(item, 1, false, false);

        player->SEND_GOSSIP_MENU(9515, creature->GetGUID());
    }

    if (action == GOSSIP_ACTION_INFO_DEF+2)
        player->CLOSE_GOSSIP_MENU();

    return true;
}

/*######
## npc_thrall_old_hillsbrad
######*/

//Thrall texts
#define SAY_TH_START_EVENT_PART1    -1560023
#define SAY_TH_ARMORY               -1560024
#define SAY_TH_SKARLOC_MEET         -1560025
#define SAY_TH_SKARLOC_TAUNT        -1560026
#define SAY_TH_START_EVENT_PART2    -1560027
#define SAY_TH_MOUNTS_UP            -1560028
#define SAY_TH_CHURCH_END           -1560029
#define SAY_TH_MEET_TARETHA         -1560030
#define SAY_TH_EPOCH_WONDER         -1560031
#define SAY_TH_EPOCH_KILL_TARETHA   -1560032
#define SAY_TH_EVENT_COMPLETE       -1560033

#define SAY_TH_RANDOM_LOW_HP1       -1560034
#define SAY_TH_RANDOM_LOW_HP2       -1560035

#define SAY_TH_RANDOM_DIE1          -1560036
#define SAY_TH_RANDOM_DIE2          -1560037

#define SAY_TH_RANDOM_AGGRO1        -1560038
#define SAY_TH_RANDOM_AGGRO2        -1560039
#define SAY_TH_RANDOM_AGGRO3        -1560040
#define SAY_TH_RANDOM_AGGRO4        -1560041

#define SAY_TH_RANDOM_KILL1         -1560042
#define SAY_TH_RANDOM_KILL2         -1560043
#define SAY_TH_RANDOM_KILL3         -1560044

#define SAY_TH_LEAVE_COMBAT1        -1560045
#define SAY_TH_LEAVE_COMBAT2        -1560046
#define SAY_TH_LEAVE_COMBAT3        -1560047

//Taretha texts
#define SAY_TA_FREE                 -1560048
#define SAY_TA_ESCAPED              -1560049

//Misc for Thrall
#define SPELL_STRIKE                14516
#define SPELL_SHIELD_BLOCK          12169
#define SPELL_SUMMON_EROZION_IMAGE  33954                   //if thrall dies during escort?

#define SPEED_WALK              (0.5f)
#define SPEED_RUN               (1.0f)
#define SPEED_MOUNT             (1.6f)

#define THRALL_WEAPON_MODEL     22106
#define THRALL_WEAPON_INFO      218169346
#define THRALL_SHIELD_MODEL     18662
#define THRALL_SHIELD_INFO      234948100
#define THRALL_MODEL_UNEQUIPPED 17292
#define THRALL_MODEL_EQUIPPED   18165

//Misc Creature entries
#define ENTRY_ARMORER               18764
#define ENTRY_SCARLOC               17862

#define MOB_ENTRY_RIFLE             17820
#define MOB_ENTRY_WARDEN            17833
#define MOB_ENTRY_VETERAN           17860
#define MOB_ENTRY_WATCHMAN          17814
#define MOB_ENTRY_SENTRY            17815

#define MOB_ENTRY_BARN_GUARDSMAN    18092
#define MOB_ENTRY_BARN_PROTECTOR    18093
#define MOB_ENTRY_BARN_LOOKOUT      18094

#define MOB_ENTRY_CHURCH_GUARDSMAN  23175
#define MOB_ENTRY_CHURCH_PROTECTOR  23179
#define MOB_ENTRY_CHURCH_LOOKOUT    23177

#define MOB_ENTRY_INN_GUARDSMAN     23176
#define MOB_ENTRY_INN_PROTECTOR     23180
#define MOB_ENTRY_INN_LOOKOUT       23178

#define SKARLOC_MOUNT               18798
#define SKARLOC_MOUNT_MODEL         18223
#define EROZION_ENTRY               18723
#define ENTRY_EPOCH                 18096

//gossip items
#define GOSSIP_ID_START         9568
#define GOSSIP_ID_SKARLOC1      9614                        //I'm glad Taretha is alive. We now must find a way to free her...
#define GOSSIP_ITEM_SKARLOC1    "Taretha cannot see you, Thrall."
#define GOSSIP_ID_SKARLOC2      9579                        //What do you mean by this? Is Taretha in danger?
#define GOSSIP_ITEM_SKARLOC2    "The situation is rather complicated, Thrall. It would be best for you to head into the mountains now, before more of Blackmoore's men show up. We'll make sure Taretha is safe."
#define GOSSIP_ID_SKARLOC3      9580

#define GOSSIP_ID_TARREN        9597                        //tarren mill is beyond these trees
#define GOSSIP_ITEM_TARREN      "We're ready, Thrall."

#define GOSSIP_ID_COMPLETE      9578                        //Thank you friends, I owe my freedom to you. Where is Taretha? I hoped to see her

#define GOSSIP_ITEM_WALKING     "We are ready to get you out of here, Thrall. Let's go!"

struct npc_thrall_old_hillsbradAI : public npc_escortAI
{
    npc_thrall_old_hillsbradAI(Creature *c) : npc_escortAI(c)
    {
        pInstance = c->GetInstanceScript();
        HadMount = false;
        me->setActive(true);
    }

    ScriptedInstance *pInstance;

    uint64 TarethaGUID;

    bool LowHp;
    bool HadMount;

    void WaypointReached(uint32 i)
    {
        if (!pInstance)
            return;

        switch (i)
        {
            case 0:
                DoScriptText(SAY_TH_START_EVENT_PART1, me);
                break;
            case 9:
                SetRun(false);
                me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACKUNARMED);
                if (Creature* armorer = me->FindNearestCreature(ENTRY_ARMORER, 2.0f))
                {
                    me->Kill(armorer, false);
                    me->Say("That's enough out of him.", 0, 0);
                }
                break;
            case 10:
                me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
                DoScriptText(SAY_TH_ARMORY, me);
                break;
            case 11:
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, THRALL_WEAPON_MODEL);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, THRALL_WEAPON_INFO);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+1, 781);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, THRALL_SHIELD_MODEL);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+2, THRALL_SHIELD_INFO);
                me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+3, 1038);
                me->SetDisplayId(THRALL_MODEL_EQUIPPED);
                me->Say("Let's go.", 0, 0);
                break;
            case 12:
                SetRun();
                break;
            case 16:
                me->SummonCreature(MOB_ENTRY_RIFLE, 2200.28f, 137.37f, 87.93f, 5.07f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_WARDEN, 2197.44f, 131.83f, 87.93f, 0.78f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_VETERAN, 2203.62f, 135.40f, 87.93f, 3.70f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_VETERAN, 2200.75f, 130.13f, 87.93f, 1.48f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                break;
            case 22:
                me->SummonCreature(MOB_ENTRY_RIFLE, 2135.80f, 154.01f, 67.45f, 4.98f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_WARDEN, 2144.36f, 151.87f, 67.74f, 4.46f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_VETERAN, 2142.12f, 154.41f, 67.12f, 4.56f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_VETERAN, 2138.08f, 155.38f, 67.24f, 4.60f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                break;
            case 26:
                me->SummonCreature(MOB_ENTRY_RIFLE, 2102.98f, 192.17f, 65.24f, 6.02f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_WARDEN, 2108.48f, 198.75f, 65.18f, 5.15f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_VETERAN, 2106.11f, 197.29f, 65.18f, 5.63f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_VETERAN, 2104.18f, 194.82f, 65.18f, 5.75f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                break;
            case 30:
                DoScriptText(SAY_TH_SKARLOC_MEET, me);
                if (Creature* Skarloc = me->SummonCreature(ENTRY_SCARLOC, 2036.48f, 271.22f, 63.43f, 5.27f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000))
                    Skarloc->GetMotionMaster()->MovePoint(0, 2067.84f, 224.376f, 64.8022f);
                me->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                break;
            case 31:
                SetEscortPaused(true);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                SetRun(false);
                break;
            case 32:
                DoScriptText(SAY_TH_MOUNTS_UP, me);
                DoMount();
                SetRun();
                break;
            case 60:
                me->SummonCreature(SKARLOC_MOUNT, 2490.08f, 627.695f, 58.539f, 1.161f, TEMPSUMMON_TIMED_DESPAWN, 9000);
                DoUnmount();
                HadMount = false;
                SetRun(false);
                break;
            case 61:
                me->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
                //make horsie run off
                if (Creature* horse = me->FindNearestCreature(SKARLOC_MOUNT, 2.0f))
                    horse->GetMotionMaster()->MovePoint(0, 2498.437f, 576.647f, 55.8595f);
                SetEscortPaused(true);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pInstance->SetData(TYPE_THRALL_PART2, DONE);
                SetRun();
                break;
            case 65:
                SetRun(false);
                break;
            case 69:
                me->SummonCreature(MOB_ENTRY_CHURCH_PROTECTOR, 2500.22f, 692.60f, 55.50f, 2.84f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                me->SummonCreature(MOB_ENTRY_CHURCH_LOOKOUT, 2500.13f, 696.55f, 55.51f, 3.38f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                me->SummonCreature(MOB_ENTRY_CHURCH_GUARDSMAN, 2500.55f, 693.64f, 55.50f, 3.14f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                me->SummonCreature(MOB_ENTRY_CHURCH_GUARDSMAN, 2500.94f, 695.81f, 55.50f, 3.14f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000);
                break;
            case 70:
                me->Say("Taretha isn't here. Let's head into town.", 0, 0);
                break;
            case 72:
                SetRun();
                break;
            case 82:
                SetRun(false);
                break;
            case 84:
                me->SummonCreature(MOB_ENTRY_CHURCH_PROTECTOR, 2627.33f, 646.82f, 56.03f, 4.28f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);
                me->SummonCreature(MOB_ENTRY_CHURCH_LOOKOUT, 2624.14f, 648.03f, 56.03f, 4.50f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);
                me->SummonCreature(MOB_ENTRY_CHURCH_GUARDSMAN, 2625.32f, 649.60f, 56.03f, 4.38f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);
                me->SummonCreature(MOB_ENTRY_CHURCH_GUARDSMAN, 2627.22f, 649.00f, 56.03f, 4.34f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 5000);
                break;
            case 85:
                DoScriptText(SAY_TH_CHURCH_END, me);
                SetRun();
                break;
            case 92:
                me->AddUnitMovementFlag(MOVEFLAG_WALK_MODE);
                SetRun(false);
                break;
            case 94:
                me->SummonCreature(MOB_ENTRY_INN_PROTECTOR, 2652.71f, 660.31f, 61.93f, 1.67f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_INN_LOOKOUT, 2648.96f, 662.59f, 61.93f, 0.79f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_INN_GUARDSMAN, 2657.36f, 662.34f, 61.93f, 2.68f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                me->SummonCreature(MOB_ENTRY_INN_GUARDSMAN, 2656.39f, 659.77f, 61.93f, 2.61f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                break;
            case 95:
                if (uint64 TarethaGUID = pInstance->GetData64(DATA_TARETHA))
                {
                    if (Unit* Taretha = Unit::GetUnit((*me), TarethaGUID))
                        DoScriptText(SAY_TA_ESCAPED, Taretha, me);
                }
                break;
            case 96:
                DoScriptText(SAY_TH_MEET_TARETHA, me);
                pInstance->SetData(TYPE_THRALL_PART3, DONE);
                SetEscortPaused(true);
                break;
            case 97:
                DoScriptText(SAY_TH_EPOCH_WONDER, me);
                break;
            case 98:
                DoScriptText(SAY_TH_EPOCH_KILL_TARETHA, me);
                SetRun();
                break;
            case 99:
                if (Creature* Epoch = me->FindNearestCreature(ENTRY_EPOCH, 50.0f, true))
                {
                    Epoch->SendPlaySound(10419, false);
                    Epoch->Yell("Taretha's life hangs in the balance. Surely you care for her. Surely you wish to save her...", 0, 0);
                }
                //trigger epoch Yell("Thrall! Come outside and face your fate! ....")
                //from here, thrall should not never be allowed to move to point 107 which he currently does.
                break;

            case 107:
                {
                    //trigger taretha to run down outside
                    if (uint64 TarethaGUID = pInstance->GetData64(DATA_TARETHA))
                    {
                        if (Creature* Taretha = (Unit::GetCreature(*me, TarethaGUID)))
                        {
                            if (Player* player = GetPlayerForEscort())
                                CAST_AI(npc_escortAI, (Taretha->AI()))->Start(false, true, player->GetGUID());
                        }
                    }

                    //kill credit Creature for quest
                    Map* pMap = me->GetMap();
                    Map::PlayerList const& players = pMap->GetPlayers();
                    if (!players.isEmpty() && pMap->IsDungeon())
                    {
                        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        {
                            if (Player* player = itr->getSource())
                                player->KilledMonsterCredit(20156, me->GetGUID());
                        }
                    }

                    //alot will happen here, thrall and taretha talk, erozion appear at spot to explain
                    me->SummonCreature(EROZION_ENTRY, 2646.47f, 680.416f, 55.38f, 4.16f, TEMPSUMMON_TIMED_DESPAWN, 120000);
                }
                break;
            case 109:
                //last waypoint, just set Thrall invisible, respawn is turned off
                me->SetVisibility(VISIBILITY_OFF);
                break;
        }
    }

    void Reset()
    {
        DoUnmount();
        HadMount = false;

        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY, 0);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO, 0);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+1, 0);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY+1, 0);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+2, 0);
        me->SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO+3, 0);
        me->SetDisplayId(THRALL_MODEL_UNEQUIPPED);
    }

    void EnterEvadeMode()
    {
        LowHp = false;

        if (HadMount)
            DoMount();

        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            switch (rand()%8)
            {
                case 1: DoScriptText(SAY_TH_LEAVE_COMBAT1, me); break;
                case 2: DoScriptText(SAY_TH_LEAVE_COMBAT2, me); break;
                case 3: DoScriptText(SAY_TH_LEAVE_COMBAT3, me); break;
                default:
                    break;
            }
        }

        npc_escortAI::EnterEvadeMode();
    }

    void StartWP()
    {
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        SetEscortPaused(false);
    }

    void DoMount()
    {
        me->Mount(SKARLOC_MOUNT_MODEL);
        me->SetSpeed(MOVE_RUN, SPEED_MOUNT);
    }

    void DoUnmount()
    {
        me->Unmount();
        me->SetSpeed(MOVE_RUN, SPEED_RUN);
    }

    void EnterCombat(Unit* who)
    {
        switch (rand()%10)
        {
            case 1: DoScriptText(SAY_TH_RANDOM_AGGRO1, me); break;
            case 2: DoScriptText(SAY_TH_RANDOM_AGGRO2, me); break;
            case 3: DoScriptText(SAY_TH_RANDOM_AGGRO3, me); break;
            case 4: DoScriptText(SAY_TH_RANDOM_AGGRO4, me); break;
            default:
                break;
        }

        if (me->IsMounted())
        {
            DoUnmount();
            HadMount = true;
        }
    }

    void JustSummoned(Creature* summoned)
    {
         switch (summoned->GetEntry())
         {
             //TODO: make Scarloc start into event instead, and not start attack directly
             case SKARLOC_MOUNT:
             case ENTRY_SCARLOC:
             case EROZION_ENTRY:
             case ENTRY_ARMORER:
             case MOB_ENTRY_CHURCH_PROTECTOR:
             case MOB_ENTRY_CHURCH_GUARDSMAN:
             case MOB_ENTRY_CHURCH_LOOKOUT:
                 break;
             default:
                 summoned->AI()->AttackStart(me);
                 break;
         }
    }

    void KilledUnit(Unit *victim)
    {
        if (victim->GetEntry() != ENTRY_ARMORER)
            DoScriptText(RAND(SAY_TH_RANDOM_KILL1, SAY_TH_RANDOM_KILL2, SAY_TH_RANDOM_KILL3), me);
    }

    void JustDied(Unit *slayer)
    {
        if (pInstance)
        {
            pInstance->HandleGameObject(pInstance->GetData64(DATA_THRALL_DOOR), false);
            pInstance->SetData(TYPE_THRALL_EVENT, FAIL);
        }

        // Don't do a yell if he kills self (if player goes too far or at the end).
        if (slayer == me)
            return;

        DoScriptText(RAND(SAY_TH_RANDOM_DIE1, SAY_TH_RANDOM_DIE2), me);
    }

    void UpdateAI(const uint32 diff)
    {
        npc_escortAI::UpdateAI(diff);

        if (!UpdateVictim())
            return;

        //TODO: add his abilities'n-crap here
        if (!LowHp && ((me->GetHealth()*100 / me->GetMaxHealth()) < 20))
        {
            DoScriptText(RAND(SAY_TH_RANDOM_LOW_HP1, SAY_TH_RANDOM_LOW_HP2), me);
            LowHp = true;
        }
    }
};

CreatureAI* GetAI_npc_thrall_old_hillsbrad(Creature* creature)
{
    return new npc_thrall_old_hillsbradAI(creature);
}

bool GossipHello_npc_thrall_old_hillsbrad(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
    {
        player->PrepareQuestMenu(creature->GetGUID());
        player->SendPreparedQuest(creature->GetGUID());
    }

    ScriptedInstance* pInstance = (creature->GetInstanceScript());
    if (pInstance)
    {
        if (pInstance->GetData(TYPE_BARREL_DIVERSION) == DONE && !pInstance->GetData(TYPE_THRALL_EVENT))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WALKING, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(GOSSIP_ID_START, creature->GetGUID());
        }

        if (pInstance->GetData(TYPE_THRALL_PART1) == DONE && !pInstance->GetData(TYPE_THRALL_PART2))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SKARLOC1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(GOSSIP_ID_SKARLOC1, creature->GetGUID());
        }

        if (pInstance->GetData(TYPE_THRALL_PART2) == DONE && !pInstance->GetData(TYPE_THRALL_PART3))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TARREN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->SEND_GOSSIP_MENU(GOSSIP_ID_TARREN, creature->GetGUID());
        }
    }
    return true;
}

bool GossipSelect_npc_thrall_old_hillsbrad(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance* pInstance = (creature->GetInstanceScript());

    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->CLOSE_GOSSIP_MENU();
            if (pInstance)
            {
                pInstance->HandleGameObject(pInstance->GetData64(DATA_THRALL_DOOR), true);
                pInstance->SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
                pInstance->SetData(TYPE_THRALL_PART1, IN_PROGRESS);
            }

            if (npc_escortAI* pEscortAI = CAST_AI(npc_thrall_old_hillsbradAI, creature->AI()))
                pEscortAI->Start(true, true, player->GetGUID());

            CAST_AI(npc_escortAI, (creature->AI()))->SetMaxPlayerDistance(100.0f);//not really needed, because it will not despawn if player is too far
            CAST_AI(npc_escortAI, (creature->AI()))->SetDespawnAtEnd(false);
            CAST_AI(npc_escortAI, (creature->AI()))->SetDespawnAtFar(false);
            break;

        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SKARLOC2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+20);
            player->SEND_GOSSIP_MENU(GOSSIP_ID_SKARLOC2, creature->GetGUID());
            break;

        case GOSSIP_ACTION_INFO_DEF+20:
            player->SEND_GOSSIP_MENU(GOSSIP_ID_SKARLOC3, creature->GetGUID());
            creature->SummonCreature(SKARLOC_MOUNT, 2038.81f, 270.26f, 63.20f, 5.41f, TEMPSUMMON_TIMED_DESPAWN, 12000);
            if (pInstance)
                pInstance->SetData(TYPE_THRALL_PART2, IN_PROGRESS);

            DoScriptText(SAY_TH_START_EVENT_PART2, creature);

            CAST_AI(npc_thrall_old_hillsbradAI, creature->AI())->StartWP();
            break;

        case GOSSIP_ACTION_INFO_DEF+3:
            player->CLOSE_GOSSIP_MENU();
            if (pInstance)
                pInstance->SetData(TYPE_THRALL_PART3, IN_PROGRESS);
            CAST_AI(npc_thrall_old_hillsbradAI, creature->AI())->StartWP();
            break;
    }
    return true;
}

/*######
## npc_taretha
######*/

#define GOSSIP_ID_EPOCH1        9610                        //Thank you for helping Thrall escape, friends. Now I only hope
#define GOSSIP_ITEM_EPOCH1      "Strange wizard?"
#define GOSSIP_ID_EPOCH2        9613                        //Yes, friends. This man was no wizard of
#define GOSSIP_ITEM_EPOCH2      "We'll get you out. Taretha. Don't worry. I doubt the wizard would wander too far away."

struct npc_tarethaAI : public npc_escortAI
{
    npc_tarethaAI(Creature *c) : npc_escortAI(c)
    {
        pInstance = c->GetInstanceScript();
    }

    ScriptedInstance *pInstance;

    void WaypointReached(uint32 i)
    {
        switch (i)
        {
            case 6:
                DoScriptText(SAY_TA_FREE, me);
                break;
            case 7:
                me->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                break;
        }
    }
    void Reset() {}
    void EnterCombat(Unit* who) {}

    void UpdateAI(const uint32 diff)
    {
        npc_escortAI::UpdateAI(diff);
    }
};

CreatureAI* GetAI_npc_taretha(Creature* creature)
{
    return new npc_tarethaAI(creature);
}

bool GossipHello_npc_taretha(Player* player, Creature* creature)
{
    ScriptedInstance* pInstance = (creature->GetInstanceScript());
    if (pInstance && pInstance->GetData(TYPE_THRALL_PART3) == DONE && pInstance->GetData(TYPE_THRALL_PART4) == NOT_STARTED)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_EPOCH1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->SEND_GOSSIP_MENU(GOSSIP_ID_EPOCH1, creature->GetGUID());
    }
    return true;
}

bool GossipSelect_npc_taretha(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance* pInstance = (creature->GetInstanceScript());
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_EPOCH2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        player->SEND_GOSSIP_MENU(GOSSIP_ID_EPOCH2, creature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        player->CLOSE_GOSSIP_MENU();

        if (pInstance && pInstance->GetData(TYPE_THRALL_EVENT) == IN_PROGRESS)
        {
            pInstance->SetData(TYPE_THRALL_PART4, IN_PROGRESS);
            if (pInstance->GetData64(DATA_EPOCH) == 0)
                if (Creature* Epoch = creature->SummonCreature(ENTRY_EPOCH, 2639.13f, 698.55f, 65.43f, 4.59f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 180000))
                {
                    Epoch->SendPlaySound(10418, false);
                    Epoch->Yell("Thrall! Come outside and face your fate!", 0, 0);
                }

             if (uint64 ThrallGUID = pInstance->GetData64(DATA_THRALL))
             {
                 Creature* Thrall = (Unit::GetCreature((*creature), ThrallGUID));
                 if (Thrall)
                     CAST_AI(npc_thrall_old_hillsbradAI, Thrall->AI())->StartWP();
             }
        }
    }
    return true;
}

/*######
## npc_durnholde_armorer
######*/
struct npc_durnholde_armorerAI : public ScriptedAI
{
    npc_durnholde_armorerAI(Creature *c) : ScriptedAI(c)
    {
        instance = c->GetInstanceScript();
    }

    ScriptedInstance *instance;

    bool has_spoken;
    uint32 talk_timer;

    void Reset()
    {
        talk_timer = 0;
        has_spoken = false;
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!instance)
            return;

        if (who->GetTypeId() == TYPEID_UNIT && who->GetGUID() == instance->GetData64(DATA_THRALL) && me->IsWithinDistInMap(who, 10.0f))
        {
            if (instance->GetData(TYPE_THRALL_EVENT) != IN_PROGRESS)
                return;

            me->StopMoving();
            me->SetFacingToObject(who);
            talk_timer = 1000;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!instance)
            return;

        if (talk_timer && !has_spoken)
        {
            if (talk_timer <= diff)
            {
                me->Say("What's the meaning of this? GUARDS!", 0, 0);
                has_spoken = true;
            }
            else
                talk_timer -= diff;
        }
    }
};

CreatureAI* GetAI_npc_durnholde_armorer(Creature* creature)
{
    return new npc_durnholde_armorerAI (creature);
}

/*######
## AddSC
######*/

void AddSC_old_hillsbrad()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_erozion";
    newscript->pGossipHello =   &GossipHello_npc_erozion;
    newscript->pGossipSelect =  &GossipSelect_npc_erozion;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_thrall_old_hillsbrad";
    newscript->pGossipHello =  &GossipHello_npc_thrall_old_hillsbrad;
    newscript->pGossipSelect = &GossipSelect_npc_thrall_old_hillsbrad;
    newscript->GetAI = &GetAI_npc_thrall_old_hillsbrad;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_taretha";
    newscript->pGossipHello =   &GossipHello_npc_taretha;
    newscript->pGossipSelect =  &GossipSelect_npc_taretha;
    newscript->GetAI = &GetAI_npc_taretha;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_durnholde_armorer";
    newscript->GetAI = &GetAI_npc_durnholde_armorer;
    newscript->RegisterSelf();
}

