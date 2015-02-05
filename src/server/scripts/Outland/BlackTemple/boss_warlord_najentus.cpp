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
SDName: Boss_Warlord_Najentus
SD%Complete: 95
SDComment:
SDCategory: Black Temple
EndScriptData */

#include "ScriptPCH.h"
#include "black_temple.h"

enum eEnums
{
    SAY_AGGRO                       = -1564000,
    SAY_NEEDLE1                     = -1564001,
    SAY_NEEDLE2                     = -1564002,
    SAY_SLAY1                       = -1564003,
    SAY_SLAY2                       = -1564004,
    SAY_SPECIAL1                    = -1564005,
    SAY_SPECIAL2                    = -1564006,
    SAY_ENRAGE1                     = -1564007,           //is this text actually in use?
    SAY_ENRAGE2                     = -1564008,
    SAY_DEATH                       = -1564009,

    //Spells
    SPELL_NEEDLE_SPINE              = 39992,
    SPELL_TIDAL_BURST               = 39878,
    SPELL_TIDAL_SHIELD              = 39872,
    SPELL_IMPALING_SPINE            = 39837,
    SPELL_CREATE_NAJENTUS_SPINE     = 39956,
    SPELL_HURL_SPINE                = 39948,
    SPELL_BERSERK                   = 45078,

    GOBJECT_SPINE                   = 185584
};

struct boss_najentusAI : public ScriptedAI
{
    boss_najentusAI(Creature *c) : ScriptedAI(c)
    {
        instance = c->GetInstanceScript();
        c->GetPosition(&centerPos);
    }

    ScriptedInstance* instance;

    uint32 NeedleSpineTimer;
    uint32 EnrageTimer;
    uint32 SpecialYellTimer;
    uint32 TidalShieldTimer;
    uint32 ImpalingSpineTimer;
    uint32 CheckTimer;

    bool checkAura;

    Position centerPos;

    std::map<uint64, uint64> SpineTargetMap;

    void Reset()
    {
        EnrageTimer = 330000;
        SpecialYellTimer = 45000 + (rand()%76)*1000;
        TidalShieldTimer = 60000;

        ImpalingSpineTimer = 20000;
        NeedleSpineTimer = 2000 + rand() % 2000;
        TidalShieldTimer = 60000;
        CheckTimer = 3000;

        checkAura = false;

        std::map<uint64, uint64>::iterator spineTarget = SpineTargetMap.begin();
        for (; spineTarget != SpineTargetMap.end(); ++spineTarget)
        {
            if (GameObject *go = GameObject::GetGameObject(*me, spineTarget->first))
            {
                go->SetLootState(GO_JUST_DEACTIVATED);
                go->SetRespawnTime(0);
            }
        }

        SpineTargetMap.clear();

        DeleteSpine();

        if (instance)
            instance->SetData(DATA_HIGHWARLORDNAJENTUSEVENT, NOT_STARTED);
    }

    void KilledUnit(Unit * /*victim*/)
    {
        DoScriptText(rand()%2 ? SAY_SLAY1 : SAY_SLAY2, me);
    }

    void JustDied(Unit * /*victim*/)
    {
        if (instance)
            instance->SetData(DATA_HIGHWARLORDNAJENTUSEVENT, DONE);

        DeleteSpine();
        DoScriptText(SAY_DEATH, me);
    }

    bool TryDoCast(Unit *victim, uint32 spellId, bool triggered = false)
    {
        if (me->IsNonMeleeSpellCasted(false)) return false;

        DoCast(victim, spellId, triggered);
        return true;
    }

