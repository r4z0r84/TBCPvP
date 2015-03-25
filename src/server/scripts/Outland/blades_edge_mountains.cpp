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
SDName: Blades_Edge_Mountains
SD%Complete: 90
SDComment: Quest support: 10556, 10609, 10682, 10980, 10512. Ogri'la->Skettis Flight. (npc_daranelle needs bit more work before consider complete)
SDCategory: Blade's Edge Mountains
EndScriptData */

/* ContentData
mobs_nether_drake
npc_daranelle
npc_overseer_nuaar
npc_saikkal_the_elder
npc_ogre_brute
npc_bloodmaul_brutebane
EndContentData */

#include "ScriptPCH.h"

/*######
## mobs_nether_drake
######*/

enum eDrake
{
    SAY_NIHIL_1                 = -1000169,
    SAY_NIHIL_2                 = -1000170,
    SAY_NIHIL_3                 = -1000171,
    SAY_NIHIL_4                 = -1000172,
    SAY_NIHIL_INTERRUPT         = -1000173,

    ENTRY_WHELP                 = 20021,
    ENTRY_PROTO                 = 21821,
    ENTRY_ADOLE                 = 21817,
    ENTRY_MATUR                 = 21820,
    ENTRY_NIHIL                 = 21823,

    SPELL_T_PHASE_MODULATOR     = 37573,

    SPELL_ARCANE_BLAST          = 38881,
    SPELL_MANA_BURN             = 38884,
    SPELL_INTANGIBLE_PRESENCE   = 36513
};

struct mobs_nether_drakeAI : public ScriptedAI
{
    mobs_nether_drakeAI(Creature *c) : ScriptedAI(c) {}

    bool IsNihil;
    uint32 NihilSpeech_Timer;
    uint32 NihilSpeech_Phase;

    uint32 ArcaneBlast_Timer;
    uint32 ManaBurn_Timer;
    uint32 IntangiblePresence_Timer;

    void Reset()
    {
        NihilSpeech_Timer = 2000;
        IsNihil = false;
        if (me->GetEntry() == ENTRY_NIHIL)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            IsNihil = true;
        }
        NihilSpeech_Phase = 1;

