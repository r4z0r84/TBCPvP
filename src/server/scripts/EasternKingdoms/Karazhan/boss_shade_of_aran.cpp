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
SDName: Boss_Shade_of_Aran
SD%Complete: 95
SDComment: Flame wreath missing cast animation, mods won't triggere.
SDCategory: Karazhan
EndScriptData */

#include "ScriptPCH.h"
#include "ScriptedSimpleAI.h"
#include "karazhan.h"
#include "GameObject.h"

enum ShadeOfAran
{
    // SAY_AGGRO
    SAY_AGGRO1                  = -1532073,
    SAY_AGGRO2                  = -1532074,
    SAY_AGGRO3                  = -1532075,

    // SAY_FLAMEWREATH
    SAY_FLAMEWREATH1            = -1532076,
    SAY_FLAMEWREATH2            = -1532077,

    // SAY_BLIZZARD
    SAY_BLIZZARD1               = -1532078,
    SAY_BLIZZARD2               = -1532079,

    // SAY_EXPLOSION
    SAY_EXPLOSION1              = -1532080,
    SAY_EXPLOSION2              = -1532081,

    SAY_DRINK                   = -1532082,
    SAY_ELEMENTALS              = -1532083,

    // SAY_KILL
    SAY_KILL1                   = -1532084,
    SAY_KILL2                   = -1532085,

    SAY_TIMEOVER                = -1532086,
    SAY_DEATH                   = -1532087,
    SAY_ATIESH                  = -1532088,
};

enum Spells
{
    SPELL_FROSTBOLT             = 29954,
    SPELL_FIREBALL              = 29953,
    SPELL_ARCMISSLE             = 29955,
    SPELL_CHAINSOFICE           = 29991,
    SPELL_DRAGONSBREATH         = 29964,
    SPELL_MASSSLOW              = 30035,
    SPELL_FLAME_WREATH          = 29946,
    SPELL_FLAME_WREATH_AURA     = 29947,
    SPELL_AOE_CS                = 29961,
    SPELL_PLAYERPULL            = 32265,
    SPELL_AEXPLOSION            = 29973,
    SPELL_MASS_POLY             = 29963,
    SPELL_BLINK_CENTER          = 29967,
    SPELL_ELEMENTALS            = 29962,
    SPELL_ELEMENTAL1            = 29962,
    SPELL_ELEMENTAL2            = 37053,
    SPELL_ELEMENTAL3            = 37051,
    SPELL_ELEMENTAL4            = 37052,
    SPELL_CONJURE               = 29975,
    SPELL_DRINKING              = 30024,
    SPELL_POTION                = 32453,
    SPELL_AOE_PYROBLAST         = 29978,
    SPELL_SUMMON_BLIZZARD       = 29969,
    SPELL_EXPLOSION             = 20476,
    SPELL_KNOCKBACK             = 11027,
    SPELL_MAGNETIC_PULL         = 29979,
    SPELL_TELEPORT_MIDDLE       = 39567,

    // Creature Spells
    SPELL_CIRCULAR_BLIZZARD     = 29951,
    SPELL_WATERBOLT             = 31012,
    SPELL_SHADOW_PYRO           = 29978,
    SPELL_FROSTBOLT_VOLLEY      = 38837,
    SPELL_AMISSILE_VOLLEY       = 29960
};

enum SuperSpell
{
    SUPER_FLAME = 0,
    SUPER_BLIZZARD,
    SUPER_AE,
};

enum Creatues
{
    // Creatures
    CREATURE_WATER_ELEMENTAL    = 17167,
    CREATURE_SHADOW_OF_ARAN     = 18254,
    CREATURE_ARAN_BLIZZARD      = 17161
};

enum DrinkingState
{
    DRINKING_NO_DRINKING,
    DRINKING_PREPARING,
    DRINKING_PREPARING_2,
    DRINKING_PREPARING_3,
    DRINKING_DONE_DRINKING
};

float shadowOfAranSpawnPoints[8][2] = {
    { -11143.5f, -1914.26f },
    { -11152.1f, -1928.2f },
    { -11167.6f, -1933.8f },
    { -11181.3f, -1925.0f },
    { -11186.8f, -1909.7f },
    { -11178.0f, -1895.7f },
    { -11162.6f, -1895.4f },
    { -11148.6f, -1899.0f },
};

