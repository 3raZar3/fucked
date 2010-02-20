/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: Boss_Jedoga
SD%Complete: 95%
SDComment:
SDCategory: Ahn'kahet
SDAuthor: ScrappyDoo (c) Andeeria
EndScriptData */

/* ToDo
DB support for Voulounter -> nomevemnt Ai
*/

#include "precompiled.h"

enum Sounds
{
    SAY_AGGRO                           = -1619017,
    SAY_CALL_SACRIFICE_1                = -1619018,
    SAY_CALL_SACRIFICE_2                = -1619019,
    SAY_SACRIFICE_1                     = -1619020,
    SAY_SACRIFICE_2                     = -1619021,
    SAY_SLAY_1                          = -1619022,
    SAY_SLAY_2                          = -1619023,
    SAY_SLAY_3                          = -1619024,
    SAY_DEATH                           = -1619025,
    SAY_PREACHING_1                     = -1619026,
    SAY_PREACHING_2                     = -1619027,
    SAY_PREACHING_3                     = -1619028,
    SAY_PREACHING_4                     = -1619029,
    SAY_PREACHING_5                     = -1619030,

    SAY_VOLUNTEER_1                     = -1619031,         //said by the volunteer image
    SAY_VOLUNTEER_2                     = -1619032
};

enum Spells
{
    SPELL_CYCLONE_STRIKE                = 56855,
    SPELL_CYCLONE_STRIKE_H              = 60030,
    SPELL_LIGHTING_BOLT                 = 56891,
    SPELL_LIGHTING_BOLT_H               = 60032,
    SPELL_THUNDER_SHOCK                 = 56926,
    SPELL_THUNDER_SHOCK_H               = 60029,
    SPELL_GIFT                          = 56219,

    SPELL_SPHERE_VISUAL                 = 56102,
};

enum Creatures
{
    CREATURE_VOLUNTEER                  = 30385,
};

/*######
## boss_jedoga
######*/

struct MANGOS_DLL_DECL boss_jedogaAI : public ScriptedAI
{
    boss_jedogaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIsSacrifice;
    bool m_bHasTaunted;

    uint64 m_uiVolunteerGUID[30];
    uint32 m_uiCycloneTimer;
    uint32 m_uiBoltTimer;
    uint32 m_uiThunderTimer;
    uint32 m_uiNextSurificeTimer;
    uint32 m_uiSacrificeTimer;
    uint8  m_uiSacrificedGUID;