        ArcaneBlast_Timer = 7500;
        ManaBurn_Timer = 10000;
        IntangiblePresence_Timer = 15000;
    }

    void EnterCombat(Unit* who) { }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_T_PHASE_MODULATOR && caster->GetTypeId() == TYPEID_PLAYER)
        {
            uint32 cEntry = 0;

            switch (me->GetEntry())
            {
                case ENTRY_WHELP:
                    switch (rand()%4)
                    {
                        case 0: cEntry = ENTRY_PROTO; break;
                        case 1: cEntry = ENTRY_ADOLE; break;
                        case 2: cEntry = ENTRY_MATUR; break;
                        case 3: cEntry = ENTRY_NIHIL; break;
                    }
                    break;
                case ENTRY_PROTO:
                    switch (rand()%3)
                    {
                        case 0: cEntry = ENTRY_ADOLE; break;
                        case 1: cEntry = ENTRY_MATUR; break;
                        case 2: cEntry = ENTRY_NIHIL; break;
                    }
                    break;
                case ENTRY_ADOLE:
                    switch (rand()%3)
                    {
                        case 0: cEntry = ENTRY_PROTO; break;
                        case 1: cEntry = ENTRY_MATUR; break;
                        case 2: cEntry = ENTRY_NIHIL; break;
                    }
                    break;
                case ENTRY_MATUR:
                    switch (rand()%3)
                    {
                        case 0: cEntry = ENTRY_PROTO; break;
                        case 1: cEntry = ENTRY_ADOLE; break;
                        case 2: cEntry = ENTRY_NIHIL; break;
                    }
                    break;
                case ENTRY_NIHIL:
                    if (NihilSpeech_Phase)
                    {
                        DoScriptText(SAY_NIHIL_INTERRUPT, me);
                        IsNihil = false;
                        switch (rand()%3)
                        {
                            case 0: cEntry = ENTRY_PROTO; break;
                            case 1: cEntry = ENTRY_ADOLE; break;
                            case 2: cEntry = ENTRY_MATUR; break;
                        }
                    }
                    break;
            }

            if (cEntry)
            {
                me->UpdateEntry(cEntry);

                if (cEntry == ENTRY_NIHIL)
                {
                    me->InterruptNonMeleeSpells(true);
                    me->RemoveAllAuras();
                    me->DeleteThreatList();
                    me->CombatStop(true);
                    Reset();
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (IsNihil)
        {
            if (NihilSpeech_Phase)
            {
                if (NihilSpeech_Timer <= diff)
                {
                    switch (NihilSpeech_Phase)
                    {
                        case 1:
                            DoScriptText(SAY_NIHIL_1, me);
                            ++NihilSpeech_Phase;
                            break;
                        case 2:
                            DoScriptText(SAY_NIHIL_2, me);
                            ++NihilSpeech_Phase;
                            break;
                        case 3:
                            DoScriptText(SAY_NIHIL_3, me);
                            ++NihilSpeech_Phase;
                            break;
                        case 4:
                            DoScriptText(SAY_NIHIL_4, me);
                            ++NihilSpeech_Phase;
                            break;
                        case 5:
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                                            // + MOVEFLAG_LEVITATING
                            me->AddUnitMovementFlag(MOVEFLAG_ONTRANSPORT);
                            //then take off to random location. creature is initially summoned, so don't bother do anything else.
                            me->GetMotionMaster()->MovePoint(0, me->GetPositionX()+100, me->GetPositionY(), me->GetPositionZ()+100);
                            NihilSpeech_Phase = 0;
                            break;
                    }
                    NihilSpeech_Timer = 5000;
                } else NihilSpeech_Timer -=diff;
            }
            return;                                         //anything below here is not interesting for Nihil, so skip it
        }

        if (!UpdateVictim())
            return;

        if (IntangiblePresence_Timer <= diff)
        {
            DoCast(me->getVictim(),SPELL_INTANGIBLE_PRESENCE);
            IntangiblePresence_Timer = 15000+rand()%15000;
        } else IntangiblePresence_Timer -= diff;

        if (ManaBurn_Timer <= diff)
        {
            Unit *pTarget = me->getVictim();
            if (pTarget && pTarget->getPowerType() == POWER_MANA)
                DoCast(pTarget, SPELL_MANA_BURN);
            ManaBurn_Timer = 8000+rand()%8000;
        } else ManaBurn_Timer -= diff;

        if (ArcaneBlast_Timer <= diff)
        {
            DoCast(me->getVictim(),SPELL_ARCANE_BLAST);
            ArcaneBlast_Timer = 2500+rand()%5000;
        } else ArcaneBlast_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_mobs_nether_drake(Creature* creature)
{
    return new mobs_nether_drakeAI (creature);
}

/*######
## npc_daranelle
######*/

#define SAY_DARANELLE -1000174

struct npc_daranelleAI : public ScriptedAI
{
    npc_daranelleAI(Creature *c) : ScriptedAI(c) {}

    void Reset()
    {
    }

    void EnterCombat(Unit* who)
    {
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (who->GetTypeId() == TYPEID_PLAYER)
        {
            if (who->HasAura(36904, 0))
            {
                DoScriptText(SAY_DARANELLE, me, who);
                //TODO: Move the below to updateAI and run if this statement == true
                CAST_PLR(who)->KilledMonsterCredit(21511, me->GetGUID());
                CAST_PLR(who)->RemoveAurasDueToSpell(36904);
            }
        }

        ScriptedAI::MoveInLineOfSight(who);
    }
};

CreatureAI* GetAI_npc_daranelle(Creature* creature)
{
    return new npc_daranelleAI (creature);
}

/*######
## npc_overseer_nuaar
######*/

#define GOSSIP_HON "Overseer, I am here to negotiate on behalf of the Cenarion Expedition."

bool GossipHello_npc_overseer_nuaar(Player* player, Creature* creature)
{
    if (player->GetQuestStatus(10682) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(0, GOSSIP_HON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU(10532, creature->GetGUID());

    return true;
}

bool GossipSelect_npc_overseer_nuaar(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        player->SEND_GOSSIP_MENU(10533, creature->GetGUID());
        player->AreaExploredOrEventHappens(10682);
    }
    return true;
}

/*######
## npc_saikkal_the_elder
######*/

#define GOSSIP_HSTE "Yes... yes, it's me."
#define GOSSIP_SSTE "Yes elder. Tell me more of the book."

bool GossipHello_npc_saikkal_the_elder(Player* player, Creature* creature)
{
    if (player->GetQuestStatus(10980) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM(0, GOSSIP_HSTE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    player->SEND_GOSSIP_MENU(10794, creature->GetGUID());

    return true;
}

bool GossipSelect_npc_saikkal_the_elder(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM(0, GOSSIP_SSTE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->SEND_GOSSIP_MENU(10795, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
            player->SEND_GOSSIP_MENU(10796, creature->GetGUID());
            break;
    }
    return true;
}

/*######
## npc_bloodmaul_brutebane
######*/

enum eBloodmaul
{
    NPC_OGRE_BRUTE        = 19995,
    NPC_QUEST_CREDIT      = 21241,
    GO_KEG                = 184315
};

struct npc_bloodmaul_brutebaneAI : public ScriptedAI
{
    npc_bloodmaul_brutebaneAI(Creature *c) : ScriptedAI(c)
    {
       if (Creature* pOgre = me->FindNearestCreature(NPC_OGRE_BRUTE, 50, true))
       {
           pOgre->SetReactState(REACT_DEFENSIVE);
           pOgre->GetMotionMaster()->MovePoint(1, me->GetPositionX()-1, me->GetPositionY()+1, me->GetPositionZ());
       }
    }

    uint64 OgreGUID;

    void Reset()
    {
        OgreGUID = 0;
    }

    void UpdateAI(const uint32 /*uiDiff*/) {}
};

CreatureAI* GetAI_npc_bloodmaul_brutebane(Creature* creature)
{
    return new npc_bloodmaul_brutebaneAI (creature);
}

/*######
## npc_ogre_brute
######*/

struct npc_ogre_bruteAI : public ScriptedAI
{
    npc_ogre_bruteAI(Creature *c) : ScriptedAI(c) {}

    uint64 PlayerGUID;

    void Reset()
    {
        PlayerGUID = 0;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!pWho || (!pWho->isAlive()))
            return;

        if (me->IsWithinDistInMap(pWho, 50.0f) && (pWho->GetTypeId() == TYPEID_PLAYER) && pWho->ToPlayer()->GetQuestStatus(10512) == QUEST_STATUS_INCOMPLETE)
            PlayerGUID = pWho->GetGUID();
    }

    void MovementInform(uint32 /*uiMotionType*/, uint32 uiPointId)
    {
        if (Player* player = Unit::GetPlayer(*me, PlayerGUID))
        {
            if (uiPointId == 1)
            {
                if (GameObject* pKeg = me->FindNearestGameObject(GO_KEG, 20))
                    pKeg->Delete();
                me->HandleEmoteCommand(7);
                me->SetReactState(REACT_AGGRESSIVE);
                me->GetMotionMaster()->MoveTargetedHome();
                if (Creature* pCredit = me->FindNearestCreature(NPC_QUEST_CREDIT, 50, true))
                    player->KilledMonsterCredit(NPC_QUEST_CREDIT, pCredit->GetGUID());
            }
        }
    }

    void UpdateAI(const uint32 /*diff*/)
    {
        if (!UpdateVictim())
            return;
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_ogre_brute(Creature* creature)
{
    return new npc_ogre_bruteAI(creature);
}

/*#########
# go_thunderspike
# UPDATE `gameobject_template` SET `ScriptName` = "go_thunderspike" WHERE `entry` = 184729;
#########*/

#define Q_THE_THUNDERSPIKE 10526
#define GOR_GRIMGUT_ENTRY  21319

bool GOUse_go_thunderspike(Player* player, GameObject* _GO)
{
    if (player->GetQuestStatus(Q_THE_THUNDERSPIKE) == QUEST_STATUS_INCOMPLETE)
    {
        // to prevent spawn spam :)
        if (Creature *pGor = GetClosestCreatureWithEntry(player, GOR_GRIMGUT_ENTRY, 50.0f, true))
        {
            if (!pGor->getVictim())
                pGor->AI()->AttackStart(player);

            return false;
        }

        Position dest;
        //player->GetValidPointInAngle(dest, 5.0f, frand(0.0f, 2*M_PI), true);
        player->GetPosition(&dest);
        if (Creature* pGor = player->SummonCreature(GOR_GRIMGUT_ENTRY, dest.m_positionX, dest.m_positionY, dest.m_positionZ, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 60000))
            pGor->AI()->AttackStart(player);
    }

    return false;
}

/*######
## mob_aether_ray
######*/

#define EMOTE_WEAK "appears ready to be wrangled."
enum eAetherRay
{
    SPELL_SUMMON_WRANGLED = 40917,
    SPELL_ROPE_CHANNEL_VISUAL = 40926,
    SPELL_CHANNEL = 40626,
    QUEST_CREDIT = 23343
};

struct mob_aether_rayAI : public ScriptedAI
{
    mob_aether_rayAI(Creature* c) : ScriptedAI(c) {}

    bool isWeak;
    uint64 playerGUID;
    uint32 checkTimer;

    void Reset()
    {
        isWeak = false;
        checkTimer = 3000;
        playerGUID = 0;
    }

    void EnterCombat(Unit* who)
    {
        if (Player* player = who->GetCharmerOrOwnerPlayerOrPlayerItself())
            playerGUID = player->GetGUID();
    }

    void JustSummoned(Creature* summoned)
    {
        if (Player* player = Unit::GetPlayer(*me, playerGUID))
        {
            player->CastSpell(summoned, SPELL_ROPE_CHANNEL_VISUAL, false);
            summoned->GetMotionMaster()->MoveFollow(player, PET_FOLLOW_DIST, me->GetFollowAngle());
        }
            
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Support for quest 11066 and 11065
        if (playerGUID) 
        {
            if (Player* target = Unit::GetPlayer(*me, playerGUID))
            {
                if (target && !isWeak && me->GetHealth() < (me->GetMaxHealth() / 100 * 40)
                    && (target->GetQuestStatus(11066) == QUEST_STATUS_INCOMPLETE || target->GetQuestStatus(11065) == QUEST_STATUS_INCOMPLETE))
                {
                    me->MonsterTextEmote(EMOTE_WEAK, 0, false);
                    isWeak = true;
                }

                if (checkTimer <= diff)
                {
                    if (isWeak && me->HasAura(40856, 0))
                    {
                        me->CastSpell(target, SPELL_SUMMON_WRANGLED, false);
                        target->KilledMonsterCredit(QUEST_CREDIT, me->GetGUID());
                        me->DisappearAndDie();
                    }

                    checkTimer = 5000;
                }
                else
                    checkTimer -= diff;
            }
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_aether_ray(Creature* creature)
{
    return new mob_aether_rayAI(creature);
}

/*######
## npc_skyguard_khatie
######*/

enum eKhatie
{
    FACTION_SHATARI_SKYGUARD = 1031,
    GOSSIP_TEXT_ENTRY1 = 10907,
    GOSSIP_TEXT_ENTRY2 = 10997,
    GOSSIP_TEXT_ENTRY3 = 11001,
    GOSSIP_TEXT_ENTRY4 = 11002,
    GOSSIP_TEXT_ENTRY5 = 11004,

    SAY1 = -1580200,
    SAY2 = -1580201,
    SAY3 = -1580202,
    SAY4 = -1580203,
    SAY5 = -1580204,
    SAY6 = -1580205,
    SAY7 = -1580206,

    QUEST_WRANGLE_MORE_AETHER_RAYS = 11066,
    QUEST_WRANGLE_SOME_AETHER_RAYS = 11065
};

bool GossipHello_npc_skyguard_khatie(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    uint32 textEntry = 0;
    switch (player->GetReputationRank(FACTION_SHATARI_SKYGUARD))
    {
        case REP_FRIENDLY:
            textEntry = GOSSIP_TEXT_ENTRY2;
            break;
        case REP_HONORED:
            textEntry = GOSSIP_TEXT_ENTRY3;
            break;
        case REP_REVERED:
            textEntry = GOSSIP_TEXT_ENTRY4;
            break;
        case REP_EXALTED:
            textEntry = GOSSIP_TEXT_ENTRY5;
            break;
        default:
            textEntry = GOSSIP_TEXT_ENTRY1;
            break;
    }

    player->SEND_GOSSIP_MENU(textEntry, creature->GetGUID());
    return true;
}

bool QuestComplete_npc_skyguard_khatie(Player* player, Creature* creature, Quest const *_Quest)
{
    if (_Quest->GetQuestId() == QUEST_WRANGLE_MORE_AETHER_RAYS ||
        _Quest->GetQuestId() == QUEST_WRANGLE_SOME_AETHER_RAYS)
    {

        creature->MonsterSay(RAND(SAY1, SAY2, SAY3, SAY4, SAY5, SAY6, SAY7), LANG_UNIVERSAL, 0);
    }

    return true;
}

/*######
## npc_skyguard_windcharger
######*/

enum eASkyguardWindcharger
{
    SPELL_NET = 12024,
    SAY_CHEER1 = -1580300,
    SAY_CHEER2 = -1580301,
    SAY_CHEER3 = -1580302,
    SAY_CHEER4 = -1580303,
    SAY_CHEER5 = -1580304,
    SAY_CHEER6 = -1580305,
    SAY_CHEER7 = -1580306
};

struct npc_skyguard_windchargerAI : public ScriptedAI
{
    npc_skyguard_windchargerAI(Creature* c) : ScriptedAI(c) {}

    bool canSay;
    uint32 sayTimer;
    uint32 netTimer;

    void Reset()
    {
        canSay = false;
        netTimer = 1000;
        sayTimer = urand(1000, 1 * HOUR * IN_MILLISECONDS);
    }

    void MoveInLineOfSight(Unit* who)
    {
        if (!canSay)
            return;

        if (Player* player = who->ToPlayer())
        {
            if (me->IsWithinDistInMap(player, 5.0f))
            {
                if (player->GetReputationRank(FACTION_SHATARI_SKYGUARD) >= REP_REVERED)
                {
                    me->MonsterSay(RAND(SAY_CHEER1, SAY_CHEER2, SAY_CHEER3, SAY_CHEER4, SAY_CHEER5, SAY_CHEER6, SAY_CHEER7), LANG_UNIVERSAL, player->GetGUID());
                    canSay = false;
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (sayTimer <= diff)
        {
            canSay = true;
            sayTimer = urand(1000, 1 * HOUR * IN_MILLISECONDS);
        }
        else
            sayTimer -= diff;

        if (!UpdateVictim())
            return;

        if (netTimer <= diff)
        {
            DoCastVictim(SPELL_NET, true);
            netTimer = 7000;
        }
        else
            netTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_skyguard_windcharger(Creature* creature)
{
    return new npc_skyguard_windchargerAI(creature);
}

/*######
## npc_skyguard_handler_irena
######*/

#define GOSSIP_IRENA "Yes, I'd love a ride to Blackwind Landing."

bool GossipHello_npc_skyguard_handler_irena(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    uint32 textEntry = 0;
    if (player->GetReputationRank(FACTION_SHATARI_SKYGUARD) >= REP_EXALTED)
    {
        textEntry = 10978;
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_IRENA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    }
    else
        textEntry = 10842;

    player->SEND_GOSSIP_MENU(textEntry, creature->GetGUID());
    return true;
}

bool GossipSelect_npc_skyguard_handler_irena(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 1)
        player->CastSpell(player, 41278, true);

    return true;
}

void AddSC_blades_edge_mountains()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mobs_nether_drake";
    newscript->GetAI = &GetAI_mobs_nether_drake;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_daranelle";
    newscript->GetAI = &GetAI_npc_daranelle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_overseer_nuaar";
    newscript->pGossipHello = &GossipHello_npc_overseer_nuaar;
    newscript->pGossipSelect = &GossipSelect_npc_overseer_nuaar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_saikkal_the_elder";
    newscript->pGossipHello = &GossipHello_npc_saikkal_the_elder;
    newscript->pGossipSelect = &GossipSelect_npc_saikkal_the_elder;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_bloodmaul_brutebane";
    newscript->GetAI = &GetAI_npc_bloodmaul_brutebane;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_ogre_brute";
    newscript->GetAI = &GetAI_npc_ogre_brute;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_thunderspike";
    newscript->pGOHello = &GOUse_go_thunderspike;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_aether_ray";
    newscript->GetAI = &GetAI_mob_aether_ray;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_skyguard_khatie";
    newscript->pGossipHello = &GossipHello_npc_skyguard_khatie;
    newscript->pQuestComplete = &QuestComplete_npc_skyguard_khatie;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_skyguard_windcharger";
    newscript->GetAI = &GetAI_npc_skyguard_windcharger;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_skyguard_handler_irena";
    newscript->pGossipHello = &GossipHello_npc_skyguard_handler_irena;
    newscript->pGossipSelect = &GossipSelect_npc_skyguard_handler_irena;
    newscript->RegisterSelf();
}
