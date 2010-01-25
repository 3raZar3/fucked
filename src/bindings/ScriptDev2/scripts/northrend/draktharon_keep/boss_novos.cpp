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
SDName: Boss_Novos
SD%Complete: 80%
SDAuthor: Aramil
SDComment: Incorect changing Phase. Change to second phase after 4th spawn of special NPC.
SDCategory: Drak'Tharon Keep
EndScriptData */

#include "precompiled.h"
#include "instance_draktharon_keep.h"

enum
{
    SAY_AGGRO                               = -1600005,
    SAY_DEATH                               = -1600006,
    SAY_KILL                                = -1600007,
    SAY_ADDS                                = -1600008,
    SAY_BUBBLE_1                            = -1600009,
    SAY_BUBBLE_2                            = -1600010,

    EMOTE_ASSISTANCE                        = -1600011,
    
    // spells
    SPELL_FIELD                             = 47346,
    
    // normal
    SPELL_FROSTBOLT                         = 49037,
    SPELL_MISERY                            = 50089,
    SPELL_ARCANE                            = 49198,
    SPELL_BLIZZARD                          = 49034,
    // heroic
    SPELL_FROSTBOLT_H                       = 59855,
    SPELL_MISERY_H                          = 59856,
    SPELL_ARCANE_H                          = 59909,
    SPELL_BLIZZARD_H                        = 59854,
    SPELL_SUMMON                            = 59910,

    SPELL_SUMMON_RISEN_SHADOWCASTER         = 49105,
    SPELL_SUMMON_SUMMON_FETID_TROLL_CORPSE  = 49103,
    SPELL_SUMMON_HULKING_CORPSE             = 49104,
    SPELL_SUMMON_CRISTAL_HANDLER            = 49179,

    // not used
    SPELL_DESPAWN_CRYSTAL_HANDLERS          = 51403
};

/*######
## boss_novos
######*/

struct MANGOS_DLL_DECL boss_novosAI : public ScriptedAI
{
    boss_novosAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
        bInitialized = false;
    }

    ScriptedInstance* m_pInstance;
    
    bool m_bIsRegularMode;
    bool bInitialized;

    uint8  Phase;
    uint32 m_uiFrostbolt_Timer;
    uint32 m_uiMisery_Timer;
    uint32 m_uiArcane_Timer;
    uint32 m_uiBlizzard_Timer;

    void Reset()
    {
        Phase = 1;
        m_uiFrostbolt_Timer = 5000;
        m_uiMisery_Timer = 10000;
        m_uiArcane_Timer = 25000;
        m_uiBlizzard_Timer = 30000;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_NOVOS, NOT_STARTED);
        m_pInstance->SetData(TYPE_CRYSTAL_EVENT, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
        DoCast(m_creature, SPELL_FIELD, false);

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_NOVOS, IN_PROGRESS);
        m_pInstance->SetData(TYPE_CRYSTAL_EVENT, IN_PROGRESS);
        Phase = 1;
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_KILL, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (!m_pInstance)
            return;

        m_pInstance->SetData(TYPE_NOVOS, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(Phase == 1)
        {
            // phase 1
            if (m_pInstance->GetData(TYPE_CRYSTAL_EVENT) == DONE)
            {
                m_creature->InterruptNonMeleeSpells(false);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                Phase = 2;
            }

        }
        else
        {
            // phase 2
            Unit* target = SelectUnit(SELECT_TARGET_RANDOM, 1);
            if(!target)
                target = m_creature->getVictim();
                
            if (m_uiFrostbolt_Timer <= uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_FROSTBOLT : SPELL_FROSTBOLT_H);
                m_uiFrostbolt_Timer = urand(5000, 15000);
            }else m_uiFrostbolt_Timer -= uiDiff;
            
            if (m_uiMisery_Timer <= uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_MISERY : SPELL_MISERY_H);
                m_uiMisery_Timer = urand(15000, 35000);
            }else m_uiMisery_Timer -= uiDiff;
            
            if (m_uiArcane_Timer <= uiDiff)
            {
                DoCast(m_creature->getVictim(), m_bIsRegularMode ? SPELL_ARCANE : SPELL_ARCANE_H);
                m_uiArcane_Timer = urand(5000, 20000);
            }else m_uiArcane_Timer -= uiDiff;
            
            if (m_uiBlizzard_Timer <= uiDiff)
            {
                DoCast(target, m_bIsRegularMode ? SPELL_ARCANE : SPELL_ARCANE_H);
                m_uiBlizzard_Timer = urand(25000, 35000);
            }else m_uiBlizzard_Timer -= uiDiff;
            
            // has to be handled in core first
            /*if(!m_bIsRegularMode && m_uiSummon_H_Timer <= uiDiff)
            {
                DoCast(m_creature, SPELL_SUMMON);
                m_uiSummon_H_Timer = urand(30000, 35000);
            }else m_uiSummon_H_Timer -= uiDiff;*/
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_novos(Creature* pCreature)
{
    return new boss_novosAI(pCreature);
}