    void Reset()
    {
        m_bHasTaunted         = false;
        m_bIsSacrifice        = false;
        m_uiCycloneTimer      = 15000;
        m_uiBoltTimer         = 5000;
        m_uiThunderTimer      = 10000;
        m_uiNextSurificeTimer = 40000;
        m_uiSacrificedGUID    = 30;

        DespawnAdds();

        for(uint8 i=0; i<30; ++i)
            m_uiVolunteerGUID[i] = 0;

        if(m_creature->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

        if(m_creature->HasAura(SPELL_GIFT))
            m_creature->RemoveAurasDueToSpell(SPELL_GIFT);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
        SummonAdds();
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_SLAY_1, m_creature); break;
            case 1: DoScriptText(SAY_SLAY_2, m_creature); break;
            case 2: DoScriptText(SAY_SLAY_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DespawnAdds();
        DoScriptText(SAY_DEATH, m_creature);   
    }

    void DespawnAdds()
    {
        for(uint8 i=0; i<30; ++i)
        {
            Unit* cVolunteer = Unit::GetUnit(*m_creature, m_uiVolunteerGUID[i]);
            if(cVolunteer && cVolunteer->isAlive())
            {
                cVolunteer->setDeathState(JUST_DIED);
                cVolunteer->SetVisibility(VISIBILITY_OFF);
                cVolunteer->setFaction(35);
            }
        }
    }

    void SummonAdds()
    {
        for(uint8 i=0; i<15; ++i)
        {
            if(Creature* cVolunteer = m_creature->SummonCreature(CREATURE_VOLUNTEER, m_creature->GetPositionX()+urand(2,20), m_creature->GetPositionY()+urand(2,25), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000))
            {
                m_uiVolunteerGUID[i] = cVolunteer->GetGUID();
                cVolunteer->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                cVolunteer->CastSpell(m_creature, SPELL_SPHERE_VISUAL, true);
            }
        }

        for(uint8 i=15; i<30; ++i)
        {
            if(Creature* cVolunteer = m_creature->SummonCreature(CREATURE_VOLUNTEER, m_creature->GetPositionX()-urand(2,20), m_creature->GetPositionY()-urand(2,25), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 600000))
            {
                m_uiVolunteerGUID[i] = cVolunteer->GetGUID();
                cVolunteer->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                cVolunteer->CastSpell(m_creature, SPELL_SPHERE_VISUAL, true);
            }
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        //Intro Sounds
        if (!m_bHasTaunted && m_creature->IsWithinDistInMap(pWho, 60.0f))
        {
            switch(urand(0, 4))
            {
                case 0: DoScriptText(SAY_PREACHING_1, m_creature); break;
                case 1: DoScriptText(SAY_PREACHING_5, m_creature); break;
                case 2: DoScriptText(SAY_PREACHING_2, m_creature); break;
                case 3: DoScriptText(SAY_PREACHING_3, m_creature); break;
                case 4: DoScriptText(SAY_PREACHING_4, m_creature); break;
            }
            m_bHasTaunted = true;
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_bIsSacrifice)
        { 
            //Stop Moving When 'Flying'
            m_creature->StopMoving();
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();

            if(m_uiSacrificeTimer < uiDiff)
            {
                //If Sacrifice End Start attack party and go walk
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if(m_creature->getVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());

                //Chck for Volounter and cast buff
                Unit* cVolunteer = Unit::GetUnit(*m_creature, m_uiVolunteerGUID[m_uiSacrificedGUID]);
                if(cVolunteer && cVolunteer->isAlive())
                {
                    switch(urand(0, 1))
                    {
                        case 0: DoScriptText(SAY_SACRIFICE_1, m_creature); break;
                        case 1: DoScriptText(SAY_SACRIFICE_2, m_creature); break;
                    }

                    m_creature->CastSpell(m_creature, SPELL_GIFT, false);
                    cVolunteer->SetVisibility(VISIBILITY_OFF);
                    cVolunteer->setFaction(35);
                }

                m_bIsSacrifice = false;
            }else m_uiSacrificeTimer -= uiDiff;
            return;
        }

        if(m_uiNextSurificeTimer < uiDiff)
        {
            switch(urand(0, 1))
            {
                case 0: DoScriptText(SAY_CALL_SACRIFICE_1, m_creature); break;
                case 1: DoScriptText(SAY_CALL_SACRIFICE_2, m_creature); break;
            }

            m_creature->StopMoving();
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            
            m_uiSacrificedGUID = urand(0,29);
            Creature* pVolunteer = ((Creature*)Unit::GetUnit(*m_creature, m_uiVolunteerGUID[m_uiSacrificedGUID]));
            if(pVolunteer && pVolunteer->isAlive())
            {
                pVolunteer->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if(pVolunteer->HasAura(SPELL_SPHERE_VISUAL))
                {
                    pVolunteer->RemoveAurasDueToSpell(SPELL_SPHERE_VISUAL);
                    m_creature->GetMap()->CreatureRelocation(pVolunteer, m_creature->GetPositionX()+1, m_creature->GetPositionY()+1, m_creature->GetPositionZ(), m_creature->GetOrientation());
                }
            }

            m_bIsSacrifice = true;
            m_uiSacrificeTimer = 10000; // ?
            m_uiNextSurificeTimer = 40000;
        }else m_uiNextSurificeTimer -= uiDiff;

        if(m_uiCycloneTimer < uiDiff)
        {
            if(m_creature->getVictim())
                m_creature->CastSpell(m_creature->getVictim(), m_bIsRegularMode ? SPELL_CYCLONE_STRIKE : SPELL_CYCLONE_STRIKE_H , false);
            m_uiCycloneTimer = urand(10000,20000);
        }else m_uiCycloneTimer -= uiDiff;

        if(m_uiBoltTimer < uiDiff)
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                m_creature->CastSpell(target, m_bIsRegularMode ? SPELL_LIGHTING_BOLT : SPELL_LIGHTING_BOLT_H, true);
            m_uiBoltTimer = urand(3000,8000);
        }else m_uiBoltTimer -= uiDiff;

        if(m_uiThunderTimer < uiDiff)
        {
            if(Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0))
                m_creature->CastSpell(target, m_bIsRegularMode ? SPELL_THUNDER_SHOCK : SPELL_THUNDER_SHOCK_H , false);
            m_uiThunderTimer = urand(8000,16000);
        }else m_uiThunderTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jedoga(Creature* pCreature)
{
    return new boss_jedogaAI(pCreature);
}

struct MANGOS_DLL_DECL mob_volounteerAI : public Scripted_NoMovementAI
{
    mob_volounteerAI(Creature *c) : Scripted_NoMovementAI(c) { Reset(); }
 
    void Reset() {}

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_volounteer(Creature* pCreature)
{
    return new mob_volounteerAI(pCreature);
}

void AddSC_boss_jedoga()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_jedoga";
    newscript->GetAI = &GetAI_boss_jedoga;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_volounteer";
    newscript->GetAI = &GetAI_mob_volounteer;
    newscript->RegisterSelf();
}