bool HasEquiped(Player* player, uint32 item)
{
    for (int i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; i++)
    {
        Item *pItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
        if (pItem && pItem->GetEntry() == item)
            return true;
    }

    return false;
}

struct boss_aranAI : public ScriptedAI
{
    boss_aranAI(Creature *creature) : ScriptedAI(creature)
    {
        Initialize();
        instance = creature->GetInstanceScript();
        creature->GetPosition(&pos);

        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CASTING_SPEED, true);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_SILENCE, true);
    }

    void Initialize()
    {
        SecondarySpellTimer = 5000;
        NormalCastTimer = 0;
        SuperCastTimer = 35000;
        BerserkTimer = 720000;
        CloseDoorTimer = 15000;

        LastSuperSpell = rand() % 3;

        CurrentNormalSpell = 0;
        ArcaneCooldown = 0;
        FireCooldown = 0;
        FrostCooldown = 0;
        PyroblastTimer = 0;
        CheckTimer = 3000;

        ElementalsSpawned = false;
        Drinking = DRINKING_NO_DRINKING;
        DrinkingDelay = 0;
    }

    ScriptedInstance* instance;

    uint32 SecondarySpellTimer;
    uint32 NormalCastTimer;
    uint32 SuperCastTimer;
    uint32 BerserkTimer;
    uint32 CloseDoorTimer;                                  // Don't close the door right on aggro in case some people are still entering.

    uint8 LastSuperSpell;

    uint32 CurrentNormalSpell;
    uint32 ArcaneCooldown;
    uint32 FireCooldown;
    uint32 FrostCooldown;
    uint32 CheckTimer;
    uint32 PyroblastTimer;

    bool ElementalsSpawned;
    DrinkingState Drinking;
    uint32 DrinkingDelay;

    Position pos;

    void Reset()
    {
        if (instance)
        {
            // Not in progress
            instance->SetData(TYPE_ARAN, NOT_STARTED);
            instance->HandleGameObject(instance->GetData64(DATA_GO_LIBRARY_DOOR), true);
        }
    }

    void KilledUnit(Unit * /*victim*/)
    {
        DoScriptText(RAND(SAY_KILL1, SAY_KILL2), me);
    }

    void JustDied(Unit * /*victim*/)
    {
        DoScriptText(SAY_DEATH, me);

        if (instance)
        {
            instance->SetData(TYPE_ARAN, DONE);
            instance->HandleGameObject(instance->GetData64(DATA_GO_LIBRARY_DOOR), true);
        }
    }

    bool PlayerHaveAtiesh()
    {
        Map::PlayerList const &PlayerList = ((InstanceMap*)me->GetMap())->GetPlayers();
        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
        {
            Player* i_pl = i->getSource();
            if (HasEquiped(i_pl, 22632) ||
                HasEquiped(i_pl, 22631) ||
                HasEquiped(i_pl, 22630) ||
                HasEquiped(i_pl, 22589))
                return true;
        }

        return false;
    }

    void EnterCombat(Unit * /*who*/)
    {
        if (PlayerHaveAtiesh())
            DoScriptText(SAY_ATIESH, me);
        else
            DoScriptText(RAND(SAY_AGGRO1, SAY_AGGRO2, SAY_AGGRO3), me);

        if (instance)
        {
            instance->SetData(TYPE_ARAN, IN_PROGRESS);
            instance->HandleGameObject(instance->GetData64(DATA_GO_LIBRARY_DOOR), false);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Check_Timer
        if (CheckTimer < diff)
        {
            if (me->IsWithinDist3d(&pos, 35.0f))
                EnterEvadeMode();
            else
                DoZoneInCombat();

            CheckTimer = 3000;
        }
        else
            CheckTimer -= diff;

        if (CloseDoorTimer)
        {
            if (CloseDoorTimer <= diff)
            {
                instance->HandleGameObject(instance->GetData64(DATA_GO_LIBRARY_DOOR), false);
                CloseDoorTimer = 0;
            }
            else CloseDoorTimer -= diff;
        }

        //Cooldowns for casts
        if (ArcaneCooldown)
        {
            if (ArcaneCooldown >= diff)
                ArcaneCooldown -= diff;
            else ArcaneCooldown = 0;
        }

        if (FireCooldown)
        {
            if (FireCooldown >= diff)
                FireCooldown -= diff;
            else FireCooldown = 0;
        }

        if (FrostCooldown)
        {
            if (FrostCooldown >= diff)
                FrostCooldown -= diff;
            else FrostCooldown = 0;
        }

        if (DrinkingDelay)
        {
            if (DrinkingDelay <= diff)
                DrinkingDelay = 0;
            else
                DrinkingDelay -= diff;
        }

        if (!DrinkingDelay && Drinking == DRINKING_NO_DRINKING && (me->GetMaxPower(POWER_MANA) && (me->GetPower(POWER_MANA) * 100 / me->GetMaxPower(POWER_MANA)) < 20) && !me->IsNonMeleeSpellCasted(true))
        {
            DoScriptText(SAY_DRINK, me);
            DoCast(me, SPELL_MASS_POLY, true);
            Drinking = DRINKING_PREPARING;
        }

        if (Drinking == DRINKING_PREPARING && !me->IsNonMeleeSpellCasted(true))
        {
            DoCast(me, SPELL_CONJURE, false);
            Drinking = DRINKING_PREPARING_2;
        }

        if (Drinking == DRINKING_PREPARING_2 && !me->IsNonMeleeSpellCasted(true))
        {
            DoCast(me, SPELL_DRINKING, false);
            me->SetStandState(UNIT_STAND_STATE_SIT);
            Drinking = DRINKING_PREPARING_3;
        }

        if (Drinking == DRINKING_PREPARING_3 && !me->HasAura(SPELL_DRINKING, 0))
        {
            DoCast(me, SPELL_POTION, false);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            PyroblastTimer = 2000;
            Drinking = DRINKING_DONE_DRINKING;
        }

        if (PyroblastTimer)
        {
            if (PyroblastTimer <= diff)
            {
                DoCast(me, SPELL_AOE_PYROBLAST, false);
                Drinking = DRINKING_NO_DRINKING;
                PyroblastTimer = 0;
            }
            else
                PyroblastTimer -= diff;
        }

        // Don't execute any more code if we are drinking
        if (Drinking)
            return;

        if (Drinking = DRINKING_NO_DRINKING)
        {
            // Normal casts
            if (NormalCastTimer <= diff)
            {
                if (!me->IsNonMeleeSpellCasted(false))
                {
                    Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
                    if (!pTarget)
                        return;

                    uint32 Spells[3];
                    uint8 AvailableSpells = 0;

                    //Check for what spells are not on cooldown
                    if (!ArcaneCooldown)
                        Spells[AvailableSpells++] = SPELL_ARCMISSLE;

                    if (!FireCooldown)
                        Spells[AvailableSpells++] = SPELL_FIREBALL;

                    if (!FrostCooldown)
                        Spells[AvailableSpells] = SPELL_FROSTBOLT;

                    // If no available spells wait 1 second and try again
                    if (AvailableSpells)
                        DoCast(pTarget, Spells[rand() % AvailableSpells]);
                }
                NormalCastTimer = 1000;
            }
            else NormalCastTimer -= diff;

            if (SecondarySpellTimer <= diff)
            {
                DoCast(me, SPELL_AOE_CS);
                SecondarySpellTimer = urand(10000, 40000);
            }
            else SecondarySpellTimer -= diff;

            if (SuperCastTimer <= diff)
            {
                uint8 Available[2];

                switch (LastSuperSpell)
                {
                    case SUPER_AE:
                        Available[0] = SUPER_FLAME;
                        Available[1] = SUPER_BLIZZARD;
                        break;
                    case SUPER_FLAME:
                        Available[0] = SUPER_AE;
                        Available[1] = SUPER_BLIZZARD;
                        break;
                    case SUPER_BLIZZARD:
                        Available[0] = SUPER_FLAME;
                        Available[1] = SUPER_AE;
                        break;
                    default:
                        Available[0] = 0;
                        Available[1] = 0;
                        break;
                }

                LastSuperSpell = Available[urand(0, 1)];

                switch (LastSuperSpell)
                {
                    case SUPER_AE:
                        DoScriptText(RAND(SAY_EXPLOSION1, SAY_EXPLOSION2), me);

                        DoCast(me, SPELL_TELEPORT_MIDDLE, true);
                        DoCast(me, SPELL_MAGNETIC_PULL, true);
                        DoCast(me, SPELL_MASSSLOW, true);
                        DoCast(me, SPELL_AEXPLOSION, false);
                        DrinkingDelay = 15000;
                        break;

                    case SUPER_FLAME:
                        DoScriptText(RAND(SAY_FLAMEWREATH1, SAY_FLAMEWREATH2), me);
                        DrinkingDelay = 25000;
                        break;

                    case SUPER_BLIZZARD:
                        DoScriptText(RAND(SAY_BLIZZARD1, SAY_BLIZZARD2), me);
                        DrinkingDelay = 30000;
                        break;
                }

                SuperCastTimer = urand(35000, 40000);
            }
            else SuperCastTimer -= diff;

            if (!ElementalsSpawned && HealthBelowPct(40))
            {
                ElementalsSpawned = true;

                DoCast(me, SPELL_TELEPORT_MIDDLE, true);
                DoCast(me, SPELL_MAGNETIC_PULL, true);
                DoCast(me, SPELL_ELEMENTAL1, true);
                DoCast(me, SPELL_ELEMENTAL2, true);
                DoCast(me, SPELL_ELEMENTAL3, true);
                DoCast(me, SPELL_ELEMENTAL4, true);

                DoScriptText(SAY_ELEMENTALS, me);
            }
        }
        
        if (BerserkTimer <= diff)
        {
            for (uint32 i = 0; i < 8; ++i)
            {
                if (Creature* unit = me->SummonCreature(CREATURE_SHADOW_OF_ARAN, shadowOfAranSpawnPoints[i][0], shadowOfAranSpawnPoints[i][1], me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
                {
                    unit->Attack(me->getVictim(), true);
                    unit->setFaction(me->getFaction());
                }
            }

            DoScriptText(SAY_TIMEOVER, me);

            BerserkTimer = 60000;
        }
        else BerserkTimer -= diff;

        if (ArcaneCooldown && FireCooldown && FrostCooldown)
            DoMeleeAttackIfReady();
    }

    void SpellHitTarget(Unit* target, const SpellEntry* spell)
    {
        if (spell->Id == SPELL_MAGNETIC_PULL)
        {
            target->RemoveAurasDueToSpell(SPELL_FLAME_WREATH_AURA);
            target->CastSpell(target, SPELL_BLINK_CENTER, true);
        }
        else if (spell->Id == SPELL_FROSTBOLT && roll_chance_i(33))
        {
            me->CastSpell(target, SPELL_CHAINSOFICE, true);
        }
    }

    void JustSummoned(Creature* summon)
    {
        if (summon->GetEntry() == 17167)
        {
            summon->AI()->AttackStart(me->getVictim());
            summon->setFaction(me->getFaction());
        }
    }

    void SpellHit(Unit* /*pAttacker*/, const SpellEntry* Spell)
    {
        // We only care about inturrupt effects and only if they are durring a spell currently being casted
        if ((Spell->Effect[0] != SPELL_EFFECT_INTERRUPT_CAST &&
            Spell->Effect[1] != SPELL_EFFECT_INTERRUPT_CAST &&
            Spell->Effect[2] != SPELL_EFFECT_INTERRUPT_CAST) || !me->IsNonMeleeSpellCasted(false))
            return;

        // Inturrupt effect
        me->InterruptNonMeleeSpells(false);

        // Normally we would set the cooldown equal to the spell duration
        // but we do not have access to the DurationStore

        switch (CurrentNormalSpell)
        {
            case SPELL_ARCMISSLE: ArcaneCooldown = 5000; break;
            case SPELL_FIREBALL: FireCooldown = 5000; break;
            case SPELL_FROSTBOLT: FrostCooldown = 5000; break;
        }
    }
};

struct water_elementalAI : public ScriptedAI
{
    water_elementalAI(Creature *creature) : ScriptedAI(creature)
    {
        Initialize();
    }

    void Initialize()
    {
        CastTimer = 2000 + (rand32() % 3000);
    }

    uint32 CastTimer;

    void Reset()
    {
        Initialize();
    }

    void EnterCombat(Unit* /*who*/) {}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (CastTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_WATERBOLT);
            CastTimer = urand(2000, 5000);
        }
        else CastTimer -= diff;
    }
};