struct MANGOS_DLL_DECL npc_novos_summon_targetAI : public ScriptedAI
{
    npc_novos_summon_targetAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    std::list<Creature*>lSummonsList;

    uint32 m_uiSummon_Timer;
    uint32 m_uiSpecial_Summon_Timer;

    void Reset() 
    {
        m_uiSummon_Timer = 5000;
        m_uiSpecial_Summon_Timer = 30000;
    }

    void CleanupAdds()
    {
        // despawn all summons
        if (!lSummonsList.empty())
        {
            for (std::list<Creature*>::iterator itr = lSummonsList.begin(); itr != lSummonsList.end(); ++itr)
                // do not remove isAlive() check! those are summoned by spell and are corepse despawns after certain amount of time
                if ((*itr) && (*itr)->isAlive())
                    (*itr)->ForcedDespawn();
        }
        lSummonsList.clear();
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (!pSummoned)
            return;

        lSummonsList.push_back(pSummoned);

        Creature* pNovos = (Creature*)Unit::GetUnit((*m_creature), m_pInstance->GetData64(DATA_NOVOS));
        if (!pNovos || !pNovos->isAlive() || !pNovos->getVictim())
            return;

        ThreatList const& lThreatList = pNovos->getThreatManager().getThreatList();
        if (lThreatList.empty())
            return;

        ThreatList::const_iterator itr = lThreatList.begin();
        advance(itr, (rand()% (lThreatList.size())));

        if (Unit* pTarget = Unit::GetUnit((*m_creature),(*itr)->getUnitGuid()))
            if (pSummoned->AI() && pTarget->isInAccessablePlaceFor(pSummoned))
                pSummoned->AI()->AttackStart(pTarget);
    }

    void UpdateAI (const uint32 uiDiff)
    {
        // summon normal npc
        if (m_uiSummon_Timer <= uiDiff)
        {
            if (m_pInstance)
            {
                // cleanup mess event not on progress
                if (m_pInstance->GetData(TYPE_NOVOS) != IN_PROGRESS)
                    CleanupAdds();
                else
                {
                    // summon random summon
                    if (urand(0, 100) < 80)
                    {
                        switch(urand(0, 2))
                        {
                            case 0: DoCast(m_creature, SPELL_SUMMON_RISEN_SHADOWCASTER, false); break;
                            case 1: DoCast(m_creature, SPELL_SUMMON_SUMMON_FETID_TROLL_CORPSE, false); break;
                            case 2: DoCast(m_creature, SPELL_SUMMON_HULKING_CORPSE, false); break;
                        }
                    }
                    else if (m_pInstance->GetData(TYPE_CRYSTAL_EVENT) != DONE)
                    {
                        if (Creature* pNovos = (Creature*)Unit::GetUnit((*m_creature), m_pInstance->GetData64(DATA_NOVOS)))
                            DoScriptText(SAY_ADDS, pNovos);
                        DoCast(m_creature, SPELL_SUMMON_CRISTAL_HANDLER, false);
                    }
                }
            }
            m_uiSummon_Timer = urand(4000, 7000);
        }else m_uiSummon_Timer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_novos_summon_target(Creature* pCreature)
{
    return new npc_novos_summon_targetAI(pCreature);
}

void AddSC_boss_novos()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_novos";
    newscript->GetAI = &GetAI_boss_novos;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_novos_summon_target";
    newscript->GetAI = &GetAI_npc_novos_summon_target;
    newscript->RegisterSelf();
}