    void SpellHit(Unit * /*caster*/, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_HURL_SPINE && me->HasAura(SPELL_TIDAL_SHIELD, 0))
        {
            me->RemoveAurasDueToSpell(SPELL_TIDAL_SHIELD);
            DoCast(me, SPELL_TIDAL_BURST, true);
            ResetTimer();
        }
    }

    void EnterCombat(Unit * /*who*/)
    {
        if (instance)
            instance->SetData(DATA_HIGHWARLORDNAJENTUSEVENT, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, me);
        DoZoneInCombat();
    }

    void ResetTimer(uint32 inc = 0)
    {
        NeedleSpineTimer = 10000 + inc;
        ImpalingSpineTimer = 20000 + inc;
    }

    bool RemoveImpalingSpine(uint64 spineGUID)
    {
        if (SpineTargetMap.empty())
            return false;

        std::map<uint64, uint64>::iterator spineTarget = SpineTargetMap.find(spineGUID);
        if (spineTarget == SpineTargetMap.end())
            return false;

        Unit *pTarget = Unit::GetUnit(*me, spineTarget->second);
        if (pTarget && pTarget->HasAura(SPELL_IMPALING_SPINE, 1))
            pTarget->RemoveAurasDueToSpell(SPELL_IMPALING_SPINE);
        SpineTargetMap.erase(spineTarget);
        return true;
    }

    void DeleteSpine()
    {
        InstanceMap::PlayerList const &playerliste = ((InstanceMap*)me->GetMap())->GetPlayers();
        InstanceMap::PlayerList::const_iterator it;

        Map::PlayerList const &PlayerList = ((InstanceMap*)me->GetMap())->GetPlayers();
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
        {
            Player* i_pl = i->getSource();
            if (i_pl && i_pl->HasItemCount(32408, i_pl->GetItemCount(32408)))
                i_pl->DestroyItemCount(32408, i_pl->GetItemCount(32408), true);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (CheckTimer < diff)
        {
            if (!me->IsWithinDist3d(&centerPos, 105.0f))
                EnterEvadeMode();

            CheckTimer = 3000;
        }
        else CheckTimer -= diff;

        if (checkAura)
        {
            if (me->HasAura(SPELL_TIDAL_SHIELD, 0))
                NeedleSpineTimer = 10000;
            else
                checkAura = false;
        }

        if (TidalShieldTimer <= diff)
        {
            if (TryDoCast(me, SPELL_TIDAL_SHIELD, true))
            {
                ResetTimer(45000);
                TidalShieldTimer = 60000;
                checkAura = true;
            }
        } else TidalShieldTimer -= diff;

        if (!me->HasAura(SPELL_BERSERK, 0))
        {
            if (EnrageTimer <= diff)
            {
                DoScriptText(SAY_ENRAGE2, me);
                DoCast(me, SPELL_BERSERK, true);
            } else EnrageTimer -= diff;
        }

        if (SpecialYellTimer <= diff)
        {
            switch (rand()%2)
            {
            case 0: DoScriptText(SAY_SPECIAL1, me); break;
            case 1: DoScriptText(SAY_SPECIAL2, me); break;
            }
            SpecialYellTimer = 25000 + (rand()%76)*1000;
        } else SpecialYellTimer -= diff;

        if (ImpalingSpineTimer <= diff)
        {
            if (!me->IsNonMeleeSpellCasted(false))
            {
                Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 150, true);
                if (!pTarget)
                    pTarget = me->getVictim();

                if (pTarget)
                {
                    DoCast(pTarget, SPELL_IMPALING_SPINE, true);
                    //must let target summon, otherwise you cannot click the spine
                    GameObject* spine = pTarget->SummonGameObject(GOBJECT_SPINE, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), me->GetOrientation(), 0, 0, 0, 0, 30);
                    if (spine)
                    {
                        std::pair<uint64, uint64> spineTarget(spine->GetGUID(), pTarget->GetGUID());
                        SpineTargetMap.insert(spineTarget);
                    }

                    switch (rand()%2)
                    {
                    case 0: DoScriptText(SAY_NEEDLE1, me); break;
                    case 1: DoScriptText(SAY_NEEDLE2, me); break;
                    }
                    ImpalingSpineTimer = 21000;
                }
            }
        } else ImpalingSpineTimer -= diff;

        if (NeedleSpineTimer <= diff)
        {
            if (TryDoCast(me, SPELL_NEEDLE_SPINE, true))
                NeedleSpineTimer = 3000;
        } else NeedleSpineTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

bool GOHello_go_najentus_spine(Player* player, GameObject* pGo)
{
    if (ScriptedInstance* instance = pGo->GetInstanceScript())
        if (Creature* Najentus = Unit::GetCreature(*pGo, instance->GetData64(DATA_HIGHWARLORDNAJENTUS)))
            if (CAST_AI(boss_najentusAI, Najentus->AI())->RemoveImpalingSpine(pGo->GetGUID()))
            {
                player->CastSpell(player, SPELL_CREATE_NAJENTUS_SPINE, true);
                pGo->Delete();
            }
    return true;
}

CreatureAI* GetAI_boss_najentus(Creature* creature)
{
    return new boss_najentusAI (creature);
}

void AddSC_boss_najentus()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_najentus";
    newscript->GetAI = &GetAI_boss_najentus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_najentus_spine";
    newscript->pGOHello = &GOHello_go_najentus_spine;
    newscript->RegisterSelf();
}