struct shadow_of_aranAI : public ScriptedAI
{
    shadow_of_aranAI(Creature *creature) : ScriptedAI(creature)
    {
        Initialize();
    }

    void Initialize()
    {
        CastTimer = 2000 + (rand32() % 3000);
    }

    uint32 CastTimer;

    void Reset()
    {
        Initialize();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (CastTimer < diff)
        {
            if (rand() % 3)
            {
                DoCast(me, SPELL_FROSTBOLT_VOLLEY);
                CastTimer = 5000;
            }
            else
            {
                DoCast(me, SPELL_AMISSILE_VOLLEY);
                CastTimer = 20000;
            }
        }
        else
            CastTimer -= diff;
    }
};

struct circular_blizzardAI : public ScriptedAI
{
    circular_blizzardAI(Creature *creature) : ScriptedAI(creature)
    {
        Initialize();
        instance = creature->GetInstanceScript();
    }

    void Initialize()
    {
        move = false;
        currentWaypoint = 0;
        waypointTimer = 0;
        SetBlizzardWaypoints();
    }

    uint16 currentWaypoint;
    uint16 waypointTimer;
    Position pos;
    ScriptedInstance *instance;
    float blizzardWaypoints[2][8];
    bool move;

    void Reset()
    {
        Initialize();
    }

    void ChangeBlizzardWaypointsOrder(uint16 change)
    {
        float temp[2] = { 0, 0 };
        for (int16 i = 0; i < change; i++)
        {
            temp[0] = blizzardWaypoints[0][0];
            temp[1] = blizzardWaypoints[1][0];
            for (int16 j = 0; j < 7; j++)
            {
                blizzardWaypoints[0][j] = blizzardWaypoints[0][j + 1];
                blizzardWaypoints[1][j] = blizzardWaypoints[1][j + 1];
            }
            blizzardWaypoints[0][7] = temp[0];
            blizzardWaypoints[1][7] = temp[1];
        }
    }


    void SetBlizzardWaypoints()
    {
        blizzardWaypoints[0][0] = -11154.3;    blizzardWaypoints[1][0] = -1903.3;
        blizzardWaypoints[0][1] = -11163.6;    blizzardWaypoints[1][1] = -1898.7;
        blizzardWaypoints[0][2] = -11173.6;    blizzardWaypoints[1][2] = -1901.2;
        blizzardWaypoints[0][3] = -11178.1;    blizzardWaypoints[1][3] = -1910.4;
        blizzardWaypoints[0][4] = -11175.4;    blizzardWaypoints[1][4] = -1920.6;
        blizzardWaypoints[0][5] = -11166.6;    blizzardWaypoints[1][5] = -1925.1;
        blizzardWaypoints[0][6] = -11156.5;    blizzardWaypoints[1][6] = -1922.8;
        blizzardWaypoints[0][7] = -11151.8;    blizzardWaypoints[1][7] = -1913.5;
    }

    void SpellHit(Unit * caster, const SpellEntry * spell)
    {
        if (spell->Id == SPELL_SUMMON_BLIZZARD)
        {
            uint64 AranGUID = 0;
            if (instance)
                AranGUID = instance->GetData64(DATA_SHADE_OF_ARAN);
            me->CastSpell(me, SPELL_CIRCULAR_BLIZZARD, false, 0, 0, AranGUID);

            ChangeBlizzardWaypointsOrder(urand(0, 7));

            pos.m_positionX = blizzardWaypoints[0][0];
            pos.m_positionY = blizzardWaypoints[1][0];
            pos.m_positionZ = me->GetPositionZ();

            DoTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ());

            currentWaypoint = 0;
            waypointTimer = 0;
            move = true;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!move)
            return;

        if (waypointTimer < diff)
        {
            if (currentWaypoint < 7)
                ++currentWaypoint;
            else
            {
                currentWaypoint = 0;
                move = false;
            }

            pos.m_positionX = blizzardWaypoints[0][currentWaypoint];
            pos.m_positionY = blizzardWaypoints[1][currentWaypoint];

            me->GetMotionMaster()->MovePoint(currentWaypoint, pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ());
            waypointTimer = 3000;
        }
        else
            waypointTimer -= diff;
    }
};


CreatureAI* GetAI_boss_aran(Creature* creature)
{
    return new boss_aranAI (creature);
}

CreatureAI* GetAI_shadow_of_aran(Creature* creature)
{
    return new shadow_of_aranAI (creature);
}

CreatureAI* GetAI_water_elemental(Creature* creature)
{
    return new water_elementalAI (creature);
}

void AddSC_boss_shade_of_aran()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_shade_of_aran";
    newscript->GetAI = &GetAI_boss_aran;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_shadow_of_aran";
    newscript->GetAI = &GetAI_shadow_of_aran;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_aran_elemental";
    newscript->GetAI = &GetAI_water_elemental;
    newscript->RegisterSelf();
}

